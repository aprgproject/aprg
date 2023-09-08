#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities::CPlusPlusUtilities {
bool isCppFileExtension(std::string const& extension);
bool isHeaderFileExtension(std::string const& extension);
bool isImplementationFileExtension(std::string const& extension);
Terms getTermsFromFile(std::string const& path);
Terms getTermsFromString(std::string const& code);
std::string getFunctionSignature(std::string const& functionText);
std::string getTextWithoutCommentsWithNewLine(Terms const& terms);
void writeAllTerms(std::string const& path, Terms const& terms);
}  // namespace alba::CodeUtilities::CPlusPlusUtilities
