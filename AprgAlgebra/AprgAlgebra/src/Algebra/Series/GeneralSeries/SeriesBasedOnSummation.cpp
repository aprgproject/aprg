#include "SeriesBasedOnSummation.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

SeriesBasedOnSummation::SeriesBasedOnSummation(Term const& formulaForEachTermInSummation, string const& variableName)
    : SeriesBasedOnFormula(getFormulaForSummation(formulaForEachTermInSummation, variableName), variableName),
      m_formulaForEachTermInSummation(formulaForEachTermInSummation),
      m_summation(getSummation(formulaForEachTermInSummation, variableName)),
      m_isSummationModelValid(!isNan(getFormulaForSeries())) {}

Term SeriesBasedOnSummation::getValueAtIndex(int const index) const {
    Term result;
    if (m_isSummationModelValid) {
        result = SeriesBasedOnFormula::getValueAtIndex(index);
    } else {
        result = m_summation.getSum(0, index);
    }
    return result;
}

Term SeriesBasedOnSummation::getTermValueAtIndex(int const index) const {
    SubstitutionOfVariablesToValues const substitution{{m_variableName, index}};
    return substitution.performSubstitutionTo(m_formulaForEachTermInSummation);
}

Term SeriesBasedOnSummation::getFormulaForEachTermInSummation() const { return m_formulaForEachTermInSummation; }
bool SeriesBasedOnSummation::isSummationModelValid() const { return m_isSummationModelValid; }

bool SeriesBasedOnSummation::isAbsolutelyConvergent() const {
    SeriesBasedOnSummation const summation(abs(m_formulaForEachTermInSummation), m_variableName);
    return summation.isConvergent();
}

bool SeriesBasedOnSummation::isConditionallyConvergent() const { return !isAbsolutelyConvergent() || isConvergent(); }

Summation SeriesBasedOnSummation::getSummation(Term const& formulaForEachTermInSummation, string const& variableName) {
    Summation summation(formulaForEachTermInSummation, variableName);
    return summation;
}

Term SeriesBasedOnSummation::getFormulaForSummation(
    Term const& formulaForEachTermInSummation, string const& variableName) {
    return getSummation(formulaForEachTermInSummation, variableName).getSummationModelWithKnownConstant(0);
}

bool SeriesBasedOnSummation::isConvergent() const {
    bool result(false);
    if (m_isSummationModelValid) {
        result = SeriesBasedOnFormula::isConvergent();
    } else {
        result = getLimit(m_formulaForEachTermInSummation, m_variableName, ALBA_NUMBER_POSITIVE_INFINITY) == 0;
    }
    return result;
}

}  // namespace alba::algebra
