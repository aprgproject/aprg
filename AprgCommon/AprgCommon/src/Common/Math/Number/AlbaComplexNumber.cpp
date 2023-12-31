#include "AlbaComplexNumber.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/Math/Helpers/FractionHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <cassert>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

template <typename DataType>
AlbaComplexNumber<DataType>::AlbaComplexNumber(DataType const realPart, DataType const imaginaryPart)
    : m_realPart(realPart), m_imaginaryPart(imaginaryPart) {}

template AlbaComplexNumber<float>::AlbaComplexNumber(float const value1, float const value2);
template AlbaComplexNumber<double>::AlbaComplexNumber(double const value1, double const value2);

template <typename DataType>
bool AlbaComplexNumber<DataType>::operator==(AlbaComplexNumber<DataType> const& second) const {
    return isAlmostEqual(m_realPart, second.m_realPart) && isAlmostEqual(m_imaginaryPart, second.m_imaginaryPart);
}

template bool AlbaComplexNumber<float>::operator==(AlbaComplexNumber<float> const& second) const;
template bool AlbaComplexNumber<double>::operator==(AlbaComplexNumber<double> const& second) const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator+(AlbaComplexNumber<DataType> const& second) const {
    return AlbaComplexNumber<DataType>(m_realPart + second.m_realPart, m_imaginaryPart + second.m_imaginaryPart);
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator+(AlbaComplexNumber<float> const& second) const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator+(AlbaComplexNumber<double> const& second) const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator-(AlbaComplexNumber<DataType> const& second) const {
    return AlbaComplexNumber<DataType>(m_realPart - second.m_realPart, m_imaginaryPart - second.m_imaginaryPart);
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator-(AlbaComplexNumber<float> const& second) const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator-(AlbaComplexNumber<double> const& second) const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator+() const {
    return *this;
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator+() const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator+() const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator-() const {
    return AlbaComplexNumber<DataType>(-m_realPart, -m_imaginaryPart);
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator-() const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator-() const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator*(AlbaComplexNumber<DataType> const& second) const {
    return AlbaComplexNumber<DataType>(
        getRealPartInMultiplication(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart),
        getImaginaryPartInMultiplication(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart));
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator*(AlbaComplexNumber<float> const& second) const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator*(AlbaComplexNumber<double> const& second) const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator/(AlbaComplexNumber<DataType> const& second) const {
    DataType denominator(second.getModulusSquared());
    return AlbaComplexNumber<DataType>(
        getRealPartInDivision(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart) / denominator,
        getImaginaryPartInDivision(m_realPart, m_imaginaryPart, second.m_realPart, second.m_imaginaryPart) /
            denominator);
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator/(AlbaComplexNumber<float> const& second) const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator/(AlbaComplexNumber<double> const& second) const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::operator^(DataType const exponent) const {
    double const modulusPart = pow(static_cast<double>(getModulus()), static_cast<double>(exponent));
    double const angleToBeUsed = getBestAngleInRaiseToPowerInRadians(exponent);
    double const realPart = modulusPart * cos(angleToBeUsed);
    double const imaginaryPart = modulusPart * sin(angleToBeUsed);
    return AlbaComplexNumber<DataType>(static_cast<DataType>(realPart), static_cast<DataType>(imaginaryPart));
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::operator^(float const second) const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::operator^(double const second) const;

template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator+=(AlbaComplexNumber<DataType> const& second) {
    AlbaComplexNumber<DataType>& thisReference(*this);
    thisReference = thisReference + second;
    return thisReference;
}

template AlbaComplexNumber<float>& AlbaComplexNumber<float>::operator+=(AlbaComplexNumber<float> const& second);
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator+=(AlbaComplexNumber<double> const& second);

template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator-=(AlbaComplexNumber<DataType> const& second) {
    AlbaComplexNumber<DataType>& thisReference(*this);
    thisReference = thisReference - second;
    return thisReference;
}

template AlbaComplexNumber<float>& AlbaComplexNumber<float>::operator-=(AlbaComplexNumber<float> const& second);
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator-=(AlbaComplexNumber<double> const& second);

template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator*=(AlbaComplexNumber<DataType> const& second) {
    AlbaComplexNumber<DataType>& thisReference(*this);
    thisReference = thisReference * second;
    return thisReference;
}

template AlbaComplexNumber<float>& AlbaComplexNumber<float>::operator*=(AlbaComplexNumber<float> const& second);
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator*=(AlbaComplexNumber<double> const& second);

template <typename DataType>
AlbaComplexNumber<DataType>& AlbaComplexNumber<DataType>::operator/=(AlbaComplexNumber<DataType> const& second) {
    AlbaComplexNumber<DataType>& thisReference(*this);
    thisReference = thisReference / second;
    return thisReference;
}

template AlbaComplexNumber<float>& AlbaComplexNumber<float>::operator/=(AlbaComplexNumber<float> const& second);
template AlbaComplexNumber<double>& AlbaComplexNumber<double>::operator/=(AlbaComplexNumber<double> const& second);

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getRealPart() const {
    return m_realPart;
}

template float AlbaComplexNumber<float>::getRealPart() const;
template double AlbaComplexNumber<double>::getRealPart() const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getImaginaryPart() const {
    return m_imaginaryPart;
}

template float AlbaComplexNumber<float>::getImaginaryPart() const;
template double AlbaComplexNumber<double>::getImaginaryPart() const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getModulus() const {
    return getSquareRootOfXSquaredPlusYSquared(m_realPart, m_imaginaryPart);
}

template float AlbaComplexNumber<float>::getModulus() const;
template double AlbaComplexNumber<double>::getModulus() const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getModulusWithSignOfRealPart() const {
    return getSquareRootOfXSquaredPlusYSquared(m_realPart, m_imaginaryPart) * getSign(m_realPart);
}

template float AlbaComplexNumber<float>::getModulusWithSignOfRealPart() const;
template double AlbaComplexNumber<double>::getModulusWithSignOfRealPart() const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getModulusSquared() const {
    return getXSquaredPlusYSquared(m_realPart, m_imaginaryPart);
}

template float AlbaComplexNumber<float>::getModulusSquared() const;
template double AlbaComplexNumber<double>::getModulusSquared() const;

template <typename DataType>
double AlbaComplexNumber<DataType>::getAngleInRadians() const {
    return atan2(static_cast<double>(m_imaginaryPart), static_cast<double>(m_realPart));
}

template double AlbaComplexNumber<float>::getAngleInRadians() const;
template double AlbaComplexNumber<double>::getAngleInRadians() const;

template <typename DataType>
double AlbaComplexNumber<DataType>::getBestAngleInRaiseToPowerInRadians(DataType const exponent) const {
    double const angleWithoutPi(getAngleInRadians() / getPi());
    FractionDetails const exponentFraction(getBestFractionDetailsForDoubleValue<size_t>(static_cast<double>(exponent)));
    constexpr size_t MINIMUM_ROOTS = 100;
    size_t const numberRootsToProcess = min(MINIMUM_ROOTS, exponentFraction.denominator);

    bool isFirst(true);
    double bestAngleWithoutPi(0);
    double minDeltaFromNearestInteger(1);
    for (size_t rootIndex = 0; rootIndex < numberRootsToProcess; ++rootIndex) {
        auto possibleAngleWithoutPi =
            (angleWithoutPi + 2.0 * static_cast<double>(rootIndex)) * static_cast<double>(exponent);
        double const deltaFromNearestInteger = getPositiveDelta(possibleAngleWithoutPi, round(possibleAngleWithoutPi));
        if (isFirst || deltaFromNearestInteger < minDeltaFromNearestInteger) {
            minDeltaFromNearestInteger = deltaFromNearestInteger;
            bestAngleWithoutPi = possibleAngleWithoutPi;
            isFirst = false;
        }
        if (isAlmostAnInteger<DataType, int>(bestAngleWithoutPi)) {
            bestAngleWithoutPi = round(bestAngleWithoutPi);
            break;
        }
    }
    return bestAngleWithoutPi * getPi();
}

template double AlbaComplexNumber<float>::getBestAngleInRaiseToPowerInRadians(float const exponent) const;
template double AlbaComplexNumber<double>::getBestAngleInRaiseToPowerInRadians(double const exponent) const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::getConjugate() const {
    return AlbaComplexNumber<DataType>(m_realPart, -m_imaginaryPart);
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::getConjugate() const;
template AlbaComplexNumber<double> AlbaComplexNumber<double>::getConjugate() const;

template <typename DataType>
AlbaComplexNumber<DataType> AlbaComplexNumber<DataType>::getNthRoot(
    size_t const rootIndex, size_t const rootDegree) const {
    assert(rootIndex < rootDegree);
    double const modulusPart =
        pow(static_cast<double>(getModulus()), static_cast<double>(1) / static_cast<double>(rootDegree));
    double const angleToBeUsed = (getAngleInRadians() + getPi() * 2 * static_cast<double>(rootIndex)) / rootDegree;
    double const realPart = modulusPart * cos(angleToBeUsed);
    double const imaginaryPart = modulusPart * sin(angleToBeUsed);
    return AlbaComplexNumber<DataType>(static_cast<DataType>(realPart), static_cast<DataType>(imaginaryPart));
}

template AlbaComplexNumber<float> AlbaComplexNumber<float>::getNthRoot(
    size_t const rootIndex, size_t const rootDegree) const;

template AlbaComplexNumber<double> AlbaComplexNumber<double>::getNthRoot(
    size_t const rootIndex, size_t const rootDegree) const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getRealPartInMultiplication(
    DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
    DataType const secondImaginaryPart) const {
    return firstRealPart * secondRealPart - firstImaginaryPart * secondImaginaryPart;
}

template float AlbaComplexNumber<float>::getRealPartInMultiplication(
    float const firstRealPart, float const firstImaginaryPart, float const secondRealPart,
    float const secondImaginaryPart) const;

template double AlbaComplexNumber<double>::getRealPartInMultiplication(
    double const firstRealPart, double const firstImaginaryPart, double const secondRealPart,
    double const secondImaginaryPart) const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getImaginaryPartInMultiplication(
    DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
    DataType const secondImaginaryPart) const {
    return firstRealPart * secondImaginaryPart + firstImaginaryPart * secondRealPart;
}

template float AlbaComplexNumber<float>::getImaginaryPartInMultiplication(
    float const firstRealPart, float const firstImaginaryPart, float const secondRealPart,
    float const secondImaginaryPart) const;

template double AlbaComplexNumber<double>::getImaginaryPartInMultiplication(
    double const firstRealPart, double const firstImaginaryPart, double const secondRealPart,
    double const secondImaginaryPart) const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getRealPartInDivision(
    DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
    DataType const secondImaginaryPart) const {
    return firstRealPart * secondRealPart + firstImaginaryPart * secondImaginaryPart;
}

template float AlbaComplexNumber<float>::getRealPartInDivision(
    float const firstRealPart, float const firstImaginaryPart, float const secondRealPart,
    float const secondImaginaryPart) const;

template double AlbaComplexNumber<double>::getRealPartInDivision(
    double const firstRealPart, double const firstImaginaryPart, double const secondRealPart,
    double const secondImaginaryPart) const;

template <typename DataType>
DataType AlbaComplexNumber<DataType>::getImaginaryPartInDivision(
    DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
    DataType const secondImaginaryPart) const {
    return firstImaginaryPart * secondRealPart - firstRealPart * secondImaginaryPart;
}

template float AlbaComplexNumber<float>::getImaginaryPartInDivision(
    float const firstRealPart, float const firstImaginaryPart, float const secondRealPart,
    float const secondImaginaryPart) const;

template double AlbaComplexNumber<double>::getImaginaryPartInDivision(
    double const firstRealPart, double const firstImaginaryPart, double const secondRealPart,
    double const secondImaginaryPart) const;

}  // namespace alba
