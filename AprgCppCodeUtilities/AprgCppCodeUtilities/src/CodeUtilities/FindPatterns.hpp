#pragma once

#include <CodeUtilities/IndexTypes.hpp>
#include <CodeUtilities/TermMatcher.hpp>

#include <string>

namespace alba::CodeUtilities {

IndexOptional findFirstPatternIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& termMatchers, int const startIndex = 0);

Indexes findPatternsIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& termMatchers, int const startIndex = 0);

}  // namespace alba::CodeUtilities
