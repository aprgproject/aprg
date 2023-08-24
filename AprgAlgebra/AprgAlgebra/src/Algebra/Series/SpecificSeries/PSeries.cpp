#include "PSeries.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba::algebra {

PSeries::PSeries(AlbaNumber const& power) : SeriesBasedOnSummation(getFormula(power), n) {}

Term PSeries::getFormula(AlbaNumber const& power) {
    Term denominatorBase(Polynomial{Monomial(1, {{n, 1}}), Monomial(1, {})});
    Term denominator(createExpressionIfPossible({denominatorBase, "^", power}));
    return Term(createExpressionIfPossible({1, "/", denominator}));
}

}  // namespace alba::algebra
