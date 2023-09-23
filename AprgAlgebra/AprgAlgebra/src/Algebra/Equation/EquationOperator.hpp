#pragma once

#include <string>

namespace alba::algebra {

class EquationOperator {
public:
    EquationOperator() = default;
    explicit EquationOperator(std::string const& operatingString);
    explicit EquationOperator(std::string&& operatingString);
    // rule of zero
    bool operator==(EquationOperator const& second) const;
    bool operator!=(EquationOperator const& second) const;
    bool operator<(EquationOperator const& second) const;
    [[nodiscard]] std::string getOperatorString() const;
    [[nodiscard]] bool isEqual() const;
    [[nodiscard]] bool isNotEqual() const;
    [[nodiscard]] bool isLessThan() const;
    [[nodiscard]] bool isGreaterThan() const;
    [[nodiscard]] bool isLessThanOrEqual() const;
    [[nodiscard]] bool isGreaterThanOrEqual() const;
    [[nodiscard]] bool isAnEqualityVariant() const;
    [[nodiscard]] bool isALessThanVariant() const;
    [[nodiscard]] bool isAGreaterThanVariant() const;

private:
    friend std::ostream& operator<<(std::ostream& out, EquationOperator const& equationOperator);
    std::string m_operatingString;
};

}  // namespace alba::algebra
