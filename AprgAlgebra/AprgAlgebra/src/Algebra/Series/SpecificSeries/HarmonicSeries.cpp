#include "HarmonicSeries.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba::algebra {

HarmonicSeries::HarmonicSeries() : SeriesBasedOnSummation(getFormula(), n) {}

Term HarmonicSeries::getFormula() {
    Term const denominator(Polynomial{Monomial(1, {{n, 1}}), Monomial(1, {})});
    return {createExpressionIfPossible({1, "/", denominator})};
}

}  // namespace alba::algebra
