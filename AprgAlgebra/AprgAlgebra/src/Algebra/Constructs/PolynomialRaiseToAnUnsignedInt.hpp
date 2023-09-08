#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <map>

namespace alba::algebra {

class PolynomialRaiseToAnUnsignedInt {
public:
    using PolynomialToNumberMap = std::map<Polynomial, int>;
    explicit PolynomialRaiseToAnUnsignedInt(Polynomial const& polynomial);
    [[nodiscard]] bool isExponentOne() const;
    [[nodiscard]] int getExponent() const;
    [[nodiscard]] Polynomial const& getBase() const;

private:
    static bool canBeSimplified(int const gcfOfExponents, Monomial const& commonMonomialInBase);
    static int getGcfOfExponents(PolynomialToNumberMap const& factorsToExponent);
    static Polynomial getRemainingBase(
        PolynomialToNumberMap const& factorsToExponent, Monomial const& commonMonomialInBase, int const gcfOfExponents);
    static void factorizeAndUpdateCommonMonomialAndFactorsToExponent(
        Polynomial const& polynomial, PolynomialToNumberMap& factorsToExponent, Monomial& commonMonomialInBase);
    Polynomial m_base;
    int m_exponent{1};
};

}  // namespace alba::algebra
