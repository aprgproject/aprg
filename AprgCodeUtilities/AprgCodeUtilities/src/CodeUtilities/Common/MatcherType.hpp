#pragma once

namespace alba::CodeUtilities {

enum class MatcherType {
    NotAWhiteSpace,
    IdentifierWithPascalCase,
    IdentifierWithSnakeCase,
    IdentifierAndNotAScreamingSnakeCase,
    Comment
};

}  // namespace alba::CodeUtilities
