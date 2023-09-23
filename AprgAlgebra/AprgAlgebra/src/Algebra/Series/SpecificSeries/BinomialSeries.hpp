#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class BinomialSeries {
public:
    BinomialSeries(Term const& monomialPart, Term const& exponent);
    BinomialSeries(Term&& monomialPart, Term&& exponent);
    [[nodiscard]] Term getMonomialPart() const;
    [[nodiscard]] Term getExponent() const;
    [[nodiscard]] Term getValueAtIndex(int const index) const;

protected:
    static Term getBinomialSeriesApproximation(Term const& monomialPart, Term const& exponent, int const numberOfTimes);
    Term m_monomialPart;
    Term m_exponent;
};

}  // namespace alba::algebra
