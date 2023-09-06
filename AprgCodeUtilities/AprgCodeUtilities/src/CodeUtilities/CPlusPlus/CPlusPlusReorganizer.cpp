#include "CPlusPlusReorganizer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizeItems.hpp>
#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/Debug/AlbaDebug.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace std;
using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

CPlusPlusReorganizer::CPlusPlusReorganizer() = default;

void CPlusPlusReorganizer::processHeaderAndImplementationFile(
    string const& headerFile, string const& implementationFile) {
    processHeaderFile(headerFile);
    processImplementationFile(implementationFile);
}

void CPlusPlusReorganizer::processHeaderFile(string const& headerFile) {
    m_purpose = Purpose::Reorganize;
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}, {}}};
    processFile(headerFile);
}

void CPlusPlusReorganizer::processImplementationFile(string const& implementationFile) {
    m_purpose = Purpose::Reorganize;
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}, {}}};
    processFile(implementationFile);
}

void CPlusPlusReorganizer::processFile(string const& headerFile) {
    AlbaLocalPathHandler filePathHandler(headerFile);
    m_terms = getTermsFromFile(filePathHandler.getFullPath());
    processTerms();
    if (Purpose::Reorganize == m_purpose) {
        writeAllTerms(filePathHandler.getFullPath(), m_terms);
    }
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
    Patterns searchPatterns{{M("\\"), M(MatcherType::HasNewLine)}, {M(MatcherType::HasNewLine)}};
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

        CPlusPlusReorganizeItems sorter(scopeToExit.items);
        Terms sortedTerms(sorter.getSortedAggregateTerms());
        m_terms.insert(m_terms.cbegin() + scopeToExit.scopeHeaderDivider + 1, sortedTerms.cbegin(), sortedTerms.cend());

        int difference = static_cast<int>(sortedTerms.size()) - scopeEndFirst + scopeToExit.scopeHeaderDivider + 1;
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, scopeEndSecond + difference);
        termIndex = scopeEndSecond + 1 + difference;
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
    if (isToReorganize() && !content.empty()) {
        m_scopeDetails.back().items.emplace_back(content);
    }
}

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::getCurrentScope() const { return m_scopeDetails.back(); }

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::constructScopeDetails(
    int const scopeHeaderStart, int const scopeHeaderDivider) const {
    ScopeDetail scopeDetail{
        scopeHeaderStart,
        scopeHeaderDivider,
        0,
        ScopeType::Unknown,
        getContents(scopeHeaderStart, scopeHeaderDivider - 1),
        {},
        {}};
    Terms scopeHeaderTerms(getTermsFromString(scopeDetail.scopeHeaderCode));
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

string CPlusPlusReorganizer::getContents(int const start, int const end) const {
    return getStringWithoutStartingAndTrailingWhiteSpace(getCombinedContents(m_terms, start, end));
}

bool CPlusPlusReorganizer::isInClassDeclaration() const {
    return ScopeType::ClassDeclaration == m_scopeDetails.back().scopeType;
}

bool CPlusPlusReorganizer::isToReorganize() const { return Purpose::Reorganize == m_purpose; }

}  // namespace alba::CodeUtilities
