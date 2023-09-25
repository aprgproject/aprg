#pragma once

#include <CodeUtilities/Common/Term/Term.hpp>

namespace alba::CodeUtilities {
Term createAttribute(std::string const& content);
Term createBoolean(std::string const& content);
Term createCharacterLiteral(std::string const& content);
Term createCommentMultiLine(std::string const& content);
Term createCommentSingleLine(std::string const& content);
Term createIdentifier(std::string const& content);
Term createKeyword(std::string const& content);
Term createMacro(std::string const& content);
Term createNumber(std::string const& content);
Term createOperator(std::string const& content);
Term createPrimitiveType(std::string const& content);
Term createStringLiteral(std::string const& content);
Term createUnknown(std::string const& content);
Term createWhiteSpace(std::string const& content);
}  // namespace alba::CodeUtilities
