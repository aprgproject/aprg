#pragma once

#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <string>
#include <vector>

namespace alba::TwoDimensions {

enum class LineType { Horizontal, Vertical, WithPositiveSlope, WithNegativeSlope, Invalid };

class Line {
public:
    Line();
    Line(Point const& first, Point const& second);
    Line(double const aCoefficient, double const bCoefficient, double const cCoefficient);  // ax+by+c=0
    Line(double const aCoefficient, double const bCoefficient, Point const& point);         // ax+by+c=0
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
    [[nodiscard]] LineType getType() const;
    [[nodiscard]] Point getAPoint() const;
    [[nodiscard]] Points getPoints(Point const& first, Point const& second, double const interval) const;

    [[nodiscard]] Points getPointsWithoutLastPoint(
        Point const& first, Point const& second, double const interval) const;

    [[nodiscard]] double getXIntercept() const;  // form: a*(x-x0) + b*(y-y0) = 0
    [[nodiscard]] double getYIntercept() const;  // form: a*(x-x0) + b*(y-y0) = 0
    [[nodiscard]] double getSlope() const;
    [[nodiscard]] double getPerpendicularSlope() const;
    [[nodiscard]] double getACoefficient() const;
    [[nodiscard]] double getBCoefficient() const;
    [[nodiscard]] double getCCoefficient() const;
    [[nodiscard]] double getAUnitIncreaseInX() const;
    [[nodiscard]] double getAUnitIncreaseInY() const;
    [[nodiscard]] double calculateYFromX(double const x) const;
    [[nodiscard]] double calculateXFromY(double const y) const;

private:
    void getPointsForVerticalLine(Points& points, Point const& first, Point const& second, double const interval) const;

    void getPointsForHorizontalLine(
        Points& points, Point const& first, Point const& second, double const interval) const;

    void getPointsForLineWithSlope(
        Points& points, Point const& first, Point const& second, double const interval) const;

    void setLineParametersBasedOnDeltas(double const deltaX, double const deltaY, Point const& point);

    void setLineParametersBasedOnCoefficients(
        double const aCoefficient, double const bCoefficient, double const cCoefficient);

    void setCoefficientsUsingLineTypeAndDeltaXandDeltaYAndAPoint(
        double const deltaY, double const deltaX, Point const& point);

    static void mergePointsFromPointsFromXAndY(
        Points& points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate,
        bool const isDirectionAscendingForX);

    static LineType determineLineTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX);
    static LineType determineLineTypeUsingCoefficients(double const aCoefficient, double const bCoefficient);
    friend std::ostream& operator<<(std::ostream& out, Line const& line);
    LineType m_type;
    double m_aCoefficient;  // form: a*x + b*y + c = 0
    double m_bCoefficient;  // form: a*x + b*y + c = 0
    double m_cCoefficient;  // form: a*x + b*y + c = 0
};

using Lines = std::vector<Line>;

}  // namespace alba::TwoDimensions
