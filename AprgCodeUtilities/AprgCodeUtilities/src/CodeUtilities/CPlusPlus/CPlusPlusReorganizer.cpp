#include "CPlusPlusReorganizer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusReorganizeItems.hpp>
#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>

#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

void CPlusPlusReorganizer::processDirectory(string const& directory) {
    AlbaLocalPathHandler const directoryPathHandler(directory);
    ListOfPaths directories;
    ListOfPaths files;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    unordered_map<string, CppFiles> filenameToFilesMap;
    for (auto const& file : files) {
        AlbaLocalPathHandler const filePathHandler(file);
        string filenameOnly(filePathHandler.getFilenameOnly());
        if (isImplementationFileExtension(filePathHandler.getExtension()) &&
            isStringFoundNotCaseSensitive(filenameOnly, "_unit")) {
            replaceAllAndReturnIfFound(filenameOnly, "_unit", "");
            CppFiles& cppFiles(filenameToFilesMap[filenameOnly]);
            cppFiles.testFile = filePathHandler.getFullPath();
            cppFiles.isTestFileProcessed = false;
        } else {
            CppFiles& cppFiles(filenameToFilesMap[filenameOnly]);
            if (isHeaderFileExtension(filePathHandler.getExtension())) {
                cppFiles.headerFile = filePathHandler.getFullPath();
                cppFiles.isHeaderFileProcessed = false;
            } else if (isImplementationFileExtension(filePathHandler.getExtension())) {
                cppFiles.implementationFile = filePathHandler.getFullPath();
                cppFiles.isImplementationFileProcessed = false;
            }
        }
        CppFiles& cppFiles(filenameToFilesMap[filenameOnly]);
        if (!cppFiles.isHeaderFileProcessed && !cppFiles.headerFile.empty()) {
            processHeaderFile(cppFiles.headerFile);
            cppFiles.isHeaderFileProcessed = true;
        }
        if (!cppFiles.isImplementationFileProcessed && !cppFiles.headerFile.empty() &&
            !cppFiles.implementationFile.empty()) {
            processImplementationFile(cppFiles.headerFile, cppFiles.implementationFile);
            cppFiles.isImplementationFileProcessed = true;
        }
        if (!cppFiles.isTestFileProcessed && !cppFiles.headerFile.empty() && !cppFiles.testFile.empty()) {
            processImplementationFile(cppFiles.headerFile, cppFiles.testFile);
            cppFiles.isTestFileProcessed = true;
        }
    }
    cout << "Processing unprocessed files:\n";
    for (auto const& filenameToFiles : filenameToFilesMap) {
        CppFiles const& cppFiles(filenameToFiles.second);
        if (!cppFiles.isHeaderFileProcessed && !cppFiles.headerFile.empty()) {
            processHeaderFile(cppFiles.headerFile);
        }
        if (!cppFiles.isImplementationFileProcessed && !cppFiles.implementationFile.empty()) {
            processImplementationFile(cppFiles.headerFile, cppFiles.implementationFile);
        }
        if (!cppFiles.isTestFileProcessed && !cppFiles.testFile.empty()) {
            processImplementationFile(cppFiles.headerFile, cppFiles.testFile);
        }
    }
}

void CPlusPlusReorganizer::processHeaderFile(string const& headerFile) {
    ALBA_INF_PRINT1(cout, headerFile);
    reorganizeFile(headerFile);
}

void CPlusPlusReorganizer::processImplementationFile(string const& headerFile, string const& implementationFile) {
    ALBA_INF_PRINT2(cout, headerFile, implementationFile);
    m_headerInformation = {};
    gatherInformationFromFile(headerFile);
    reorganizeFile(implementationFile);
    m_headerInformation = {};
}

CPlusPlusReorganizer::ScopeDetail CPlusPlusReorganizer::constructScopeDetails(
    int const scopeHeaderStart, int const openingBraceIndex) const {
    Terms scopeHeaderTerms(extractTermsInRange(scopeHeaderStart, openingBraceIndex));
    ScopeDetail scopeDetail{scopeHeaderStart, openingBraceIndex, 0, ScopeType::Unknown, {}, {}};
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
        Indexes hitIndexes = searchForwardsForPatterns(scopeHeaderTerms, nextIndex, searchPatterns);
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

Terms CPlusPlusReorganizer::extractTermsInRange(int const start, int const end) const {
    Terms extractedTerms;
    if (start <= end) {
        extractedTerms.reserve(end + 1 - start);
        copy(m_terms.begin() + start, m_terms.cbegin() + end + 1, back_inserter(extractedTerms));
    }
    return extractedTerms;
}

string CPlusPlusReorganizer::getFormattedContent(int const start, int const end) const {
    Terms formattedTerms(extractTermsInRange(start, end));
    removeStartingAndTrailingWhiteSpace(formattedTerms);
    makeIsolatedCommentsStickWithNextLine(formattedTerms);
    return getCombinedContents(formattedTerms);
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

strings CPlusPlusReorganizer::getSavedSignatures() const { return m_headerInformation.functionSignatures; }

int CPlusPlusReorganizer::getIndexAtSameLineComment(int const index) const {
    int endIndex = index;
    Patterns const searchPatterns{{M(TermType::WhiteSpace), M(MatcherType::Comment)}, {M(MatcherType::Comment)}};
    Indexes hitIndexes = searchPatternsAt(m_terms, index + 1, searchPatterns);
    if (!hitIndexes.empty()) {
        int const firstHitIndex = hitIndexes.front();
        int const lastHitIndex = hitIndexes.back();
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

void CPlusPlusReorganizer::reorganizeFile(string const& file) {
    m_purpose = Purpose::Reorganize;
    AlbaLocalPathHandler const filePathHandler(file);
    if (filePathHandler.isFoundInLocalSystem()) {
        // ALBA_INF_PRINT(cout, filePathHandler.getFullPath());
        // string command("cat \"");
        // command += filePathHandler.getFullPath();
        // command += "\"";
        // system(command.c_str());
        m_fileType = getFileType(filePathHandler.getExtension());
        m_terms = getTermsFromFile(filePathHandler.getFullPath());
        processTerms();
        writeAllTerms(filePathHandler.getFullPath(), m_terms);
    } else {
        cout << "File not found: [" << filePathHandler.getFullPath() << "]\n";
    }
}

void CPlusPlusReorganizer::gatherInformationFromFile(string const& file) {
    m_purpose = Purpose::GatherInformation;
    AlbaLocalPathHandler const filePathHandler(file);
    if (filePathHandler.isFoundInLocalSystem()) {
        // ALBA_INF_PRINT(cout, filePathHandler.getFullPath());
        // string command("cat \"");
        // command += filePathHandler.getFullPath();
        // command += "\"";
        // system(command.c_str());
        m_fileType = getFileType(filePathHandler.getExtension());
        m_terms = getTermsFromFile(filePathHandler.getFullPath());
        processTerms();
    } else {
        cout << "File not found: [" << filePathHandler.getFullPath() << "]\n";
    }
}

void CPlusPlusReorganizer::processTerms() {
    enterAndSetTopLevelScope();

    Patterns const searchPatterns{
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
    int nextIndex = 0;
    int searchIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_terms, searchIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            int const lastHitIndex = hitIndexes.back();
            Term const& firstTerm(m_terms[firstHitIndex]);
            Term const& lastTerm(m_terms[lastHitIndex]);
            if (firstTerm.getTermType() == TermType::Macro) {
                processMacro(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            } else if (firstTerm.getContent() == ";") {
                processSemiColon(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            } else if (
                (firstTerm.getContent() == "{" && m_terms[hitIndexes[1]].getContent() == "}" &&
                 lastTerm.getContent() == ";") ||
                (firstTerm.getContent() == "{" && lastTerm.getContent() == "}")) {
                processOpeningAndClosingBrace(nextIndex, firstHitIndex, lastHitIndex);
                searchIndex = nextIndex;
            } else if (firstTerm.getContent() == "{") {
                processOpeningBrace(nextIndex, firstHitIndex);
                searchIndex = nextIndex;
            } else if (firstTerm.getContent() == "}") {
                processClosingBrace(nextIndex, firstHitIndex, lastHitIndex);
                searchIndex = nextIndex;
            } else if (firstTerm.getContent() == "(") {
                searchIndex = getIndexAtClosingString(m_terms, firstHitIndex, "(", ")");
            } else {
                processRecognizedItem(nextIndex, lastHitIndex);
                searchIndex = nextIndex;
            }
        }
    }
    addItemIfNeeded(nextIndex, static_cast<int>(m_terms.size()) - 1);

    exitTopLevelScope();
}

void CPlusPlusReorganizer::processMacro(int& nextIndex, int const macroStartIndex) {
    int searchIndex = macroStartIndex;
    Patterns const searchPatterns{
        {M(MatcherType::WhiteSpaceWithNewLine)}, {M("\\"), M(MatcherType::WhiteSpaceWithNewLine)}};
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_terms, searchIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            int const lastHitIndex = hitIndexes.back();
            Term const& firstTerm(m_terms[firstHitIndex]);
            if (firstTerm == M(MatcherType::WhiteSpaceWithNewLine)) {
                addItemIfNeeded(nextIndex, lastHitIndex);
                nextIndex = lastHitIndex + 1;
                break;
            }
            searchIndex = lastHitIndex + 1;
        }
    }
}

void CPlusPlusReorganizer::processSemiColon(int& nextIndex, int const semiColonIndex) {
    int const endIndex = getIndexAtSameLineComment(semiColonIndex);
    addItemIfNeeded(nextIndex, endIndex);
    nextIndex = endIndex + 1;
}

void CPlusPlusReorganizer::processOpeningAndClosingBrace(
    int& nextIndex, int const openingBraceIndex, int const closingBraceSemiColonIndex) {
    int const endIndex = getIndexAtSameLineComment(closingBraceSemiColonIndex);
    Terms const scopeHeaderTerms(extractTermsInRange(nextIndex, openingBraceIndex - 1));
    strings& currentItems(m_scopeDetails.back().items);
    if (!currentItems.empty() && hasEndBrace(currentItems.back()) && shouldConnectToPreviousItem(scopeHeaderTerms)) {
        currentItems.back() += getCombinedContents(m_terms, nextIndex, endIndex);
    } else {
        addItemIfNeeded(nextIndex, endIndex);
    }
    nextIndex = endIndex + 1;
}

void CPlusPlusReorganizer::processOpeningBrace(int& nextIndex, int const openingBraceIndex) {
    if (!m_scopeDetails.empty()) {
        strings& currentItems(m_scopeDetails.back().items);
        Terms const scopeHeaderTerms(extractTermsInRange(nextIndex, openingBraceIndex - 1));
        if (!currentItems.empty() && hasEndBrace(currentItems.back()) &&
            shouldConnectToPreviousItem(scopeHeaderTerms)) {
            Terms const lastItemTerms = getTermsFromString(currentItems.back());
            currentItems.pop_back();
            nextIndex -= static_cast<int>(lastItemTerms.size()) + 1;
        }
        enterScope(nextIndex, openingBraceIndex);
        nextIndex = openingBraceIndex + 1;
    }
}

void CPlusPlusReorganizer::processClosingBrace(
    int& nextIndex, int const closingBraceIndex, int const closingBraceSemiColonIndex) {
    int const endIndex = getIndexAtSameLineComment(closingBraceSemiColonIndex);
    addItemIfNeeded(nextIndex, closingBraceIndex - 1);
    exitScope(nextIndex, closingBraceIndex, endIndex);
}

void CPlusPlusReorganizer::processRecognizedItem(int& nextIndex, int const recognizedItemEndIndex) {
    addItemIfNeeded(nextIndex, recognizedItemEndIndex);
    nextIndex = recognizedItemEndIndex + 1;
}

void CPlusPlusReorganizer::enterAndSetTopLevelScope() {
    m_scopeDetails = {ScopeDetail{0, 0, 0, ScopeType::TopLevel, {}, {}}};
}

void CPlusPlusReorganizer::exitTopLevelScope() {
    ScopeDetail const& scopeToExit(m_scopeDetails.back());

    CPlusPlusReorganizeItems const sorter(
        {m_fileType, scopeToExit.scopeType, scopeToExit.items, getScopeNames(), m_headerInformation.functionSignatures,
         m_headerInformation.functionNamePatterns});
    Terms const sortedTerms(sorter.getReorganizedTerms());
    m_terms = sortedTerms;

    m_scopeDetails.pop_back();
}

void CPlusPlusReorganizer::enterScope(int const scopeHeaderStart, int const openingBraceIndex) {
    m_scopeDetails.emplace_back(constructScopeDetails(scopeHeaderStart, openingBraceIndex));
}

void CPlusPlusReorganizer::exitScope(int& nextIndex, int const closingBraceIndex, int const endIndex) {
    ScopeDetail const& scopeToExit(m_scopeDetails.back());
    if (shouldReorganizeInThisScope(scopeToExit)) {
        m_terms.erase(m_terms.cbegin() + scopeToExit.openingBraceIndex + 1, m_terms.cbegin() + closingBraceIndex);

        CPlusPlusReorganizeItems const sorter(
            {m_fileType, scopeToExit.scopeType, scopeToExit.items, getScopeNames(),
             m_headerInformation.functionSignatures, m_headerInformation.functionNamePatterns});
        Terms const sortedTerms(sorter.getReorganizedTerms());
        m_terms.insert(m_terms.cbegin() + scopeToExit.openingBraceIndex + 1, sortedTerms.cbegin(), sortedTerms.cend());

        int const sizeDifference =
            static_cast<int>(sortedTerms.size()) - closingBraceIndex + scopeToExit.openingBraceIndex + 1;
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, endIndex + sizeDifference);
        nextIndex = endIndex + 1 + sizeDifference;
    } else {
        m_scopeDetails.pop_back();
        addItemIfNeeded(scopeToExit.scopeHeaderStart, endIndex);
        nextIndex = endIndex + 1;
    }
}

void CPlusPlusReorganizer::addItemIfNeeded(int const startIndex, int const endIndex) {
    if (shouldReorganizeInThisScope(m_scopeDetails.back())) {
        string const content = getFormattedContent(startIndex, endIndex);
        if (!content.empty()) {
            switch (m_purpose) {
                case Purpose::Reorganize: {
                    m_scopeDetails.back().items.emplace_back(content);
                    break;
                }
                case Purpose::GatherInformation: {
                    string functionSignature(getFunctionSignature(content));
                    if (!functionSignature.empty()) {
                        m_headerInformation.functionSignatures.emplace_back(functionSignature);
                        string functionName(getFunctionName(functionSignature));
                        if (!functionName.empty()) {
                            m_headerInformation.functionNamePatterns.emplace_back(Pattern{M(functionName), M("(")});
                            m_headerInformation.functionNamePatterns.emplace_back(Pattern{M(functionName), M("<")});
                        }
                    }
                    break;
                }
                case Purpose::Unknown:
                    break;
            }
        }
    }
}

bool CPlusPlusReorganizer::shouldReorganizeInThisScope(ScopeDetail const& scope) {
    return scope.scopeType == ScopeType::TopLevel || scope.scopeType == ScopeType::NamedNamespace ||
           scope.scopeType == ScopeType::AnonymousNamespace || scope.scopeType == ScopeType::ClassDeclaration ||
           scope.scopeType == ScopeType::EnumClass;
}

bool CPlusPlusReorganizer::shouldConnectToPreviousItem(Terms const& scopeHeaderTerms) {
    bool const isOnlyWhiteSpaceOrComment(isAllWhiteSpaceOrComment(scopeHeaderTerms));
    bool const hasInvalidKeyword = any_of(scopeHeaderTerms.cbegin(), scopeHeaderTerms.cend(), [](Term const& term) {
        return term.getTermType() == TermType::Keyword &&
               (term.getContent() == "catch" || term.getContent() == "class" || term.getContent() == "do" ||
                term.getContent() == "else" || term.getContent() == "enum" || term.getContent() == "if" ||
                term.getContent() == "namespace" || term.getContent() == "struct" || term.getContent() == "switch" ||
                term.getContent() == "while" || term.getContent() == "union");
    });
    bool const hasCommaAtTheStart = !searchPatternsAt(scopeHeaderTerms, 0, Patterns{{M(",")}}).empty();
    return isOnlyWhiteSpaceOrComment || (!hasInvalidKeyword && hasCommaAtTheStart);
}

bool CPlusPlusReorganizer::hasEndBrace(string const& content) {
    Terms const termsToCheck(getTermsFromString(content));
    Indexes const hitIndexes =
        searchBackwardsWithMatcher(termsToCheck, static_cast<int>(termsToCheck.size()) - 1, M("}"));
    return !hitIndexes.empty();
}

void CPlusPlusReorganizer::makeIsolatedCommentsStickWithNextLine(Terms& terms) {
    if (!terms.empty()) {
        int searchIndex = 0;
        Patterns const searchPatterns{{M(MatcherType::Comment), M(MatcherType::WhiteSpaceWithNewLine)}};
        bool isFound(true);
        while (isFound) {
            Indexes hitIndexes = searchForwardsForPatterns(terms, searchIndex, searchPatterns);
            isFound = !hitIndexes.empty();
            if (isFound) {
                int const firstHitIndex = hitIndexes.front();
                int const lastHitIndex = hitIndexes.back();
                if (firstHitIndex == 0 || (firstHitIndex > 0 && isWhiteSpaceWithNewLine(terms[firstHitIndex - 1]))) {
                    terms[lastHitIndex] = Term(TermType::WhiteSpace, "\n");
                }
                searchIndex = lastHitIndex + 1;
            }
        }
    }
}

void CPlusPlusReorganizer::removeStartingAndTrailingWhiteSpace(Terms& terms) {
    if (!terms.empty()) {
        int nonWhiteSpace = 0;
        for (; nonWhiteSpace < static_cast<int>(terms.size()); ++nonWhiteSpace) {
            Term const& term(terms[nonWhiteSpace]);
            if (!isWhiteSpace(term)) {
                break;
            }
        }
        terms.erase(terms.begin(), terms.begin() + nonWhiteSpace);
    }
    if (!terms.empty()) {
        int nonWhiteSpace = static_cast<int>(terms.size()) - 1;
        for (; nonWhiteSpace >= 0; --nonWhiteSpace) {
            Term const& term(terms[nonWhiteSpace]);
            if (!isWhiteSpace(term)) {
                break;
            }
        }
        terms.erase(terms.begin() + 1 + nonWhiteSpace, terms.end());
    }
}

int CPlusPlusReorganizer::getIndexAtClosingString(
    Terms const& terms, int const openingIndex, string const& openingString, string const& closingString) {
    Patterns const searchPatterns{{M(openingString)}, {M(closingString)}};
    int endIndex = openingIndex + 1;
    int numberOfOpenings = 1;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(terms, endIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
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

}  // namespace alba::CodeUtilities
