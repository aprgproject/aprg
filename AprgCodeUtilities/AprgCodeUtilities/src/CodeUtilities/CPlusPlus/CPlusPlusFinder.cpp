#include "CPlusPlusFinder.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/CommonUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

void CPlusPlusFinder::processDirectory(path const& directory) {
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

void CPlusPlusFinder::processFile(path const& file) {
    m_currentFile = file;
    m_terms = getTermsFromFile(file);
    findTerms();
    writeAllTerms(file, m_terms);
}

CPlusPlusFinder::ScopeDetail CPlusPlusFinder::constructScopeDetails(
    int const scopeHeaderStart, int const openingBraceIndex) const {
    Terms scopeHeaderTerms(extractTermsInRange(scopeHeaderStart, openingBraceIndex, m_terms));
    ScopeDetail scopeDetail{scopeHeaderStart, openingBraceIndex, 0, ScopeType::Unknown, {}};
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
                scopeDetail.name = lastTerm.getContent();
                break;
            }
            if (firstTerm.getContent() == "namespace" && lastTerm.getContent() == "{") {
                scopeDetail.scopeType = ScopeType::AnonymousNamespace;
                scopeDetail.name.clear();
                break;
            }
            if (firstTerm.getContent() == "enum" && scopeHeaderTerms[hitIndexes[1]].getContent() == "class" &&
                lastTerm.getTermType() == TermType::Identifier) {
                scopeDetail.scopeType = ScopeType::EnumClass;
                scopeDetail.name = lastTerm.getContent();
                break;
            }
            if ((firstTerm.getContent() == "class" || firstTerm.getContent() == "struct" ||
                 firstTerm.getContent() == "union") &&
                lastTerm.getTermType() == TermType::Identifier) {
                scopeDetail.scopeType = ScopeType::ClassDeclaration;
                scopeDetail.name = lastTerm.getContent();
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

void CPlusPlusFinder::findTerms() {
    findRegardlessOfScope();
    findBasedOnScopes();
}

void CPlusPlusFinder::findRegardlessOfScope() {
    // findInitializationOutsideClass();
}

void CPlusPlusFinder::findBasedOnScopes() { findByCheckingScopes(); }

void CPlusPlusFinder::findInitializationOutsideClass() {
    Patterns const searchPatterns{
        {M(SpecialMatcherType::IdentifierStartsWithLetterUnderscore), M("("), M(SpecialMatcherType::Literal), M(")")}};
    int nextIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(nextIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            cout << "Found file: [" << m_currentFile << "]\n";
            cout << "Initialization outside class at: [" << getLocatorString(firstHitIndex, m_terms) << "]\n";
            nextIndex = hitIndexes.back() + 1;
        }
    }
}

void CPlusPlusFinder::findByCheckingScopes() {
    enterAndSetTopLevelScope();

    Patterns const searchPatterns{{M("{")}, {M("}")}, {M(";")}};
    int nextIndex = 0;
    int searchIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(searchIndex, m_terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            Term const& firstTerm(m_terms[firstHitIndex]);
            int findStartIndex = nextIndex > 0 ? nextIndex - 1 : nextIndex;
            findOnScopeLoop(findStartIndex, firstHitIndex);
            if (firstTerm.getContent() == "{") {
                processOpeningBrace(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            } else if (firstTerm.getContent() == "}") {
                processClosingBrace(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            } else {
                ++nextIndex;
                searchIndex = nextIndex;
            }
        }
    }
    findOnScopeLoop(nextIndex, static_cast<int>(m_terms.size()) - 1);

    exitTopLevelScope();
}

void CPlusPlusFinder::processOpeningBrace(int& nextIndex, int const openingBraceIndex) {
    enterScope(nextIndex, openingBraceIndex);
    nextIndex = openingBraceIndex + 1;
}

void CPlusPlusFinder::processClosingBrace(int& nextIndex, int const closingBraceIndex) {
    exitScope();
    nextIndex = closingBraceIndex + 1;
}

void CPlusPlusFinder::enterAndSetTopLevelScope() { m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}}}; }
void CPlusPlusFinder::exitTopLevelScope() { m_scopeDetails.pop_back(); }

void CPlusPlusFinder::enterScope(int const scopeHeaderStart, int const openingBraceIndex) {
    m_scopeDetails.emplace_back(constructScopeDetails(scopeHeaderStart, openingBraceIndex));
}

void CPlusPlusFinder::exitScope() { m_scopeDetails.pop_back(); }

void CPlusPlusFinder::findOnScopeLoop(int const startIndex, int const endIndex) {
    // findItemsToCtadFix(startIndex, endIndex);
}

void CPlusPlusFinder::findItemsToCtadFix(int const startIndex, int const endIndex) {
    if (ScopeType::ClassDeclaration == getCurrentScope().scopeType) {
        Patterns const searchPatterns{{M(getCurrentScope().name), M("<")}};
        int nextIndex = startIndex;
        bool isFound(true);
        while (isFound) {
            Indexes hitIndexes = searchForwardsForPatterns(nextIndex, endIndex, m_terms, searchPatterns);
            isFound = !hitIndexes.empty();
            if (isFound) {
                int const firstHitIndex = hitIndexes.front();
                cout << "Found file: [" << m_currentFile << "]\n";
                cout << "Possible CTAD fix at: [" << getLocatorString(firstHitIndex, m_terms) << "]\n";
                nextIndex = hitIndexes.back() + 1;
            }
        }
    }
}

CPlusPlusFinder::ScopeDetail& CPlusPlusFinder::getCurrentScope() { return m_scopeDetails.back(); }

}  // namespace alba::CodeUtilities
