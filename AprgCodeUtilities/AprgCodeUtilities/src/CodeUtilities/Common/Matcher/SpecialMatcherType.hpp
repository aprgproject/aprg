#pragma once

namespace alba::CodeUtilities {

enum class SpecialMatcherType {
    Comment,
    HasNewLine,
    IdentifierWithPascalCase,
    IdentifierWithSnakeCase,
    IdentifierAndNotAScreamingSnakeCase,
    Literal,
    NotACommentNorWhiteSpace,
    WhiteSpaceWithNewLine
};

}  // namespace alba::CodeUtilities
