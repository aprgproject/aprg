#include "LogicalGroupOfMatchers.hpp"

#include <CodeUtilities/Common/CommonUtilities.hpp>

using namespace std;

namespace alba::CodeUtilities {

LogicalGroupOfMatchers::LogicalGroupOfMatchers(OperationType const operationType, Matchers const& matchers)
    : m_operationType(operationType), m_matchers(matchers) {}

LogicalGroupOfMatchers::LogicalGroupOfMatchers(OperationType const operationType, Matchers&& matchers)
    : m_operationType(operationType), m_matchers(matchers) {}

LogicalGroupOfMatchers::Matchers const& LogicalGroupOfMatchers::getMatchers() const { return m_matchers; }
LogicalGroupOfMatchers::OperationType LogicalGroupOfMatchers::getOperationType() const { return m_operationType; }

ostream& operator<<(ostream& out, LogicalGroupOfMatchers const& groupOfMatchers) {
    string const delimeter(groupOfMatchers.getOperationString());
    out << "{ ";
    bool isFirst(true);
    for (Matcher const& matcher : groupOfMatchers.m_matchers) {
        if (isFirst) {
            isFirst = false;
        } else {
            out << delimeter;
        }
        out << matcher;
    }
    out << " }";
    return out;
}

string LogicalGroupOfMatchers::getOperationString() const {
    switch (m_operationType) {
        case OperationType::And:
            return "&&";
        case OperationType::Or:
            return "||";
    }
    return "";
}

bool LogicalGroupOfMatchers::isAndConditionSatisfied(Term const& term) const {
    bool result(true);
    for (Matcher const& matcher : m_matchers) {
        result = result && matcher.isAMatch(term);
        if (!result) {
            break;
        }
    }
    return result;
}

bool LogicalGroupOfMatchers::isOrConditionSatisfied(Term const& term) const {
    bool result(false);
    for (Matcher const& matcher : m_matchers) {
        result = result || matcher.isAMatch(term);
        if (result) {
            break;
        }
    }
    return result;
}

LogicalGroupOfMatchers::BaseMatcherPtr LogicalGroupOfMatchers::createClone() const {
    return make_unique<LogicalGroupOfMatchers>(*this);
}

bool LogicalGroupOfMatchers::isAMatch(Term const& term) const {
    switch (m_operationType) {
        case OperationType::And:
            return isAndConditionSatisfied(term);
        case OperationType::Or:
            return isOrConditionSatisfied(term);
    }
    return false;
}

}  // namespace alba::CodeUtilities
