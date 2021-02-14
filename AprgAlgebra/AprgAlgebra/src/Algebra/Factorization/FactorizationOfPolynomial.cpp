#include "FactorizationOfPolynomial.hpp"

#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeAPolynomial(Polynomial const& polynomial)
{
    Polynomials result;
    factorizeAPolynomialAndPutToResult(result, polynomial);
    return result;
}

Polynomials factorizePolynomials(Polynomials const& polynomials)
{
    Polynomials result;
    for(Polynomial const& polynomial : polynomials)
    {
        Polynomials factorizedPolynomials(factorizeAPolynomial(polynomial));
        if(factorizedPolynomials.size() == 1)
        {
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, polynomial);
        }
        else
        {
            result.reserve(result.size()+factorizedPolynomials.size());
            copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
        }
    }
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeCommonMonomialIfPossible(polynomial),
                polynomial);
}

Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(!polynomial.isOneMonomial())
    {
        Monomial gcfMonomial(getGcfMonomialInMonomials(polynomial.getMonomialsConstReference()));
        if(!isTheValue(gcfMonomial, 1))
        {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(gcfMonomial);
            reducedPolynomial.simplify();
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, createPolynomialFromMonomial(gcfMonomial));
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, reducedPolynomial);
        }
    }
    return result;
}

void factorizeAPolynomialAndPutToResult(Polynomials & result, Polynomial const& polynomial)
{
    Polynomial polynomialToFactorize(polynomial);
    polynomialToFactorize.simplify();
    if(doesNotNeedToBeFactorized(polynomial))
    {
        result.emplace_back(polynomialToFactorize);
    }
    else
    {
        result = factorizeCommonMonomialIfPossible(polynomialToFactorize);

        if(result.empty())
        {
            Polynomials factorizedPolynomials(factorizeUsingPatternsIfPossible(polynomialToFactorize));
            putFactorizedPolynomialsIfPossible(result, factorizedPolynomials);
        }
        if(result.empty())
        {
            Polynomials factorizedPolynomials(factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToFactorize));
            putFactorizedPolynomialsIfPossible(result, factorizedPolynomials);
        }
        if(result.empty() && polynomialToFactorize.getMonomialsConstReference().size() > 2)
        {
            Polynomials factorizedPolynomials(factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialToFactorize));
            putFactorizedPolynomialsIfPossible(result, factorizedPolynomials);
        }

        if(result.empty())
        {
            result.emplace_back(polynomialToFactorize);
        }
        else if(result.size() > 1)
        {
            result = factorizePolynomials(result);
        }
    }
}

void putFactorizedPolynomialsIfPossible(
        Polynomials & result,
        Polynomials const& factorizedPolynomials)
{
    bool shouldPutFactorizedPolynomials =
            !(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() && doesOnePolynomialHaveADoubleValue(factorizedPolynomials));
    if(shouldPutFactorizedPolynomials)
    {
        result.reserve(result.size() + factorizedPolynomials.size());
        copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
    }
}

void simplifyAndRemoveEmptyPolynomials(
        Polynomials & polynomials)
{
    for(Polynomial & polynomial : polynomials)
    {
        polynomial.simplify();
    }
    polynomials.erase(remove_if(polynomials.begin(), polynomials.end(), [](Polynomial const& polynomial)
    {
        return polynomial.isEmpty();
    }), polynomials.end());
}


}

}

}
