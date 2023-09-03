#pragma once

#include <CodeUtilities/Common/TermMatcher.hpp>

#include <string>
#include <vector>

namespace alba::CodeUtilities::CPlusPlusFixer {

bool isCppFile(std::string const& extension);
void processDirectory(std::string const& path);
void processFile(std::string const& path);

Terms getTermsFromFile(std::string const& path);
void writeAllTerms(std::string const& path, Terms const& terms);
void fixTerms(Terms& terms);
void fixPostFixIncrementDecrement(Terms& terms, std::string const& crementOperator);
void fixConstReferenceOrder(Terms& terms);
void findTermsAndSwapAt(Terms& terms, TermMatchers const& matchers, int const index1, int const index2);

}  // namespace alba::CodeUtilities::CPlusPlusFixer
