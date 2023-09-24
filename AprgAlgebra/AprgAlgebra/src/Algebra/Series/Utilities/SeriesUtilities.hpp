#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>
#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>
#include <Algebra/Series/SpecificSeries/AlternatingSeries.hpp>
#include <Algebra/Series/SpecificSeries/PowerSeries.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

void performLimitComparisonTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series1, SeriesBasedOnSummation const& series2,
    std::string const& variableName);

void performIntegralTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series, std::string const& variableName);

void performRatioTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series, std::string const& variableName);

void performRootTest(
    bool& isConvergent, bool& isDivergent, SeriesBasedOnSummation const& series, std::string const& variableName);

PowerSeries getEToTheXPowerSeries();
Term getLimitForRatioTest(SeriesBasedOnSummation const& series, std::string const& variableName);
Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(Term const& firstTerm, Term const& lastTerm, Term const& count);

Term getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
    Term const& firstValue, Term const& commonMultiplier, int const count);

Term getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
    Term const& firstValue, Term const& commonMultiplier);

bool isAxiomOfCompletenessTrue(SeriesBasedOnFormula const& series);
bool isBoundedMonotonicSeriesConvergent(SeriesBasedOnFormula const& series);
bool isConvergentMonotonicSeriesBounded(SeriesBasedOnFormula const& series);

bool isConvergentUsingComparisonTest(
    SeriesBasedOnSummation const& seriesToCheck, SeriesBasedOnSummation const& convergentSeries,
    int const numberOfIndexesToTest);

bool isDivergentUsingComparisonTest(
    SeriesBasedOnSummation const& seriesToCheck, SeriesBasedOnSummation const& divergentSeries,
    int const numberOfIndexesToTest);

bool hasLinearity(
    Term const& termToSum, std::string const& variableName, AlbaNumber const& multiplier,
    AlbaNumber const& startNumber);

}  // namespace alba::algebra
