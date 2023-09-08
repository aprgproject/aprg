#pragma once

#include <CodeUtilities/Common/TermMatcher.hpp>

#include <vector>

namespace alba::CodeUtilities {
using Indexes = std::vector<int>;
using Pattern = std::vector<TermMatcher>;
using Patterns = std::vector<Pattern>;
}  // namespace alba::CodeUtilities
