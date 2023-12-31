#include "Equation.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfEquation.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba::algebra {

Equation::Equation(Term const& leftHandTerm, string const& equationOperator, Term const& rightHandTerm)
    : m_equationOperator(equationOperator), m_leftHandTerm(leftHandTerm), m_rightHandTerm(rightHandTerm) {}

Equation::Equation(Term&& leftHandTerm, string&& equationOperator, Term&& rightHandTerm)
    : m_equationOperator(equationOperator), m_leftHandTerm(leftHandTerm), m_rightHandTerm(rightHandTerm) {}

bool Equation::operator==(Equation const& second) const {
    return m_equationOperator == second.m_equationOperator && m_leftHandTerm == second.m_leftHandTerm &&
           m_rightHandTerm == second.m_rightHandTerm;
}

bool Equation::operator!=(Equation const& second) const { return !(operator==(second)); }

bool Equation::operator<(Equation const& second) const {
    bool result(false);
    if (m_equationOperator == second.m_equationOperator) {
        if (m_leftHandTerm == second.m_leftHandTerm) {
            result = m_rightHandTerm < second.m_rightHandTerm;
        } else {
            result = m_leftHandTerm < second.m_leftHandTerm;
        }
    } else {
        result = m_equationOperator < second.m_equationOperator;
    }
    return result;
}

EquationOperator const& Equation::getEquationOperator() const { return m_equationOperator; }
Term const& Equation::getLeftHandTerm() const { return m_leftHandTerm; }
Term const& Equation::getRightHandTerm() const { return m_rightHandTerm; }

bool Equation::isEmpty() const {
    return m_equationOperator.getOperatorString().empty() && m_leftHandTerm.isEmpty() && m_rightHandTerm.isEmpty();
}

bool Equation::isEquationSatisfied() const {
    return isEquationOperationSatisfied(m_equationOperator, m_leftHandTerm, m_rightHandTerm);
}

void Equation::simplify() {
    SimplificationOfEquation simplification(*this);
    simplification.simplify();
    *this = simplification.getEquation();
}

Term& Equation::getLeftHandTermReference() { return m_leftHandTerm; }
Term& Equation::getRightHandTermReference() { return m_rightHandTerm; }

ostream& operator<<(ostream& out, Equation const& equation) {
    out << equation.m_leftHandTerm << " " << equation.m_equationOperator << " " << equation.m_rightHandTerm;
    return out;
}

}  // namespace alba::algebra
