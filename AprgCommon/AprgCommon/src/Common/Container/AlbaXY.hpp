#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <ostream>
#include <tuple>

namespace alba {

template <typename CoordinateType>
class AlbaXY {
public:
    AlbaXY() : m_x{}, m_y{} {}
    AlbaXY(CoordinateType const& xValue, CoordinateType const& yValue) : m_x(xValue), m_y(yValue) {}
    AlbaXY operator+() const { return *this; }
    AlbaXY operator-() const { return AlbaXY(-m_x, -m_y); }
    AlbaXY operator+(AlbaXY const& secondXy) const { return AlbaXY(m_x + secondXy.m_x, m_y + secondXy.m_y); }
    AlbaXY operator-(AlbaXY const& secondXy) const { return AlbaXY(m_x - secondXy.m_x, m_y - secondXy.m_y); }
    AlbaXY operator*(CoordinateType const& multiplier) const { return AlbaXY(m_x * multiplier, m_y * multiplier); }
    AlbaXY operator/(CoordinateType const& divisor) const { return AlbaXY(m_x / divisor, m_y / divisor); }

    // rule of zero
    bool operator==(AlbaXY const& xyValues) const {
        return mathHelper::isAlmostEqual(m_x, xyValues.m_x) && mathHelper::isAlmostEqual(m_y, xyValues.m_y);
    }

    bool operator!=(AlbaXY const& secondXy) const {
        AlbaXY const& firstXy(*this);
        return !(firstXy == secondXy);
    }

    bool operator<(AlbaXY const& xyValues) const {
        // this is added so it can be used in map
        return std::tie(m_x, m_y) < std::tie(xyValues.m_x, xyValues.m_y);
    }

    AlbaXY& operator+=(AlbaXY const& secondXy) {
        m_x += secondXy.m_x;
        m_y += secondXy.m_y;
        return *this;
    }

    AlbaXY& operator-=(AlbaXY const& secondXy) {
        m_x -= secondXy.m_x;
        m_y -= secondXy.m_y;
        return *this;
    }

    AlbaXY& operator*=(CoordinateType const& multiplier) {
        m_x *= multiplier;
        m_y *= multiplier;
        return *this;
    }

    AlbaXY& operator/=(CoordinateType const& divisor) {
        m_x /= divisor;
        m_y /= divisor;
        return *this;
    }

    [[nodiscard]] CoordinateType getX() const { return m_x; }
    [[nodiscard]] CoordinateType getY() const { return m_y; }
    [[nodiscard]] CoordinateType getXTimesY() const { return m_x * m_y; }
    [[nodiscard]] bool isEmpty() const { return CoordinateType{} == m_x && CoordinateType{} == m_y; }
    void setX(CoordinateType const& xValue) { m_x = xValue; }
    void setY(CoordinateType const& yValue) { m_y = yValue; }

    void setXAndY(CoordinateType const& xValue, CoordinateType const& yValue) {
        m_x = xValue;
        m_y = yValue;
    }

    void saveMinimumXAndY(AlbaXY const xyValues) {
        if (m_x > xyValues.m_x) {
            m_x = xyValues.m_x;
        }
        if (m_y > xyValues.m_y) {
            m_y = xyValues.m_y;
        }
    }

    void saveMaximumXAndY(AlbaXY const xyValues) {
        if (m_x < xyValues.m_x) {
            m_x = xyValues.m_x;
        }
        if (m_y < xyValues.m_y) {
            m_y = xyValues.m_y;
        }
    }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaXY const& xyValues) {
        out << "(" << xyValues.m_x << "," << xyValues.m_y << ")";
        return out;
    }

    CoordinateType m_x;
    CoordinateType m_y;
};

}  // namespace alba
