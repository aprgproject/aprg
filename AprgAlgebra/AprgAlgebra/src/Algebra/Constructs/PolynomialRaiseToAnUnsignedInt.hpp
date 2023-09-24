#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <map>

namespace alba::algebra {

class PolynomialRaiseToAnUnsignedInt {
public:
    using PolynomialToNumberMap = std::map<Polynomial, int>;
    explicit PolynomialRaiseToAnUnsignedInt(Polynomial const& polynomial);
    [[nodiscard]] Polynomial const& getBase() const;
    [[nodiscard]] int getExponent() const;
    [[nodiscard]] bool isExponentOne() const;

private:
    static void factorizeAndUpdateCommonMonomialAndFactorsToExponent(
        Polynomial const& polynomial, PolynomialToNumberMap& factorsToExponent, Monomial& commonMonomialInBase);

    static Polynomial getRemainingBase(
        PolynomialToNumberMap const& factorsToExponent, Monomial const& commonMonomialInBase, int const gcfOfExponents);

    static int getGcfOfExponents(PolynomialToNumberMap const& factorsToExponent);
    static bool canBeSimplified(int const gcfOfExponents, Monomial const& commonMonomialInBase);
    Polynomial m_base;
    int m_exponent{1};
};

}  // namespace alba::algebra
