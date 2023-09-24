#pragma once

#include <filesystem>
#include <string>

namespace alba::CodeUtilities {
void clearFile(std::filesystem::path const& file);
void copyFile(std::string const& source, std::string const& destination);
void verifyFile(std::string const& expectedFile, std::string const& testFile);
void runFormatter(std::filesystem::path const& file);
void runDiffForTwoFiles(std::filesystem::path const& file1, std::filesystem::path const& file2);
void runFormatterInDirectory(std::filesystem::path const& directoryPath);
void runInConsole(std::string const& command);
}  // namespace alba::CodeUtilities
