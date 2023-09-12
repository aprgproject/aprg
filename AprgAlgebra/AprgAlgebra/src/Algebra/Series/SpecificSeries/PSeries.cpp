#include "PSeries.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba::algebra {

PSeries::PSeries(AlbaNumber const& power) : SeriesBasedOnSummation(getFormula(power), n) {}

Term PSeries::getFormula(AlbaNumber const& power) {
    Term const denominatorBase(Polynomial{Monomial(1, {{n, 1}}), Monomial(1, {})});
    Term const denominator(createExpressionIfPossible({denominatorBase, "^", power}));
    return {createExpressionIfPossible({1, "/", denominator})};
}

}  // namespace alba::algebra
