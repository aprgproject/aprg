#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace alba {

class AlbaCombineAndGrepFiles {
public:
    AlbaCombineAndGrepFiles(
        std::filesystem::path const& outputFilePath, std::string const& fileCondition,
        std::string const& lineCondition);

    void processDirectory(std::filesystem::path const& path);
    void processFile(std::filesystem::path const& path);

private:
    AlbaLocalPathHandler m_pathHandler;
    std::ofstream m_outputFileStream;
    AlbaGrepStringEvaluator m_fileEvaluator;
    AlbaGrepStringEvaluator m_lineEvaluator;
};

}  // namespace alba
