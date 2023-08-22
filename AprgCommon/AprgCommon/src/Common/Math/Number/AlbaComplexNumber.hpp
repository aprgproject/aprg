#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <ostream>

namespace alba {

template <typename DataType>
class AlbaComplexNumber {
public:
    static_assert(typeHelper::isArithmeticType<DataType>(), "DataType should be an arithmetic type.");

    AlbaComplexNumber();
    AlbaComplexNumber(DataType const realPart, DataType const imaginaryPart);

    // rule of zero

    bool operator==(AlbaComplexNumber const& second) const;
    AlbaComplexNumber<DataType> operator+(AlbaComplexNumber<DataType> const& second) const;
    AlbaComplexNumber<DataType> operator-(AlbaComplexNumber<DataType> const& second) const;
    AlbaComplexNumber<DataType> operator+() const;
    AlbaComplexNumber<DataType> operator-() const;
    AlbaComplexNumber<DataType> operator*(AlbaComplexNumber<DataType> const& second) const;
    AlbaComplexNumber<DataType> operator/(AlbaComplexNumber<DataType> const& second) const;
    AlbaComplexNumber<DataType> operator^(DataType const exponent) const;
    AlbaComplexNumber<DataType>& operator+=(AlbaComplexNumber<DataType> const& second);
    AlbaComplexNumber<DataType>& operator-=(AlbaComplexNumber<DataType> const& second);
    AlbaComplexNumber<DataType>& operator*=(AlbaComplexNumber<DataType> const& second);
    AlbaComplexNumber<DataType>& operator/=(AlbaComplexNumber<DataType> const& second);
    [[nodiscard]] DataType getRealPart() const;
    [[nodiscard]] DataType getImaginaryPart() const;
    [[nodiscard]] DataType getModulus() const;
    [[nodiscard]] DataType getModulusWithSignOfRealPart() const;
    [[nodiscard]] DataType getModulusSquared() const;
    [[nodiscard]] double getAngleInRadians() const;
    [[nodiscard]] double getBestAngleInRaiseToPowerInRadians(DataType const exponent) const;
    [[nodiscard]] AlbaComplexNumber<DataType> getConjugate() const;
    [[nodiscard]] AlbaComplexNumber<DataType> getNthRoot(size_t const rootIndex, size_t const rootDegree) const;

private:
    [[nodiscard]] DataType getRealPartInMultiplication(
        DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
        DataType const secondImaginaryPart) const;
    [[nodiscard]] DataType getImaginaryPartInMultiplication(
        DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
        DataType const secondImaginaryPart) const;
    [[nodiscard]] DataType getRealPartInDivision(
        DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
        DataType const secondImaginaryPart) const;
    [[nodiscard]] DataType getImaginaryPartInDivision(
        DataType const firstRealPart, DataType const firstImaginaryPart, DataType const secondRealPart,
        DataType const secondImaginaryPart) const;

    friend std::ostream& operator<<(std::ostream& out, AlbaComplexNumber<DataType> const& complexNumber) {
        out << "(" << complexNumber.m_realPart << " + " << complexNumber.m_imaginaryPart << "i)";
        return out;
    }

    DataType m_realPart;
    DataType m_imaginaryPart;
};

}  // namespace alba
