#include "BaseSolver.hpp"

namespace alba::algebra {

bool BaseSolver::isSolved() const { return m_isSolved; }
bool BaseSolver::isACompleteSolution() const { return m_isACompleteSolution; }

void BaseSolver::setAsCompleteSolution() {
    m_isSolved = true;
    m_isACompleteSolution = true;
}

void BaseSolver::setAsIncompleteSolution() {
    m_isSolved = true;
    m_isACompleteSolution = false;
}

}  // namespace alba::algebra
