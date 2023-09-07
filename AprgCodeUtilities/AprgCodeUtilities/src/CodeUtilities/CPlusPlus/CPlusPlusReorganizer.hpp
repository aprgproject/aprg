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
        int scopeHeaderDivider;
        int scopeEnd;
        ScopeType scopeType;
        std::string name;
        stringHelper::strings items;
    };

    CPlusPlusReorganizer();

    void processHeaderAndImplementationFile(std::string const& headerFile, std::string const& implementationFile);
    void reorganizeFile(std::string const& file);

private:
    void gatherInformationFromFile(std::string const& file);
    void processFile(std::string const& file);
    void processTerms();
    void processMacro(int& termIndex, int const macroStartIndex);
    void processSemiColon(int& termIndex, int const semiColonIndex);
    void processOpeningBrace(int& termIndex, int const scopeHeaderDivider);
    void processClosingBrace(int& termIndex, int const scopeEndFirst, int const scopeEndSecond);
    void processRecognizedItem(int& termIndex, int const recognizedItemEndIndex);
    void enterScope(int const scopeHeaderStart, int const scopeHeaderDivider);
    void exitScope(int& termIndex, int const scopeEndFirst, int const scopeEndSecond);
    void addItemIfNeeded(int const startIndex, int const endIndex);
    void addItemIfNeeded(std::string const& content);
    [[nodiscard]] ScopeDetail getCurrentScope() const;
    [[nodiscard]] ScopeDetail constructScopeDetails(int const scopeHeaderStart, int const scopeHeaderDivider) const;
    [[nodiscard]] stringHelper::strings getScopeNames() const;
    [[nodiscard]] std::string getContents(int const start, int const end) const;
    Purpose m_purpose{Purpose::Unknown};
    std::vector<ScopeDetail> m_scopeDetails;
    stringHelper::strings m_informationItems;
    Terms m_terms;
};

}  // namespace alba::CodeUtilities
