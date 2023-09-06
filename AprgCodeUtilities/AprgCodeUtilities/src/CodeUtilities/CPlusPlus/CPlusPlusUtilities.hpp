#pragma once

#include <CodeUtilities/Common/Term.hpp>

#include <string>

namespace alba::CodeUtilities::CPlusPlusUtilities {

Terms getTermsFromFile(std::string const& path);
Terms getTermsFromString(std::string const& code);
void writeAllTerms(std::string const& path, Terms const& terms);

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
