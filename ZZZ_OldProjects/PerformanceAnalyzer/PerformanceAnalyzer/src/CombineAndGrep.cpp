#include "CombineAndGrep.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace alba {

CombineAndGrep::CombineAndGrep(path const& outputFilePath, string const& grepString)
    : m_outputFileStream(AlbaLocalPathHandler(outputFilePath).getPath()), m_grepString(grepString) {}

CombineAndGrep::CombineAndGrep(path const& outputFilePath, string&& grepString)
    : m_outputFileStream(AlbaLocalPathHandler(outputFilePath).getPath()), m_grepString(grepString) {}

void CombineAndGrep::processDirectory(path const& inputDirectoryPath) {
    AlbaLocalPathHandler const inputDirectoryPathHandler(inputDirectoryPath);
    cout << "processDirectory() inputDirectoryPath:" << inputDirectoryPath << "\n";
    inputDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) { processFile(filePath); });
}

void CombineAndGrep::processFile(path const& inputFilePath) {
    AlbaLocalPathHandler const inputFilePathHandler(inputFilePath);
    cout << "processFile() inputFilePath:" << inputFilePath << "\n";
    ifstream inputFileStream(inputFilePathHandler.getPath());
    AlbaFileReader fileToRead(inputFileStream);
    while (fileToRead.isNotFinished()) {
        string const lineFromFile(fileToRead.getLineAndIgnoreWhiteSpaces());
        if (stringHelper::isStringFoundNotCaseSensitive(lineFromFile, m_grepString)) {
            m_outputFileStream << lineFromFile << "\n";
        }
    }
}

}  // namespace alba
