#include "HarmonicSeries.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba::algebra {

HarmonicSeries::HarmonicSeries() : SeriesBasedOnSummation(getFormula(), n) {}

Term HarmonicSeries::getFormula() {
    Term denominator(Polynomial{Monomial(1, {{n, 1}}), Monomial(1, {})});
    return Term(createExpressionIfPossible({1, "/", denominator}));
}

}  // namespace alba
