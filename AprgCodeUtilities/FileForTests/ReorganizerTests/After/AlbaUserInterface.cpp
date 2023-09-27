#include "AlbaUserInterface.hpp"
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/User/DisplayTable.hpp>
#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaUserInterface::AlbaUserInterface() = default;

string AlbaUserInterface::getUserInput() {
    cin.getline(m_buffer.data(), BUFFER_SIZE);
    return {m_buffer.data()};
}

string AlbaUserInterface::getFilePathInput() {
    while (true) {
        string const pathString(getUserInput());
        AlbaLocalPathHandler const filePath(pathString);
        if (filePath.doesExist() && filePath.isFile()) {
            return filePath.getPath();
        }
        cout << "File not found\n";
    }
}

template <typename NumberType>
NumberType AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(
    string_view const question, Choices<NumberType> const& choices) {
    cout << question << "\n";

    StringConverterWithFormatting const converter(5, ' ');

    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Choice", HorizontalAlignment::Right);
    table.getLastRow().addCell("  :  ");
    table.getLastRow().addCell("Description", HorizontalAlignment::Left);
    for (auto const& [choiceString, descriptionString] : choices) {
        table.addRow();
        table.getLastRow().addCell(
            string("[") + converter.convertToString<NumberType>(choiceString) + "]", HorizontalAlignment::Right);
        table.getLastRow().addCell("  :  ");
        table.getLastRow().addCell(descriptionString, HorizontalAlignment::Left);
    }
    cout << table << "\n";

    cout << "Input your answer: ";
    return convertStringToNumber<NumberType>(getUserInput());
}

template int AlbaUserInterface::displayQuestionAndChoicesAndGetNumberAnswer(
    string_view const question, Choices<int> const& choices);

string AlbaUserInterface::displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(
    string_view const question, Choices<string> const& choices) {
    cout << question << "\n";

    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Choice", HorizontalAlignment::Right);
    table.getLastRow().addCell("  :  ");
    table.getLastRow().addCell("Description", HorizontalAlignment::Left);
    for (auto const& [choiceString, descriptionString] : choices) {
        table.addRow();
        table.getLastRow().addCell(
            string("[") + getStringWithCapitalLetters(choiceString) + "]", HorizontalAlignment::Right);
        table.getLastRow().addCell("  :  ");
        table.getLastRow().addCell(descriptionString, HorizontalAlignment::Left);
    }
    cout << table << "\n";

    cout << "Input your answer: ";
    return getStringWithCapitalLetters(getUserInput());
}

}  // namespace alba
