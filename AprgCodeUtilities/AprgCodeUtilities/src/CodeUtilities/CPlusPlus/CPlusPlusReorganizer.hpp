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
    void gatherInformationFromFile(std::string const& file);
    void processTerms();
    void processMacro(int& termIndex, int const macroStartIndex);
    void processSemiColon(int& termIndex, int const endIndex);
    void processOpeningAndClosingBrace(
        int& termIndex, int const openingBraceIndex, int const closingBraceSemiColonIndex);
    void processOpeningBrace(int& termIndex, int const openingBraceIndex);
    void processClosingBrace(int& termIndex, int const closingBraceIndex, int const closingBraceSemiColonIndex);
    void processRecognizedItem(int& termIndex, int const recognizedItemEndIndex);
    void enterScope(int const scopeHeaderStart, int const openingBraceIndex);
    void exitScope(int& termIndex, int const closingBraceIndex, int const endIndex);
    [[nodiscard]] static bool shouldReorganizeInThisScope(ScopeDetail const& scope);
    void addItemIfNeeded(int const startIndex, int const endIndex);
    [[nodiscard]] int getIndexAtSameLineComment(int const index) const;
    static int getIndexAtClosing(
        Terms const& terms, int const openingIndex, std::string const& openingString, std::string const& closingString);
    [[nodiscard]] static bool shouldConnectToPreviousItem(Terms const& scopeHeaderTerms);
    [[nodiscard]] ScopeDetail constructScopeDetails(int const scopeHeaderStart, int const openingBraceIndex) const;
    [[nodiscard]] stringHelper::strings getScopeNames() const;
    [[nodiscard]] stringHelper::strings getSavedSignatures() const;
    [[nodiscard]] std::string getContents(int const start, int const end) const;
    Purpose m_purpose{Purpose::Unknown};
    std::vector<ScopeDetail> m_scopeDetails;
    HeaderInformation m_headerInformation;
    Terms m_terms;
};

}  // namespace alba::CodeUtilities
