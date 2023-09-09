#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba::algebra {

class AlternatingSeries : public SeriesBasedOnSummation {
public:
    AlternatingSeries(Term const& formulaForEachTermWithoutSign, std::string const& variableName);
    [[nodiscard]] Term getRemainderAtIndex(int const index) const override;
    [[nodiscard]] bool isConvergent() const override;

protected:
    static Term getFormula(Term const& formulaForEachTermWithoutSign, std::string const& variableName);
    Term m_formulaForEachTermWithoutSign;
};

}  // namespace alba::algebra
