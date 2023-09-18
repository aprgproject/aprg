#include "CopyGoogleTemplates.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <fstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

void CopyGoogleTemplates::copyTemplatesForOneRound(
    string const& destinationPath, StringPairs const& replacePairs) const {
    AlbaLocalPathHandler localPathHandler(m_googleTemplatesPath);
    ListOfPaths files;
    ListOfPaths directories;
    localPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& originalFilePath : files) {
        AlbaLocalPathHandler originalFilePathHandler(originalFilePath);
        string newFile(originalFilePathHandler.getFile());
        for (auto const& replacePair : replacePairs) {
            replaceAllAndReturnIfFound(newFile, replacePair.first, replacePair.second);
        }
        if (!isStringFoundCaseSensitive(newFile, "SampleProblem")) {
            string newFilePath(destinationPath);
            newFilePath += "/";
            newFilePath += newFile;
            AlbaLocalPathHandler newFilePathHandler(newFilePath);
            newFilePathHandler.createDirectoriesForNonExisitingDirectories();
            replaceStringWithStringOnFile(originalFilePath, newFilePathHandler.getPath(), replacePairs);
        }
    }
}

void CopyGoogleTemplates::replaceStringWithStringOnFile(
    string const& inputFilePath, string const& outputFilePath, StringPairs const& replacePairs) {
    AlbaLocalPathHandler outputFilePathHandler(outputFilePath);
    outputFilePathHandler.createDirectoriesForNonExisitingDirectories();
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    if (inputFile.is_open()) {
        AlbaFileReader inputFileReader(inputFile);
        while (inputFileReader.isNotFinished()) {
            string line(inputFileReader.getLine());
            for (auto const& replacePair : replacePairs) {
                replaceAllAndReturnIfFound(line, replacePair.first, replacePair.second);
            }
            outputFile << line << "\n";
        }
    }
}

}  // namespace alba
