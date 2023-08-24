#pragma once

#include <string>

namespace alba {

enum class AlbaGrepStringEvaluatorTermType { Unknown, BooleanResult, StringToFind };

class AlbaGrepStringEvaluatorTerm {
public:
    static void setMainString(std::string const& mainString);

    AlbaGrepStringEvaluatorTerm();
    explicit AlbaGrepStringEvaluatorTerm(std::string const& stringToFind);
    explicit AlbaGrepStringEvaluatorTerm(bool const result);
    [[nodiscard]] bool getResult() const;

private:
    static std::string s_mainString;
    AlbaGrepStringEvaluatorTermType m_type;
    bool m_savedResult;
    std::string m_stringToFind;
};

}  // namespace alba
