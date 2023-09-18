#include "UserInterface.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/User/AlbaUserInterface.hpp>

#include <iostream>

using namespace std;

namespace alba::soosa {

InputConfiguration UserInterface::getSavedConfiguration() const { return m_savedConfiguration; }
void UserInterface::setPath(string const& path) { m_savedConfiguration.setPath(path); }

void UserInterface::askUserForMainDetails() {
    cout << "Enter area:\n";
    string area(m_userInterface.getUserInput());

    cout << "Enter period:"
         << "\n";
    string period(m_userInterface.getUserInput());

    cout << "Enter discharge:\n";
    auto discharge(m_userInterface.getNumberFromInput<double>());

    cout << "Enter minimum satisfactory score (inclusive):\n";
    int minimumSatisfactoryScore(m_userInterface.getNumberFromInput<int>());

    m_savedConfiguration.setMainParameters(area, period, discharge, minimumSatisfactoryScore);
}

void UserInterface::askUserForFormDetails() {
    AlbaLocalPathHandler formDetailsDirectoryPath(AlbaLocalPathHandler::createPathHandlerForDetectedPath());
    formDetailsDirectoryPath.input(formDetailsDirectoryPath.getDirectory() / "FormDetails/");
    saveFormDetailsFromFormDetailPath(askUserForPathOfFormDetailToRead(formDetailsDirectoryPath.getPath().string()));
}

void UserInterface::saveFormDetailsFromFormDetailPath(string const& formDetailsFilePath) {
    ifstream formDetailsStream(formDetailsFilePath);
    AlbaFileReader fileReader(formDetailsStream);

    m_savedConfiguration.setFormDetailsTitle(fileReader.getLineAndIgnoreWhiteSpaces());

    int columnNumber = 0;
    while (fileReader.isNotFinished()) {
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        if (!line.empty()) {
            if (line == "NEW_COLUMN") {
                ++columnNumber;
            } else {
                m_savedConfiguration.addQuestion(columnNumber, line);
            }
        }
    }
}

string UserInterface::askUserForPathOfFormDetailToRead(string const& formDetailsDirectoryPath) {
    AlbaLocalPathHandler formDetailsPathHandler(formDetailsDirectoryPath);
    AlbaUserInterface::Choices<int> choices;
    int choice(0);

    formDetailsPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler filePathHandler(filePath);
            cout << "Choice " << choice << " :: " << filePathHandler.getFile() << "\n";
            choices.emplace(choice++, filePathHandler.getPath().string());
        });

    auto chosenChoice(m_userInterface.displayQuestionAndChoicesAndGetNumberAnswer("Select formDetails:", choices));
    cout << "Chosen choice: " << chosenChoice << "\n";

    return choices[chosenChoice];
}

}  // namespace alba::soosa
