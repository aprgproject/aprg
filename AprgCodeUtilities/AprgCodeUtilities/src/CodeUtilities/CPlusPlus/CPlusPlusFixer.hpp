#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

namespace alba::CodeUtilities {

class CPlusPlusFixer {
public:
    CPlusPlusFixer() = default;
    void processPath(std::string const& path);
    void processDirectory(std::string const& directory);
    void processFile(std::string const& file);

private:
    void fixTerms();
    void fixPostFixIncrementDecrement();
    void fixPostFixIncrementDecrement(std::string const& crementOperator);
    void fixPostFixIncrementDecrementInLine(std::string const& crementOperator);
    void fixPostFixIncrementDecrementInForLoop(std::string const& crementOperator);
    void fixConstReferenceOrder();
    void fixConstReferenceOrder(TermMatcher const& typeMatcher);
    void fixCStyleStaticCast();
    void fixCStyleStaticCast(TermMatcher const& typeMatcher);
    void fixNoConstPassByValue();
    void fixNoConstPassByValue(TermMatcher const& typeMatcher);
    void fixNoConstPassByValue(Patterns const& searchPatterns);
    void fixCommentsPositionOfBraces();
    void findTermsAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2);
    void findTermsAndCheckForLoopAndSwapAt(Patterns const& searchPatterns, int const index1, int const index2);
    void combinePrimitiveTypes();

private:
    std::string m_currentFile;
    Terms m_currentTerms;
};

}  // namespace alba::CodeUtilities
