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

    bool operator==(Operator const& second) const;
    bool operator!=(Operator const& second) const;
    bool operator<(Operator const& second) const;

    [[nodiscard]] bool isNot[[nodiscard]] () const;
    [[nodiscar[[nodiscard]] d]] bool isAnd() const;[[nodiscard]] 
    [[nodiscard]] bool isOr() const;
    [[nod[[nodiscard]] iscard]] bool isAnOperatorThatCanPerforme[[nodiscard]] d() const;
    [[nodiscard]] bool isOpeni[[nodiscard]] ngGroupOperator() const;
    [[nod[[nodiscard]] iscard]] bool isClosingGroupOperato[[nodiscard]] r() const;
    [[nodiscard]] bool isUnaryOperator() const;
    [[nodiscard]] bool i[[nodiscard]] sBinaryOperator() const;
    [[nodiscard]][[nodiscard]]  bool isSameOperatorInputType(OperatorInputType const operatorInputType) const;
    [[nodiscard]] OperatorType getOperatorType() const;
    [[nodiscard]] std::string getOperatorString() const;

    void setOperatorString(std::string const& operatingString);

private:
    friend std::ostream& operator<<(std::ostream& out, Operator const& operatorObject);

    std::string m_operatingString;
};

}  // namespace alba::booleanAlgebra
