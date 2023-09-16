#pragma once

#include <string_view>

namespace alba {
void clearContentsOfFile(std::string_view const path);
void createEmptyFile(std::string_view const path);
}  // namespace alba
