#include "CPlusPlusFixer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

void CPlusPlusFixer::processPath(path const& path) {
    AlbaLocalPathHandler const pathHandler(path);
    if (pathHandler.doesExist()) {
        if (pathHandler.isExistingDirectory()) {
            processDirectory(path);
        } else {
            processFile(path);
        }
    }
}

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
    m_currentTerms = getTermsFromFile(file);
    fixTerms();
    writeAllTerms(file, m_currentTerms);
}

void CPlusPlusFixer::fixTerms() {
    combinePrimitiveTypes();
    fixPostFixIncrementDecrement();
    fixConstReferenceOrder();
    fixCStyleStaticCast();
    fixNoConstPassByValue();
    fixCommentsPositionOfBraces();
}

void CPlusPlusFixer::fixPostFixIncrementDecrement() {
    fixPostFixIncrementDecrement("++");
    fixPostFixIncrementDecrement("--");
}

void CPlusPlusFixer::fixPostFixIncrementDecrement(string const& crementOperator) {
    fixPostFixIncrementDecrementInLine(crementOperator);
    fixPostFixIncrementDecrementInForLoop(crementOperator);
}

void CPlusPlusFixer::fixPostFixIncrementDecrementInLine(string const& crementOperator) {
    findTermsAndSwapAt({{M("{"), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt({{M("}"), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt({{M(";"), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt({{M(","), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt({{M(";"), M(TermType::Identifier), M(crementOperator), M(",")}}, 1, 2);
    findTermsAndSwapAt({{M(";"), M(TermType::Identifier), M(crementOperator), M(")")}}, 1, 2);
}

void CPlusPlusFixer::fixPostFixIncrementDecrementInForLoop(string const& crementOperator) {
    findTermsAndCheckForLoopAndSwapAt({{M(","), M(TermType::Identifier), M(crementOperator), M(")")}}, 1, 2);
    findTermsAndCheckForLoopAndSwapAt({{M(","), M(TermType::Identifier), M(crementOperator), M(",")}}, 1, 2);
}

void CPlusPlusFixer::fixConstReferenceOrder() {
    fixConstReferenceOrder(M(TermType::Identifier));
    fixConstReferenceOrder(M(TermType::PrimitiveType));
    fixConstReferenceOrder(M("auto"));
}

void CPlusPlusFixer::fixConstReferenceOrder(TermMatcher const& typeMatcher) {
    findTermsAndSwapAt({{M("{"), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt({{M("}"), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt({{M(";"), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt({{M("("), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt({{M(","), M("const"), typeMatcher, M("&")}}, 1, 2);
}

void CPlusPlusFixer::fixCStyleStaticCast() { fixCStyleStaticCast(M(TermType::PrimitiveType)); }

void CPlusPlusFixer::fixCStyleStaticCast(TermMatcher const& typeMatcher) {
    Patterns const searchPatterns{{M(TermType::Operator), M("("), typeMatcher, M(")"), M(MatcherType::NotAWhiteSpace)}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            if (m_currentTerms[hitIndexes[4]].getContent() != "=") {
                changeTerm(m_currentTerms[hitIndexes[1]], TermType::Aggregate, "static_cast<");
                changeTerm(m_currentTerms[hitIndexes[3]], TermType::Aggregate, ">(");
                cout << "Fixed file: [" << m_currentFile << "] converted to static_cast at: ["
                     << getLocatorString(m_currentTerms, hitIndexes[1]) << "]\n";
            }
        }
    }
}

void CPlusPlusFixer::fixNoConstPassByValue() {
    fixNoConstPassByValue(M(MatcherType::IdentifierAndNotAScreamingSnakeCase));
    fixNoConstPassByValue(M(TermType::PrimitiveType));
}

void CPlusPlusFixer::fixNoConstPassByValue(TermMatcher const& typeMatcher) {
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
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            m_currentTerms.insert(m_currentTerms.begin() + hitIndexes[2], Term(TermType::Identifier, "const "));
            cout << "Fixed file: [" << m_currentFile << "] added const at: ["
                 << getLocatorString(m_currentTerms, hitIndexes[2]) << "]\n";
        }
    }
}

void CPlusPlusFixer::fixCommentsPositionOfBraces() {
    Patterns const searchPatterns{{M(MatcherType::Comment), M("{")}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            std::swap(m_currentTerms[hitIndexes[0]], m_currentTerms[hitIndexes[1]]);
            Term const nextTermAfterComment = m_currentTerms[hitIndexes[1] + 1];
            if (!hasNewLine(nextTermAfterComment)) {
                m_currentTerms.insert(m_currentTerms.begin() + hitIndexes[1] + 1, Term(TermType::WhiteSpace, "\n"));
            }
            cout << "Fixed file: [" << m_currentFile << "] fixed comment position at: ["
                 << getLocatorString(m_currentTerms, hitIndexes[1]) << "]\n";
        }
    }
}

void CPlusPlusFixer::findTermsAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            std::swap(m_currentTerms[hitIndexes[index1]], m_currentTerms[hitIndexes[index2]]);
            cout << "Fixed file: [" << m_currentFile << "] swapped at: ["
                 << getLocatorString(m_currentTerms, hitIndexes[index1]) << "]\n";
        }
    }
}

void CPlusPlusFixer::findTermsAndCheckForLoopAndSwapAt(
    Patterns const& searchPatterns, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            Patterns const forLoopPatterns{{M("for"), M("(")}, {M(";")}, {M("{")}, {M("}")}};
            Indexes forLoopHitIndexes = searchBackwardsForPatterns(m_currentTerms, hitIndexes.front(), forLoopPatterns);
            if (forLoopHitIndexes.size() == 2 && m_currentTerms[forLoopHitIndexes[0]].getContent() == "for" &&
                m_currentTerms[forLoopHitIndexes[1]].getContent() == "(") {
                std::swap(m_currentTerms[hitIndexes[index1]], m_currentTerms[hitIndexes[index2]]);
                cout << "Fixed file: [" << m_currentFile << "] swapped at: ["
                     << getLocatorString(m_currentTerms, hitIndexes[index1]) << "]\n";
            }
        }
    }
}

void CPlusPlusFixer::combinePrimitiveTypes() {
    int termIndex = 0;
    bool isFound(true);
    Patterns const primitiveTypesPatterns{{M(TermType::PrimitiveType), M(TermType::PrimitiveType)}};
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, primitiveTypesPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.front();
            combineTermsInPlace(m_currentTerms, TermType::PrimitiveType, hitIndexes[0], hitIndexes[1]);
        }
    }
}

}  // namespace alba::CodeUtilities
