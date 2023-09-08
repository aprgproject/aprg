#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

#include <functional>

namespace alba::algebra {

class NewtonMethod {
public:
    using Function = std::function<AlbaNumber(AlbaNumber const&)>;
    NewtonMethod(AlbaNumber const& initialValue, Function const& functionToIterate);
    [[nodiscard]] bool isSolved() const;
    [[nodiscard]] bool isFinished() const;
    [[nodiscard]] int getNumberOfIterationsExecuted() const;
    [[nodiscard]] AlbaNumber const& getCurrentValue() const;
    void runOneIteration();
    void runMaxNumberOfIterationsOrUntilFinished(int const maxIterations);
    void runUntilFinished();

private:
    [[nodiscard]] AlbaNumber getSlopeApproximationAt(AlbaNumber const& value) const;
    void updatePositiveDeltaForSlopeIfNeeded(AlbaNumber const& newValue);
    int m_numberOfIterationsExecuted{0};
    static constexpr double INITIAL_DELTA_FOR_SLOPE = 1E-6;
    AlbaNumber m_currentValue;
    AlbaNumber m_positiveDeltaForSlope;
    Function m_functionToIterate;
};

}  // namespace alba::algebra
