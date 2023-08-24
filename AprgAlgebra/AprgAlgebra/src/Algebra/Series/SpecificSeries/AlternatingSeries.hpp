#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba::algebra {

class AlternatingSeries : public SeriesBasedOnSummation {
public:
    AlternatingSeries(Term const& formulaForEachTermWithoutSign, std::string const& variableName);

    [[nodiscard]] bool isConvergent() const override;
    [[nodiscard]] Term getRemainderAtIndex(int const index) const override;

protected:
    static Term getFormula(Term const& formulaForEachTermWithoutSign, std::string const& variableName);
    Term m_formulaForEachTermWithoutSign;
};

}  // namespace alba::algebra
