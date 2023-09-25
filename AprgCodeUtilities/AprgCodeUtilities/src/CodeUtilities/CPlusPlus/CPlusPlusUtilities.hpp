#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/Term/Term.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <filesystem>

namespace alba::CodeUtilities::CPlusPlusUtilities {
void writeAllTerms(std::filesystem::path const& path, Terms const& terms);
CppFileType getFileType(std::string const& extension);
Terms getTermsFromFile(std::filesystem::path const& path);
Terms getTermsFromString(std::string const& code);
std::string getFunctionSignature(std::string const& functionText);
std::string getFunctionName(std::string const& functionSignature);
std::string getTextWithoutCommentsWithNewLine(Terms const& terms);
bool isCppFileExtension(std::string const& extension);
bool isHeaderFileExtension(std::string const& extension);
bool isImplementationFileExtension(std::string const& extension);
}  // namespace alba::CodeUtilities::CPlusPlusUtilities
