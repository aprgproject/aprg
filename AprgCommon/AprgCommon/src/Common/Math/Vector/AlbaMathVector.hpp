#pragma once

#include <Common/Math/Vector/AlbaMathVectorUtilitiesHeaders.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>

namespace alba {

template <typename DataType, size_t SIZE>
class AlbaMathVector {
public:
    using ValuesInArray = std::array<DataType, SIZE>;
    AlbaMathVector() : m_values{} {}
    explicit AlbaMathVector(ValuesInArray const& values) : m_values(values) {}

    AlbaMathVector(std::initializer_list<DataType> const& values) : m_values{} {
        size_t const limit = std::min(SIZE, static_cast<size_t>(values.size()));
        std::copy(begin(values), begin(values) + limit, begin(m_values));
    }

    AlbaMathVector operator+(AlbaMathVector const& second) const {
        AlbaMathVector result;
        ValuesInArray const& firstValues(m_values);
        ValuesInArray const& secondValues(second.m_values);
        ValuesInArray& resultValues(result.m_values);
        std::transform(
            begin(firstValues), end(firstValues), begin(secondValues), begin(resultValues), std::plus<DataType>());
        return result;
    }

    AlbaMathVector operator-(AlbaMathVector const& second) const {
        AlbaMathVector result;
        ValuesInArray const& firstValues(m_values);
        ValuesInArray const& secondValues(second.m_values);
        ValuesInArray& resultValues(result.m_values);
        std::transform(
            begin(firstValues), end(firstValues), begin(secondValues), begin(resultValues), std::minus<DataType>());
        return result;
    }

    AlbaMathVector operator+() const { return *this; }

    AlbaMathVector operator-() const {
        AlbaMathVector result;
        ValuesInArray& resultValues(result.m_values);
        std::transform(begin(m_values), end(m_values), begin(resultValues), std::negate<DataType>());
        return result;
    }

    AlbaMathVector operator*(DataType const& scalarValue) const {
        AlbaMathVector result;
        ValuesInArray& resultValues(result.m_values);
        std::transform(begin(m_values), end(m_values), begin(resultValues), [&](DataType const value) {
            return value * scalarValue;
        });
        return result;
    }

    AlbaMathVector operator/(DataType const& scalarValue) const {
        AlbaMathVector result;
        ValuesInArray& resultValues(result.m_values);
        std::transform(begin(m_values), end(m_values), begin(resultValues), [&](DataType const value) {
            return value / scalarValue;
        });
        return result;
    }

    // rule of zero
    bool operator==(AlbaMathVector const& second) const {
        return std::equal(
            m_values.cbegin(), m_values.cend(), second.m_values.cbegin(),
            [](DataType const first, DataType const second) { return isEqualForMathVectorDataType(first, second); });
    }

    bool operator!=(AlbaMathVector const& second) const {
        AlbaMathVector const& first(*this);
        return !(first == second);
    }

    bool operator<(AlbaMathVector const& second) const {
        // this is added so it can be used in map
        bool result(false);
        auto [firstMismatchIt, secondMismatchIt] =
            std::mismatch(m_values.cbegin(), m_values.cend(), second.m_values.cbegin());
        if (firstMismatchIt != m_values.cend()) {
            result = *firstMismatchIt < *secondMismatchIt;
        }
        return result;
    }

    AlbaMathVector& operator+=(AlbaMathVector const& second) {
        ValuesInArray const& secondValues(second.m_values);
        std::transform(begin(m_values), end(m_values), begin(secondValues), begin(m_values), std::plus<DataType>());
        return *this;
    }

    AlbaMathVector& operator-=(AlbaMathVector const& second) {
        ValuesInArray const& secondValues(second.m_values);
        std::transform(begin(m_values), end(m_values), begin(secondValues), begin(m_values), std::minus<DataType>());
        return *this;
    }

    AlbaMathVector& operator*=(DataType const& scalarValue) {
        std::transform(
            begin(m_values), end(m_values), begin(m_values), [&](DataType const value) { return value * scalarValue; });
        return *this;
    }

    AlbaMathVector& operator/=(DataType const& scalarValue) {
        std::transform(
            begin(m_values), end(m_values), begin(m_values), [&](DataType const value) { return value / scalarValue; });
        return *this;
    }

    [[nodiscard]] DataType const& getValueAt(size_t const index) const {
        assert(index < SIZE);
        return m_values[index];
    }

    [[nodiscard]] DataType getMagnitude() const {
        // In 2D, in c++ complex number class this is same with abs(v).
        DataType sumOfSquaredTerms = std::accumulate(
            m_values.cbegin(), m_values.cend(), static_cast<DataType>(0),
            [](DataType const partialResult, DataType const currentValue) {
                return partialResult +
                       static_cast<DataType>(raiseToPowerForMathVectorDataType(currentValue, static_cast<DataType>(2)));
            });
        return static_cast<DataType>(
            raiseToPowerForMathVectorDataType(sumOfSquaredTerms, static_cast<DataType>(1) / static_cast<DataType>(2)));
    }

    [[nodiscard]] ValuesInArray const& getValues() const { return m_values; }
    [[nodiscard]] size_t getSize() const { return SIZE; }

    DataType& getValueReferenceAt(size_t const index) {
        assert(index < SIZE);
        return m_values[index];
    }

    ValuesInArray& getValuesReference() { return m_values; }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaMathVector const& mathVector) {
        ValuesInArray const& values(mathVector.m_values);
        if (!values.empty()) {
            out << "{" << values.front();
            for (auto it = values.cbegin() + 1; it != values.cend(); ++it) {
                out << ", " << *it;
            }
            out << "}";
        }
        return out;
    }

    ValuesInArray m_values;
};

}  // namespace alba
