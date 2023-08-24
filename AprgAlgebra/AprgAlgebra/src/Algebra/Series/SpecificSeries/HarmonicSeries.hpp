#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba::algebra {

class HarmonicSeries : public SeriesBasedOnSummation {
public:
    HarmonicSeries();

protected:
    static Term getFormula();
};

}  // namespace alba::algebra
