#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba::algebra {

class PSeries : public SeriesBasedOnSummation {
public:
    explicit PSeries(AlbaNumber const& power);

protected:
    static Term getFormula(AlbaNumber const& power);
};

}  // namespace alba::algebra
