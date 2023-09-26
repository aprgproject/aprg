#pragma once

namespace alba::CodeUtilities {

enum class SpecialMatcherType {
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
