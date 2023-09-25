#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusFixer {
public:
    CPlusPlusFixer() = default;
    void processDirectory(std::filesystem::path const& directory);
    void processFile(std::filesystem::path const& file);

private:
    stringHelper::strings getPrintItems(int& printfEnd, int const printStringIndex) const;
    void fixTerms();
    void combinePrimitiveTypes();
    void fixPostFixIncrementDecrement();
    void fixPostFixIncrementDecrement(std::string const& crementOperator);
    void fixPostFixIncrementDecrementInLine(std::string const& crementOperator);
    void fixPostFixIncrementDecrementInForLoop(std::string const& crementOperator);
    void fixConstReferenceOrder();
    void fixConstReferenceOrder(Matcher const& typeMatcher);
    void fixConstToConstexpr();
    void fixNoConstPassByValue();
    void fixNoConstPassByValue(Matcher const& typeMatcher);
    void fixNoConstPassByValue(Patterns const& searchPatterns);
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

    static Terms getNewPrintTerms(std::string const& printString, stringHelper::strings const& printItems);
    std::filesystem::path m_currentFile;
    Terms m_terms;
};

}  // namespace alba::CodeUtilities
