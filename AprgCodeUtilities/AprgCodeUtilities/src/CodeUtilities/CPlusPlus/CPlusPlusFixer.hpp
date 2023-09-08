#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

namespace alba::CodeUtilities::CPlusPlusFixer {

void processAprgDirectory(std::string const& aprgPath);
void processPath(std::string const& path);
void processDirectory(std::string const& path);
void processFile(std::string const& path);

void fixTerms(Terms& terms);
void fixPostFixIncrementDecrement(Terms& terms);
void fixPostFixIncrementDecrement(Terms& terms, std::string const& crementOperator);
void fixPostFixIncrementDecrementInLine(Terms& terms, std::string const& crementOperator);
void fixPostFixIncrementDecrementInForLoop(Terms& terms, std::string const& crementOperator);
void fixConstReferenceOrder(Terms& terms);
void fixConstReferenceOrder(Terms& terms, TermMatcher const& typeMatcher);
void fixCStyleStaticCast(Terms& terms);
void fixCStyleStaticCast(Terms& terms, TermMatcher const& typeMatcher);
void fixNoConstPassByValue(Terms& terms);
void fixNoConstPassByValue(Terms& terms, TermMatcher const& typeMatcher);
void fixNoConstPassByValue(Terms& terms, Patterns const& searchPatterns);
void fixCommentsPositionOfBraces(Terms& terms);
void findTermsAndSwapAt(Terms& terms, Patterns const& searchPatterns, int const index1, int const index2);
void findTermsAndCheckForLoopAndSwapAt(
    Terms& terms, Patterns const& searchPatterns, int const index1, int const index2);
void combinePrimitiveTypes(Terms& terms);

}  // namespace alba::CodeUtilities::CPlusPlusFixer
