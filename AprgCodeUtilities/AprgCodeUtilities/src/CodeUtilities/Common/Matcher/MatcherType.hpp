#pragma once

namespace alba::CodeUtilities {

enum class MatcherType {
    Comment,
    HasNewLine,
    IdentifierWithPascalCase,
    IdentifierWithSnakeCase,
    IdentifierAndNotAScreamingSnakeCase,
    Literal,
    NotAWhiteSpace,
    WhiteSpaceWithNewLine
};

}  // namespace alba::CodeUtilities
