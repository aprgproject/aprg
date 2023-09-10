#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba::mathHelper {

template <typename NumberType>
NumberType getNumberOfPossibilities(NumberType const numberOfPossibilitiesPerTime, NumberType const numberOfTimes) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return getRaiseToPowerForIntegers(numberOfPossibilitiesPerTime, numberOfTimes);
}

template <typename NumberType>
NumberType getFactorial(NumberType const number) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    NumberType result(1);
    for (NumberType currentNumber = number; currentNumber > 1; --currentNumber) {
        result *= currentNumber;
    }
    return result;
}

template <typename NumberType>
NumberType getNumberOfPermutations(NumberType const nValue, NumberType const rValue) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(0);
    if (nValue >= rValue) {
        result = 1;
        for (NumberType currentNumber = nValue; currentNumber > nValue - rValue; --currentNumber) {
            result *= currentNumber;
        }
    }
    return result;
}

template <typename NumberType>
NumberType getNumberOfCombinations(NumberType const nValue, NumberType const rValue) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // Formula 1(recursive formula): (nValue, kValue) = (nValue-1, kValue-1) + (nValue-1, kValue)
    // Base cases: (nValue, 0) = 1, (nValue, nValue) = 1
    // Idea: The idea is to fix an element x in the set.
    // If x is included in the subset, we have to choose kValue-1 elements from nValue-1 elements,
    // and if x is not included in the subset, we have to choose kValue elements from nValue-1 elements.
    // Note: Formula 1 might be useful in dynamic programming
    // Formula 2(factorial formula): (nValue, kValue) = nValue! / (kValue! * (nValue-kValue)!)
    // Idea: There are nValue! permutations of nValue elements.
    // We go through all permutations and always include the first kValue elements of the permutation in the subset.
    // Since the order of the elements in the subset and outside the subset does not matter,
    // the result is divided by kValue! and (nValue-kValue)!
    // Formula 2 is the one implemented below:
    if (nValue >= rValue) {
        NumberType smallerR = (nValue < 2 * rValue) ? nValue - rValue : rValue;
        NumberType accumulatedNumerator = 1;
        NumberType accumulatedDenominator = 1;
        NumberType numeratorMultiplier = nValue;
        NumberType denominatorMultiplier = smallerR;
        for (NumberType iterations = 0; iterations < smallerR; ++iterations) {
            accumulatedNumerator *= numeratorMultiplier--;
            accumulatedDenominator *= denominatorMultiplier--;
            if (accumulatedDenominator > 1 &&
                isValueBeyondLimits<NumberType>(static_cast<double>(accumulatedNumerator) * numeratorMultiplier)) {
                NumberType gcf = getGreatestCommonFactor(accumulatedNumerator, accumulatedDenominator);
                accumulatedNumerator /= gcf;
                accumulatedDenominator /= gcf;
            }
        }
        return accumulatedNumerator / accumulatedDenominator;
    }
    return 0;
}

template <typename NumberType>
NumberType getNumberOfCombinationsFasterButPossibleOfRange(NumberType const nValue, NumberType const rValue) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    // C(nValue, kValue)
    // -> = nValue! / (nValue-kValue)! * kValue!
    // -> = [nValue * (nValue-1) *....* 1]  / [ ( (nValue-kValue) * (nValue-kValue-1) * .... * 1) *
    //                             ( kValue * (kValue-1) * .... * 1 ) ]
    // After simplifying, we get
    // -> C(nValue, kValue)
    // -> = [nValue * (nValue-1) * .... * (nValue-kValue+1)] / [kValue * (kValue-1) * .... * 1]
    //
    // Also, C(nValue, kValue) = C(nValue, nValue-kValue)
    // -> So rValue can be changed to nValue-rValue if (nValue-rValue < rValue) or (nValue < 2*rValue)
    if (nValue >= rValue) {
        NumberType smallerR = (nValue < 2 * rValue) ? nValue - rValue : rValue;
        NumberType result(1);
        for (NumberType offset = 0; offset < smallerR; ++offset) {
            result *= (nValue - offset);
            result /= (offset + 1);
        }
        return result;
    }
    return 0;
}

template <typename NumberType>
NumberType getBinomialCoefficient(NumberType const rowIndex, NumberType const columnIndex) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // The binomial coefficient equals the number of ways we can choose a subset of kValue elements from a set of nValue
    // elements. The binomial coefficient = the number of combinations
    return getNumberOfCombinations(rowIndex, columnIndex);
}

template <typename NumberType>
NumberType getValueAtPascalTriangle(NumberType const rowIndex, NumberType const columnIndex) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // This is same with the number of combinations and binomial coefficient.
    return getNumberOfCombinations(rowIndex, columnIndex);
}

template <typename NumberType>
typename std::make_signed<NumberType>::type getStirlingNumberOfTheSecondKind(
    NumberType const nValue, NumberType const kValue) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // In mathematics, particularly in combinatorics, a Stirling number of the second kind (or Stirling partition
    // number) is the number of ways to partition a set of nValue objects into kValue non-empty subsets
    // Stirling numbers of the second kind occur in the field of mathematics called combinatorics and the study of
    // partitions.
    using SignedType = typename std::make_signed<NumberType>::type;

    SignedType sum(0);
    bool isDivisibleByTwo(true);
    for (NumberType i = 0; i <= kValue; ++i) {
        SignedType const sign = isDivisibleByTwo ? 1 : -1;
        sum += sign * getNumberOfCombinations(kValue, i) * getRaiseToPowerForIntegersUsingPow(kValue - i, nValue);
        isDivisibleByTwo = !isDivisibleByTwo;
    }
    sum /= getFactorial(kValue);
    return sum;
}

}  // namespace alba::mathHelper
