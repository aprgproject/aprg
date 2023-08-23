#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class TermRaiseToANumber {
public:
    TermRaiseToANumber();
    TermRaiseToANumber(Term const& base, AlbaNumber const& exponent);

    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isRadical() const;

    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] Term const& getBase() const;
    [[nodiscard]] AlbaNumber const& getExponent() const;

    Term& getBaseReference();

    void setBase(Term const& base);
    void setExponent(AlbaNumber const& exponent);

private:
    Term m_base;
    AlbaNumber m_exponent;
};

using ListOfTermRaiseToANumber = std::vector<TermRaiseToANumber>;

}  // namespace alba
