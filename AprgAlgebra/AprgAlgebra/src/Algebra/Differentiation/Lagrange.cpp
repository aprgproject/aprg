#include "Lagrange.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

void calculateLagrangeEquations(
    Equations& lagrangeEquations, Term const& termWithLagrangeFunctions, strings const& coordinateNames,
    strings const& lagrangeMultiplierNames) {
    for (string const& coordinateName : coordinateNames) {
        lagrangeEquations.emplace_back(getPartialDerivative(termWithLagrangeFunctions, coordinateName), "=", 0);
    }
    for (string const& lagrangeMultiplierName : lagrangeMultiplierNames) {
        lagrangeEquations.emplace_back(getPartialDerivative(termWithLagrangeFunctions, lagrangeMultiplierName), "=", 0);
    }
}

Term getTermWithLagrangeFunctions(
    Term const& term, Terms const& lagrangeFunctions, strings const& lagrangeMultiplierNames) {
    int const size(min(lagrangeFunctions.size(), lagrangeMultiplierNames.size()));
    Term result(term);
    for (int i = 0; i < size; ++i) {
        result += lagrangeFunctions[i] * Term(lagrangeMultiplierNames[i]);
    }
    return result;
}

Terms getLagrangeMultipliers(Term const& term, strings const& coordinateNames, Terms const& lagrangeFunctions) {
    strings const lagrangeMultiplierNames(getLagrangeMultiplierNames(lagrangeFunctions.size()));
    Term const termWithLagrangeFunctions(
        getTermWithLagrangeFunctions(term, lagrangeFunctions, lagrangeMultiplierNames));
    Equations lagrangeEquations;
    calculateLagrangeEquations(lagrangeEquations, termWithLagrangeFunctions, coordinateNames, lagrangeMultiplierNames);

    Terms result;
    IsolationOfOneVariableOnEqualityEquations const isolation(lagrangeEquations);
    for (string const& lagrangeMultiplierName : lagrangeMultiplierNames) {
        result.emplace_back(isolation.getEquivalentTermByIsolatingAVariable(lagrangeMultiplierName));
    }
    return result;
}

string getLagrangeMultiplierName(int const index) {
    static StringConverterWithFormatting const converter(3, '0');
    return "multiplier" + converter.convertToString(index);
}

strings getLagrangeMultiplierNames(int const size) {
    strings result;
    for (int i = 0; i < size; ++i) {
        result.emplace_back(getLagrangeMultiplierName(i));
    }
    return result;
}

}  // namespace alba::algebra
