#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>
#include <Common/Math/Number/Interval/AlbaNumberInterval.hpp>

namespace alba::algebra {

class PowerSeries : public SeriesBasedOnSummation {
public:
    PowerSeries(
        Term const& multiplierForEachTerm, std::string const& nName, std::string const& xName,
        AlbaNumber const& aValue);

    [[nodiscard]] AlbaNumber getRadiusOfConvergence() const;
    [[nodiscard]] AlbaNumberIntervals getIntervalsOfConvergence() const;
    void differentiate();
    void integrate();

protected:
    static Term getFormula(
        Term const& multiplierForEachTerm, std::string const& nName, std::string const& xName,
        AlbaNumber const& aValue);

    std::string const m_nName;
    std::string const m_xName;
};

}  // namespace alba::algebra
