#include "AlbaCombineAndGrepFiles.hpp"

#include <Common/File/AlbaFileReader.hpp>

#include <iostream>
#include <set>

using namespace std;

namespace alba {

AlbaCombineAndGrepFiles::AlbaCombineAndGrepFiles(
    string const& outputFilePath, string const& fileCondition, string const& lineCondition)
    : m_pathHandler(outputFilePath),
      m_outputFileStream(m_pathHandler.getPath()),
      m_fileEvaluator(fileCondition),
      m_lineEvaluator(lineCondition) {}

void AlbaCombineAndGrepFiles::processDirectory(string const& path) {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(path).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        processFile(filePath);
    }
}

void AlbaCombineAndGrepFiles::processFile(string const& path) {
    AlbaLocalPathHandler const filePathHandler(path);
    if (m_fileEvaluator.evaluate(filePathHandler.getFile())) {
        cout << "ProcessFile: " << path << "\n";
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

}  // namespace alba
