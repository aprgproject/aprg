#pragma once

namespace alba {

template <typename DataType>
class DataCollection {
public:
    DataCollection() : m_minimum(0), m_maximum(0), m_theCountForMinimum(0), m_theCountForMaximum(0), m_sum(0) {}
    [[nodiscard]] int getCount() const { return m_count; }
    [[nodiscard]] double getAverageWithDoubleFormat() const { return static_cast<double>(m_sum) / m_count; }
    [[nodiscard]] DataType getMinimum() const { return m_minimum; }
    [[nodiscard]] DataType getMaximum() const { return m_maximum; }
    [[nodiscard]] DataType getTheCountForMinimum() const { return m_theCountForMinimum; }
    [[nodiscard]] DataType getTheCountForMaximum() const { return m_theCountForMaximum; }
    [[nodiscard]] DataType getSum() const { return m_sum; }
    [[nodiscard]] DataType getAverage() const { return (m_count == 0) ? 0 : m_sum / m_count; }

    void addData(DataType const& dataValue) {
        if (m_count == 0) {
            m_minimum = dataValue;
            m_maximum = dataValue;
        } else {  // no std::min, std::max because algorithm header is needed
            if (m_minimum > dataValue) {
                m_minimum = dataValue;
                m_theCountForMinimum = m_count;
            }
            if (m_maximum < dataValue) {
                m_maximum = dataValue;
                m_theCountForMaximum = m_count;
            }
        }
        m_sum += dataValue;
        ++m_count;
    }

    void clear() {
        m_minimum = 0;
        m_maximum = 0;
        m_sum = 0;
        m_count = 0;
    }

private:
    DataType m_minimum;
    DataType m_maximum;
    DataType m_theCountForMinimum;
    DataType m_theCountForMaximum;
    DataType m_sum;
    int m_count{0};
};

}  // namespace alba
