#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorInputType.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorType.hpp>

#include <string>

namespace alba::booleanAlgebra {

class Operator : public BaseTermData {
public:
    Operator() = default;
    explicit Operator(std::string const& operatingString);
    explicit Operator(std::string&& operatingString);
    bool operator==(Operator const& second) const;
    bool operator!=(Operator const& second) const;
    bool operator<(Operator const& second) const;
    [[nodiscard]] OperatorType getOperatorType() const;
    [[nodiscard]] std::string getOperatorString() const;
    [[nodiscard]] bool isNot() const;
    [[nodiscard]] bool isAnd() const;
    [[nodiscard]] bool isOr() const;
    [[nodiscard]] bool isAnOperatorThatCanPerformed() const;
    [[nodiscard]] bool isOpeningGroupOperator() const;
    [[nodiscard]] bool isClosingGroupOperator() const;
    [[nodiscard]] bool isUnaryOperator() const;
    [[nodiscard]] bool isBinaryOperator() const;
    [[nodiscard]] bool isSameOperatorInputType(OperatorInputType const operatorInputType) const;
    void setOperatorString(std::string const& operatingString);

private:
    friend std::ostream& operator<<(std::ostream& out, Operator const& operatorObject);
    std::string m_operatingString;
};

}  // namespace alba::booleanAlgebra
