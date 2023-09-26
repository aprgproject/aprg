#include "StepHandler.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <FileExtractor/AprgFileExtractor.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <ProcessFiles/CropFile/AlbaCropFile.hpp>
#include <ProcessFiles/GrepFile/AlbaGrepFile.hpp>
#include <WcdmaToolsBackend/BtsLogSorter.hpp>

#include <fstream>
#include <iostream>
#include <string>

namespace alba {
namespace ProgressCounters {
extern int grepProcessProgress;
extern int cropProcessProgress;
extern int numberOfStepsEnabled;
extern void resetProgressCounters();
}  // namespace ProgressCounters
}  // namespace alba

using namespace alba;
using namespace std;

namespace wcdmaToolsGui {

StepHandler::StepHandler() {}

void StepHandler::execute(WcdmaToolsConfiguration const& configuration) const {
    AlbaLocalPathHandler currentPathHandler(configuration.inputFileOrDirectory);
    ProgressCounters::resetProgressCounters();
    ProgressCounters::numberOfStepsEnabled = configuration.isExtractStepOn + configuration.isCombineAndSortStepOn +
                                             configuration.isGrepStepOn + configuration.isCropStepOn;
    for (int step = 1; step < 5; step++) {
        if (!currentPathHandler.doesExist()) {
            cout << currentPathHandler.getPath() << " is not found in local system\n";
            return;
        }
        if (1 == step && configuration.isExtractStepOn) {
            currentPathHandler.input(executeExtractStep(configuration, currentPathHandler.getPath().string()));
        } else if (2 == step && configuration.isCombineAndSortStepOn) {
            currentPathHandler.input(executeCombineAndSortStep(configuration, currentPathHandler.getPath().string()));
        } else if (3 == step && configuration.isGrepStepOn) {
            currentPathHandler.input(executeGrepStep(configuration, currentPathHandler.getPath().string()));
        } else if (4 == step && configuration.isCropStepOn) {
            currentPathHandler.input(executeCropStep(configuration, currentPathHandler.getPath().string()));
        }
    }
}

string StepHandler::executeExtractStep(WcdmaToolsConfiguration const& configuration, string const& inputPath) const {
    cout << " (Extract) start | Input path: " << inputPath << "\n";
    AlbaLocalPathHandler tempFileFor7zPathHandler(getTempFileFor7zBasedOnLogSorter(configuration));
    tempFileFor7zPathHandler.createDirectoriesAndIsSuccessful();
    cout << " (Extract) tempFileFor7z: " << tempFileFor7zPathHandler.getPath() << "\n";
    AprgFileExtractor fileExtractor(
        configuration.extractGrepCondition, configuration.locationOf7zExecutable, tempFileFor7zPathHandler.getPath());
    AlbaLocalPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    cout << " (Extract) Extracting: " << pathHandler.getPath() << "\n";
    if (pathHandler.isExistingDirectory()) {
        fileExtractor.extractAllRelevantFiles(pathHandler.getPath());
    } else if (fileExtractor.isRecognizedCompressedFile(pathHandler.getExtension().string())) {
        fileExtractor.extractAllRelevantFiles(pathHandler.getPath());
        pathHandler.input(pathHandler.getDirectory() / pathHandler.getFilenameOnly());
        outputPath = pathHandler.getPath().string();
    } else {
        cout << "Extraction step did not proceed. Current path: " << pathHandler.getPath() << "\n";
    }
    cout << " (Extract) done | Output path: " << outputPath << "\n";
    return outputPath;
}

string StepHandler::executeCombineAndSortStep(
    WcdmaToolsConfiguration const& configuration, string const& inputPath) const {
    cout << " (CombineAndSort) start | Input path: " << inputPath << "\n";
    AlbaLocalPathHandler pathHandler(inputPath);
    string outputPath(inputPath);
    if (pathHandler.isExistingDirectory()) {
        wcdmaToolsBackend::BtsLogSorterConfiguration sorterConfiguration(configuration.btsLogSorterConfiguration);
        sorterConfiguration.m_isFilterGrepOn = configuration.isFilterSubStepOn;
        sorterConfiguration.m_acceptedFilesGrepCondition = configuration.acceptedFilesGrepCondition;
        sorterConfiguration.m_filterGrepCondition = configuration.filterGrepCondition;
        wcdmaToolsBackend::BtsLogSorter btsLogSorter(sorterConfiguration);
        btsLogSorter.processDirectory(pathHandler.getDirectory().string());
        pathHandler.moveUpADirectory();
        pathHandler.input(pathHandler.getDirectory() / configuration.getSortedFileName());
        outputPath = pathHandler.getPath().string();
        btsLogSorter.saveLogsToOutputFile(outputPath);
    } else {
        cout << "Combine and sort step did not proceed. Current path: " << pathHandler.getPath() << "\n";
    }
    cout << " (CombineAndSort) done | Output path: " << inputPath << "\n";
    return outputPath;
}

string StepHandler::executeGrepStep(WcdmaToolsConfiguration const& configuration, string const& inputPath) const {
    cout << " (Grep) start | Input path: " << inputPath << "\n";
    AlbaLocalPathHandler inputPathHandler(inputPath);
    string outputPath(inputPathHandler.getPath().string());
    AlbaGrepFile::UpdateFunctionWithPercentage grepUpdateFunction = [&](double percentage) -> void {
        ProgressCounters::grepProcessProgress = percentage;
    };
    AlbaGrepFile grepFile(configuration.getGrepCondition(), grepUpdateFunction);
    AlbaGrepStringEvaluator& evaluator(grepFile.getGrepEvaluator());
    if (evaluator.isInvalid()) {
        cout << "Grep condition is invalid. Grep condition: " << configuration.getGrepCondition()
             << " Error message: " << evaluator.getErrorMessage() << "\n";
    } else if (inputPathHandler.isExistingFile()) {
        AlbaLocalPathHandler outputPathHandler(inputPathHandler.getDirectory() / configuration.getGrepFileName());
        grepFile.processFile(inputPathHandler.getPath(), outputPathHandler.getPath());
        if (grepFile.isOutputFileWritten()) {
            outputPath = outputPathHandler.getPath().string();
        }
    } else {
        cout << "Grep step did not proceed. Current path: " << inputPathHandler.getPath() << "\n";
    }
    cout << " (Grep) done | Output path: " << outputPath << "\n";
    return outputPath;
}

string StepHandler::executeCropStep(WcdmaToolsConfiguration const& configuration, string const& inputPath) const {
    cout << " (Crop) start | Input path: " << inputPath << "\n";
    AlbaLocalPathHandler inputPathHandler(inputPath);
    string outputPath(inputPathHandler.getPath().string());
    if (inputPathHandler.isExistingFile()) {
        AlbaLocalPathHandler outputPathHandler(inputPathHandler.getDirectory() / configuration.getCropFileName());
        AlbaGrepFile::UpdateFunctionWithPercentage cropUpdateFunction = [&](double percentage) -> void {
            ProgressCounters::cropProcessProgress = percentage;
        };
        AlbaCropFile cropFile(
            configuration.prioritizedLogCondition, configuration.cropSize * 1000000, cropUpdateFunction);
        cropFile.processFile(inputPathHandler.getPath(), outputPathHandler.getPath());
        if (cropFile.isOutputFileWritten()) {
            outputPath = outputPathHandler.getPath().string();
        }
    } else {
        cout << "Crop step did not proceed. Current path: " << inputPathHandler.getPath() << "\n";
    }
    cout << " (Crop) done | Output path: " << outputPath << "\n";
    return outputPath;
}

string StepHandler::getTempFileFor7zBasedOnLogSorter(WcdmaToolsConfiguration const& configuration) const {
    return configuration.btsLogSorterConfiguration.m_pathOfTempFiles + R"(\)" +
           stringHelper::getRandomAlphaNumericString(30) + R"(\TempFileFor7z.txt)";
}

}  // namespace wcdmaToolsGui
