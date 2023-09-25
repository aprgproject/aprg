#include "TermCreateHelpers.hpp"

using namespace std;

namespace alba::CodeUtilities {
Term createAttribute(string const& content) { return {TermType::Attribute, content}; }
Term createBoolean(string const& content) { return {TermType::Boolean, content}; }
Term createCharacterLiteral(string const& content) { return {TermType::CharacterLiteral, content}; }
Term createCommentMultiLine(string const& content) { return {TermType::CommentMultiline, content}; }
Term createCommentSingleLine(string const& content) { return {TermType::CommentSingleLine, content}; }
Term createIdentifier(string const& content) { return {TermType::Identifier, content}; }
Term createKeyword(string const& content) { return {TermType::Keyword, content}; }
Term createMacro(string const& content) { return {TermType::Macro, content}; }
Term createNumber(string const& content) { return {TermType::Number, content}; }
Term createOperator(string const& content) { return {TermType::Operator, content}; }
Term createPrimitiveType(string const& content) { return {TermType::PrimitiveType, content}; }
Term createStringLiteral(string const& content) { return {TermType::StringLiteral, content}; }
Term createUnknown(string const& content) { return {TermType::Unknown, content}; }
Term createWhiteSpace(string const& content) { return {TermType::WhiteSpace, content}; }
}  // namespace alba::CodeUtilities
