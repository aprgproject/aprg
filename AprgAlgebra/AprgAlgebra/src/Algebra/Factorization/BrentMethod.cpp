#include "BrentMethod.hpp"

#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <ranges>

using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

// In numerical analysis, Brent's method is a root-finding algorithm combining the bisection method, the secant method
// and inverse quadratic interpolation. It has the reliability of bisection but it can be as quick as some of the
// less-reliable methods. The algorithm tries to use the potentially fast-converging secant method or inverse quadratic
// interpolation if possible, but it falls back to the more robust bisection method if necessary. Brent's method is due
// to Richard Brent[1] and builds on an earlier algorithm by Theodorus Dekker.[2] Consequently, the method is also known
// as the Brent–Dekker method.
namespace {
constexpr double BRENT_METHOD_COMPARISON_TOLERANCE = 1E-13;
constexpr double BRENT_METHOD_TOLERANCE_TO_ZERO_FOR_A_AND_B = 1E-11;
}  // namespace

BrentMethod::BrentMethod(AlbaNumbers const& coefficients) : m_coefficients(coefficients), m_values{} {}
BrentMethod::BrentMethod(AlbaNumbers&& coefficients) : m_coefficients(coefficients), m_values{} {}
AlbaNumbers const& BrentMethod::getCoefficients() const { return m_coefficients; }
BrentMethod::CalculationValues const& BrentMethod::getCalculationValues() const { return m_values; }
int BrentMethod::getNumberOfIterationsExecuted() const { return m_numberOfIterationsExecuted; }
bool BrentMethod::isFinished() const { return m_values.solutionOptional.has_value(); }

void BrentMethod::resetCalculation(AlbaNumber const& start, AlbaNumber const& end) {
    m_numberOfIterationsExecuted = 0;
    m_values.solutionOptional.reset();
    m_values.a = start;
    m_values.b = end;
    m_values.d = 0;
    m_values.s = 0;
    m_values.fa = calculate(m_values.a);
    m_values.fb = calculate(m_values.b);
    m_values.mflag = true;

    if (getAbsoluteValue(m_values.fa) < getAbsoluteValue(m_values.fb)) {
        swap(m_values.a, m_values.b);
        swap(m_values.fa, m_values.fb);
    }
    m_values.c = m_values.a;
}

void BrentMethod::runOneIteration() {
    AlbaNumber::ScopeConfigurationObject const scopeConfigurationObject;
    AlbaNumber::ScopeConfigurationObject::setInThisScopeTheTolerancesToZero();

    if (isAlmostEqualForBrentMethod(calculate(m_values.s), 0)) {
        m_values.solutionOptional = m_values.s;
        return;
    }
    if (isAlmostEqualForBrentMethod(calculate(m_values.b), 0)) {
        m_values.solutionOptional = m_values.b;
        return;
    }
    if (isAlmostEqualForBrentMethod(m_values.a, m_values.b) &&
        isAlmostEqual(calculate(m_values.a).getDouble(), 0.0, BRENT_METHOD_TOLERANCE_TO_ZERO_FOR_A_AND_B)) {
        m_values.solutionOptional = m_values.a;
        return;
    }
    AlbaNumber const fc = calculate(m_values.c);
    if (!isAlmostEqualForBrentMethod(m_values.fa, fc) && !isAlmostEqualForBrentMethod(m_values.fb, fc)) {
        AlbaNumberOptional sOptional(calculateInverseQuadraticInterpolation(m_values.a, m_values.b, m_values.c));
        if (!sOptional) {
            return;
        }
        m_values.s = sOptional.value();
    } else if (!isAlmostEqualForBrentMethod(m_values.fa, m_values.fb)) {
        AlbaNumberOptional sOptional(calculateSecantMethod(m_values.a, m_values.b));
        if (!sOptional) {
            return;
        }
        m_values.s = sOptional.value();
    }
    if (isBisectionMethodNeeded(m_values.a, m_values.b, m_values.c, m_values.d, m_values.s, m_values.mflag) ||
        isAlmostEqualForBrentMethod(m_values.a, m_values.s) || isAlmostEqualForBrentMethod(m_values.b, m_values.s)) {
        m_values.s = calculateBiSectionMethod(m_values.a, m_values.b);
        m_values.mflag = true;
    } else {
        m_values.mflag = false;
    }
    AlbaNumber const fs = calculate(m_values.s);
    m_values.d = m_values.c;
    m_values.c = m_values.b;
    if (m_values.fa * fs < 0) {
        m_values.b = m_values.s;
    } else {
        m_values.a = m_values.s;
    }
    m_values.fa = calculate(m_values.a);
    m_values.fb = calculate(m_values.b);
    if (getAbsoluteValue(m_values.fa) < getAbsoluteValue(m_values.fb)) {
        swap(m_values.a, m_values.b);
        swap(m_values.fa, m_values.fb);
    }
    ++m_numberOfIterationsExecuted;
}

void BrentMethod::runMaxNumberOfIterationsOrUntilFinished(int const maxIterations) {
    for (int i = 0; !isFinished() && i < maxIterations; ++i) {
        runOneIteration();
    }
}

AlbaNumberOptional const& BrentMethod::getSolution() {
    convertSolutionToIntegerIfNeeded();
    return m_values.solutionOptional;
}

AlbaNumber BrentMethod::calculate(AlbaNumber const& inputValue) const {
    AlbaNumber result;
    AlbaNumber partialProduct(1);
    // NOLINTBEGIN(modernize-loop-convert)
    for (auto it = m_coefficients.crbegin(); it != m_coefficients.crend(); ++it) {
        result = result + (*it) * partialProduct;
        partialProduct = partialProduct * inputValue;
    }
    // NOLINTEND(modernize-loop-convert)
    return result;
}

AlbaNumberOptional BrentMethod::calculateInverseQuadraticInterpolation(
    AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c) const {
    AlbaNumberOptional result;
    AlbaNumber const fa = calculate(a);
    AlbaNumber const fb = calculate(b);
    AlbaNumber const fc = calculate(c);
    AlbaNumber const firstDenominator((fa - fb) * (fa - fc));
    AlbaNumber const secondDenominator((fb - fa) * (fb - fc));
    AlbaNumber const thirdDenominator((fc - fa) * (fc - fb));
    if (!isAlmostEqualForBrentMethod(firstDenominator, 0) && !isAlmostEqualForBrentMethod(secondDenominator, 0) &&
        !isAlmostEqualForBrentMethod(thirdDenominator, 0)) {
        AlbaNumber const firstPart = (a * fb * fc) / firstDenominator;
        AlbaNumber const secondPart = (b * fa * fc) / secondDenominator;
        AlbaNumber const thirdPart = (c * fa * fb) / thirdDenominator;
        result = firstPart + secondPart + thirdPart;
    }
    return result;
}

AlbaNumberOptional BrentMethod::calculateSecantMethod(AlbaNumber const& a, AlbaNumber const& b) const {
    AlbaNumberOptional result;
    AlbaNumber const fa = calculate(a);
    AlbaNumber const fb = calculate(b);
    AlbaNumber const denominator(fb - fa);
    if (!isAlmostEqualForBrentMethod(denominator, 0)) {
        AlbaNumber const firstPart = b;
        AlbaNumber const secondPart = (fb * (b - a)) / (denominator);
        result = firstPart - secondPart;
    }
    return result;
}

void BrentMethod::convertSolutionToIntegerIfNeeded() {
    if (m_values.solutionOptional && !m_coefficients.empty()) {
        AlbaNumber const aCoefficient(m_coefficients.front());
        if (aCoefficient.isIntegerOrFractionType()) {
            AlbaNumber possibleValue(m_values.solutionOptional.value() * aCoefficient);
            possibleValue.convertToInteger();
            possibleValue = possibleValue / aCoefficient;
            if (isAlmostEqualForBrentMethod(calculate(possibleValue), 0.0)) {
                m_values.solutionOptional = possibleValue;
            }
        }
    }
}

AlbaNumber BrentMethod::calculateBiSectionMethod(AlbaNumber const& a, AlbaNumber const& b) { return (a + b) / 2; }

bool BrentMethod::isAlmostEqualForBrentMethod(AlbaNumber const& value1, AlbaNumber const& value2) {
    return isAlmostEqual(value1.getDouble(), value2.getDouble(), BRENT_METHOD_COMPARISON_TOLERANCE);
}

bool BrentMethod::isAlmostEqualForBrentMethod(AlbaNumber const& value1, double const value2) {
    return isAlmostEqual(value1.getDouble(), value2, BRENT_METHOD_COMPARISON_TOLERANCE);
}

bool BrentMethod::isBisectionMethodNeeded(
    AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c, AlbaNumber const& d, AlbaNumber const& s,
    bool const mflag) {
    AlbaNumber const first = ((a * 3) + b) / 4;
    AlbaNumber const second = b;
    AlbaNumber const minForConditionOne = min(first, second);
    AlbaNumber const maxForConditionOne = max(first, second);
    AlbaNumber const gamma = 1;
    bool const isConditionOne = s < minForConditionOne || maxForConditionOne < s;
    bool const isConditionTwo = mflag && getAbsoluteValue(s - b) >= (getAbsoluteValue(b - c) / 2);
    bool const isConditionThree = !mflag && getAbsoluteValue(s - b) >= (getAbsoluteValue(c - d) / 2);
    bool const isConditionFour = mflag && getAbsoluteValue(b - c) < getAbsoluteValue(gamma);
    bool const isConditionFive = !mflag && getAbsoluteValue(c - d) < getAbsoluteValue(gamma);
    return isConditionOne || isConditionTwo || isConditionThree || isConditionFour || isConditionFive;
}

}  // namespace alba::algebra
