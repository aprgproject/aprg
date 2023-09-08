#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/Term.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities {

class CPlusPlusReorganizer {
public:
    enum class Purpose { Unknown, Reorganize, GatherInformation };

    struct ScopeDetail {
        int scopeHeaderStart;
        int openingBraceIndex;
        int scopeEnd;
        ScopeType scopeType;
        std::string name;
        stringHelper::strings items;
    };

    struct HeaderInformation {
        stringHelper::strings signatures;
    };

    CPlusPlusReorganizer();
    void processDirectory(std::string const& directory);
    void processHeaderAndImplementationFile(std::string const& headerFile, std::string const& implementationFile);
    void reorganizeFile(std::string const& file);

private:
    [[nodiscard]] static bool shouldReorganizeInThisScope(ScopeDetail const& scope);
    [[nodiscard]] static bool shouldConnectToPreviousItem(Terms const& scopeHeaderTerms);
    [[nodiscard]] static bool hasEndBrace(std::string const& content);
    static int getIndexAtClosingString(
        Terms const& terms, int const openingIndex, std::string const& openingString, std::string const& closingString);
    [[nodiscard]] int getIndexAtSameLineComment(int const index) const;
    [[nodiscard]] ScopeDetail constructScopeDetails(int const scopeHeaderStart, int const openingBraceIndex) const;
    [[nodiscard]] stringHelper::strings getScopeNames() const;
    [[nodiscard]] stringHelper::strings getSavedSignatures() const;
    [[nodiscard]] std::string getContents(int const start, int const end) const;
    void gatherInformationFromFile(std::string const& file);
    void processTerms();
    void processMacro(int& lastProcessedIndex, int const macroStartIndex);
    void processSemiColon(int& lastProcessedIndex, int const endIndex);
    void processOpeningAndClosingBrace(
        int& lastProcessedIndex, int const openingBraceIndex, int const closingBraceSemiColonIndex);
    void processOpeningBrace(int& lastProcessedIndex, int const openingBraceIndex);
    void processClosingBrace(
        int& lastProcessedIndex, int const closingBraceIndex, int const closingBraceSemiColonIndex);
    void processRecognizedItem(int& lastProcessedIndex, int const recognizedItemEndIndex);
    void enterScope(int const scopeHeaderStart, int const openingBraceIndex);
    void exitScope(int& lastProcessedIndex, int const closingBraceIndex, int const endIndex);
    void addItemIfNeeded(int const startIndex, int const endIndex);
    Purpose m_purpose{Purpose::Unknown};
    std::vector<ScopeDetail> m_scopeDetails;
    HeaderInformation m_headerInformation;
    Terms m_terms;
};

}  // namespace alba::CodeUtilities
