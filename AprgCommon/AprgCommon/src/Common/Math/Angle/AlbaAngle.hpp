#pragma once

#include <ostream>
#include <vector>

namespace alba {

enum class AngleUnitType { Radians, Degrees };

class AlbaAngle {
public:
    AlbaAngle() = default;
    AlbaAngle(AngleUnitType const angleUnitType, double const angleValue);
    AlbaAngle operator+(AlbaAngle const& secondAngle) const;
    AlbaAngle operator-(AlbaAngle const& secondAngle) const;
    AlbaAngle operator+() const;
    AlbaAngle operator-() const;
    // rule of zero
    bool operator==(AlbaAngle const& angle) const;
    bool operator!=(AlbaAngle const& angle) const;
    bool operator<(AlbaAngle const& angle) const;
    AlbaAngle& operator+=(AlbaAngle const& secondAngle);
    AlbaAngle& operator-=(AlbaAngle const& secondAngle);
    [[nodiscard]] double getDegrees() const;
    [[nodiscard]] double getRadians() const;
    void setAngleValueInDegreesNearestToZero();

private:
    static double calculateAngleValueInDegrees(AngleUnitType const angleInputType, double const angleValue);
    friend std::ostream& operator<<(std::ostream& out, AlbaAngle const& angle);
    double m_angleValueInDegrees{};
};

using AlbaAngles = std::vector<AlbaAngle>;

}  // namespace alba
