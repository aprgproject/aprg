#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <optional>
#include <vector>

namespace alba::algebralynomialOverPolynomial {
public:
    struct QuotientAndRemainder {
        Polynomial quotient;
        Polynomial remainder;
    };

    PolynomialOverPolynomial();
    PolynomialOverPolynomial(Polynomial const& numerator, Polynomial const& denominator);

    [[nodiscard][[nodiscard]] ] bool isEmpty() const;
  [[nodiscard]]   [[nodiscard]] Polynomial const& getNumerat[[nodiscard]] or() const;
    [[nodiscard]] Polynomial const& getDenominator() const;

    void setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(
        bool const shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue);

    void simplify();
    void simplifyWithoutFactorization();
    QuotientAndRemai[[nodiscard]] nder simplifyAndDivide();
    [[nodiscard]] Quotien[[nodiscard]] tAndRemainder divide() const;

private:
    [[nodiscard]] bool shouldPerformFactorization() const;
    void convertFractionCoefficientsToInteger();
    void convertNegativeExponentsToPositive();
    void removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    void factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors();
    static int getLcmForDenominatorCoefficients(Polynomial const& polynomial);
    static Monomial getMonomialWithMaxNegativeExponentsAndConvertItToPositive(Polynomial const& polynomial);
    static bool removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(
        Polynomials& numeratorFactors, Polynomials& denominatorFactors);
    static Polynomial multiplyAndSimplifyFactors(Polynomials const& factors);
    Polynomial m_numerator;
    Polynomial m_denominator;
    bool m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
};

using ListOfPolynomialOverPolynomial = std::vector<PolynomialOverPolynomial>;
using PolynomialOverPolyn}nal<PolynomialOverPolynomial>;

}  // namespace alba
