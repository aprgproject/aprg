#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <initializer_list>

namespace alba {

using DataSampleInitializerList = std::initializer_list<double>;

template <int DIMENSIONS>
class DataSample {
public:
    using BufferType = std::array<double, DIMENSIONS>;
    DataSample() : m_data{} {}
    explicit DataSample(BufferType const& dataSampleValues) : m_data(dataSampleValues) {}
    explicit DataSample(BufferType&& dataSampleValues) : m_data(dataSampleValues) {}

    DataSample(std::initializer_list<double> const& dataSampleValues) {
        int const limit = std::min(DIMENSIONS, static_cast<int>(dataSampleValues.size()));
        std::copy(dataSampleValues.begin(), dataSampleValues.begin() + limit, m_data.begin());
    }

    DataSample operator+(DataSample const& value) const {
        return performDataTypeAndDataTypeFunction(value, std::plus<>());
    }

    DataSample operator-(DataSample const& value) const {
        return performDataTypeAndDataTypeFunction(value, std::minus<>());
    }

    DataSample operator*(DataSample const& value) const {
        return performDataTypeAndDataTypeFunction(value, std::multiplies<>());
    }

    DataSample operator/(DataSample const& value) const {
        return performDataTypeAndDataTypeFunction(value, std::divides<>());
    }

    DataSample operator+(double const value) const { return performDataTypeAndConstantFunction(value, std::plus<>()); }
    DataSample operator-(double const value) const { return performDataTypeAndConstantFunction(value, std::minus<>()); }

    DataSample operator*(double const value) const {
        return performDataTypeAndConstantFunction(value, std::multiplies<>());
    }

    DataSample operator/(double const value) const {
        return performDataTypeAndConstantFunction(value, std::divides<>());
    }

    bool operator==(DataSample const& value) const {
        return std::equal(m_data.cbegin(), m_data.cend(), value.m_data.cbegin());
    }

    bool operator!=(DataSample const& value) const { return !(*this == value); }

    [[nodiscard]] DataSample calculateAbsoluteValue() const {
        return performDataTypeFunction(
            [](double const value) -> double { return mathHelper::getAbsoluteValue<double>(value); });
    }

    [[nodiscard]] DataSample calculateRaiseToPower(double const value) const {
        return performDataTypeAndConstantFunction(
            value, [](double const value1, double const value2) -> double { return pow(value1, value2); });
    }

    [[nodiscard]] DataSample calculateRaiseToInversePower(double const value) const {
        return performDataTypeAndConstantFunction(value, [](double const value1, double const value2) -> double {
            return pow(value1, static_cast<double>(1) / value2);
        });
    }

    [[nodiscard]] double getValueAt(int const index) const {
        double result(0);
        if (isIndexValid(index)) {
            result = m_data[index];
        }
        return result;
    }

    [[nodiscard]] double getSum() const {
        double result(0);
        for (int index = 0; index < DIMENSIONS; ++index) {
            result += m_data[index];
        }
        return result;
    }

    [[nodiscard]] int getSize() const { return m_data.size(); }
    [[nodiscard]] bool isIndexValid(int const index) const { return index >= 0 && index < DIMENSIONS; }

    DataSample performDataTypeAndDataTypeFunction(
        DataSample const& value, std::function<double(double, double)> binaryFunction) const {
        DataSample result;
        std::transform(m_data.cbegin(), m_data.cend(), value.m_data.cbegin(), result.m_data.begin(), binaryFunction);
        return result;
    }

    DataSample performDataTypeAndConstantFunction(
        double const value, std::function<double(double, double)> const& binaryFunction) const {
        DataSample result;
        std::transform(m_data.begin(), m_data.cend(), result.m_data.begin(), [&](double const data) -> double {
            return binaryFunction(data, value);
        });
        return result;
    }

    DataSample performDataTypeFunction(std::function<double(double)> const& unaryFunction) const {
        DataSample result;
        std::transform(m_data.begin(), m_data.cend(), result.m_data.begin(), unaryFunction);
        return result;
    }

    void setValueAt(int const index, double const dataSampleValue) {
        if (isIndexValid(index)) {
            m_data[index] = dataSampleValue;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, DataSample const& sample) {
        containerHelper::saveContentsToStream(out, sample.m_data, containerHelper::StreamFormat::String);
        return out;
    }

private:
    BufferType m_data;
};

}  // namespace alba
