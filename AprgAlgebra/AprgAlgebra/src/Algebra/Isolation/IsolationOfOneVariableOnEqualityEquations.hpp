#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba {

namespace algebra {

class IsolationOfOneVariableOnEqualityEquations {
public:
    IsolationOfOneVariableOnEqualityEquations(Equations const& equations);

    void isolateTermWithVariable(
        std::string const& variableName, Term& termWithVariable, Term& termWithWithoutVariable) const;
    Term getEquivalentTermByIsolatingAVariable(std::string const& variableName) const;

private:
    static void sortEquationsWithVariable(Equations& equationsWithVariable);

    Equations m_equations;
};

}  // namespace algebra

}  // namespace alba
