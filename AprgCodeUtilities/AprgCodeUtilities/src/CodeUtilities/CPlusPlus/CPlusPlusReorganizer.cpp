#include "CPlusPlusReorganizer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizeItems.hpp>
#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/Debug/AlbaDebug.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>

#include <iostream>

using namespace std;
using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

CPlusPlusReorganizer::CPlusPlusReorganizer() = default;

void CPlusPlusReorganizer::processDirectory(string const& directory) {
    AlbaLocalPathHandler directoryPathHandler(directory);
    ListOfPaths directories;
    ListOfPaths files;
    AlbaLocalPathHandler previousFilePathHandler("");
    bool isPreviousFileProcessed(false);
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        if (filePathHandler.getDirectory() == previousFilePathHandler.getDirectory() &&
            filePathHandler.getFilenameOnly() == previousFilePathHandler.getFilenameOnly() &&
            isHeaderFile(filePathHandler.getExtension()) &&
            isImplementationFile(previousFilePathHandler.getExtension())) {
            processHeaderAndImplementationFile(filePathHandler.getFullPath(), previousFilePathHandler.getFullPath());
            isPreviousFileProcessed = true;
        } else {
            if (!isPreviousFileProcessed && isCppFile(previousFilePathHandler.getExtension())) {
                reorganizeFile(previousFilePathHandler.getFullPath());
            }
            isPreviousFileProcessed = false;
        }
        previousFilePathHandler = filePathHandler;
    }
    if (!isPreviousFileProcessed) {
        reorganizeFile(previousFilePathHandler.getFullPath());
    }
}

void CPlusPlusReorganizer::processHeaderAndImplementationFile(
    string const& headerFile, string const& implementationFile) {
    ALBA_INF_PRINT2(cout, headerFile, implementationFile);
    reorganizeFile(headerFile);
    gatherInformationFromFile(headerFile);
    reorganizeFile(implementationFile);
    m_headerInformation = {};
}

void CPlusPlusReorganizer::reorganizeFile(string const& file) {
    ALBA_INF_PRINT1(cout, file);
    m_purpose = Purpose::Reorganize;
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}}};
    AlbaLocalPathHandler filePathHandler(file);
    m_terms = getTermsFromFile(filePathHandler.getFullPath());
    processTerms();
    writeAllTerms(filePathHandler.getFullPath(), m_terms);
}

void CPlusPlusReorganizer::gatherInformationFromFile(string const& file) {
    ALBA_INF_PRINT1(cout, file);
    m_purpose = Purpose::GatherInformation;
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}}};
    AlbaLocalPathHandler filePathHandler(file);
    m_terms = getTermsFromFile(filePathHandler.getFullPath());
    processTerms();
}

void CPlusPlusReorganizer::processTerms() {
    Patterns searchPatterns{
        {M(TermType::Macro)}, {M(";")}, {M("{"), M("}"), M(";")}, {M("{"), M("}")},         {M("{")},
        {M("}"), M(";")},     {M("}")}, {M("public"), M(":")},    {M("protected"), M(":")}, {M("private"), M(":")}};
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
            } else if (
                (m_terms[firstHitIndex].getContent() == "{" && m_terms[hitIndexes[1]].getContent() == "}" &&
                 m_terms[hitIndexes.back()].getContent() == ";") ||
                (m_terms[firstHitIndex].getContent() == "{" && m_terms[hitIndexes.back()].getContent() == "}")) {
                processOpeningAndClosingBrace(termIndex, firstHitIndex, hitIndexes.back());
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

/*
void CPlusPlusReorganizer::processComment(int& termIndex, int const commentIndex) {
 bool connectCommentToPrevious(true);
 if (commentIndex > 0) {
     Term termBeforeComment = m_terms[commentIndex - 1];
     if (hasNewLine(termBeforeComment)) {
         connectCommentToPrevious = false;
     }
 }
 strings& currentItems(m_scopeDetails.back().items);
 if (!currentItems.empty() && connectCommentToPrevious) {
     string& lastItem(currentItems.back());
     lastItem += " ";
     lastItem += getCombinedContents(m_terms, commentIndex, commentIndex);
 } else {
     addItemIfNeeded(commentIndex, commentIndex);
 }
 termIndex = commentIndex + 1;
}
 */

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
    int endIndex = semiColonIndex;
    Patterns searchPatterns{{M(TermType::WhiteSpace), M(MatcherType::Comment)}};
    Indexes hitIndexes = checkPatternAt(m_terms, endIndex + 1, searchPatterns);
    if (!hitIndexes.empty()) {
        int firstHitIndex = hitIndexes.front();
        if (m_terms[firstHitIndex] == M(TermType::WhiteSpace) &&
            m_terms[hitIndexes.back()] == M(MatcherType::Comment) && !hasNewLine(m_terms[firstHitIndex])) {
            endIndex = hitIndexes.back();
        }
    }
    addItemIfNeeded(termIndex, endIndex);
    termIndex = endIndex + 1;
}

void CPlusPlusReorganizer::processOpeningAndClosingBrace(
    int& termIndex, int const openingBraceIndex, int const endIndex) {
    Terms scopeHeaderTerms(getTermsFromString(getContents(termIndex, openingBraceIndex - 1)));
    strings& currentItems(m_scopeDetails.back().items);
    if (!currentItems.empty() && shouldConnectToPreviousItem(scopeHeaderTerms)) {
        currentItems.back() += getCombinedContents(m_terms, termIndex, endIndex);
    } else {
        addItemIfNeeded(termIndex, endIndex);
    }
    termIndex = endIndex + 1;
}

void CPlusPlusReorganizer::processOpeningBrace(int& termIndex, int const openingBraceIndex) {
    Terms scopeHeaderTerms(getTermsFromString(getContents(termIndex, openingBraceIndex - 1)));
    strings& currentItems(m_scopeDetails.back().items);
    if (!currentItems.empty() && shouldConnectToPreviousItem(scopeHeaderTerms)) {
        string const& lastItem(currentItems.back());
        if (hasBraces(lastItem)) {
            Terms lastItemTerms = getTermsFromString(lastItem);
            currentItems.pop_back();
            termIndex -= static_cast<int>(lastItemTerms.size()) + 1;
        }
    }
    enterScope(termIndex, openingBraceIndex);
    termIndex = openingBraceIndex + 1;
}

void CPlusPlusReorganizer::processClosingBrace(
    int& termIndex, int const closingBraceIndex, int const possibleSemiColonIndex) {
    addItemIfNeeded(termIndex, closingBraceIndex - 1);
    exitScope(termIndex, closingBraceIndex, possibleSemiColonIndex);
}

void CPlusPlusReorganizer::processRecognizedItem(int& termIndex, int const recognizedItemEndIndex) {
    addItemIfNeeded(termIndex, recognizedItemEndIndex);
    termIndex = recognizedItemEndIndex + 1;
}

void CPlusPlusReorganizer::enterScope(int const scopeHeaderStart, int const openingBraceIndex) {
    m_scopeDetails.emplace_back(constructScopeDetails(scopeHeaderStart, openingBraceIndex));
}

void CPlusPlusReorganizer::exitScope(int& termIndex, int const closingBraceIndex, int const possibleSemiColonIndex) {
    ScopeDetail& scopeToExit(m_scopeDetails.back());
    if (scopeToExit.scopeType == ScopeType::ClassDeclaration || scopeToExit.scopeType == ScopeType::Namespace) {
        m_terms.erase(m_terms.cbegin() + scopeToExit.openingBraceIndex + 1, m_terms.cbegin() + closingBraceIndex);

        CPlusPlusReorganizeItems sorter(scopeToExit.items, getScopeNames(), m_headerInformation.signatures);
        Terms sortedTerms(sorter.getSortedAggregateTerms());
        m_terms.insert(m_terms.cbegin() + scopeToExit.openingBraceIndex + 1, sortedTerms.cbegin(), sortedTerms.cend());

        int sizeDifference =
            static_cast<int>(sortedTerms.size()) - closingBraceIndex + scopeToExit.openingBraceIndex + 1;
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, possibleSemiColonIndex + sizeDifference);
        termIndex = possibleSemiColonIndex + 1 + sizeDifference;
    } else {
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, possibleSemiColonIndex);
        termIndex = possibleSemiColonIndex + 1;
    }
}

void CPlusPlusReorganizer::addItemIfNeeded(int const startIndex, int const endIndex) {
    addItemIfNeeded(getContents(startIndex, endIndex));
}

void CPlusPlusReorganizer::addItemIfNeeded(string const& content) {
    if (!content.empty()) {
        switch (m_purpose) {
            case Purpose::Reorganize: {
                m_scopeDetails.back().items.emplace_back(content);
                break;
            }
            case Purpose::GatherInformation:
                m_headerInformation.signatures.emplace_back(getFunctionSignature(content));
                break;
            case Purpose::Unknown:
                break;
        }
    }
}

bool CPlusPlusReorganizer::shouldConnectToPreviousItem(Terms const& scopeHeaderTerms) {
    return all_of(scopeHeaderTerms.cbegin(), scopeHeaderTerms.cend(), [](Term const& term) {
        return isCommentOrWhiteSpace(term) || isOperator(term);
    });
}

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::constructScopeDetails(
    int const scopeHeaderStart, int const openingBraceIndex) const {
    string scopeHeader(getContents(scopeHeaderStart, openingBraceIndex - 1));
    Terms scopeHeaderTerms(getTermsFromString(scopeHeader));
    ScopeDetail scopeDetail{scopeHeaderStart, openingBraceIndex, 0, ScopeType::Unknown, {}, {}};
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
