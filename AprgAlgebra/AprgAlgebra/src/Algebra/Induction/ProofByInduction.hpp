#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class ProofByInduction {
public:
    using ManualCalculationFunction = std::function<AlbaNumber(AlbaNumber const&)>;

    ProofByInduction(
        std::string const& variableName, Term const& expressionForEachStep, Operator const& accumulateOperator,
        Term const& guessExpression, ManualCalculationFunction const& manualCalculation);
    ProofByInduction(
        std::string&& variableName, Term&& expressionForEachStep, Operator&& accumulateOperator, Term&& guessExpression,
        ManualCalculationFunction&& manualCalculation);

    [[nodiscard]] bool isCorrectOnASpecificValue(AlbaNumber const& value) const;
    [[nodiscard]] bool isCorrectOnInductionStep() const;
    std::string m_variableName;
    Term m_expressionForEachStep;
    Operator m_accumulateOperator;
    Term m_guessExpression;
    ManualCalculationFunction m_manualCalculation;
};

}  // namespace alba::algebra
