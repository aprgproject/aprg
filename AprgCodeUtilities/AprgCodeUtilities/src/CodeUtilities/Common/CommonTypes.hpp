#pragma once

#include <CodeUtilities/Common/Matcher/Matcher.hpp>

#include <vector>

namespace alba::CodeUtilities {
using Indexes = std::vector<int>;
using Pattern = std::vector<Matcher>;
using Patterns = std::vector<Pattern>;
}  // namespace alba::CodeUtilities
