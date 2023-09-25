#pragma once

#include <filesystem>

namespace alba {
void clearContentsOfFile(std::filesystem::path const& filePath);
void createEmptyFile(std::filesystem::path const& filePath);
}  // namespace alba
