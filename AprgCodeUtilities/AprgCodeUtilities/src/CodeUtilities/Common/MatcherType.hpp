#pragma once

namespace alba::CodeUtilities {

enum class MatcherType {
    Comment,
    HasNewLine,
    IdentifierWithPascalCase,
    IdentifierWithSnakeCase,
    IdentifierAndNotAScreamingSnakeCase,
    NotAWhiteSpace
};

}  // namespace alba::CodeUtilities
