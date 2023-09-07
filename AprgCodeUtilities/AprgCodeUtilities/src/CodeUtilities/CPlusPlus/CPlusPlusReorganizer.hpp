#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities {

class CPlusPlusReorganizer {
public:
    enum class Purpose { Unknown, Reorganize, GatherInformation };
    enum class ScopeType { Unknown, TopLevel, ClassDeclaration, Namespace };
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
    void processOpeningAndClosingBrace(int& termIndex, int const openingBraceIndex, int const endIndex);
    void processOpeningBrace(int& termIndex, int const openingBraceIndex);
    void processClosingBrace(int& termIndex, int const closingBraceIndex, int const possibleSemiColonIndex);
    void processRecognizedItem(int& termIndex, int const recognizedItemEndIndex);
    void enterScope(int const scopeHeaderStart, int const openingBraceIndex);
    void exitScope(int& termIndex, int const closingBraceIndex, int const possibleSemiColonIndex);
    void addItemIfNeeded(int const startIndex, int const endIndex);
    void addItemIfNeeded(std::string const& content);
    static bool shouldConnectToPreviousItem(Terms const& scopeHeaderTerms);
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
