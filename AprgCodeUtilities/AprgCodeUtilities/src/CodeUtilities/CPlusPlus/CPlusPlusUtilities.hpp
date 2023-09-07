#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities::CPlusPlusUtilities {

Terms getTermsFromFile(std::string const& path);
void writeAllTerms(std::string const& path, Terms const& terms);
Terms getTermsFromString(std::string const& code);
std::string getFunctionSignature(std::string const& functionText);
bool isCppFile(std::string const& extension);
bool isHeaderFile(std::string const& extension);
bool isImplementationFile(std::string const& extension);

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
