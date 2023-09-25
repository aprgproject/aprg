#include "AlbaCropFile.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <fstream>
#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace alba {

AlbaCropFile::AlbaCropFile(string const& prioritizedLineCondition, double const cropSize)
    : m_isOutputFileWritten(false), m_cropSize(cropSize), m_prioritizedLineEvaluator(prioritizedLineCondition) {}

AlbaCropFile::AlbaCropFile(
    string const& prioritizedLineCondition, double const cropSize,
    UpdateFunctionWithPercentage const& updateFunctionAfterOneIteration)
    : m_isOutputFileWritten(false),
      m_cropSize(cropSize),
      m_prioritizedLineEvaluator(prioritizedLineCondition),
      m_updateFunctionAfterOneIterationOptional(updateFunctionAfterOneIteration) {}

bool AlbaCropFile::isOutputFileWritten() const { return m_isOutputFileWritten; }

void AlbaCropFile::processFile(path const& inputFilePath, path const& outputFilePath) {
    m_isOutputFileWritten = false;
    AlbaLocalPathHandler const inputPathHandler(inputFilePath);
    AlbaLocalPathHandler const outputPathHandler(outputFilePath);

    double const foundLocation(getLocationOfPrioritizedPrint(inputPathHandler.getPath()));
    if (foundLocation >= 0) {
        performCropForFile(inputPathHandler.getPath(), outputPathHandler.getPath(), foundLocation);
    } else {
        cout << "CropFile: Crop process did not proceed. Prioritized line not found."
             << "\n";
    }
    updateAfterOneIteration(100);
}

AlbaCropFile::LocationsInFile AlbaCropFile::getLocationsInFile(
    double const foundLocation, double const fileSize) const {
    LocationsInFile locations{};
    locations.startLocation = foundLocation - (m_cropSize / 2);
    locations.endLocation = foundLocation + (m_cropSize / 2);
    double const overFlowOnTheLeft = -locations.startLocation;
    double const overFlowOnTheRight = locations.endLocation - fileSize;
    if (overFlowOnTheLeft > 0 || overFlowOnTheRight > 0) {
        if (overFlowOnTheLeft < 0 && overFlowOnTheRight + overFlowOnTheLeft <= 0) {
            locations.startLocation -= overFlowOnTheRight;
            locations.endLocation -= overFlowOnTheRight;
        } else if (overFlowOnTheRight < 0 && overFlowOnTheRight + overFlowOnTheLeft <= 0) {
            locations.startLocation += overFlowOnTheLeft;
            locations.endLocation += overFlowOnTheLeft;
        } else {
            locations.startLocation = 0;
            locations.endLocation = fileSize;
        }
    }
    return locations;
}

void AlbaCropFile::performCropForFile(
    path const& inputFilePath, path const& outputFilePath, double const foundLocation) {
    ifstream inputFileStream(inputFilePath);
    ofstream outputFileStream(outputFilePath);

    AlbaFileReader fileReader(inputFileStream);
    LocationsInFile const locations(getLocationsInFile(foundLocation, static_cast<double>(fileReader.getFileSize())));
    inputFileStream.clear();
    fileReader.moveLocation(static_cast<uint64_t>(locations.startLocation));

    double const locationDifference = locations.endLocation - locations.startLocation;
    while (fileReader.isNotFinished()) {
        auto const currentLocation = static_cast<double>(fileReader.getCurrentLocation());
        string const lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if (currentLocation < locations.endLocation) {
            m_isOutputFileWritten = true;
            outputFileStream << lineInFile << "\n";
        } else {
            break;
        }
        if (fileReader.isNotFinished()) {
            updateAfterOneIteration(50 + (currentLocation - locations.startLocation) * 50 / locationDifference);
        }
    }
}

void AlbaCropFile::updateAfterOneIteration(double const percentage) {
    if (m_updateFunctionAfterOneIterationOptional) {
        m_updateFunctionAfterOneIterationOptional.value()(percentage);
    }
}

double AlbaCropFile::getLocationOfPrioritizedPrint(path const& inputFilePath) {
    double foundLocation(-1);
    ifstream inputFileStream(inputFilePath);
    AlbaFileReader fileReader(inputFileStream);
    auto const sizeOfFile = static_cast<double>(fileReader.getFileSize());
    while (fileReader.isNotFinished()) {
        auto const currentLocation = static_cast<double>(fileReader.getCurrentLocation());
        string const lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if (m_prioritizedLineEvaluator.evaluate(lineInFile)) {
            cout << "CropFile: Found the prioritized line in input file. Line: " << lineInFile << "\n";
            foundLocation = currentLocation;
            break;
        }
        if (fileReader.isNotFinished()) {
            updateAfterOneIteration(static_cast<double>(fileReader.getCurrentLocation()) * 50 / sizeOfFile);
        }
    }
    return foundLocation;
}

}  // namespace alba
