#pragma once

namespace alba::CodeUtilities {

enum class SpecialMatcherType {
    Comment,
    HasNewLine,
    IdentifierWithPascalCase,
    IdentifierWithSnakeCase,
    IdentifierAndNotAScreamingSnakeCase,
    Literal,
    WhiteSpaceWithNewLine
};

}  // namespace alba::CodeUtilities
