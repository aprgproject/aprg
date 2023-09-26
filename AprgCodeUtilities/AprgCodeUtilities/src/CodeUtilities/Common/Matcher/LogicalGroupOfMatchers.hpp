#pragma once

#include <CodeUtilities/Common/Matcher/Matcher.hpp>

#include <vector>

namespace alba::CodeUtilities {

class LogicalGroupOfMatchers : public BaseMatcher {
public:
    enum class OperationType { And, Or };

    using Matchers = std::vector<Matcher>;
    LogicalGroupOfMatchers(OperationType const operationType, Matchers const& matchers);
    LogicalGroupOfMatchers(OperationType const operationType, Matchers&& matchers);
    [[nodiscard]] BaseMatcherPtr createClone() const override;
    [[nodiscard]] bool isAMatch(Term const& term) const override;
    [[nodiscard]] Matchers const& getMatchers() const;
    [[nodiscard]] OperationType getOperationType() const;
    friend std::ostream& operator<<(std::ostream& out, LogicalGroupOfMatchers const& groupOfMatchers);

private:
    [[nodiscard]] std::string getOperationString() const;
    [[nodiscard]] bool isAndConditionSatisfied(Term const& term) const;
    [[nodiscard]] bool isOrConditionSatisfied(Term const& term) const;
    OperationType m_operationType;
    Matchers m_matchers;
};

}  // namespace alba::CodeUtilities
