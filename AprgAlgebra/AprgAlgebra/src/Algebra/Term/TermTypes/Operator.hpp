#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/OperatorInputType.hpp>
#include <Algebra/Term/TermTypes/OperatorLevel.hpp>

#include <string>

namespace alba::algebra {

class Operator : public BaseTermData {
public:
    Operator() = default;
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    Operator(std::string const& operatingString);
    Operator(std::string&& operatingString);
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    // rule of zero
    bool operator==(Operator const& second) const;
    bool operator!=(Operator const& second) const;
    bool operator<(Operator const& second) const;
    [[nodiscard]] OperatorLevel getOperatorLevel() const;
    [[nodiscard]] std::string getOperatorString() const;
    [[nodiscard]] bool isAddition() const;
    [[nodiscard]] bool isSubtraction() const;
    [[nodiscard]] bool isMultiplication() const;
    [[nodiscard]] bool isDivision() const;
    [[nodiscard]] bool isRaiseToPower() const;
    [[nodiscard]] bool isAnOperatorThatCanPerformed() const;
    [[nodiscard]] bool isOpeningGroupOperator() const;
    [[nodiscard]] bool isClosingGroupOperator() const;
    [[nodiscard]] bool isSameOperatorInputType(OperatorInputType const operatorInputType) const;
    void setOperatorString(std::string const& operatingString);

private:
    friend std::ostream& operator<<(std::ostream& out, Operator const& operatorObject);
    std::string m_operatingString;
};

}  // namespace alba::algebra
