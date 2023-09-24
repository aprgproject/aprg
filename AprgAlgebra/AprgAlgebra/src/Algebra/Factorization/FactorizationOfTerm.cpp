#include "FactorizationOfTerm.hpp"

#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba::algebra::Factorization {

Terms factorizeTerm(Term const& term) { return factorizeTerms({term}); }

Terms factorizeTerms(Terms const& terms) {
    Terms result;
    for (Term const& term : terms) {
        if (term.isPolynomial()) {
            Polynomial simplifiedPolynomial(term.getAsPolynomial());
            simplifiedPolynomial.simplify();
            Polynomials const polynomialFactors(factorizeAPolynomial(simplifiedPolynomial));
            result.reserve(result.size() + polynomialFactors.size());
            transform(
                polynomialFactors.cbegin(), polynomialFactors.cend(), back_inserter(result),
                [&](Polynomial const& polynomialFactor) {
                    return simplifyAndConvertPolynomialToSimplestTerm(polynomialFactor);
                });
        } else if (term.isExpression()) {
            if (shouldSimplifyExpressionsToFactors()) {
                Terms const factors(factorizeAnExpression(term.getAsExpression()));
                result.reserve(result.size() + factors.size());
                copy(factors.cbegin(), factors.cend(), back_inserter(result));
            } else {
                result.emplace_back(term);
            }
        } else {
            result.emplace_back(term);
        }
    }
    return result;
}

}  // namespace alba::algebra::Factorization
