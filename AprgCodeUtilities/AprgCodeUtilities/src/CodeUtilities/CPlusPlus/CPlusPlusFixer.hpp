#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusFixer {
public:
    CPlusPlusFixer() = default;
    void processDirectory(std::filesystem::path const& directory);
    void processFile(std::filesystem::path const& file);

private:
    void fixTerms();
    void combinePrimitiveTypes();
    void fixPostFixIncrementDecrement();
    void fixPostFixIncrementDecrement(std::string const& crementOperator);
    void fixPostFixIncrementDecrementInLine(std::string const& crementOperator);
    void fixPostFixIncrementDecrementInForLoop(std::string const& crementOperator);
    void fixConstReferenceOrder();
    void fixConstReferenceOrder(TermMatcher const& typeMatcher);
    void fixConstToConstexpr();
    void fixConstToConstexpr(TermMatcher const& typeMatcher);
    void fixNoConstPassByValue();
    void fixNoConstPassByValue(TermMatcher const& typeMatcher);
    void fixNoConstPassByValue(Patterns const& searchPatterns);
    void fixCStyleStaticCast();
    void fixCStyleStaticCast(TermMatcher const& typeMatcher);
    void findTermsAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2);
    void findTermsAndCheckForLoopAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2);
    void findTermsAndConvertToConstexpr(Patterns const& searchPatterns, int const typeIndex, int const variableIndex);
    void fixCommentsPositionOfBraces();
    std::filesystem::path m_currentFile;
    Terms m_currentTerms;
};

}  // namespace alba::CodeUtilities
