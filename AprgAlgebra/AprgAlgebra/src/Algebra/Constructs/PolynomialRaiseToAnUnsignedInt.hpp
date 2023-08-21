#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <map>

namespace alba {

namespace algebra {

class PolynomialRaiseToAnUnsignedInt {
public:
    using PolynomialToNumberMap = std::map<Polynomial, int>;

    PolynomialRaiseToAnUnsignedInt(Polynomial const& polynomial);

    bool isExponentOne() const;

    Polynomial const& getBase() const;
    int getExponent() const;

private:
    static bool canBeSimplified(int const gcfOfExponents, Monomial const& commonMonomialInBase);
    static void factorizeAndUpdateCommonMonomialAndFactorsToExponent(
        Polynomial const& polynomial, PolynomialToNumberMap& factorsToExponent, Monomial& commonMonomialInBase);
    static int getGcfOfExponents(PolynomialToNumberMap const& factorsToExponent);
    static Polynomial getRemainingBase(
        PolynomialToNumberMap const& factorsToExponent, Monomial const& commonMonomialInBase, int const gcfOfExponents);
    Polynomial m_base;
    int m_exponent;
};

}  // namespace algebra

}  // namespace alba
