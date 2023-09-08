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
            isHeaderFileExtension(filePathHandler.getExtension()) &&
            isImplementationFileExtension(previousFilePathHandler.getExtension())) {
            processHeaderAndImplementationFile(filePathHandler.getFullPath(), previousFilePathHandler.getFullPath());
            isPreviousFileProcessed = true;
        } else {
            if (!isPreviousFileProcessed && isCppFileExtension(previousFilePathHandler.getExtension())) {
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
        {M(TermType::Macro)},
        {M(";")},
        {M("{"), M("}"), M(";")},
        {M("{"), M("}")},
        {M("{")},
        {M("}"), M(";")},
        {M("}")},
        {M("(")},
        {M("public"), M(":")},
        {M("protected"), M(":")},
        {M("private"), M(":")}};
    int lastProcessedIndex = 0;
    int searchIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(m_terms, searchIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            int lastHitIndex = hitIndexes.back();
            Term const& firstTerm(m_terms[firstHitIndex]);
            Term const& lastTerm(m_terms[lastHitIndex]);
            if (firstTerm.getTermType() == TermType::Macro) {
                processMacro(lastProcessedIndex, firstHitIndex);
                searchIndex = lastProcessedIndex;
            } else if (firstTerm.getContent() == ";") {
                processSemiColon(lastProcessedIndex, firstHitIndex);
                searchIndex = lastProcessedIndex;
            } else if (
                (firstTerm.getContent() == "{" && m_terms[hitIndexes[1]].getContent() == "}" &&
                 lastTerm.getContent() == ";") ||
                (firstTerm.getContent() == "{" && lastTerm.getContent() == "}")) {
                processOpeningAndClosingBrace(lastProcessedIndex, firstHitIndex, lastHitIndex);
                searchIndex = lastProcessedIndex;
            } else if (firstTerm.getContent() == "{") {
                processOpeningBrace(lastProcessedIndex, firstHitIndex);
                searchIndex = lastProcessedIndex;
            } else if (firstTerm.getContent() == "}") {
                processClosingBrace(lastProcessedIndex, firstHitIndex, lastHitIndex);
                searchIndex = lastProcessedIndex;
            } else if (firstTerm.getContent() == "(") {
                searchIndex = getIndexAtClosingString(m_terms, firstHitIndex, "(", ")");
            } else {
                processRecognizedItem(lastProcessedIndex, lastHitIndex);
                searchIndex = lastProcessedIndex;
            }
        }
    }
}

void CPlusPlusReorganizer::processMacro(int& lastProcessedIndex, int const macroStartIndex) {
    addItemIfNeeded(lastProcessedIndex, macroStartIndex - 1);  // add item before macro
    lastProcessedIndex = macroStartIndex + 1;
    Patterns searchPatterns{{M(MatcherType::WhiteSpaceWithNewLine)}, {M("\\"), M(MatcherType::WhiteSpaceWithNewLine)}};
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(m_terms, lastProcessedIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            int lastHitIndex = hitIndexes.back();
            Term const& firstTerm(m_terms[firstHitIndex]);
            lastProcessedIndex = lastHitIndex + 1;
            if (firstTerm == M(MatcherType::WhiteSpaceWithNewLine)) {
                addItemIfNeeded(macroStartIndex, lastHitIndex);
                break;
            }
        }
    }
}

void CPlusPlusReorganizer::processSemiColon(int& lastProcessedIndex, int const semiColonIndex) {
    int endIndex = getIndexAtSameLineComment(semiColonIndex);
    addItemIfNeeded(lastProcessedIndex, endIndex);
    lastProcessedIndex = endIndex + 1;
}

void CPlusPlusReorganizer::processOpeningAndClosingBrace(
    int& lastProcessedIndex, int const openingBraceIndex, int const closingBraceSemiColonIndex) {
    int endIndex = getIndexAtSameLineComment(closingBraceSemiColonIndex);
    Terms scopeHeaderTerms(getTermsFromString(getContents(lastProcessedIndex, openingBraceIndex - 1)));
    strings& currentItems(m_scopeDetails.back().items);
    if (!currentItems.empty() && hasEndBrace(currentItems.back()) && shouldConnectToPreviousItem(scopeHeaderTerms)) {
        currentItems.back() += getCombinedContents(m_terms, lastProcessedIndex, endIndex);
    } else {
        addItemIfNeeded(lastProcessedIndex, endIndex);
    }
    lastProcessedIndex = endIndex + 1;
}

void CPlusPlusReorganizer::processOpeningBrace(int& lastProcessedIndex, int const openingBraceIndex) {
    Terms scopeHeaderTerms(getTermsFromString(getContents(lastProcessedIndex, openingBraceIndex - 1)));
    strings& currentItems(m_scopeDetails.back().items);
    if (!currentItems.empty() && hasEndBrace(currentItems.back()) && shouldConnectToPreviousItem(scopeHeaderTerms)) {
        Terms lastItemTerms = getTermsFromString(currentItems.back());
        currentItems.pop_back();
        lastProcessedIndex -= static_cast<int>(lastItemTerms.size()) + 1;
    }
    enterScope(lastProcessedIndex, openingBraceIndex);
    lastProcessedIndex = openingBraceIndex + 1;
}

void CPlusPlusReorganizer::processClosingBrace(
    int& lastProcessedIndex, int const closingBraceIndex, int const closingBraceSemiColonIndex) {
    int endIndex = getIndexAtSameLineComment(closingBraceSemiColonIndex);
    addItemIfNeeded(lastProcessedIndex, closingBraceIndex - 1);
    exitScope(lastProcessedIndex, closingBraceIndex, endIndex);
}

void CPlusPlusReorganizer::processRecognizedItem(int& lastProcessedIndex, int const recognizedItemEndIndex) {
    addItemIfNeeded(lastProcessedIndex, recognizedItemEndIndex);
    lastProcessedIndex = recognizedItemEndIndex + 1;
}

void CPlusPlusReorganizer::enterScope(int const scopeHeaderStart, int const openingBraceIndex) {
    m_scopeDetails.emplace_back(constructScopeDetails(scopeHeaderStart, openingBraceIndex));
}

void CPlusPlusReorganizer::exitScope(int& lastProcessedIndex, int const closingBraceIndex, int const endIndex) {
    ScopeDetail& scopeToExit(m_scopeDetails.back());
    if (shouldReorganizeInThisScope(scopeToExit)) {
        m_terms.erase(m_terms.cbegin() + scopeToExit.openingBraceIndex + 1, m_terms.cbegin() + closingBraceIndex);

        CPlusPlusReorganizeItems sorter(
            scopeToExit.scopeType, scopeToExit.items, getScopeNames(), m_headerInformation.signatures);
        Terms sortedTerms(sorter.getSortedAggregateTerms());
        m_terms.insert(m_terms.cbegin() + scopeToExit.openingBraceIndex + 1, sortedTerms.cbegin(), sortedTerms.cend());

        int sizeDifference =
            static_cast<int>(sortedTerms.size()) - closingBraceIndex + scopeToExit.openingBraceIndex + 1;
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, endIndex + sizeDifference);
        lastProcessedIndex = endIndex + 1 + sizeDifference;
    } else {
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, endIndex);
        lastProcessedIndex = endIndex + 1;
    }
}

bool CPlusPlusReorganizer::shouldReorganizeInThisScope(ScopeDetail const& scope) {
    return scope.scopeType == ScopeType::ClassDeclaration || scope.scopeType == ScopeType::Namespace;
}

void CPlusPlusReorganizer::addItemIfNeeded(int const startIndex, int const endIndex) {
    string content = getContents(startIndex, endIndex);
    if (!content.empty() && shouldReorganizeInThisScope(m_scopeDetails.back())) {
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

int CPlusPlusReorganizer::getIndexAtSameLineComment(int const index) const {
    int endIndex = index;
    Patterns searchPatterns{{M(TermType::WhiteSpace), M(MatcherType::Comment)}, {M(MatcherType::Comment)}};
    Indexes hitIndexes = checkPatternAt(m_terms, index + 1, searchPatterns);
    if (!hitIndexes.empty()) {
        int firstHitIndex = hitIndexes.front();
        int lastHitIndex = hitIndexes.back();
        Term const& firstTerm(m_terms[firstHitIndex]);
        Term const& lastTerm(m_terms[lastHitIndex]);
        if (firstTerm == M(TermType::WhiteSpace) && lastTerm == M(MatcherType::Comment) && !hasNewLine(firstTerm)) {
            endIndex = lastHitIndex;
        }
        if (firstTerm == M(MatcherType::Comment)) {
            endIndex = firstHitIndex;
        }
    }
    return endIndex;
}

int CPlusPlusReorganizer::getIndexAtClosingString(
    Terms const& terms, int const openingIndex, string const& openingString, string const& closingString) {
    Patterns searchPatterns{{M(openingString)}, {M(closingString)}};
    int endIndex = openingIndex + 1;
    int numberOfOpenings = 1;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, endIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            Term const& firstTerm(terms[firstHitIndex]);
            if (firstTerm.getContent() == openingString) {
                endIndex = firstHitIndex + 1;
                ++numberOfOpenings;
            } else if (firstTerm.getContent() == closingString) {
                endIndex = firstHitIndex + 1;
                if (--numberOfOpenings == 0) {
                    break;
                }
            } else {
                break;
            }
        }
    }
    return endIndex;
}

bool CPlusPlusReorganizer::shouldConnectToPreviousItem(Terms const& scopeHeaderTerms) {
    bool isEmpty(scopeHeaderTerms.empty());
    bool hasNoInvalidKeyword = all_of(scopeHeaderTerms.cbegin(), scopeHeaderTerms.cend(), [](Term const& term) {
        return term.getTermType() != TermType::Keyword || term.getContent() == "const_cast" ||
               term.getContent() == "dynamic_cast" || term.getContent() == "reinterpret_cast" ||
               term.getContent() == "static_cast";
    });
    bool hasCommaAtTheStart = !checkPatternAt(scopeHeaderTerms, 0, Patterns{{M(",")}}).empty();
    return isEmpty || (hasNoInvalidKeyword && hasCommaAtTheStart);
}

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::constructScopeDetails(
    int const scopeHeaderStart, int const openingBraceIndex) const {
    string scopeHeader(getContents(scopeHeaderStart, openingBraceIndex - 1));
    Terms scopeHeaderTerms(getTermsFromString(scopeHeader));
    ScopeDetail scopeDetail{scopeHeaderStart, openingBraceIndex, 0, ScopeType::Unknown, {}, {}};
    Patterns searchPatterns{
        {M("template"), M("<")},
        {M("namespace"), M(TermType::Identifier)},
        {M("class"), M(TermType::Identifier)},
        {M("struct"), M(TermType::Identifier)},
        {M("union"), M(TermType::Identifier)}};
    int lastProcessedIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(scopeHeaderTerms, lastProcessedIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            int lastHitIndex = hitIndexes.back();
            Term const& firstTerm(scopeHeaderTerms[firstHitIndex]);
            Term const& lastTerm(scopeHeaderTerms[lastHitIndex]);
            if (firstTerm.getContent() == "namespace") {
                scopeDetail.scopeType = ScopeType::Namespace;
                scopeDetail.name = lastTerm.getContent();
                break;
            }
            if (firstTerm.getContent() == "class" || firstTerm.getContent() == "struct" ||
                firstTerm.getContent() == "union") {
                scopeDetail.scopeType = ScopeType::ClassDeclaration;
                scopeDetail.name = lastTerm.getContent();
                break;
            }
            if (firstTerm.getContent() == "template" && lastTerm.getContent() == "<") {
                lastProcessedIndex = getIndexAtClosingString(scopeHeaderTerms, lastHitIndex, "<", ">");
            } else {
                lastProcessedIndex = lastHitIndex + 1;
            }
        }
    }
    return scopeDetail;
}

bool CPlusPlusReorganizer::hasEndBrace(string const& content) {
    Terms termsToCheck(getTermsFromString(content));
    Indexes hitIndexes = checkMatcherAtBackwards(termsToCheck, static_cast<int>(termsToCheck.size()) - 1, M("}"));
    return !hitIndexes.empty();
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
