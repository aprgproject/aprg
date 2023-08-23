#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <optional>
#include <vector>

namespace alba::algebra {

class PolynomialOverPolynomial {
public:
    struct QuotientAndRemainder {
        Polynomial quotient;
        Polynomial remainder;
    };

    PolynomialOverPolynomial();
    PolynomialOverPolynomial(Polynomial const& numerator, Polynomial const& denominator);

    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] Polynomial const& getNumerator() const;
    [[nodiscard]] Polynomial const& getDenominator() const;

    void setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(
        bool const shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue);

    void simplify();
    void simplifyWithoutFactorization();
    QuotientAndRemainder simplifyAndDivide();
    [[nodiscard]] QuotientAndRemainder divide() const;

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
using PolynomialOverPolynomialOptional = std::optional<PolynomialOverPolynomial>;

}  // namespace alba::algebra
