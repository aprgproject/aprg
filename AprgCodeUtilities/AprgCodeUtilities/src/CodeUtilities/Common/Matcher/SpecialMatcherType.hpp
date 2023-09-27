#pragma once

namespace alba::CodeUtilities {

enum class SpecialMatcherType {
    Comment,
    HasNewLine,
    IdentifierAndNotAScreamingSnakeCase,
    IdentifierStartsWithLetterUnderscore,
    IdentifierWithPascalCase,
    IdentifierWithSnakeCase,
    Literal,
    NotACommentNorWhiteSpace,
    WhiteSpaceWithNewLine
};

}  // namespace alba::CodeUtilities
