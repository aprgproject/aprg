#include "NewtonMethod.hpp"

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

// In numerical analysis, Newton's method, also known as the Newton–Raphson method, named after Isaac Newton and Joseph
// Raphson, is a root-finding algorithm which produces successively better approximations to the roots (or zeroes) of a
// real-valued function.
NewtonMethod::NewtonMethod(AlbaNumber const& initialValue, Function const& functionToIterate)
    : m_currentValue(initialValue),
      m_positiveDeltaForSlope(INITIAL_DELTA_FOR_SLOPE),
      m_functionToIterate(functionToIterate) {}

NewtonMethod::NewtonMethod(AlbaNumber&& initialValue, Function&& functionToIterate)
    : m_currentValue(initialValue),
      m_positiveDeltaForSlope(INITIAL_DELTA_FOR_SLOPE),
      m_functionToIterate(functionToIterate) {}

AlbaNumber const& NewtonMethod::getCurrentValue() const { return m_currentValue; }
int NewtonMethod::getNumberOfIterationsExecuted() const { return m_numberOfIterationsExecuted; }
bool NewtonMethod::isSolved() const { return m_functionToIterate(m_currentValue) == 0; }
bool NewtonMethod::isFinished() const { return !m_currentValue.isARealFiniteValue() || isSolved(); }

void NewtonMethod::runOneIteration() {
    AlbaNumber::ScopeConfigurationObject const scopeConfigurationObject;
    AlbaNumber::ScopeConfigurationObject::setInThisScopeTheTolerancesToZero();

    AlbaNumber const newValue =
        m_currentValue - (m_functionToIterate(m_currentValue) / getSlopeApproximationAt(m_currentValue));
    updatePositiveDeltaForSlopeIfNeeded(newValue);
    m_currentValue = newValue;
    ++m_numberOfIterationsExecuted;
}

void NewtonMethod::runMaxNumberOfIterationsOrUntilFinished(int const maxIterations) {
    for (int i = 0; !isFinished() && i < maxIterations; ++i) {
        runOneIteration();
    }
}

void NewtonMethod::runUntilFinished() {
    while (!isFinished()) {
        runOneIteration();
    }
}

AlbaNumber NewtonMethod::getSlopeApproximationAt(AlbaNumber const& value) const {
    return (m_functionToIterate(value + m_positiveDeltaForSlope) -
            m_functionToIterate(value - m_positiveDeltaForSlope)) /
           (m_positiveDeltaForSlope * 2);
}

void NewtonMethod::updatePositiveDeltaForSlopeIfNeeded(AlbaNumber const& newValue) {
    AlbaNumber const newPositiveDelta = getPositiveDelta(newValue, m_currentValue);
    if (newPositiveDelta < m_positiveDeltaForSlope) {
        m_positiveDeltaForSlope = newPositiveDelta;
    }
}

}  // namespace alba::algebra
