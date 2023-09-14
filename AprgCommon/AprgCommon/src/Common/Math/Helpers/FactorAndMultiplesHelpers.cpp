#include "FactorAndMultiplesHelpers.hpp"

using namespace std;

namespace alba::mathHelper {

AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber) {
    AlbaNumber result(0);
    if (firstNumber.isDoubleType() || secondNumber.isDoubleType()) {
        result = 1;
    } else {
        AlbaNumber::FractionData const firstFractionData(firstNumber.getFractionData());
        AlbaNumber::FractionData const secondFractionData(secondNumber.getFractionData());
        uint32_t const lcmDenominator =
            getLeastCommonMultiple(firstFractionData.denominator, secondFractionData.denominator);
        uint32_t const firstNumerator = static_cast<uint32_t>(getAbsoluteValue(firstFractionData.numerator)) *
                                        lcmDenominator / firstFractionData.denominator;
        uint32_t const secondNumerator = static_cast<uint32_t>(getAbsoluteValue(secondFractionData.numerator)) *
                                         lcmDenominator / secondFractionData.denominator;
        uint32_t const gcfNumerator = getGreatestCommonFactor(firstNumerator, secondNumerator);
        result = AlbaNumber::createFraction(static_cast<int>(gcfNumerator), lcmDenominator);
    }
    return result;
}

AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber) {
    AlbaNumber result(0);
    if (firstNumber.isDoubleType() || secondNumber.isDoubleType()) {
        result = 1;
    } else {
        AlbaNumber::FractionData const firstFractionData(firstNumber.getFractionData());
        AlbaNumber::FractionData const secondFractionData(secondNumber.getFractionData());
        uint32_t const lcmDenominator =
            getLeastCommonMultiple(firstFractionData.denominator, secondFractionData.denominator);
        uint32_t const firstNumerator = static_cast<uint32_t>(getAbsoluteValue(firstFractionData.numerator)) *
                                        lcmDenominator / firstFractionData.denominator;
        uint32_t const secondNumerator = static_cast<uint32_t>(getAbsoluteValue(secondFractionData.numerator)) *
                                         lcmDenominator / secondFractionData.denominator;
        uint32_t const lcmNumerator = getLeastCommonMultiple(firstNumerator, secondNumerator);
        result = AlbaNumber::createFraction(static_cast<int>(lcmNumerator), lcmDenominator);
    }
    return result;
}

}  // namespace alba::mathHelper
