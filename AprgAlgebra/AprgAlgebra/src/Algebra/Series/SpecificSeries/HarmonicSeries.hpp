#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba {

namespace algebra {

class HarmonicSeries : public SeriesBasedOnSummation {
public:
    HarmonicSeries();

protected:
    static Term getFormula();
};

}  // namespace algebra

}  // namespace alba
