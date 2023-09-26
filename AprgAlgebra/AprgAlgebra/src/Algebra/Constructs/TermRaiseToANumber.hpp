#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class TermRaiseToANumber {
public:
    TermRaiseToANumber() = default;
    TermRaiseToANumber(Term const& base, AlbaNumber const& exponent);
    TermRaiseToANumber(Term&& base, AlbaNumber&& exponent);
    [[nodiscard]] AlbaNumber const& getExponent() const;
    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] Term const& getBase() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isRadical() const;
    void setBase(Term const& base);
    void setExponent(AlbaNumber const& exponent);
    Term& getBaseReference();

private:
    Term m_base;
    AlbaNumber m_exponent;
};

using ListOfTermRaiseToANumber = std::vector<TermRaiseToANumber>;

}  // namespace alba::algebra
