#pragma once

namespace alba::CodeUtilities {

enum class TermType {
    Aggregate,
    Attribute,
    Boolean,
    CharacterLiteral,
    CommentMultiline,
    CommentSingleLine,
    Empty,
    Identifier,
    Keyword,
    Macro,
    Number,
    Operator,
    PrimitiveType,
    StringLiteral,
    Unknown,
    WhiteSpace
};

}  // namespace alba::CodeUtilities
