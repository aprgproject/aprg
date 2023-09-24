#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <vector>

namespace alba::algebra {

class BrentMethod {
public:
    struct CalculationValues {
        AlbaNumberOptional solutionOptional;
        AlbaNumber a;
        AlbaNumber b;
        AlbaNumber c;
        AlbaNumber d;
        AlbaNumber s;
        AlbaNumber fa;
        AlbaNumber fb;
        bool mflag;
    };

    using ListOfCoefficients = std::vector<AlbaNumbers>;
    explicit BrentMethod(AlbaNumbers const& coefficients);
    explicit BrentMethod(AlbaNumbers&& coefficients);
    [[nodiscard]] AlbaNumbers const& getCoefficients() const;
    [[nodiscard]] CalculationValues const& getCalculationValues() const;
    [[nodiscard]] int getNumberOfIterationsExecuted() const;
    [[nodiscard]] bool isFinished() const;
    void resetCalculation(AlbaNumber const& start, AlbaNumber const& end);
    void runOneIteration();
    void runMaxNumberOfIterationsOrUntilFinished(int const maxIterations);
    AlbaNumberOptional const& getSolution();

private:
    [[nodiscard]] AlbaNumber calculate(AlbaNumber const& inputValue) const;

    [[nodiscard]] AlbaNumberOptional calculateInverseQuadraticInterpolation(
        AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c) const;

    [[nodiscard]] AlbaNumberOptional calculateSecantMethod(AlbaNumber const& a, AlbaNumber const& b) const;
    void convertSolutionToIntegerIfNeeded();
    static AlbaNumber calculateBiSectionMethod(AlbaNumber const& a, AlbaNumber const& b);
    static bool isAlmostEqualForBrentMethod(AlbaNumber const& value1, AlbaNumber const& value2);
    static bool isAlmostEqualForBrentMethod(AlbaNumber const& value1, double const value2);

    static bool isBisectionMethodNeeded(
        AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c, AlbaNumber const& d, AlbaNumber const& s,
        bool const mflag);

    int m_numberOfIterationsExecuted{};
    AlbaNumbers m_coefficients;
    CalculationValues m_values;
};

}  // namespace alba::algebra
