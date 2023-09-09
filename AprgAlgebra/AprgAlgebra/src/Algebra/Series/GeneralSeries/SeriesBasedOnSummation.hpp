#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>
#include <Algebra/Summation/Summation.hpp>

namespace alba::algebra {

class SeriesBasedOnSummation : public SeriesBasedOnFormula {
public:
    SeriesBasedOnSummation(Term const& formulaForEachTermInSummation, std::string const& variableName);
    [[nodiscard]] Term getValueAtIndex(int const index) const override;
    [[nodiscard]] Term getTermValueAtIndex(int const index) const;
    [[nodiscard]] Term getFormulaForEachTermInSummation() const;
    [[nodiscard]] bool isSummationModelValid() const;
    [[nodiscard]] bool isConvergent() const override;
    [[nodiscard]] bool isAbsolutelyConvergent() const;
    [[nodiscard]] bool isConditionallyConvergent() const;

protected:
    static Summation getSummation(Term const& formulaForEachTermInSummation, std::string const& variableName);
    static Term getFormulaForSummation(Term const& formulaForEachTermInSummation, std::string const& variableName);
    Term m_formulaForEachTermInSummation;
    Summation m_summation;
    bool m_isSummationModelValid;
};

}  // namespace alba::algebra
