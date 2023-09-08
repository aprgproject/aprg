#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class TaylorSeries {
public:
    TaylorSeries(Term const& formulaForTaylorSeries, std::string const& variableName);
    [[nodiscard]] Term getFormulaForTaylorSeries() const;
    [[nodiscard]] Term getValueAtIndex(int const index, Term const& startingValue) const;
    [[nodiscard]] Term getValueForMaclaurinSeriesAtIndex(int const index) const;

protected:
    Term m_formulaForTaylorSeries;
    std::string m_variableName;
};

}  // namespace alba::algebra
