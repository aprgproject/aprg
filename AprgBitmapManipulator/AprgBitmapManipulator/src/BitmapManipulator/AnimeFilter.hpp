#pragma once

#include <BitmapManipulator/BitmapFilters.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <filesystem>
#include <string>

namespace alba::AprgBitmap {

void animize(std::filesystem::path const& inputFile, std::filesystem::path const& outputFile);
void doStuffsAfterSteps(AlbaLocalTimer& localTimer, std::string const& description);

void doStuffsAfterSteps(
    AlbaLocalTimer& localTimer, BitmapFilters& bitmapFilter, BitmapSnippet const& snippet,
    std::filesystem::path const& inputFilePath, std::string const& description);

std::filesystem::path getNewFilePath(
    std::filesystem::path const& inputFilePath, int const step, std::string const& description);

}  // namespace alba::AprgBitmap
