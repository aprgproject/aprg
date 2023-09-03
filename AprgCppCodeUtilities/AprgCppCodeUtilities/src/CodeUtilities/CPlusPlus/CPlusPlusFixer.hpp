#pragma once

#include <CodeUtilities/Common/TermMatcher.hpp>

#include <string>
#include <vector>

namespace alba::CodeUtilities::CPlusPlusFixer {

void processAprgDirectory(std::string const& aprgPath);
void processPath(std::string const& path);
void processDirectory(std::string const& path);
void processFile(std::string const& path);

Terms getTermsFromFile(std::string const& path);
void writeAllTerms(std::string const& path, Terms const& terms);
void fixTerms(Terms& terms);
void fixPostFixIncrementDecrement(Terms& terms);
void fixPostFixIncrementDecrement(Terms& terms, std::string const& crementOperator);
void fixConstReferenceOrder(Terms& terms);
void fixConstReferenceOrder(Terms& terms, TermMatcher const& typeMatcher);
void fixCStyleStaticCast(Terms& terms);
void fixCStyleStaticCast(Terms& terms, TermMatcher const& typeMatcher);
void findTermsAndSwapAt(Terms& terms, TermMatchers const& matchers, int const index1, int const index2);
void combinePrimitiveTypes(Terms& terms);

bool isCppFile(std::string const& extension);

}  // namespace alba::CodeUtilities::CPlusPlusFixer
