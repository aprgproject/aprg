#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusFixer {
public:
    struct ScopeDetail {
        int scopeHeaderStart;
        int openingBraceIndex;
        int scopeEnd;
        ScopeType scopeType;
        std::string name;
    };

    CPlusPlusFixer() = default;
    void processDirectory(std::filesystem::path const& directory);
    void processFile(std::filesystem::path const& file);

private:
    [[nodiscard]] ScopeDetail constructScopeDetails(int const scopeHeaderStart, int const openingBraceIndex) const;
    [[nodiscard]] stringHelper::strings getPrintItems(int& printfEnd, int const printStringIndex) const;
    void fixTerms();
    void fixRegardlessOfScope();
    void fixBasedOnScopes();
    void combinePrimitiveTypes();
    void fixPostFixIncrementDecrement();
    void fixPostFixIncrementDecrementInLine();
    void fixPostFixIncrementDecrementInForLoop();
    void fixConstReferenceOrder();
    void fixConstToConstexpr();
    void fixNoConstPassByValue();
    void fixNoConstPassByValue(Patterns const& searchPatterns);
    void fixNoExceptOnMoveConstructor();
    void fixNoExceptOnMoveAssignment();
    void fixGTestNames();
    void fixCStylePrintf();
    void fixCStylePrintf(Patterns const& searchPatterns);
    void fixCStylePrintf(int const printfStart, int const printStringIndex);
    void fixCommentsPositionOfBraces();
    void fixCStyleStaticCast();
    void fixCStyleStaticCast(Matcher const& typeMatcher);
    void findTermsAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2);
    void findTermsAndCheckForLoopAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2);

    void findTermsAndConvertToConstexpr(
        Patterns const& searchPatterns, int const typeIndex, int const constIndex, int const openingParenthesisIndex,
        int const closingParenthesisIndex);

    void fixByCheckingScopes();
    void processOpeningBrace(int& nextIndex, int const openingBraceIndex);
    void processClosingBrace(int& nextIndex, int const closingBraceIndex);
    void enterAndSetTopLevelScope();
    void exitTopLevelScope();
    void enterScope(int const scopeHeaderStart, int const openingBraceIndex);
    void exitScope();
    void fixOnScopeLoop(int const startIndex, int const endIndex);
    void fixConstexprToInlineConstExpr(int const startIndex, int const endIndex);
    ScopeDetail& getCurrentScope();
    [[nodiscard]] static std::string getCorrectedGTestName(std::string const& testName);
    static Terms getNewPrintTerms(std::string const& printString, stringHelper::strings const& printItems);
    std::filesystem::path m_currentFile;
    Terms m_terms;
    std::vector<ScopeDetail> m_scopeDetails;
};

}  // namespace alba::CodeUtilities
