#include "CombineAndGrep.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;

namespace alba {

CombineAndGrep::CombineAndGrep(string const& outputFilePath, string const& grepString)
    : m_outputFileStream(AlbaLocalPathHandler(outputFilePath).getFullPath()), m_grepString(grepString) {}

void CombineAndGrep::processDirectory(string const& inputDirectoryPath) {
    AlbaLocalPathHandler const inputDirectoryPathHandler(inputDirectoryPath);
    cout << "processDirectory() inputDirectoryPath:" << inputDirectoryPath << "\n";
    ListOfPaths files;
    ListOfPaths directories;
    inputDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (string const& file : files) {
        processFile(file);
    }
}

void CombineAndGrep::processFile(string const& inputFilePath) {
    AlbaLocalPathHandler const inputFilePathHandler(inputFilePath);
    cout << "processFile() inputFilePath:" << inputFilePath << "\n";
    ifstream inputFileStream(inputFilePathHandler.getFullPath());
    AlbaFileReader fileToRead(inputFileStream);
    while (fileToRead.isNotFinished()) {
        string const lineFromFile(fileToRead.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(lineFromFile, m_grepString)) {
            m_outputFileStream << lineFromFile << "\n";
        }
    }
}

}  // namespace alba
