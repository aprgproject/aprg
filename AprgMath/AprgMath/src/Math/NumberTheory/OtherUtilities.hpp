#pragma once

#include <Math/Types.hpp>

namespace alba::math {
UnsignedInteger getNthFibonacciNumber(UnsignedInteger const number);
UnsignedInteger getNthFibonacciNumberUsingBinetsFormula(UnsignedInteger const number);
UnsignedInteger getNthFibonacciNumberUsingRecursion(UnsignedInteger const number);
UnsignedInteger getNthFibonacciUsingMatrixPowerWithLogarithmicTime(UnsignedInteger const number);
UnsignedInteger getNthFibonacciUsingLogarithmicTabularDP(UnsignedInteger const number);
UnsignedIntegers getFibonacciNumbersBelowThisNumber(UnsignedInteger const number);
bool isAFibonacciNumber(UnsignedInteger const number);
bool isALuckyNumber(UnsignedInteger const number);
bool isLagrangeTheoremTrue(UnsignedInteger const number);
bool isZeckendorfTheoremTrue(UnsignedInteger const number);
}  // namespace alba::math
