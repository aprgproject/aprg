#include "PowerSeries.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Series/Utilities/SeriesUtilities.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableNonEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <numeric>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

PowerSeries::PowerSeries(
    Term const& multiplierForEachTerm, string const& nName, string const& xName, AlbaNumber const& aValue)
    : SeriesBasedOnSummation(getFormula(multiplierForEachTerm, nName, xName, aValue), nName),
      m_nName(nName),
      m_xName(xName) {}

AlbaNumber PowerSeries::getRadiusOfConvergence() const {
    AlbaNumberIntervals const intervals(getIntervalsOfConvergence());
    AlbaNumber result = accumulate(
        intervals.cbegin(), intervals.cend(), AlbaNumber(),
        [](AlbaNumber const& partialSum, AlbaNumberInterval const& nextInterval) {
            return partialSum +
                   getAbsoluteValue(
                       nextInterval.getHigherEndpoint().getValue() - nextInterval.getLowerEndpoint().getValue());
        });
    result = result / static_cast<int64_t>(intervals.size()) / 2;
    return result;
}

AlbaNumberIntervals PowerSeries::getIntervalsOfConvergence() const {
    Term const limitForRatioTest(
        getLimitForRatioTest(static_cast<SeriesBasedOnSummation const&>(*this), getNameForVariableInFormula()));
    Term const limitWithAbsoluteValue(abs(limitForRatioTest));
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet const solutionSet(
        solver.calculateSolutionAndReturnSolutionSet(Equation(limitWithAbsoluteValue, "<", 1)));
    return solutionSet.getAcceptedIntervals();
}

void PowerSeries::differentiate() {
    Differentiation const differentiation(m_xName);
    m_formulaForEachTermInSummation = differentiation.differentiate(m_formulaForEachTermInSummation);
    m_isSummationModelValid = false;
}

void PowerSeries::integrate() {
    Integration integration(m_xName);
    m_formulaForEachTermInSummation = integration.integrate(m_formulaForEachTermInSummation);
    m_isSummationModelValid = false;
}

Term PowerSeries::getFormula(
    Term const& multiplierForEachTerm, string const& nName, string const& xName, AlbaNumber const& aValue) {
    Term const subTerm(createExpressionIfPossible({xName, "-", aValue}));
    return createExpressionIfPossible({multiplierForEachTerm, "*", subTerm, "^", nName});
}

}  // namespace alba::algebra
