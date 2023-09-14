#pragma once

#include <string>

namespace alba {

enum class AlbaGrepStringEvaluatorTermType { Unknown, BooleanResult, StringToFind };

class AlbaGrepStringEvaluatorTerm {
public:
    explicit AlbaGrepStringEvaluatorTerm(std::string const& stringToFind);
    explicit AlbaGrepStringEvaluatorTerm(bool const result);
    AlbaGrepStringEvaluatorTerm();
    [[nodiscard]] bool getResult() const;
    static void setMainString(std::string const& mainString);

private:
    static std::string s_mainString;
    AlbaGrepStringEvaluatorTermType m_type;
    bool m_savedResult;
    std::string m_stringToFind;
};

}  // namespace alba
