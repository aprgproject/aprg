#pragma once

#include <map>
#include <string>
#include <vector>

namespace alba::soosa {

struct FormDetails {
    using ColumnToNumberOfQuestionsMap = std::map<int, int>;
    using ColumnToNumberOfQuestionsPair = std::pair<int, int>;
    std::string title;
    std::vector<std::string> questions;
    ColumnToNumberOfQuestionsMap columnToNumberOfQuestionsMap;
};

class InputConfiguration {
public:
    InputConfiguration();
    [[nodiscard]] std::string getQuestionAt(int const questionIndex) const;
    [[nodiscard]] std::string getFormDetailsTitle() const;
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] std::string getArea() const;
    [[nodiscard]] std::string getPeriod() const;
    [[nodiscard]] double getDischarge() const;
    [[nodiscard]] int getNumberOfColumns() const;
    [[nodiscard]] int getNumberOfQuestions() const;
    [[nodiscard]] int getNumberOfQuestionsAtColumn(int const column) const;
    [[nodiscard]] int getQuestionIndexInColumn(int const columnNumber, int const questionOffsetInColumn) const;
    [[nodiscard]] int getMinimumSatisfactoryScore() const;
    void setPath(std::string const& path);

    void setMainParameters(
        std::string const& area, std::string const& period, double const discharge, int const minimumSatisfactoryScore);

    void addQuestion(int const columnNumber, std::string const& question);
    void setFormDetailsTitle(std::string const& title);

private:
    std::string m_path;
    std::string m_area;
    std::string m_period;
    double m_discharge{};
    int m_minimumSatisfactoryScore{};
    FormDetails m_formDetails;
};

}  // namespace alba::soosa
