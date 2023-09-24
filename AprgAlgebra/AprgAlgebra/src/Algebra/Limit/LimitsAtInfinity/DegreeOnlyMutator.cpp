#include "DegreeOnlyMutator.hpp"

using namespace std;

namespace alba::algebra {

DegreeOnlyMutator::DegreeOnlyMutator(string const& variableName) : m_variableName(variableName) {}
DegreeOnlyMutator::DegreeOnlyMutator(string&& variableName) : m_variableName(variableName) {}

Monomial DegreeOnlyMutator::getMonomialWithDegree(AlbaNumber const& degree) const {
    Monomial result(1, {{m_variableName, degree}});
    if (degree == 0) {
        result = Monomial(1, {});
    }
    return result;
}

AlbaNumber DegreeOnlyMutator::getMaxDegreeForVariable(Polynomial const& polynomial) {
    AlbaNumber maxDegreeForVariable;
    auto const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        maxDegreeForVariable = monomials.front().getExponentForVariable(m_variableName);
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); ++it) {
            AlbaNumber const currentDegreeForVariable(it->getExponentForVariable(m_variableName));
            if (maxDegreeForVariable < currentDegreeForVariable) {
                maxDegreeForVariable = currentDegreeForVariable;
            }
        }
    }
    return maxDegreeForVariable;
}

void DegreeOnlyMutator::mutateTerm(Term& term) {
    Term beforeMutation;
    do {
        beforeMutation = term;
        BaseMutator::mutateTerm(term);
        term.simplify();
    } while (beforeMutation != term);
}

void DegreeOnlyMutator::mutateMonomial(Monomial& monomial) {
    AlbaNumber const degreeForVariable(monomial.getExponentForVariable(m_variableName));
    monomial = getMonomialWithDegree(degreeForVariable);
}

void DegreeOnlyMutator::mutatePolynomial(Polynomial& polynomial) {
    AlbaNumber const maxDegreeForVariable(getMaxDegreeForVariable(polynomial));
    polynomial.clear();
    polynomial.addMonomial(getMonomialWithDegree(maxDegreeForVariable));
}

void DegreeOnlyMutator::mutateExpression(Expression& expression) {
    Expression beforeMutation;
    do {
        beforeMutation = expression;
        BaseMutator::mutateExpression(expression);
        expression.simplify();
    } while (beforeMutation != expression);
}

}  // namespace alba::algebra
