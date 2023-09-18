#include "AlbaCombineAndGrepFiles.hpp"

#include <Common/File/AlbaFileReader.hpp>

#include <iostream>
#include <set>

using namespace std;
using namespace std::filesystem;

namespace alba {

AlbaCombineAndGrepFiles::AlbaCombineAndGrepFiles(
    path const& outputFilePath, string const& fileCondition, string const& lineCondition)
    : m_pathHandler(outputFilePath),
      m_outputFileStream(m_pathHandler.getPath()),
      m_fileEvaluator(fileCondition),
      m_lineEvaluator(lineCondition) {}

void AlbaCombineAndGrepFiles::processFile(path const& filePath) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    if (m_fileEvaluator.evaluate(filePathHandler.getFile().string())) {
        cout << "ProcessFile: " << filePath << "\n";
        ifstream inputLogFileStream(filePathHandler.getPath());
        AlbaFileReader fileReader(inputLogFileStream);
        while (fileReader.isNotFinished()) {
            string const line(fileReader.getLineAndIgnoreWhiteSpaces());
            if (m_lineEvaluator.evaluate(line)) {
                m_outputFileStream << filePathHandler.getPath() << " ||| " << line << "\n";
            }
        }
    }
}

void AlbaCombineAndGrepFiles::processDirectory(path const& directoryPath) {
    AlbaLocalPathHandler(directoryPath)
        .findFilesAndDirectoriesUnlimitedDepth(
            [](AlbaLocalPathHandler::LocalPath const&) {},
            [&](AlbaLocalPathHandler::LocalPath const& filePath) { processFile(filePath); });
}

}  // namespace alba
