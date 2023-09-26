#pragma once

namespace alba::algebra {

class BaseSolver {
public:
    BaseSolver();
    BaseSolver(BaseSolver const &) = default;
    BaseSolver(BaseSolver &&) noexcept = default;
    BaseSolver &operator=(BaseSolver const &) = default;
    BaseSolver &operator=(BaseSolver &&) noexcept = default;
    [[nodiscard]] bool isSolved() const;
    [[nodiscard]] bool isACompleteSolution() const;

protected:
    // No need for virtual destructor because this class is not destroyed polymorphically.
    // Guideline #4: A base class destructor should be either public and virtual, or protected and nonvirtual.
    // Source: http://www.gotw.ca/publications/mill18.htm
    ~BaseSolver() = default;
    void setAsCompleteSolution();
    void setAsIncompleteSolution();

private:
    bool m_isSolved{false};
    bool m_isACompleteSolution{false};
};

}  // namespace alba::algebra
