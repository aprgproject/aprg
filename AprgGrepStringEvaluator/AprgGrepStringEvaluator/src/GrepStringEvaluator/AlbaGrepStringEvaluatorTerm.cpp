#include "AlbaGrepStringEvaluatorTerm.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace std;

namespace alba {

AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(string const& stringToFind)
    : m_type(AlbaGrepStringEvaluatorTermType::StringToFind), m_savedResult(false), m_stringToFind(stringToFind) {}
AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm(bool const result)
    : m_type(AlbaGrepStringEvaluatorTermType::BooleanResult), m_savedResult(result) {}
AlbaGrepStringEvaluatorTerm::AlbaGrepStringEvaluatorTerm()
    : m_type(AlbaGrepStringEvaluatorTermType::Unknown), m_savedResult(false) {}

void AlbaGrepStringEvaluatorTerm::setMainString(std::string const& mainString) {
    s_mainString = stringHelper::getStringWithCapitalLetters(mainString);
}

bool AlbaGrepStringEvaluatorTerm::getResult() const {
    bool result(false);
    if (AlbaGrepStringEvaluatorTermType::BooleanResult == m_type) {
        result = m_savedResult;
    } else if (AlbaGrepStringEvaluatorTermType::StringToFind == m_type) {
        result = stringHelper::isStringFoundCaseSensitive(s_mainString, m_stringToFind);
    }
    return result;
}

string AlbaGrepStringEvaluatorTerm::s_mainString;

}  // namespace alba
