#include "CPlusPlusReorganizer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizeItems.hpp>
#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

using namespace std;
using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

CPlusPlusReorganizer::CPlusPlusReorganizer() = default;

void CPlusPlusReorganizer::processHeaderAndImplementationFile(
    string const& headerFile, string const& implementationFile) {
    reorganizeFile(headerFile);
    gatherInformationFromFile(headerFile);
    reorganizeFile(implementationFile);
    m_headerInformation = {};
}

void CPlusPlusReorganizer::reorganizeFile(string const& file) {
    m_purpose = Purpose::Reorganize;
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}}};
    AlbaLocalPathHandler filePathHandler(file);
    m_terms = getTermsFromFile(filePathHandler.getFullPath());
    processTerms();
    writeAllTerms(filePathHandler.getFullPath(), m_terms);
}

void CPlusPlusReorganizer::gatherInformationFromFile(string const& file) {
    m_purpose = Purpose::GatherInformation;
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}}};
    AlbaLocalPathHandler filePathHandler(file);
    m_terms = getTermsFromFile(filePathHandler.getFullPath());
    processTerms();
}

void CPlusPlusReorganizer::processTerms() {
    Patterns searchPatterns{{M(TermType::Macro)},
                            {M(";")},
                            {M("{")},
                            {M("}"), M(";")},
                            {M("}")},
                            {M("public"), M(":")},
                            {M("protected"), M(":")},
                            {M("private"), M(":")}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(m_terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            if (m_terms[firstHitIndex].getTermType() == TermType::Macro) {
                processMacro(termIndex, firstHitIndex);
            } else if (m_terms[firstHitIndex].getContent() == ";") {
                processSemiColon(termIndex, firstHitIndex);
            } else if (m_terms[firstHitIndex].getContent() == "{") {
                processOpeningBrace(termIndex, firstHitIndex);
            } else if (m_terms[firstHitIndex].getContent() == "}") {
                processClosingBrace(termIndex, firstHitIndex, hitIndexes.back());
            } else {
                processRecognizedItem(termIndex, hitIndexes.back());
            }
        }
    }
}

void CPlusPlusReorganizer::processMacro(int& termIndex, int const macroStartIndex) {
    addItemIfNeeded(termIndex, macroStartIndex - 1);
    termIndex = macroStartIndex + 1;
    Patterns searchPatterns{{M(MatcherType::HasNewLine)}, {M("\\"), M(MatcherType::HasNewLine)}};
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(m_terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            termIndex = hitIndexes.back() + 1;
            if (m_terms[firstHitIndex] == M(MatcherType::HasNewLine)) {
                addItemIfNeeded(macroStartIndex, hitIndexes.back());
                break;
            }
        }
    }
}

void CPlusPlusReorganizer::processSemiColon(int& termIndex, int const semiColonIndex) {
    addItemIfNeeded(termIndex, semiColonIndex);
    termIndex = semiColonIndex + 1;
}

void CPlusPlusReorganizer::processOpeningBrace(int& termIndex, int const scopeHeaderDivider) {
    Patterns searchPatterns{{M("}"), M("{")}};
    int updatedDivider = scopeHeaderDivider;
    int afterOpeningBrace = scopeHeaderDivider + 1;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = checkPatternAt(m_terms, afterOpeningBrace, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            afterOpeningBrace = hitIndexes.back() + 1;
            updatedDivider = hitIndexes.back();
        }
    }
    enterScope(termIndex, updatedDivider);
    termIndex = updatedDivider + 1;
}

void CPlusPlusReorganizer::processClosingBrace(int& termIndex, int const scopeEndFirst, int const scopeEndSecond) {
    addItemIfNeeded(termIndex, scopeEndFirst - 1);
    exitScope(termIndex, scopeEndFirst, scopeEndSecond);
}

void CPlusPlusReorganizer::processRecognizedItem(int& termIndex, int const recognizedItemEndIndex) {
    addItemIfNeeded(termIndex, recognizedItemEndIndex);
    termIndex = recognizedItemEndIndex + 1;
}

void CPlusPlusReorganizer::enterScope(int const scopeHeaderStart, int const scopeHeaderDivider) {
    m_scopeDetails.emplace_back(constructScopeDetails(scopeHeaderStart, scopeHeaderDivider));
}

void CPlusPlusReorganizer::exitScope(int& termIndex, int const scopeEndFirst, int const scopeEndSecond) {
    ScopeDetail& scopeToExit(m_scopeDetails.back());
    if (scopeToExit.scopeType == ScopeType::ClassDeclaration || scopeToExit.scopeType == ScopeType::Namespace) {
        m_terms.erase(m_terms.cbegin() + scopeToExit.scopeHeaderDivider + 1, m_terms.cbegin() + scopeEndFirst);

        CPlusPlusReorganizeItems sorter(scopeToExit.items, getScopeNames(), m_headerInformation.signatures);
        Terms sortedTerms(sorter.getSortedAggregateTerms());
        m_terms.insert(m_terms.cbegin() + scopeToExit.scopeHeaderDivider + 1, sortedTerms.cbegin(), sortedTerms.cend());

        int sizeDifference = static_cast<int>(sortedTerms.size()) - scopeEndFirst + scopeToExit.scopeHeaderDivider + 1;
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, scopeEndSecond + sizeDifference);
        termIndex = scopeEndSecond + 1 + sizeDifference;
    } else {
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, scopeEndSecond);
        termIndex = scopeEndSecond + 1;
    }
}

void CPlusPlusReorganizer::addItemIfNeeded(int const startIndex, int const endIndex) {
    addItemIfNeeded(getContents(startIndex, endIndex));
}

void CPlusPlusReorganizer::addItemIfNeeded(string const& content) {
    if (!content.empty()) {
        switch (m_purpose) {
            case Purpose::Reorganize:
                m_scopeDetails.back().items.emplace_back(content);
                break;
            case Purpose::GatherInformation:
                m_headerInformation.signatures.emplace_back(getFunctionSignature(content));
                break;
            case Purpose::Unknown:
                break;
        }
    }
}

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::getCurrentScope() const { return m_scopeDetails.back(); }

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::constructScopeDetails(
    int const scopeHeaderStart, int const scopeHeaderDivider) const {
    ScopeDetail scopeDetail{scopeHeaderStart, scopeHeaderDivider, 0, ScopeType::Unknown, {}, {}};
    Terms scopeHeaderTerms(getTermsFromString(getContents(scopeHeaderStart, scopeHeaderDivider - 1)));
    Patterns searchPatterns{
        {M("namespace"), M(TermType::Identifier)},
        {M("class"), M(TermType::Identifier)},
        {M("struct"), M(TermType::Identifier)},
        {M("union"), M(TermType::Identifier)}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(scopeHeaderTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            if (scopeHeaderTerms[firstHitIndex].getContent() == "namespace") {
                scopeDetail.scopeType = ScopeType::Namespace;
                scopeDetail.name = scopeHeaderTerms[hitIndexes[1]].getContent();
                break;
            }
            if (scopeHeaderTerms[firstHitIndex].getContent() == "class" ||
                scopeHeaderTerms[firstHitIndex].getContent() == "struct" ||
                scopeHeaderTerms[firstHitIndex].getContent() == "union") {
                scopeDetail.scopeType = ScopeType::ClassDeclaration;
                scopeDetail.name = scopeHeaderTerms[hitIndexes[1]].getContent();
                break;
            }
            termIndex = hitIndexes.back() + 1;
        }
    }
    return scopeDetail;
}

strings CPlusPlusReorganizer::getScopeNames() const {
    strings result;
    for (ScopeDetail const& scopeDetail : m_scopeDetails) {
        if (!scopeDetail.name.empty()) {
            result.emplace_back(scopeDetail.name);
        }
    }
    return result;
}

strings CPlusPlusReorganizer::getSavedSignatures() const { return m_headerInformation.signatures; }

string CPlusPlusReorganizer::getContents(int const start, int const end) const {
    return getStringWithoutStartingAndTrailingWhiteSpace(getCombinedContents(m_terms, start, end));
}

}  // namespace alba::CodeUtilities
