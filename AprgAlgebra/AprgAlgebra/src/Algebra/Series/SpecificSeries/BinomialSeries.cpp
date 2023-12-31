#include "BinomialSeries.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace std;

namespace alba::algebra {

BinomialSeries::BinomialSeries(Term const& monomialPart, Term const& exponent)
    : m_monomialPart(monomialPart), m_exponent(exponent) {}

BinomialSeries::BinomialSeries(Term&& monomialPart, Term&& exponent)
    : m_monomialPart(monomialPart), m_exponent(exponent) {}

Term BinomialSeries::getMonomialPart() const { return m_monomialPart; }
Term BinomialSeries::getExponent() const { return m_exponent; }

Term BinomialSeries::getValueAtIndex(int const index) const {
    Term result;
    if (index >= 0) {
        int const positiveIndex(static_cast<int>(index));
        result = getBinomialSeriesApproximation(m_monomialPart, m_exponent, positiveIndex);
    }
    return result;
}

Term BinomialSeries::getBinomialSeriesApproximation(
    Term const& monomialPart, Term const& exponent, int const numberOfTimes) {
    // Approximation:
    // (1+x)^m = Summation of [m*(m-1)*(m-2)....(m-n+1) * (x^n)/(n!)] until n reaches infinity
    Term result(1);
    Term partialProduct(1);
    Term monomialPartRaiseToPower(1);
    AlbaNumber factorialValue(1);
    for (int n = 1; n <= numberOfTimes; ++n) {
        monomialPartRaiseToPower *= monomialPart;
        Term const multiplier(exponent - n + 1);
        partialProduct *= multiplier;
        factorialValue *= n;
        Term const currentTerm(partialProduct * monomialPartRaiseToPower / factorialValue);
        result += currentTerm;
    }
    result.simplify();
    return result;
}

}  // namespace alba::algebra
