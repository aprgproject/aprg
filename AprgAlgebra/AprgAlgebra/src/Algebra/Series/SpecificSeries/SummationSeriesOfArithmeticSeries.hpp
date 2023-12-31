#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba::algebra {

class SummationSeriesOfArithmeticSeries : public SeriesBasedOnSummation {
public:
    SummationSeriesOfArithmeticSeries(AlbaNumber const& firstValue, AlbaNumber const& commonDifference);

    SummationSeriesOfArithmeticSeries(
        AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2,
        int const nthIndex2);

protected:
};

}  // namespace alba::algebra
