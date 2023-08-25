#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <cmath>

namespace alba::mathHelper {

enum class RootType {
    RealRootsOnly,
    RealAndImaginaryRoots,
};

template <typename NumberType>
inline NumberType getAverage(NumberType const value1, NumberType const value2) {
    return (value1 + value2) / 2;
}

template <typename NumberType>
inline NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3) {
    return (value1 + value2 + value3) / 3;
}

template <typename NumberType>
inline NumberType getXSquaredPlusYSquared(NumberType const xValue, NumberType const yValue) {
    return xValue * xValue + yValue * yValue;
}

template <typename NumberType>
inline NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const xValue, NumberType const yValue) {
    return static_cast<NumberType>(pow(xValue * xValue + yValue * yValue, 0.5));
}

template <typename NumberType>
inline NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(
    NumberType const xValue, NumberType const yValue, NumberType const zValue) {
    return static_cast<NumberType>(pow(xValue * xValue + yValue * yValue + zValue * zValue, 0.5));
}

template <typename NumberType>
inline NumberType clampLowerBound(NumberType const value, NumberType const limit) {
    return (value < limit) ? limit : value;
}

template <typename NumberType>
inline NumberType clampHigherBound(NumberType const value, NumberType const limit) {
    return (value > limit) ? limit : value;
}

template <typename NumberType>
inline NumberType clampWithin(NumberType const value, NumberType const lowest, NumberType const highest) {
    // you can also use std::clamp but its in <algorithm>
    return clampHigherBound(clampLowerBound(value, lowest), highest);
}

inline AlbaNumber getAverage(AlbaNumber const& value1, AlbaNumber const& value2)  // pass as const reference
{
    return (value1 + value2) / 2;
}

AlbaNumbers getQuadraticRoots(
    RootType const rootType, AlbaNumber const& aValue, AlbaNumber const& bValue, AlbaNumber const& cValue);

}  // namespace alba::mathHelper
