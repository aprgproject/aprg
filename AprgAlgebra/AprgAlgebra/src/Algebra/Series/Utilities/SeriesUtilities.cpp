#include "SeriesUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

void performLimitComparisonTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series1, SeriesBasedOnSummation const& series2,
    string const& variableName) {
    Term const formula1(series1.getFormulaForEachTermInSummation());
    Term const formula2(series2.getFormulaForEachTermInSummation());
    Term const termForLimitChecking(formula1 / formula2);
    Term const limit(getLimit(termForLimitChecking, variableName, ALBA_NUMBER_POSITIVE_INFINITY));
    if (isTheValue(limit, 0)) {
        if (series2.isConvergent()) {
            isConvergent = true;
        }
    } else if (isTheValue(limit, ALBA_NUMBER_POSITIVE_INFINITY)) {
        if (!series2.isConvergent()) {
            isDivergent = true;
        }
    }
}

void performIntegralTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series, string const& variableName) {
    Integration integration(variableName);
    Term const integratedTerm(integration.integrateAtDefiniteTerms(
        series.getFormulaForEachTermInSummation(), 1, ALBA_NUMBER_POSITIVE_INFINITY));
    if (isTheValue(integratedTerm, ALBA_NUMBER_POSITIVE_INFINITY)) {
        isDivergent = true;
    } else if (!isNan(integratedTerm)) {
        isConvergent = true;
    }
}

void performRatioTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series, string const& variableName) {
    Term const limitTerm(getLimitForRatioTest(series, variableName));
    if (limitTerm.isConstant()) {
        AlbaNumber const limitValue(limitTerm.getAsNumber());
        if (limitValue < 1) {
            isConvergent = true;
        } else if (limitValue > 1) {
            isDivergent = true;
        }
    }
}

void performRootTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series, string const& variableName) {
    Term const formulaForEachTerm(series.getFormulaForEachTermInSummation());
    TermsOverTerms const termsOverTerms(createTermsOverTermsFromTerm(formulaForEachTerm));
    TermsRaiseToTerms termsRaiseToTerms(termsOverTerms.getTermsRaiseToTerms());
    termsRaiseToTerms.multiplyToExponents(Monomial(1, {{variableName, -1}}));
    Term const termForLimit(termsRaiseToTerms.getCombinedTerm());
    Term const limitTerm(getLimit(termForLimit, variableName, ALBA_NUMBER_POSITIVE_INFINITY));
    if (limitTerm.isConstant()) {
        AlbaNumber const limitValue(limitTerm.getAsNumber());
        if (limitValue < 1) {
            isConvergent = true;
        } else if (limitValue > 1) {
            isDivergent = true;
        }
    }
}

PowerSeries getEToTheXPowerSeries() {
    Term const formula(convertExpressionToSimplestTerm(createExpressionIfPossible({1, "/", factorial(n)})));
    return {formula, n, x, 0};
}

Term getLimitForRatioTest(SeriesBasedOnSummation const& series, string const& variableName) {
    SubstitutionOfVariablesToTerms const substitution{
        {variableName, Polynomial{Monomial(1, {{variableName, 1}}), Monomial(1, {})}}};
    Term const formulaForEachTerm(series.getFormulaForEachTermInSummation());
    Term const formulaForEachTermWithPlusOne(substitution.performSubstitutionTo(formulaForEachTerm));
    Term const termForLimit(
        convertPositiveTermIfNegative(formulaForEachTermWithPlusOne) /
        convertPositiveTermIfNegative(formulaForEachTerm));
    return getLimit(termForLimit, variableName, ALBA_NUMBER_POSITIVE_INFINITY);
}

Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(Term const& firstTerm, Term const& lastTerm, Term const& count) {
    return (firstTerm + lastTerm) * count / 2;
}

Term getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
    Term const& firstValue, Term const& commonMultiplier, int const count) {
    return firstValue * (1 - (commonMultiplier ^ count)) / (1 - commonMultiplier);
}

Term getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
    Term const& firstValue, Term const& commonMultiplier) {
    return firstValue / (1 - commonMultiplier);
}

bool isAxiomOfCompletenessTrue(SeriesBasedOnFormula const& series) {
    // Axiom of completeness
    // Every non empty set of real numbers that has a lower bound has a greatest lower bound.
    // Also, every non empty set of real numbers that has an upper bound has a least upper bound.
    AlbaNumberOptional const greatestLowerBound(series.getGreatestLowerBound());
    AlbaNumberOptional const leastUpperBound(series.getLeastUpperBound());
    return (greatestLowerBound && leastUpperBound) || (!greatestLowerBound && !leastUpperBound);
}

bool isBoundedMonotonicSeriesConvergent(SeriesBasedOnFormula const& series) {
    return (series.isBounded() && series.isMonotonic()) == series.isConvergent();
}

bool isConvergentMonotonicSeriesBounded(SeriesBasedOnFormula const& series) {
    return (series.isConvergent() && series.isMonotonic()) == series.isBounded();
}

bool isConvergentUsingComparisonTest(
    SeriesBasedOnSummation const& seriesToCheck, SeriesBasedOnSummation const& convergentSeries,
    int const numberOfIndexesToTest) {
    bool result(false);
    if (convergentSeries.isConvergent()) {
        bool areAllValuesSatisfied(true);
        for (int i = 0; i < static_cast<int>(numberOfIndexesToTest); ++i) {
            Term const termToCheck(seriesToCheck.getTermValueAtIndex(i));
            Term const convergentTerm(convergentSeries.getTermValueAtIndex(i));
            if (termToCheck.isConstant() && convergentTerm.isConstant()) {
                areAllValuesSatisfied = (termToCheck.getAsNumber() <= convergentTerm.getAsNumber());
                if (!areAllValuesSatisfied) {
                    break;
                }
            }
        }
        result = areAllValuesSatisfied;
    }
    return result;
}

bool isDivergentUsingComparisonTest(
    SeriesBasedOnSummation const& seriesToCheck, SeriesBasedOnSummation const& divergentSeries,
    int const numberOfIndexesToTest) {
    bool result(false);
    if (!divergentSeries.isConvergent()) {
        bool areAllValuesSatisfied(true);
        for (int i = 0; i < static_cast<int>(numberOfIndexesToTest); ++i) {
            Term const termToCheck(seriesToCheck.getTermValueAtIndex(i));
            Term const divergentTerm(divergentSeries.getTermValueAtIndex(i));
            if (termToCheck.isConstant() && divergentTerm.isConstant()) {
                areAllValuesSatisfied = (termToCheck.getAsNumber() >= divergentTerm.getAsNumber());
                if (!areAllValuesSatisfied) {
                    break;
                }
            }
        }
        result = areAllValuesSatisfied;
    }
    return result;
}

bool hasLinearity(
    Term const& termToSum, string const& variableName, AlbaNumber const& multiplier, AlbaNumber const& startNumber) {
    Summation const summation(termToSum, variableName);
    Summation const summationInTimesConstant(termToSum * multiplier, variableName);
    Term termWithOuterMultiplier(summation.getSummationModelWithKnownConstant(startNumber) * multiplier);
    Term termWithInnerMultiplier(summationInTimesConstant.getSummationModelWithKnownConstant(startNumber));
    termWithInnerMultiplier.simplify();
    termWithOuterMultiplier.simplify();
    return termWithInnerMultiplier == termWithOuterMultiplier;
}

}  // namespace alba::algebra
