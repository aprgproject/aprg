#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <initializer_list>

namespace alba {

template <int DIMENSIONS>
class DataSample {
public:
    using Sample = DataSample<DIMENSIONS>;
    using BufferType = std::array<double, DIMENSIONS>;

    DataSample() { std::fill(m_data.begin(), m_data.end(), 0); }

    DataSample(std::initializer_list<double> const& dataSampleValues) {
        int limit = std::min(DIMENSIONS, static_cast<int>(dataSampleValues.size()));
        std::copy(dataSampleValues.begin(), dataSampleValues.begin() + limit, m_data.begin());
    }

    [[nodiscard]] bool isIndexValid(int const index) const { return index >= 0 && index < DIMENSIONS; }

    [[nodiscard]] int getSize() const { return m_data.size(); }

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

    void setValueAt(int const index, double const dataSampleValue) {
        if (isIndexValid(index)) {
            m_data[index] = dataSampleValue;
        }
    }

    bool operator==(Sample const& value) const {
        return std::equal(m_data.cbegin(), m_data.cend(), value.m_data.cbegin());
    }

    bool operator!=(Sample const& value) const { return !(*this == value); }

    Sample operator+(Sample const& value) const { return performDataTypeAndDataTypeFunction(value, std::plus<>()); }

    Sample operator-(Sample const& value) const { return performDataTypeAndDataTypeFunction(value, std::minus<>()); }

    Sample operator*(Sample const& value) const {
        return performDataTypeAndDataTypeFunction(value, std::multiplies<>());
    }

    Sample operator/(Sample const& value) const { return performDataTypeAndDataTypeFunction(value, std::divides<>()); }

    Sample operator+(double const value) const { return performDataTypeAndConstantFunction(value, std::plus<>()); }

    Sample operator-(double const value) const { return performDataTypeAndConstantFunction(value, std::minus<>()); }

    Sample operator*(double const value) const {
        return performDataTypeAndConstantFunction(value, std::multiplies<>());
    }

    Sample operator/(double const value) const { return performDataTypeAndConstantFunction(value, std::divides<>()); }

    [[nodiscard]] Sample calculateAbsoluteValue() const {
        return performDataTypeFunction(
            [](double const value) -> double { return mathHelper::getAbsoluteValue<double>(value); });
    }

    [[nodiscard]] Sample calculateRaiseToPower(double const value) const {
        return performDataTypeAndConstantFunction(
            value, [](double const value1, double const value2) -> double { return pow(value1, value2); });
    }

    [[nodiscard]] Sample calculateRaiseToInversePower(double const value) const {
        return performDataTypeAndConstantFunction(
            value, [](double const value1, double const value2) -> double { return pow(value1, static_cast<double>(1) / value2); });
    }

    Sample performDataTypeAndDataTypeFunction(
        Sample const& value, std::function<double(double, double)> binaryFunction) const {
        Sample result;
        std::transform(m_data.cbegin(), m_data.cend(), value.m_data.cbegin(), result.m_data.begin(), binaryFunction);
        return result;
    }

    Sample performDataTypeAndConstantFunction(
        double const value, std::function<double(double, double)> const& binaryFunction) const {
        Sample result;
        std::transform(m_data.begin(), m_data.cend(), result.m_data.begin(), [&](double const data) -> double {
            return binaryFunction(data, value);
        });
        return result;
    }

    Sample performDataTypeFunction(std::function<double(double)> const& unaryFunction) const {
        Sample result;
        std::transform(m_data.begin(), m_data.cend(), result.m_data.begin(), unaryFunction);
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, DataSample<DIMENSIONS> const& sample) {
        containerHelper::saveContentsToStream(out, sample.m_data, containerHelper::StreamFormat::String);
        return out;
    }

private:
    BufferType m_data;
};

}  // namespace alba
