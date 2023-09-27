#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/CommonTypes.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusFinder {
public:
    struct ScopeDetail {
        int scopeHeaderStart;
        int openingBraceIndex;
        int scopeEnd;
        ScopeType scopeType;
        std::string name;
    };

    CPlusPlusFinder() = default;
    void processDirectory(std::filesystem::path const& directory);
    void processFile(std::filesystem::path const& file);

private:
    [[nodiscard]] ScopeDetail constructScopeDetails(int const scopeHeaderStart, int const openingBraceIndex) const;
    void findTerms();
    void findRegardlessOfScope();
    void findBasedOnScopes();
    void findInitializationOutsideClass();
    void findByCheckingScopes();
    void processOpeningBrace(int& nextIndex, int const openingBraceIndex);
    void processClosingBrace(int& nextIndex, int const closingBraceIndex);
    void enterAndSetTopLevelScope();
    void exitTopLevelScope();
    void enterScope(int const scopeHeaderStart, int const openingBraceIndex);
    void exitScope();
    void findOnScopeLoop(int const startIndex, int const endIndex);
    void findItemsToCtadFix(int const startIndex, int const endIndex);
    void findTerms(Patterns const& searchPatterns);
    ScopeDetail& getCurrentScope();
    std::filesystem::path m_currentFile;
    Terms m_terms;
    std::vector<ScopeDetail> m_scopeDetails;
};

}  // namespace alba::CodeUtilities
