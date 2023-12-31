#include "FactorizationOfPolynomial.hpp"

#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba::algebra::Factorization {

void factorizeCommonMonomialIfPossible(Polynomials& result, Polynomial const& polynomial) {
    if (!isOneMonomial(polynomial)) {
        Monomial const gcfMonomial(getGcfMonomialInMonomials(polynomial.getMonomials()));
        if (!isTheValue(gcfMonomial, 1)) {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(gcfMonomial);
            reducedPolynomial.simplify();
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, createPolynomialFromMonomial(gcfMonomial));
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, reducedPolynomial);
        }
    }
}

void factorizePolynomialsAndPutToResult(Polynomials& result, Polynomials const& polynomials) {
    Polynomials polynomialsToFactorize(polynomials);
    for (int i = 0; i < static_cast<int>(polynomialsToFactorize.size()); ++i) {
        Polynomial const& polynomial(polynomialsToFactorize[i]);
        Polynomial simplifiedPolynomial(polynomial);
        simplifiedPolynomial.simplify();
        if (doesNotNeedToBeFactorized(simplifiedPolynomial)) {
            result.emplace_back(simplifiedPolynomial);
        } else {
            int const originalSize(static_cast<int>(polynomialsToFactorize.size()));
            int deltaSize = static_cast<int>(polynomialsToFactorize.size()) - originalSize;
            tryToFactorizeCommonMonomial(polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);
            tryToFactorizeUsingPatterns(polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);
            tryToFactorizeIncreasingAndDecreasingExponentsForm(
                polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);
            tryToFactorizeBySplittingToSmallerPolynomials(
                polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);

            if (deltaSize == 0) {
                result.emplace_back(simplifiedPolynomial);
            } else if (deltaSize == 1) {
                polynomialsToFactorize.pop_back();
            }
        }
    }
}

void putFactorizedPolynomialsIfPossible(Polynomials& result, Polynomials const& factorizedPolynomials) {
    bool const shouldPutFactorizedPolynomials =
        !(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() &&
          doesOnePolynomialHaveADoubleValue(factorizedPolynomials));
    if (shouldPutFactorizedPolynomials) {
        result.reserve(result.size() + factorizedPolynomials.size());
        copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
    }
}

void simplifyAndRemoveEmptyPolynomials(Polynomials& polynomials) {
    for (Polynomial& polynomial : polynomials) {
        polynomial.simplify();
    }
    polynomials.erase(
        remove_if(
            polynomials.begin(), polynomials.end(), [](Polynomial const& polynomial) { return polynomial.isEmpty(); }),
        polynomials.end());
}

void tryToFactorizeCommonMonomial(
    Polynomials& polynomialsToFactorize, int& deltaSize, Polynomial const& simplifiedPolynomial,
    int const originalSize) {
    if (deltaSize == 0) {
        Polynomials factorizedPolynomials;
        factorizeCommonMonomialIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = getDeltaSize(polynomialsToFactorize, originalSize);
    }
}

void tryToFactorizeUsingPatterns(
    Polynomials& polynomialsToFactorize, int& deltaSize, Polynomial const& simplifiedPolynomial,
    int const originalSize) {
    if (deltaSize == 0 && isFactorizeUsingPatternsNeeded(simplifiedPolynomial)) {
        Polynomials factorizedPolynomials;
        factorizeUsingPatternsIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = static_cast<int>(polynomialsToFactorize.size()) - originalSize;
    }
}

void tryToFactorizeIncreasingAndDecreasingExponentsForm(
    Polynomials& polynomialsToFactorize, int& deltaSize, Polynomial const& simplifiedPolynomial,
    int const originalSize) {
    if (deltaSize == 0 && isFactorizeIncreasingAndDecreasingExponentsFormNeeded(simplifiedPolynomial)) {
        Polynomials factorizedPolynomials;
        factorizeIncreasingAndDecreasingExponentsFormIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = static_cast<int>(polynomialsToFactorize.size()) - originalSize;
    }
}

void tryToFactorizeBySplittingToSmallerPolynomials(
    Polynomials& polynomialsToFactorize, int& deltaSize, Polynomial const& simplifiedPolynomial,
    int const originalSize) {
    if (deltaSize == 0 && isFactorizeBySplittingToSmallerPolynomialsNeeded(simplifiedPolynomial)) {
        Polynomials factorizedPolynomials;
        factorizeBySplittingToSmallerPolynomialsIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = static_cast<int>(polynomialsToFactorize.size()) - originalSize;
    }
}

Polynomials factorizeAPolynomial(Polynomial const& polynomial) {
    Polynomials result;
    factorizePolynomialsAndPutToResult(result, {polynomial});
    return result;
}

Polynomials factorizePolynomials(Polynomials const& polynomials) {
    Polynomials result;
    factorizePolynomialsAndPutToResult(result, polynomials);
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial) {
    Polynomials result;
    factorizeCommonMonomialIfPossible(result, polynomial);
    simplifyAndEmplaceBackPolynomialIfListIsEmpty(result, polynomial);
    return result;
}

int getDeltaSize(Polynomials const& polynomials, int const originalSize) {
    return static_cast<int>(polynomials.size()) - originalSize;
}

bool isFactorizeUsingPatternsNeeded(Polynomial const& polynomial) {
    return polynomial.getMonomials().size() == 2 && hasAMonomialWithDegreeMoreThanOneOrFractional(polynomial);
}

bool isFactorizeIncreasingAndDecreasingExponentsFormNeeded(Polynomial const& polynomial) {
    return hasAMonomialWithDegreeMoreThanOneOrFractional(polynomial);
}

bool isFactorizeBySplittingToSmallerPolynomialsNeeded(Polynomial const& polynomial) {
    return polynomial.getMonomials().size() >= 4 && hasAMonomialWithMultipleVariables(polynomial);
}

}  // namespace alba::algebra::Factorization
