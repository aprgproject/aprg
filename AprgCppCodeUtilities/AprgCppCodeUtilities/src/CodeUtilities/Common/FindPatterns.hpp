#pragma once

#include <CodeUtilities/Common/TermMatcher.hpp>

#include <string>

namespace alba::CodeUtilities {

using PatternIndexes = std::vector<int>;

PatternIndexes findFirstPatternIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& matchers, int const startIndex = 0);

}  // namespace alba::CodeUtilities
