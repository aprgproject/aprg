#pragma once

#include <Common/Container/AlbaConfigurationHolder.hpp>
#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Number/AlbaComplexNumber.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <cmath>
#include <cstdint>
#include <ostream>

// NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions,cppcoreguidelines-pro-type-union-access)
namespace alba {

class AlbaNumber {
    // This is value type.
public:
    using IntDataType = int64_t;
    using NumeratorDataType = int32_t;
    using DenominatorDataType = uint32_t;
    using ComplexFloat = AlbaComplexNumber<float>;

    enum class Type { Integer, Double, Fraction, ComplexNumber };

    struct FractionData {
        // alignas(8) has no effect on performance (tested in benchmark)
        NumeratorDataType numerator;
        DenominatorDataType denominator;
    };

    struct ComplexNumberData {
        // alignas(8) has no effect on performance (tested in benchmark)
        float realPart;
        float imaginaryPart;
    };

    struct ConfigurationDetails {
        double comparisonTolerance;
        double floatAdjustmentTolerance;
    };

    union NumberUnionData {
        // alignas(8) has no effect on performance (tested in benchmark)
        constexpr NumberUnionData() : intData{} {}
        constexpr NumberUnionData(IntDataType const integer) : intData(integer) {}
        constexpr NumberUnionData(double const doubleValue) : doubleData(doubleValue) {}
        constexpr NumberUnionData(FractionData const& fractionData) : fractionData(fractionData) {}
        constexpr NumberUnionData(ComplexNumberData const& complexNumberData) : complexNumberData(complexNumberData) {}
        IntDataType intData;
        double doubleData;
        FractionData fractionData;
        ComplexNumberData complexNumberData;
    };

    class Configuration : public AlbaConfigurationHolder<ConfigurationDetails> {
    public:
        using BaseConfigurationHolder = AlbaConfigurationHolder<ConfigurationDetails>;
        void setConfigurationTolerancesToZero();
        void setComparisonTolerance(double const comparisonTolerance);
        void setFloatAdjustmentTolerance(double const comparisonTolerance);
        static ConfigurationDetails getConfigurationDetailsWithZeroTolerance();
    };

    class ScopeConfigurationObject : public AlbaConfigurationScopeObject<ConfigurationDetails> {
    public:
        static void setInThisScopeTheTolerancesToZero();
    };

    // static functions
    static AlbaNumber createNumberFromDoubleAndRoundIfNeeded(double const doubleValue);
    static AlbaNumber createFraction(NumeratorDataType const numerator, NumeratorDataType const denominator);
    static AlbaNumber createFraction(NumeratorDataType const numerator, DenominatorDataType const denominator);
    static constexpr double ADJUSTMENT_FLOAT_TOLERANCE = 1E-15;

    template <typename NumberType>
    static AlbaNumber createComplexNumber(NumberType const realPart, NumberType const imaginaryPart);

    static AlbaNumber createComplexNumber(ComplexFloat const& complexNumber);

    // constexpr functions
    template <typename ArithmeticType>
    void constexpr checkArithmeticType() {
        static_assert(sizeof(ArithmeticType) <= 8, "Maximum size is 8 bytes/64 bits.");
        static_assert(
            !(sizeof(ArithmeticType) == 8 && typeHelper::isUnsignedType<ArithmeticType>()),
            "Unsigned integers with 8 bytes/64 bits are not supported.");
    }

    template <typename ArithmeticType>
    Type constexpr getTypeBasedFromArithmeticType() {
        return typeHelper::isIntegralType<ArithmeticType>() ? Type::Integer : Type::Double;
    }

    // no need to be explicit in the constructors (allow implicit conversions)
    constexpr AlbaNumber() : m_type(Type::Integer) {}

    template <
        typename ArithmeticType,
        typename =
            std::enable_if_t<typeHelper::isArithmeticType<ArithmeticType>()>>  // enabled via a type template parameter
    constexpr AlbaNumber(ArithmeticType const value)
        : m_type(getTypeBasedFromArithmeticType<ArithmeticType>()),
          m_data(static_cast<
                 typeHelper::ConditionalType<typeHelper::isIntegralType<ArithmeticType>(), IntDataType, double>>(
              value)) {
        checkArithmeticType<ArithmeticType>();
    }

    // rule of zero
    // remove character to integer conversion (delete any functions is a C++11 feature)
    AlbaNumber(char const character) = delete;
    constexpr AlbaNumber(FractionData const& fractionData) : m_type(Type::Fraction), m_data(fractionData) {}

    constexpr AlbaNumber(ComplexNumberData const& complexNumberData)
        : m_type(Type::ComplexNumber), m_data(complexNumberData) {}

    AlbaNumber operator+() const;
    AlbaNumber operator-() const;
    AlbaNumber operator+(AlbaNumber const& second) const;
    AlbaNumber operator-(AlbaNumber const& second) const;
    AlbaNumber operator*(AlbaNumber const& second) const;
    AlbaNumber operator/(AlbaNumber const& second) const;
    AlbaNumber operator^(AlbaNumber const& second) const;
    // This should be constexpr as well but a lot of coding is needed
    bool operator==(AlbaNumber const& second) const;
    bool operator!=(AlbaNumber const& second) const;
    bool operator<=(AlbaNumber const& second) const;
    bool operator>=(AlbaNumber const& second) const;
    bool operator<(AlbaNumber const& second) const;
    bool operator>(AlbaNumber const& second) const;
    AlbaNumber& operator+=(AlbaNumber const& second);
    AlbaNumber& operator-=(AlbaNumber const& second);
    AlbaNumber& operator*=(AlbaNumber const& second);
    AlbaNumber& operator/=(AlbaNumber const& second);
    [[nodiscard]] ComplexNumberData getComplexNumberData() const;
    [[nodiscard]] FractionData getFractionData() const;
    [[nodiscard]] IntDataType getInteger() const;
    [[nodiscard]] Type getType() const;
    [[nodiscard]] double getDouble() const;
    [[nodiscard]] bool isIntegerType() const;
    [[nodiscard]] bool isDoubleType() const;
    [[nodiscard]] bool isFractionType() const;
    [[nodiscard]] bool isComplexNumberType() const;
    [[nodiscard]] bool isIntegerOrFractionType() const;
    [[nodiscard]] bool isPositiveInfinity() const;
    [[nodiscard]] bool isNegativeInfinity() const;
    [[nodiscard]] bool isPositiveOrNegativeInfinity() const;
    [[nodiscard]] bool isNotANumber() const;
    [[nodiscard]] bool isAFiniteValue() const;
    [[nodiscard]] bool isARealFiniteValue() const;
    void convertToInteger();
    void convertToFraction();

private:
    static void correctPowerResult(double& powerResult, double const base, double const exponent);
    static ComplexFloat createComplexFloat(ComplexNumberData const& data);
    // static functions
    static double getComparisonTolerance();
    static double getFloatAdjustmentTolerance();
    static double adjustFloatValue(float const value);

    template <typename NumberType1, typename NumberType2>
    void constructBasedFromComplexNumberDetails(NumberType1 const realPart, NumberType2 const imaginaryPart);

    static AlbaNumber addBothIntegersAndReturnNumber(IntDataType const integerValue1, IntDataType const integerValue2);
    static AlbaNumber addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2);

    static AlbaNumber addBothFractionsAndReturnNumber(
        FractionData const& fractionData1, FractionData const& fractionData2);

    static AlbaNumber addIntegerAndDoubleAndReturnNumber(IntDataType const integerValue, double const doubleValue);

    static AlbaNumber addIntegerAndFractionAndReturnNumber(
        IntDataType const integerValue, FractionData const& fractionData);

    static AlbaNumber addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue);

    static AlbaNumber multiplyBothIntegersAndReturnNumber(
        IntDataType const integerValue1, IntDataType const integerValue2);

    static AlbaNumber multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2);

    static AlbaNumber multiplyBothFractionsAndReturnNumber(
        FractionData const& fractionData1, FractionData const& fractionData2);

    static AlbaNumber multiplyIntegerAndDoubleAndReturnNumber(IntDataType const integerValue, double const doubleValue);

    static AlbaNumber multiplyIntegerAndFractionAndReturnNumber(
        IntDataType const integerValue, FractionData const& fractionData);

    static AlbaNumber multiplyFractionAndDoubleAndReturnNumber(
        FractionData const& fractionData, double const doubleValue);

    static AlbaNumber divideBothIntegersAndReturnNumber(IntDataType const dividend, IntDataType const divisor);

    static AlbaNumber divideDividendsAndDivisorsAndReturnNumber(
        IntDataType const dividendInteger, DenominatorDataType const dividendUnsignedInteger,
        IntDataType const divisorInteger, DenominatorDataType const divisorUnsignedInteger);

    static AlbaNumber divideBothFractionsAndReturnNumber(
        FractionData const& dividendFractionData, FractionData const& divisorFractionData);

    static AlbaNumber raisePowerOfBothIntegersAndReturnNumber(IntDataType const base, IntDataType const exponent);

    static AlbaNumber raisePowerOfFractionsAndIntegerAndReturnNumber(
        FractionData const& baseFractionData, IntDataType const exponent);

    friend std::ostream& operator<<(std::ostream& out, AlbaNumber const& number);
    Type m_type;  // Hotness: Type is much hotter.
    // use std::variant instead? Nah, I dont wanna deal with getting the "index" to know the "type".
    NumberUnionData m_data;
    static_assert(sizeof(m_type) == 4, "The size of AlbaNumber type should be 4 bytes/32 bits.");
    static_assert(sizeof(m_data) == 8, "The size of AlbaNumber data should be 8 bytes/64 bits.");
};

// Source: https://en.cppreference.com/w/cpp/language/user_literal
// NOTE: The string needs to have a underscore '_' prefix because all letters as prefix are reserved.
// NOLINTNEXTLINE(google-runtime-int)
constexpr AlbaNumber operator"" _AS_ALBA_NUMBER(unsigned long long int const value) {
    return {static_cast<AlbaNumber::IntDataType>(value)};
}

constexpr AlbaNumber operator"" _AS_ALBA_NUMBER(long double const value) { return {static_cast<double>(value)}; }
static_assert(sizeof(AlbaNumber) == 16, "The size of AlbaNumber should be 16 bytes/128 bits.");

// AlbaNumber operator "" _AS_ALBA_NUMBER(char const value) = delete;
// not needed to delete because there is no implicit conversion
template <>
AlbaNumber::ConfigurationDetails getDefaultConfigurationDetails<AlbaNumber::ConfigurationDetails>();

}  // namespace alba

// NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions,cppcoreguidelines-pro-type-union-access)
