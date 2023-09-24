#pragma once

#include <array>
#include <Common/String/AlbaStringHelper.hpp>
#include <map>
#include <string>

namespace alba {

class AlbaUserInterface {
public:
template <typename AnswerType>
    using Choices = std::map<AnswerType, std::string>;

// rule of zero
AlbaUserInterface();
std::string getUserInput();
std::string getFilePathInput();

std::string displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(
        std::string_view const question, Choices<std::string> const& choices);

template <typename NumberType>
    NumberType getNumberFromInput();

template <typename NumberType>
    NumberType displayQuestionAndChoicesAndGetNumberAnswer(
        std::string_view const question, Choices<NumberType> const& choices);

private:
static constexpr int BUFFER_SIZE = 1000;
std::array<char, BUFFER_SIZE> m_buffer{};

};

template <typename NumberType>
NumberType AlbaUserInterface::getNumberFromInput() {
    return stringHelper::convertStringToNumber<NumberType>(getUserInput());
}

}  // namespace alba
