#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace alba {

struct CombineAndGrep {
    CombineAndGrep(std::filesystem::path const& outputFilePath, std::string const& grepString);
    void processDirectory(std::filesystem::path const& inputDirectoryPath);
    void processFile(std::filesystem::path const& inputFilePath);

private:
    std::ofstream m_outputFileStream;
    std::string m_grepString;
};

}  // namespace alba
