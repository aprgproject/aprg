#include "PolynomialRaiseToAnUnsignedInt.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

PolynomialRaiseToAnUnsignedInt::PolynomialRaiseToAnUnsignedInt(Polynomial const& polynomial) : m_base(polynomial) {
    PolynomialToNumberMap factorsToExponent;
    Monomial commonMonomialInBase(1, {});
    factorizeAndUpdateCommonMonomialAndFactorsToExponent(polynomial, factorsToExponent, commonMonomialInBase);
    int gcfOfExponents(getGcfOfExponents(factorsToExponent));
    if (canBeSimplified(gcfOfExponents, commonMonomialInBase)) {
        m_base = getRemainingBase(factorsToExponent, commonMonomialInBase, gcfOfExponents);
        m_exponent = gcfOfExponents;
    }
}

Polynomial const& PolynomialRaiseToAnUnsignedInt::getBase() const { return m_base; }
int PolynomialRaiseToAnUnsignedInt::getExponent() const { return m_exponent; }
bool PolynomialRaiseToAnUnsignedInt::isExponentOne() const { return m_exponent == 1; }

void PolynomialRaiseToAnUnsignedInt::factorizeAndUpdateCommonMonomialAndFactorsToExponent(
    Polynomial const& polynomial, PolynomialToNumberMap& factorsToExponent, Monomial& commonMonomialInBase) {
    Polynomials factors(factorizeAPolynomial(polynomial));
    for (Polynomial const& factor : factors) {
        if (isOneMonomial(factor)) {
            commonMonomialInBase.multiplyMonomial(getFirstMonomial(factor));
        } else {
            auto it = factorsToExponent.find(factor);
            if (it == factorsToExponent.cend()) {
                factorsToExponent.emplace(factor, 1);
            } else {
                (it->second)++;
            }
        }
    }
}

Polynomial PolynomialRaiseToAnUnsignedInt::getRemainingBase(
    PolynomialToNumberMap const& factorsToExponent, Monomial const& commonMonomialInBase, int const gcfOfExponents) {
    Monomial remainingCommonMonomial(commonMonomialInBase);
    remainingCommonMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, gcfOfExponents));
    Polynomial result{remainingCommonMonomial};
    for (auto const& [factor, exponent] : factorsToExponent) {
        int remainingExponent(exponent / gcfOfExponents);
        Polynomial remainingFactor(factor);
        remainingFactor.raiseToUnsignedInteger(remainingExponent);
        result.multiplyPolynomial(remainingFactor);
    }
    return result;
}

int PolynomialRaiseToAnUnsignedInt::getGcfOfExponents(PolynomialToNumberMap const& factorsToExponent) {
    int result(1);
    if (!factorsToExponent.empty()) {
        auto it = factorsToExponent.cbegin();
        result = it->second;
        ++it;
        for (; it != factorsToExponent.cend(); ++it) {
            result = getGreatestCommonFactor(result, it->second);
        }
    }
    return result;
}

bool PolynomialRaiseToAnUnsignedInt::canBeSimplified(int const gcfOfExponents, Monomial const& commonMonomialInBase) {
    return gcfOfExponents != 1 &&
           (!isEven(gcfOfExponents) || (isEven(gcfOfExponents) && !isANegativeMonomial(commonMonomialInBase)));
}

}  // namespace alba::algebra
