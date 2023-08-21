#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba {

namespace algebra {

class PSeries : public SeriesBasedOnSummation {
public:
    PSeries(AlbaNumber const& power);

protected:
    static Term getFormula(AlbaNumber const& power) ;
};

}  // namespace algebra

}  // namespace alba
