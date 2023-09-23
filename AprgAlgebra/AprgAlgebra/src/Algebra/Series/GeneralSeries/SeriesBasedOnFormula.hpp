#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <string>

namespace alba::algebra {

class SeriesBasedOnFormula {
public:
    virtual ~SeriesBasedOnFormula() = default;  // virtual destructor because of virtual functions (vtable exists)
    SeriesBasedOnFormula(SeriesBasedOnFormula const &series) = default;
    SeriesBasedOnFormula(SeriesBasedOnFormula &&series) = default;
    SeriesBasedOnFormula &operator=(SeriesBasedOnFormula const &series) = default;
    SeriesBasedOnFormula &operator=(SeriesBasedOnFormula &&series) = default;
    SeriesBasedOnFormula(Term const &formulaForSeries, std::string const &variableName);
    SeriesBasedOnFormula(Term &&formulaForSeries, std::string &&variableName);
    [[nodiscard]] virtual AlbaNumberOptional getGreatestLowerBound() const;
    [[nodiscard]] virtual AlbaNumberOptional getLeastUpperBound() const;
    [[nodiscard]] virtual Term getFormulaForSeries() const;
    [[nodiscard]] virtual Term getValueAtIndex(int const index) const;
    [[nodiscard]] virtual Term getSum(int const startingIndex, int const endingIndex) const;
    [[nodiscard]] virtual Term getSumStartingAtIndexAndToInfinity(int const startingIndex) const;
    [[nodiscard]] virtual Term getValueAtInfinity() const;
    [[nodiscard]] virtual Term getRemainderAtIndex(int const index) const;
    [[nodiscard]] virtual std::string getNameForVariableInFormula() const;
    [[nodiscard]] virtual bool isConvergent() const;
    [[nodiscard]] virtual bool isIncreasing() const;
    [[nodiscard]] virtual bool isDecreasing() const;
    [[nodiscard]] virtual bool isMonotonic() const;
    [[nodiscard]] virtual bool isBounded() const;

protected:
    [[nodiscard]] AlbaNumbers getBoundValues() const;
    [[nodiscard]] AlbaNumbers getExtremaIndexes() const;
    [[nodiscard]] Term getSignDerivativeForFiniteCalculus() const;
    Term m_formulaForSeries;
    std::string m_variableName;
};

}  // namespace alba::algebra
