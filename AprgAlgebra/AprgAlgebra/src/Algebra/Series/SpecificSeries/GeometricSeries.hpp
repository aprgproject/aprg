#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>

namespace alba::algebra {

class GeometricSeries : public SeriesBasedOnFormula {
public:
    GeometricSeries(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier);

    GeometricSeries(
        AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2,
        int const nthIndex2);

    Term getInfiniteSumStartingFrom(int const startingNthIndex);

protected:
    static Term getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier);
    static Term getFormula(
        AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2,
        int const nthIndex2);
};

}  // namespace alba::algebra
