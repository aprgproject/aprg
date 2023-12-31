#include "TaylorSeries.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>

using namespace std;

namespace alba::algebra {

TaylorSeries::TaylorSeries(Term const& formulaForTaylorSeries, string const& variableName)
    : m_formulaForTaylorSeries(formulaForTaylorSeries), m_variableName(variableName) {}

TaylorSeries::TaylorSeries(Term&& formulaForTaylorSeries, string&& variableName)
    : m_formulaForTaylorSeries(formulaForTaylorSeries), m_variableName(variableName) {}

Term TaylorSeries::getFormulaForTaylorSeries() const { return m_formulaForTaylorSeries; }

Term TaylorSeries::getValueAtIndex(int const index, Term const& startingValue) const {
    Term result;
    if (index >= 0) {
        int const positiveIndex(static_cast<int>(index));
        result = getApproximationUsingTaylorsFormula(
            m_formulaForTaylorSeries, m_variableName, startingValue, m_variableName, positiveIndex);
    }
    return result;
}

Term TaylorSeries::getValueForMaclaurinSeriesAtIndex(int const index) const { return getValueAtIndex(index, 0); }

}  // namespace alba::algebra
