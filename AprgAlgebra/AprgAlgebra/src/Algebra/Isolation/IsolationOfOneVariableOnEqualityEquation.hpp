#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba::algebra {

class IsolationOfOneVariableOnEqualityEquation {
public:
    explicit IsolationOfOneVariableOnEqualityEquation(Equation const& equation);
    [[nodiscard]] AlbaNumber getIdenticalExponentForVariableIfPossible(std::string const& variableName) const;
    [[nodiscard]] Equation isolateTermWithVariableOnLeftSideOfEquation(std::string const& variableName) const;
    [[nodiscard]] Equation isolateTermWithVariableOnRightSideOfEquation(std::string const& variableName) const;
    [[nodiscard]] Term getEquivalentTermByIsolatingAVariable(std::string const& variableName) const;
    [[nodiscard]] bool canBeIsolated(std::string const& variableName) const;

    void isolateTermWithVariable(
        std::string const& variableName, Term& termWithVariable, Term& termWithWithoutVariable) const;

    void setEquation(Equation const& equation);

private:
    static void isolateTermWithVariable(
        std::string const& variableName, Polynomial const& polynomial, Term& termWithVariable,
        Term& termWithWithoutVariable);

    static void isolateTermWithVariable(
        std::string const& variableName, Expression const& expression, Term& termWithVariable,
        Term& termWithWithoutVariable);

    static void simplifyForIsolation(Term& term);
    static void simplifyForIsolation(Expression& expression);

    static AlbaNumber getIdenticalExponentForVariableIfPossible(
        std::string const& variableName, Polynomial const& polynomial);

    static bool canBeIsolatedBasedOnExponent(AlbaNumber const& identicalExponentForVariable);
    Term m_simplifiedLeftSideTerm;
};

}  // namespace alba::algebra
