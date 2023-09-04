#pragma once

namespace alba::CodeUtilities {

enum class TermType {
    Aggregate,
    Boolean,
    CharacterLiteral,
    CommentMultiline,
    CommentSingleLine,
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
