#include "CPlusPlusFixer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/CommonUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

void CPlusPlusFixer::processDirectory(path const& directory) {
    AlbaLocalPathHandler const directoryPathHandler(directory);
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (isCppFileExtension(filePathHandler.getExtension().string())) {
                processFile(filePathHandler.getPath());
            }
        });
}

void CPlusPlusFixer::processFile(path const& file) {
    m_currentFile = file;
    m_terms = getTermsFromFile(file);
    fixTerms();
    writeAllTerms(file, m_terms);
}

strings CPlusPlusFixer::getPrintItems(int& printfEnd, int const printStringIndex) const {
    strings printItems;
    int parenthesisLevel = 1;
    int printItemStart = printStringIndex + 1;
    for (int termIndex = printStringIndex + 1; termIndex < static_cast<int>(m_terms.size()); ++termIndex) {
        if ("(" == m_terms[termIndex].getContent()) {
            ++parenthesisLevel;
        } else if (")" == m_terms[termIndex].getContent()) {
            --parenthesisLevel;
            if (parenthesisLevel == 0) {
                printfEnd = termIndex;
                break;
            }
        } else if (parenthesisLevel == 1 && "," == m_terms[termIndex].getContent()) {
            int printItemEnd = termIndex - 1;
            if (printItemStart < printItemEnd) {
                printItems.emplace_back(getCombinedContents(printItemStart, printItemEnd, m_terms));
            }
            printItemStart = termIndex + 1;
        }
    }
    int printItemEnd = printfEnd - 1;
    if (printItemStart < printItemEnd) {
        printItems.emplace_back(getCombinedContents(printItemStart, printItemEnd, m_terms));
    }
    return printItems;
}

void CPlusPlusFixer::fixTerms() {
    combinePrimitiveTypes();
    fixPostFixIncrementDecrement();
    fixConstReferenceOrder();
    fixConstToConstexpr();
    fixNoConstPassByValue();
    fixCStylePrintf();
    fixCommentsPositionOfBraces();
    fixCStyleStaticCast();
}

void CPlusPlusFixer::combinePrimitiveTypes() {
    int termIndex = 0;
    bool isFound(true);
    Patterns const primitiveTypesPatterns{{M(TermType::PrimitiveType), M(TermType::PrimitiveType)}};
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, primitiveTypesPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.front();
            combineTermsInPlace(m_terms, TermType::PrimitiveType, hitIndexes[0], hitIndexes[1]);
        }
    }
}

void CPlusPlusFixer::fixPostFixIncrementDecrement() {
    fixPostFixIncrementDecrementInLine();
    fixPostFixIncrementDecrementInForLoop();
}

void CPlusPlusFixer::fixPostFixIncrementDecrementInLine() {
    auto const startDivider = M_OR(M("{"), M("}"), M(";"), M(","));
    auto const crementOperator = M_OR(M("++"), M("--"));
    findTermsAndSwapAt({{startDivider, M(TermType::Identifier), crementOperator, M(";")}}, 1, 2);
    findTermsAndSwapAt({{M(";"), M(TermType::Identifier), crementOperator, M_OR(M(","), M(")"))}}, 1, 2);
}

void CPlusPlusFixer::fixPostFixIncrementDecrementInForLoop() {
    auto const crementOperator = M_OR(M("++"), M("--"));
    auto const endDivider = M_OR(M(","), M(")"));
    findTermsAndCheckForLoopAndSwapAt({{M(","), M(TermType::Identifier), crementOperator, endDivider}}, 1, 2);
}

void CPlusPlusFixer::fixConstReferenceOrder() {
    auto const startDivider = M_OR(M("{"), M("}"), M(";"), M("("), M(","));
    auto const typeMatcher = M_OR(M(TermType::Identifier), M(TermType::PrimitiveType), M("auto"));
    findTermsAndSwapAt({{startDivider, M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt({{startDivider, M("const"), typeMatcher, M(TermType::Identifier), M("=")}}, 1, 2);
    findTermsAndSwapAt({{startDivider, M("const"), typeMatcher, M("("), M(TermType::Identifier), M(")")}}, 1, 2);
}

void CPlusPlusFixer::fixConstToConstexpr() {
    auto const startDivider = M_OR(M("{"), M("}"), M(";"));
    findTermsAndConvertToConstexpr(
        {{startDivider, M(TermType::PrimitiveType), M("const"), M(TermType::Identifier), M("="),
          M(SpecialMatcherType::Literal), M(";")}},
        1, 2, 0, 0);
    findTermsAndConvertToConstexpr(
        {{startDivider, M(TermType::PrimitiveType), M("const"), M(TermType::Identifier), M("("),
          M(SpecialMatcherType::Literal), M(")"), M(";")}},
        1, 2, 4, 6);
    findTermsAndConvertToConstexpr(
        {{startDivider, M(TermType::PrimitiveType), M("const"), M(TermType::Identifier), M("{"),
          M(SpecialMatcherType::Literal), M("}"), M(";")}},
        1, 2, 4, 6);
}

void CPlusPlusFixer::fixNoConstPassByValue() {
    auto const typeMatcher =
        M_OR(M(SpecialMatcherType::IdentifierAndNotAScreamingSnakeCase), M(TermType::PrimitiveType));
    fixNoConstPassByValue({{M("("), typeMatcher, M(TermType::Identifier), M(")")}});
    fixNoConstPassByValue({{M("("), typeMatcher, M(TermType::Identifier), M(",")}});
    fixNoConstPassByValue({{M(","), typeMatcher, M(TermType::Identifier), M(",")}});
    fixNoConstPassByValue({{M(","), typeMatcher, M(TermType::Identifier), M(")")}});
    fixNoConstPassByValue({{M("::"), typeMatcher, M(TermType::Identifier), M(",")}});
    fixNoConstPassByValue({{M("::"), typeMatcher, M(TermType::Identifier), M(")")}});
}

void CPlusPlusFixer::fixNoConstPassByValue(Patterns const& searchPatterns) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            m_terms.insert(m_terms.begin() + hitIndexes[2], Term(TermType::Identifier, "const "));
            cout << "Fixed file: [" << m_currentFile << "]\n";
            cout << "Added const at: [" << getLocatorString(hitIndexes[2], m_terms) << "]\n";
        }
    }
}

void CPlusPlusFixer::fixCStylePrintf() { fixCStylePrintf({{M("printf"), M("("), M(TermType::StringLiteral)}}); }

void CPlusPlusFixer::fixCStylePrintf(Patterns const& searchPatterns) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            fixCStylePrintf(hitIndexes.front(), hitIndexes.back());
            termIndex = hitIndexes.front();
        }
    }
}

void CPlusPlusFixer::fixCStylePrintf(int const printfStart, int const printStringIndex) {
    string printString = m_terms[printStringIndex].getContent();
    int printfEnd{};
    strings printItems(getPrintItems(printfEnd, printStringIndex));
    Terms newPrintTerms(getNewPrintTerms(printString, printItems));

    m_terms.erase(m_terms.begin() + printfStart, m_terms.begin() + printfEnd + 1);
    m_terms.insert(m_terms.cbegin() + printfStart, newPrintTerms.cbegin(), newPrintTerms.cend());
    cout << "Fixed file: [" << m_currentFile << "]\n";
    cout << "Converted printf to C++ print at: [" << getLocatorString(printfStart, m_terms) << "]\n";
}

void CPlusPlusFixer::fixCommentsPositionOfBraces() {
    Patterns const searchPatterns{{M(SpecialMatcherType::Comment), M("{")}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            swap(m_terms[hitIndexes[0]], m_terms[hitIndexes[1]]);
            Term const nextTermAfterComment = m_terms[hitIndexes[1] + 1];
            if (!hasNewLine(nextTermAfterComment)) {
                m_terms.insert(m_terms.begin() + hitIndexes[1] + 1, Term(TermType::WhiteSpace, "\n"));
            }
            cout << "Fixed file: [" << m_currentFile << "]\n";
            cout << "Fixed comment position at: [" << getLocatorString(hitIndexes[1], m_terms) << "]\n";
        }
    }
}

void CPlusPlusFixer::fixCStyleStaticCast() { fixCStyleStaticCast(M(TermType::PrimitiveType)); }

void CPlusPlusFixer::fixCStyleStaticCast(Matcher const& typeMatcher) {
    Patterns const searchPatterns{{M(TermType::Operator), M("("), typeMatcher, M(")"), M_NOT(TermType::WhiteSpace)}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            if (m_terms[hitIndexes[4]].getContent() != "=") {
                changeTerm(m_terms[hitIndexes[1]], TermType::Aggregate, "static_cast<");
                changeTerm(m_terms[hitIndexes[3]], TermType::Aggregate, ">(");
                cout << "Fixed file: [" << m_currentFile << "]\n";
                cout << "Converted to static_cast at: [" << getLocatorString(hitIndexes[1], m_terms) << "]\n";
            }
        }
    }
}

void CPlusPlusFixer::findTermsAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            swap(m_terms[hitIndexes[index1]], m_terms[hitIndexes[index2]]);
            cout << "Fixed file: [" << m_currentFile << "]\n";
            cout << "Swapped at: [" << getLocatorString(hitIndexes[index1], m_terms) << "]\n";
        }
    }
}

void CPlusPlusFixer::findTermsAndCheckForLoopAndSwapAt(
    Patterns const& searchPatterns, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            Patterns const forLoopPatterns{
                {M("for"), M("(")}, {M(";"), M(SpecialMatcherType::WhiteSpaceWithNewLine)}, {M("{")}, {M("}")}};
            Indexes forLoopHitIndexes = searchBackwardsForPatterns(hitIndexes.front(), m_terms, forLoopPatterns);
            if (forLoopHitIndexes.size() == 2 && m_terms[forLoopHitIndexes[0]].getContent() == "for" &&
                m_terms[forLoopHitIndexes[1]].getContent() == "(") {
                swap(m_terms[hitIndexes[index1]], m_terms[hitIndexes[index2]]);
                cout << "Fixed file: [" << m_currentFile << "]\n";
                cout << "Swapped at: [" << getLocatorString(hitIndexes[index1], m_terms) << "]\n";
            }
        }
    }
}

void CPlusPlusFixer::findTermsAndConvertToConstexpr(
    Patterns const& searchPatterns, int const typeIndex, int const constIndex, int const openingParenthesisIndex,
    int const closingParenthesisIndex) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            m_terms[hitIndexes[constIndex]].setContent("constexpr");
            swap(m_terms[hitIndexes[typeIndex]], m_terms[hitIndexes[constIndex]]);
            if (m_terms[hitIndexes[openingParenthesisIndex]].getContent() == "(" &&
                m_terms[hitIndexes[closingParenthesisIndex]].getContent() == ")") {
                m_terms[hitIndexes[openingParenthesisIndex]].setContent("=");
                m_terms[hitIndexes[closingParenthesisIndex]].clear();
            }
            cout << "Fixed file: [" << m_currentFile << "]\n";
            cout << "Swapped at: [" << getLocatorString(hitIndexes[typeIndex], m_terms) << "]\n";
        }
    }
}

Terms CPlusPlusFixer::getNewPrintTerms(string const& printString, strings const& printItems) {
    Terms newPrintTerms{Term(TermType::Identifier, "cout")};
    string currentString;
    int printItemIndex = 0;
    bool isInString = true;
    for (char const character : printString) {
        if (isInString) {
            if (character == '%') {
                isInString = false;
                if (currentString != R"(")") {
                    currentString += R"(")";
                    newPrintTerms.emplace_back(TermType::Operator, "<<");
                    newPrintTerms.emplace_back(TermType::StringLiteral, currentString);
                }
                if (printItemIndex < static_cast<int>(printItems.size())) {
                    newPrintTerms.emplace_back(TermType::Operator, "<<");
                    newPrintTerms.emplace_back(TermType::Aggregate, printItems[printItemIndex++]);
                }
            } else {
                currentString += character;
            }
        } else {
            if (isLetter(character)) {
                isInString = true;
                currentString = R"(")";
            }
        }
    }
    if (currentString != R"(")") {
        newPrintTerms.emplace_back(TermType::Operator, "<<");
        newPrintTerms.emplace_back(TermType::StringLiteral, currentString);
    }
    for (; printItemIndex < static_cast<int>(printItems.size()); ++printItemIndex) {
        newPrintTerms.emplace_back(TermType::Operator, "<<");
        newPrintTerms.emplace_back(TermType::Aggregate, printItems[printItemIndex]);
    }
    return newPrintTerms;
}

}  // namespace alba::CodeUtilities
