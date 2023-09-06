#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <Common/Debug/AlbaDebug.hpp>

#include <string>
#include <vector>

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
        std::string scopeHeaderCode;
        std::string name;
        std::vector<std::string> items;
        friend ALBA_DBG_CLASS_OUTPUT_OPERATOR_DEFINITION(
            ScopeDetail const& object, "(scopeHeaderStart:" << object.scopeHeaderStart
                                                            << ",scopeHeaderDivider:" << object.scopeHeaderDivider
                                                            << ",scopeEnd:" << object.scopeEnd << ")");
    };

    CPlusPlusReorganizer();

    void processHeaderAndImplementationFile(std::string const& headerFile, std::string const& implementationFile);
    void processHeaderFile(std::string const& headerFile);
    void processImplementationFile(std::string const& implementationFile);

private:
    void processFile(std::string const& headerFile);
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
    [[nodiscard]] std::string getContents(int const start, int const end) const;
    [[nodiscard]] bool isInClassDeclaration() const;
    [[nodiscard]] bool isToReorganize() const;
    Purpose m_purpose{Purpose::Unknown};
    std::vector<ScopeDetail> m_scopeDetails;
    Terms m_terms;
};

}  // namespace alba::CodeUtilities
