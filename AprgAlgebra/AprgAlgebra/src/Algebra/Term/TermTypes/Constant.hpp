#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <string>

namespace alba::algebra {

class Constant : public BaseTermData {
public:
    Constant() = default;
    explicit Constant(AlbaNumber const& constantValue);

    template <
        typename ArithmeticType,
        typename =
            std::enable_if_t<typeHelper::isArithmeticType<ArithmeticType>()>>  // enabled via a type template parameter
    explicit Constant(ArithmeticType const value) : Constant(AlbaNumber(value)) {}

    // rule of zero
    bool operator==(Constant const& second) const;
    bool operator!=(Constant const& second) const;
    bool operator<(Constant const& second) const;
    [[nodiscard]] AlbaNumber const& getNumber() const;
    void setNumber(AlbaNumber const& constantValue);

private:
    friend std::ostream& operator<<(std::ostream& out, Constant const& constant);
    AlbaNumber m_constantValue;
};

}  // namespace alba::algebra
