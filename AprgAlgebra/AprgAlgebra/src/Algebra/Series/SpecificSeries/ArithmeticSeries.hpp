#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>

namespace alba::algebra {

class ArithmeticSeries : public SeriesBasedOnFormula {
public:
    ArithmeticSeries(AlbaNumber const& firstValue, AlbaNumber const& commonDifference);

    ArithmeticSeries(
        AlbaNumber const& valueAtIndex1, int const index1, AlbaNumber const& valueAtIndex2, int const index2);

protected:
    static Term getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonDifference);

    static Term getFormula(
        AlbaNumber const& valueAtIndex1, int const index1, AlbaNumber const& valueAtIndex2, int const index2);
};

}  // namespace alba::algebra
