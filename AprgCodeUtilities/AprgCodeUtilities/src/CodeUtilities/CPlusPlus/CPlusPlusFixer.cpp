#include "CPlusPlusFixer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/CommonUtilities.hpp>
#include <Common/Debug/AlbaDebug.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <algorithm>
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

string CPlusPlusFixer::getCorrectedGTestName(string const& testName) {
    if (testName.find_first_of('_') != std::string::npos) {
        if (testName.substr(0, std::min(static_cast<int>(testName.length()), 9)) == "DISABLED_") {
            string withoutUnderscore = testName.substr(9);
            replaceAllAndReturnIfFound(withoutUnderscore, "_", "");
            return string("DISABLED_") + withoutUnderscore;
        }
        string withoutUnderscore = testName;
        replaceAllAndReturnIfFound(withoutUnderscore, "_", "");
        return withoutUnderscore;
    }
    return testName;
}

void CPlusPlusFixer::fixTerms() {
    combinePrimitiveTypes();
    fixRegardlessWithScopes();
    fixBasedOnScopes();
}

void CPlusPlusFixer::fixRegardlessWithScopes() {
    fixPostFixIncrementDecrement();
    fixConstReferenceOrder();
    fixConstToConstexpr();
    fixNoConstPassByValue();
    fixNoExceptOnMoveConstructor();
    fixNoExceptOnMoveAssignment();
    fixGTestNames();
    fixCStylePrintf();
    fixCommentsPositionOfBraces();
    fixCStyleStaticCast();
}

void CPlusPlusFixer::fixBasedOnScopes() { fixByCheckingScopes(); }

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

void CPlusPlusFixer::fixNoExceptOnMoveConstructor() {
    Patterns const searchPatterns{
        {M(TermType::Identifier), M("("), M(TermType::Identifier), M("&&"), M(")"),
         M(SpecialMatcherType::NotACommentNorWhiteSpace)},
        {M(TermType::Identifier), M("("), M(TermType::Identifier), M("&&"), M(TermType::Identifier), M(")"),
         M(SpecialMatcherType::NotACommentNorWhiteSpace)}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            if (m_terms[hitIndexes[0]] == m_terms[hitIndexes[2]]) {
                if (m_terms[hitIndexes[4]].getContent() == ")") {
                    if (m_terms[hitIndexes[5]].getContent() != "noexcept") {
                        changeTerm(m_terms[hitIndexes[4]], TermType::Aggregate, ") noexcept ");
                        cout << "Fixed file: [" << m_currentFile << "]\n";
                        cout << "Fixed noexcept at: [" << getLocatorString(hitIndexes[4], m_terms) << "]\n";
                    }
                } else if (m_terms[hitIndexes[5]].getContent() == ")") {
                    if (m_terms[hitIndexes[6]].getContent() != "noexcept") {
                        changeTerm(m_terms[hitIndexes[5]], TermType::Aggregate, ") noexcept ");
                        cout << "Fixed file: [" << m_currentFile << "]\n";
                        cout << "Fixed noexcept at: [" << getLocatorString(hitIndexes[5], m_terms) << "]\n";
                    }
                }
            }
            termIndex = hitIndexes.back();
        }
    }
}

void CPlusPlusFixer::fixNoExceptOnMoveAssignment() {
    Patterns const searchPatterns{
        {M(TermType::Identifier), M("&"), M("operator"), M("="), M("("), M(TermType::Identifier), M("&&"), M(")"),
         M(SpecialMatcherType::NotACommentNorWhiteSpace)},
        {M(TermType::Identifier), M("&"), M("operator"), M("="), M("("), M(TermType::Identifier), M("&&"),
         M(TermType::Identifier), M(")"), M(SpecialMatcherType::NotACommentNorWhiteSpace)}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            if (m_terms[hitIndexes[0]] == m_terms[hitIndexes[5]]) {
                if (m_terms[hitIndexes[7]].getContent() == ")") {
                    if (m_terms[hitIndexes[8]].getContent() != "noexcept") {
                        changeTerm(m_terms[hitIndexes[7]], TermType::Aggregate, ") noexcept ");
                        cout << "Fixed file: [" << m_currentFile << "]\n";
                        cout << "Fixed noexcept at: [" << getLocatorString(hitIndexes[7], m_terms) << "]\n";
                    }
                } else if (m_terms[hitIndexes[8]].getContent() == ")") {
                    if (m_terms[hitIndexes[9]].getContent() != "noexcept") {
                        changeTerm(m_terms[hitIndexes[8]], TermType::Aggregate, ") noexcept ");
                        cout << "Fixed file: [" << m_currentFile << "]\n";
                        cout << "Fixed noexcept at: [" << getLocatorString(hitIndexes[8], m_terms) << "]\n";
                    }
                }
            }
            termIndex = hitIndexes.back();
        }
    }
}

void CPlusPlusFixer::fixGTestNames() {
    Patterns const searchPatterns{
        {M_OR(M("TEST"), M("TEST_F")), M("("), M(TermType::Identifier), M(","), M(TermType::Identifier), M(")")}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            string testSuiteName(getCorrectedGTestName(m_terms[hitIndexes[2]].getContent()));
            string testName(getCorrectedGTestName(m_terms[hitIndexes[4]].getContent()));
            m_terms[hitIndexes[2]].setContent(testSuiteName);
            m_terms[hitIndexes[4]].setContent(testName);
            termIndex = hitIndexes.back();
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
    Patterns const searchPatterns{
        {M(TermType::Operator), M("("), typeMatcher, M(")"), M(SpecialMatcherType::NotACommentNorWhiteSpace)}};
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

void CPlusPlusFixer::fixByCheckingScopes() {
    enterAndSetTopLevelScope();

    Patterns const searchPatterns{{M("{")}, {M("}")}};
    int nextIndex = 0;
    int searchIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(searchIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            Term const& firstTerm(m_terms[firstHitIndex]);
            int fixStartIndex = nextIndex > 0 ? nextIndex - 1 : nextIndex;
            if (firstTerm.getContent() == "{") {
                fixOnScopeLoop(fixStartIndex, firstHitIndex);
                processOpeningBrace(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            } else if (firstTerm.getContent() == "}") {
                fixOnScopeLoop(fixStartIndex, firstHitIndex);
                processClosingBrace(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            }
        }
    }
    fixOnScopeLoop(nextIndex, static_cast<int>(m_terms.size()) - 1);

    exitTopLevelScope();
}

void CPlusPlusFixer::processOpeningBrace(int& nextIndex, int const openingBraceIndex) {
    enterScope(nextIndex, openingBraceIndex);
    nextIndex = openingBraceIndex + 1;
}

void CPlusPlusFixer::processClosingBrace(int& nextIndex, int const closingBraceIndex) {
    exitScope();
    nextIndex = closingBraceIndex + 1;
}

void CPlusPlusFixer::enterAndSetTopLevelScope() { m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel}}; }

void CPlusPlusFixer::exitTopLevelScope() { m_scopeDetails.pop_back(); }

void CPlusPlusFixer::enterScope(int const scopeHeaderStart, int const openingBraceIndex) {
    m_scopeDetails.emplace_back(constructScopeDetails(scopeHeaderStart, openingBraceIndex));
}

void CPlusPlusFixer::exitScope() { m_scopeDetails.pop_back(); }

void CPlusPlusFixer::fixOnScopeLoop(int const startIndex, int const endIndex) {
    fixConstexprToInlineConstExpr(startIndex, endIndex);
}

void CPlusPlusFixer::fixConstexprToInlineConstExpr(int const startIndex, int const endIndex) {
    if (ScopeType::NamedNamespace == m_scopeDetails.back().scopeType &&
        isHeaderFileExtension(getStringWithoutCharAtTheStart(m_currentFile.extension().string(), '.'))) {
        auto const startDivider = M_OR(M("{"), M("}"), M(";"));
        Patterns const searchPatterns{{startDivider, M("constexpr")}};
        int nextIndex = startIndex;
        bool isFound(true);
        while (isFound) {
            Indexes hitIndexes = searchForwardsForPatterns(nextIndex, endIndex, m_terms, searchPatterns);
            isFound = !hitIndexes.empty();
            if (isFound) {
                int const lastHitIndex = hitIndexes.back();
                changeTerm(m_terms[lastHitIndex], TermType::Aggregate, "inline constexpr");
                cout << "Fixed file: [" << m_currentFile << "]\n";
                cout << "Fixed inline constexpr at: [" << getLocatorString(lastHitIndex, m_terms) << "]\n";
            }
        }
    }
}

CPlusPlusFixer::ScopeDetail CPlusPlusFixer::constructScopeDetails(
    int const scopeHeaderStart, int const openingBraceIndex) const {
    Terms scopeHeaderTerms(extractTermsInRange(scopeHeaderStart, openingBraceIndex, m_terms));
    ScopeDetail scopeDetail{scopeHeaderStart, openingBraceIndex, 0, ScopeType::Unknown};
    Patterns const searchPatterns{
        {M("template"), M("<")},
        {M("namespace"), M(TermType::Identifier)},
        {M("namespace"), M("{")},
        {M("enum"), M("class"), M(TermType::Identifier)},
        {M("class"), M(TermType::Identifier)},
        {M("struct"), M(TermType::Identifier)},
        {M("union"), M(TermType::Identifier)}};
    int nextIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(nextIndex, scopeHeaderTerms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            int const lastHitIndex = hitIndexes.back();
            Term const& firstTerm(scopeHeaderTerms[firstHitIndex]);
            Term const& lastTerm(scopeHeaderTerms[lastHitIndex]);
            if (firstTerm.getContent() == "namespace" && lastTerm.getTermType() == TermType::Identifier) {
                scopeDetail.scopeType = ScopeType::NamedNamespace;
                break;
            }
            if (firstTerm.getContent() == "namespace" && lastTerm.getContent() == "{") {
                scopeDetail.scopeType = ScopeType::AnonymousNamespace;
                break;
            }
            if (firstTerm.getContent() == "enum" && scopeHeaderTerms[hitIndexes[1]].getContent() == "class" &&
                lastTerm.getTermType() == TermType::Identifier) {
                scopeDetail.scopeType = ScopeType::EnumClass;
                break;
            }
            if ((firstTerm.getContent() == "class" || firstTerm.getContent() == "struct" ||
                 firstTerm.getContent() == "union") &&
                lastTerm.getTermType() == TermType::Identifier) {
                scopeDetail.scopeType = ScopeType::ClassDeclaration;
                break;
            }
            if (firstTerm.getContent() == "template" && lastTerm.getContent() == "<") {
                nextIndex = getIndexAtClosingString(scopeHeaderTerms, lastHitIndex, "<", ">");
            } else {
                nextIndex = lastHitIndex + 1;
            }
        }
    }
    return scopeDetail;
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
