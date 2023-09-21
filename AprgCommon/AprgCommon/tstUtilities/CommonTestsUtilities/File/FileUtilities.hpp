#pragma once

#include <filesystem>

using namespace std::filesystem;

namespace alba {
void clearContentsOfFile(path const& filePath);
void createEmptyFile(path const& filePath);
}  // namespace alba
