#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

enum class ExtremumType { Unknown, Maximum, Minimum, SaddlePoint };

struct MinimumAndMaximum {
    std::pair<AlbaNumber, AlbaNumber> minimumInputOutputValues;
    std::pair<AlbaNumber, AlbaNumber> maximumInputOutputValues;
};

struct Extremum {
    ExtremumType extremumType{ExtremumType::Unknown};
    std::pair<AlbaNumber, AlbaNumber> inputOutputValues;
};

struct ExtremumWithMultipleVariables {
    ExtremumType extremumType{ExtremumType::Unknown};
    std::map<std::string, AlbaNumber> variableNamesToValues;
};

using Extrema = std::vector<Extremum>;
using ExtremaWithMultipleVariables = std::vector<ExtremumWithMultipleVariables>;
using VariableNameToCriticalNumbersMap = std::map<std::string, AlbaNumbers>;

AlbaNumbers getInputValuesInIntervalWithSameAsMeanOfInterval(
    Term const& term, std::string const& variableName, AlbaNumber const& a, AlbaNumber const& b);

AlbaNumbers getInputValuesForCauchyMeanValueTheorem(
    Term const& term, std::string const& variableName, AlbaNumber const& a, AlbaNumber const& b);

AlbaNumbers getCriticalNumbers(Term const& term, std::string const& variableName);
AlbaNumbers getInputValuesAtPointsOfInflection(Term const& term, std::string const& variableName);
Extrema getRelativeExtrema(Term const& term, std::string const& variableName);

ExtremaWithMultipleVariables getRelativeExtremaWithMultipleVariables(
    Term const& term, stringHelper::strings const& coordinateNames);

Extremum getAbsoluteExtremumBasedOnRelativeExtremaOnInterval(
    Extrema const& relativeExtrema, AlbaNumberInterval const& interval);

MinimumAndMaximum getMinimumAndMaximumAtClosedInterval(
    Term const& term, std::string const& variableName, AlbaNumberInterval const& closedInterval);

VariableNameToCriticalNumbersMap getCriticalNumbersWithMultipleVariables(
    Term const& term, stringHelper::strings const& coordinateNames);

bool willYieldToAbsoluteMinimumValue(
    Term const& term, std::string const& variableName, AlbaNumber const& valueForEvaluation);

bool willYieldToAbsoluteMaximumValue(
    Term const& term, std::string const& variableName, AlbaNumber const& valueForEvaluation);

bool willYieldToRelativeMinimumValue(
    Term const& term, std::string const& variableName, AlbaNumber const& valueForEvaluation,
    AlbaNumberInterval const& openInterval);

bool willYieldToRelativeMaximumValue(
    Term const& term, std::string const& variableName, AlbaNumber const& valueForEvaluation,
    AlbaNumberInterval const& openInterval);

bool willYieldToExtremumValue(
    ExtremumType const extremumType, Term const& term, std::string const& variableName,
    AlbaNumber const& valueForEvaluation, AlbaNumbers const& valuesUsedForChecking);

bool isDerivativeZeroOnPossibleExtremum(
    Term const& term, std::string const& variableName, AlbaNumber const& valueAtPossibleExtremum,
    AlbaNumberInterval const& interval);

bool isDecreasingAt(Term const& term, std::string const& variableName, AlbaNumber const& value);
bool isIncreasingAt(Term const& term, std::string const& variableName, AlbaNumber const& value);
bool isConcaveDownwardAt(Term const& term, std::string const& variableName, AlbaNumber const& value);
bool isConcaveUpwardAt(Term const& term, std::string const& variableName, AlbaNumber const& value);
bool hasPointOfInflectionAt(Term const& term, std::string const& variableName, AlbaNumber const& value);

bool isRolleTheoremSatisfied(
    Term const& term, std::string const& variableName, AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);

}  // namespace alba::algebra
