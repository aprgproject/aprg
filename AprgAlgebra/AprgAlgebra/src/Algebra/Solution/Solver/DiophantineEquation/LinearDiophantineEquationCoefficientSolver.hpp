#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba::algebra {

class LinearDiophantineEquationCoefficientSolver {
public:
    // A Linear Diophantine Equation is an equation of the form ax+by = c

    using Integer = int64_t;

    enum class SolutionStatus { Unknown, CannotBeSolved, InfiniteSolutions, NoSolution, Solved };

    LinearDiophantineEquationCoefficientSolver(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);

    [[nodiscard]] bool isSolved() const;

    [[nodiscard]] SolutionStatus getSolutionStatus() const;
    [[nodiscard]] Integer getX() const;
    [[nodiscard]] Integer getY() const;
    [[nodiscard]] Integer getAnotherXValue(Integer const muliplier) const;
    [[nodiscard]] Integer getAnotherYValue(Integer const muliplier) const;

private:
    void solve(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);
    SolutionStatus m_solutionStatus{SolutionStatus::Unknown};
    Integer m_x{};
    Integer m_y{};
    Integer m_a{};
    Integer m_b{};
    Integer m_c{};
    Integer m_gcfOfAAndB{};
};

}  // namespace alba::algebra
