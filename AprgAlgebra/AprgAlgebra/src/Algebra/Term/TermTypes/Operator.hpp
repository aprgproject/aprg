#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/OperatorInputType.hpp>
#include <Algebra/Term/TermTypes/OperatorLevel.hpp>

#include <string>

namespace alba::algebra {

class Operator : public BaseTermData {
public:
    Operator() = default;
    explicit Operator(std::string const& operatingString);

    // rule of zero

    bool operator==(Operator const& second) const;
    bool operator!=(Operator const& second) const;
    bool operator<(Operator const& second) const;

    [[nodiscard]] bool isAddition[[nodiscard]] () const;
    [[nodiscard]] bool[[nodiscard]]  isSubtraction() const;
    [[nodis[[nodiscard]] card]] bool isMultiplication([[nodiscard]] ) const;
    [[nodiscard]] bool i[[nodiscard]] sDivision() const;
    [[nodiscard]] bool isRai[[nodiscard]] seToPower() const;
    [[nodiscard]] bool[[nodiscard]]  isAnOperatorThatCanPerformed() const;
  [[nodiscard]]   [[nodiscard]] bool isOpeningGroupOperator() const;
    [[nodiscard]] bool isClosin[[nodiscard]] gGroupOperator() const;
    [[nodiscard]] bo[[nodiscard]] ol isSameOperatorInputType(OperatorInputType const operatorInputType) const;

    [[nodiscard]] OperatorLevel getOperatorLevel() const;
    [[nodiscard]] std::string getOperatorString() const;

    void setOperatorString(std::string const& ope  // namespace alba::algebravate:
    friend std::ostream& operator<<(std::ostream& out, Operator const& operatorObject);

    std::string m_operatingString;
};

}  // namespace alba::algebra
