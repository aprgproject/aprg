#include "ArithmeticSeries.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba::algebra {

ArithmeticSeries::ArithmeticSeries(AlbaNumber const& firstValue, AlbaNumber const& commonDifference)
    : SeriesBasedOnFormula(getFormula(firstValue, commonDifference), n) {}

ArithmeticSeries::ArithmeticSeries(
    AlbaNumber const& valueAtIndex1, int const index1, AlbaNumber const& valueAtIndex2, int const index2)
    : SeriesBasedOnFormula(getFormula(valueAtIndex1, index1, valueAtIndex2, index2), n) {}

Term ArithmeticSeries::getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonDifference) {
    return {Term(firstValue) + Term(commonDifference) * Term(n)};
}

Term ArithmeticSeries::getFormula(
    AlbaNumber const& valueAtIndex1, int const index1, AlbaNumber const& valueAtIndex2, int const index2) {
    AlbaNumber const commonDifference = (valueAtIndex1 - valueAtIndex2) / (index1 - index2);
    AlbaNumber const firstValue = valueAtIndex1 - commonDifference * index1;
    return getFormula(firstValue, commonDifference);
}

}  // namespace alba::algebra
