#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities::CPlusPlusUtilities {

Terms getTermsFromFile(std::string const& path);
void writeAllTerms(std::string const& path, Terms const& terms);
Terms getTermsFromString(std::string const& code);
std::string getFunctionSignature(std::string const& functionText);

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
