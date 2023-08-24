#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class Summation {
public:
    Summation(Term const& termToSum, std::string const& variableName);

    [[nodiscard]] Term getSummationModelWithKnownConstant(AlbaNumber const& startNumber) const;
    [[nodiscard]] Term getSummationModelWithUnknownConstant() const;

    [[nodiscard]] Term getSum(Term const& start, Term const& end) const;

private:
    void calculateSumFromANumberToANumber(
        Term& result, AlbaNumber const& startNumber, AlbaNumber const& endNumber) const;
    void calculateSumStartingFromANumber(Term& result, AlbaNumber const& startNumber, Term const& end) const;
    void calculateSumUsingEachTerm(Term& result, AlbaNumber const& startNumber, AlbaNumber const& endNumber) const;
    void calculateSumUsingModel(Term& result, AlbaNumber const& startNumber, AlbaNumber const& endNumber) const;
    [[nodiscard]] Term getSummationModel() const;

    Term m_termToSum;
    std::string m_variableName;
    Term m_summationModel;
};

}  // namespace alba::algebra
