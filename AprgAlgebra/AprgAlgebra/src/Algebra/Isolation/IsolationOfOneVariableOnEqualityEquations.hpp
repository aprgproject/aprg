#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba::algebra {

class IsolationOfOneVariableOnEqualityEquations {
public:
    explicit IsolationOfOneVariableOnEqualityEquations(Equations const& equations);
    explicit IsolationOfOneVariableOnEqualityEquations(Equations&& equations);
    [[nodiscard]] Term getEquivalentTermByIsolatingAVariable(std::string const& variableName) const;
    void isolateTermWithVariable(
        std::string const& variableName, Term& termWithVariable, Term& termWithWithoutVariable) const;

private:
    static void sortEquationsWithVariable(Equations& equationsWithVariable);
    Equations m_equations;
};

}  // namespace alba::algebra
