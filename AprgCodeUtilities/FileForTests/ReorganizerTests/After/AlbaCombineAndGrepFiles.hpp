#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <filesystem>
#include <fstream>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <string>

namespace alba {

class AlbaCombineAndGrepFiles {
public:
AlbaCombineAndGrepFiles(
        std::filesystem::path const& outputFilePath, std::string const& fileCondition,
        std::string const& lineCondition);

void processDirectory(std::filesystem::path const& directoryPath);
void processFile(std::filesystem::path const& filePath);

private:
AlbaLocalPathHandler m_pathHandler;
std::ofstream m_outputFileStream;
AlbaGrepStringEvaluator m_fileEvaluator;
AlbaGrepStringEvaluator m_lineEvaluator;

};

}  // namespace alba
