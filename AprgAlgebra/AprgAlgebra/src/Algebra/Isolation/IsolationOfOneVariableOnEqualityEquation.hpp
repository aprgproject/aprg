#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba {

namespace algebra {

class IsolationOfOneVariableOnEqualityEquation {
public:
    IsolationOfOneVariableOnEqualityEquation(Equation const& equation);

    bool canBeIsolated(std::string const& variableName) const;
    AlbaNumber getIdenticalExponentForVariableIfPossible(std::string const& variableName) const;
    Term getEquivalentTermByIsolatingAVariable(std::string const& variableName) const;
    Equation isolateTermWithVariableOnLeftSideOfEquation(std::string const& variableName) const;
    Equation isolateTermWithVariableOnRightSideOfEquation(std::string const& variableName) const;

    void isolateTermWithVariable(
        std::string const& variableName, Term& termWithVariable, Term& termWithWithoutVariable) const;

    void setEquation(Equation const& equation);

private:
    static void isolateTermWithVariable(
        std::string const& variableName, Polynomial const& polynomial, Term& termWithVariable,
        Term& termWithWithoutVariable) ;
    static void isolateTermWithVariable(
        std::string const& variableName, Expression const& expression, Term& termWithVariable,
        Term& termWithWithoutVariable) ;
    static bool canBeIsolatedBasedOnExponent(AlbaNumber const& identicalExponentForVariable) ;
    static AlbaNumber getIdenticalExponentForVariableIfPossible(
        std::string const& variableName, Polynomial const& polynomial) ;
    static void simplifyForIsolation(Term& term) ;
    static void simplifyForIsolation(Expression& expression) ;
    Term m_simplifiedLeftSideTerm;
};

}  // namespace algebra

}  // namespace alba
