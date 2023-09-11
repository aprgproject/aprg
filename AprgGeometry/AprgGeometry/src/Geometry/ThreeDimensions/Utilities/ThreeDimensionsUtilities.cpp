#include "ThreeDimensionsUtilities.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba::ThreeDimensions::threeDimensionsUtilities {

namespace {

// end of internal functions
// Internal functions
double calculateMultiplierForIntersection(
    double const firstCoordinateCoefficientLine1, double const firstCoordinateCoefficientLine2,
    double const secondCoordinateCoefficientLine1, double const secondCoordinateCoefficientLine2,
    double const firstCoordinateInitialValueLine1, double const firstCoordinateInitialValueLine2,
    double const secondCoordinateInitialValueLine1, double const secondCoordinateInitialValueLine2) {
    // put math here
    double const denominator = (firstCoordinateCoefficientLine2 * secondCoordinateCoefficientLine1) -
                               (firstCoordinateCoefficientLine1 * secondCoordinateCoefficientLine2);
    double const numerator =
        ((firstCoordinateInitialValueLine1 - firstCoordinateInitialValueLine2) * secondCoordinateCoefficientLine1) -
        ((secondCoordinateInitialValueLine1 - secondCoordinateInitialValueLine2) * firstCoordinateCoefficientLine1);
    return numerator / denominator;
}

double getCoordinateinLineIntersection(
    double const coefficientOfCommonCoordinate1, double const coefficientOfCommonCoordinate2,
    double const coefficientOfCoordinateToDetermine1, double const coefficientOfCoordinateToDetermine2,
    double const dCoefficient1, double const dCoefficient2) {
    // yCoordinateIntersection calculation is (a1d2-a2d1)/(a2b1-a1b2)
    double const numerator =
        (coefficientOfCommonCoordinate1 * dCoefficient2) - (coefficientOfCommonCoordinate2 * dCoefficient1);
    double const denominator = (coefficientOfCommonCoordinate2 * coefficientOfCoordinateToDetermine1) -
                               (coefficientOfCommonCoordinate1 * coefficientOfCoordinateToDetermine2);
    return numerator / denominator;
}

bool isCoordinateValuesInLineEqual(
    double const coordinateValueToCompare, optional<double> const& coordinateOptionalToCompare1,
    double const coordinate2Value, double const coordinate2InitialValue,
    optional<double> const& coordinateOptionalToCompare2, double const coordinate3Value,
    double const coordinate3InitialValue) {
    bool result(false);
    if (coordinateOptionalToCompare1) {
        result = isAlmostEqual(coordinateValueToCompare, coordinateOptionalToCompare1.value());
    } else if (coordinateOptionalToCompare2) {
        result = isAlmostEqual(coordinateValueToCompare, coordinateOptionalToCompare2.value());
    } else {
        result = isAlmostEqual(coordinate2Value, coordinate2InitialValue) &&
                 isAlmostEqual(coordinate3Value, coordinate3InitialValue);
    }
    return result;
}

bool isCoordinateValuesInPlaneEqual(
    double const coordinateValueToCompare, optional<double> const& coordinateOptionalToCompare) {
    bool result(false);
    if (coordinateOptionalToCompare) {
        result = isAlmostEqual(coordinateValueToCompare, coordinateOptionalToCompare.value());
    } else {
        result = true;
    }
    return result;
}

}  // namespace

AlbaAngle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC) {
    Point const deltaBA(pointB - pointA);
    Point const deltaCA(pointC - pointA);
    return {
        AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(constructVector(deltaBA), constructVector(deltaCA)))};
}

AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2) {
    AlbaAngle smallerAngle;
    if (areLinesParallel(line1, line2)) {
        smallerAngle = AlbaAngle(AngleUnitType::Degrees, 0);
    } else {
        // absolute value is used to ensure lower angle
        // from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
        smallerAngle = AlbaAngle(
            AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(
                                        constructDeltaVector(line1), constructDeltaVector(line2)))));
    }
    return smallerAngle;
}

AlbaAngle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2) {
    AlbaAngle const smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return {AngleUnitType::Degrees, 180 - smallerAngle.getDegrees()};
}

AlbaAngle getTheSmallerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2) {
    AlbaAngle result;
    if (arePlanesParallel(plane1, plane2)) {
        result = AlbaAngle(AngleUnitType::Degrees, 0);
    } else {
        result = AlbaAngle(
            AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(
                                        constructNormalVector(plane1), constructNormalVector(plane2)))));
    }
    return result;
}

AlbaAngle getTheLargerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2) {
    AlbaAngle const smallerAngle(getTheSmallerDihedralAngleBetweenTwoPlanes(plane1, plane2));
    return {AngleUnitType::Degrees, 180 - smallerAngle.getDegrees()};
}

Line getLineWithSameSlope(Line const& line, Point const& point) {
    return {line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient(), point};
}

Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2) {
    Vector const perpendicularVector = getCrossProduct(constructNormalVector(plane1), constructNormalVector(plane2));
    double const yCoordinateIntersection = getCoordinateinLineIntersection(
        plane1.getACoefficient(), plane2.getACoefficient(), plane1.getBCoefficient(), plane2.getBCoefficient(),
        plane1.getDCoefficient(), plane2.getDCoefficient());

    // format is a1x+b1y+c1z+d1 = 0
    // format is a2x+b2y+c2z+d2 = 0
    // assuming z=0
    // yCoordinateIntersection calculation is (a1d2-a2d1)/(a2b1-a1b2)
    double const xCoordinateIntersection = plane1.calculateXFromYAndZ(yCoordinateIntersection, 0.0).value();
    Point const point1(xCoordinateIntersection, yCoordinateIntersection, 0.0);
    Point const point2(
        point1 +
        Point(perpendicularVector.getValueAt(0), perpendicularVector.getValueAt(1), perpendicularVector.getValueAt(2)));
    return {point1, point2};
}

Line getPerpendicularLineOfPlaneWithAPoint(Plane const& plane, Point const& point) {
    return {plane.getACoefficient(),
            plane.getBCoefficient(),
            plane.getCCoefficient(),
            point.getX(),
            point.getY(),
            point.getZ()};
}

Line getProjectedLineInPlaneOfASkewedPlaneAndLine(Plane const& plane, Line const& line) {
    Vector const planeCoefficients{plane.getACoefficient(), plane.getBCoefficient(), plane.getCCoefficient()};
    Vector const lineCoefficients{line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient()};
    Vector const perpendicularVectorPlaneAndLine(getCrossProduct(planeCoefficients, lineCoefficients));
    Vector const directionCoefficients(getCrossProduct(planeCoefficients, perpendicularVectorPlaneAndLine));
    Point const pointInLine(getPointOfIntersectionOfAPlaneAndALine(plane, line));
    return {
        directionCoefficients.getValueAt(0), directionCoefficients.getValueAt(1), directionCoefficients.getValueAt(2),
        pointInLine};
}

Plane getPlaneWithContainsALineAndAPoint(Line const& line, Point const& point) {
    Point const point1InLine(line.getXInitialValue(), line.getYInitialValue(), line.getZInitialValue());
    Point const point2InLine(
        point1InLine + Point(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient()));
    return {point, point1InLine, point2InLine};
}

Plane getPlaneWithTwoIntersectingLines(Line const& line1, Line const& line2) {
    Point const pointOfIntersection(getPointOfIntersectionOfTwoLines(line1, line2));
    Point const pointInLine1(
        pointOfIntersection + Point(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient()));
    Point const pointInLine2(
        pointOfIntersection + Point(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient()));
    return {pointOfIntersection, pointInLine1, pointInLine2};
}

Plane getPlaneOfTwoDifferentLinesWithSameSlope(Line const& line1, Line const& line2) {
    Point const pointInLine1(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue());
    Point const secondPointInLine1(
        pointInLine1 + Point(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient()));
    Point const pointInLine2(line2.getXInitialValue(), line2.getYInitialValue(), line2.getZInitialValue());
    return {pointInLine1, secondPointInLine1, pointInLine2};
}

Plane getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line const& line, Point const& pointInPerpendicularPlane) {
    return {line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient(), pointInPerpendicularPlane};
}

Point getMidpoint(Point const& point1, Point const& point2) {
    return {
        (point1.getX() + point2.getX()) / 2, (point1.getY() + point2.getY()) / 2, (point1.getZ() + point2.getZ()) / 2};
}

Point getPointOfIntersectionOfTwoLines(Line const& line1, Line const& line2) {
    double const multiplier1 = calculateMultiplierForIntersection(
        line1.getACoefficient(), line2.getACoefficient(), line1.getBCoefficient(), line2.getBCoefficient(),
        line1.getXInitialValue(), line2.getXInitialValue(), line1.getYInitialValue(), line2.getYInitialValue());
    // double multiplier2 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(),
    // line1.getCCoefficient(), line2.getCCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(),
    // line1.getZInitialValue(), line2.getZInitialValue()); double multiplier3 =
    // calculateMultiplierForIntersection(line1.getCCoefficient(), line2.getCCoefficient(), line1.getACoefficient(),
    // line2.getACoefficient(), line1.getZInitialValue(), line2.getZInitialValue(), line1.getXInitialValue(),
    // line2.getXInitialValue()); assert(isAlmostEqual(multiplier1, multiplier2)); assert(isAlmostEqual(multiplier1,
    // multiplier3)); assert(isAlmostEqual(multiplier2, multiplier3));
    return {
        Point(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue()) +
        Point(
            multiplier1 * line1.getACoefficient(), multiplier1 * line1.getBCoefficient(),
            multiplier1 * line1.getCCoefficient())};
}

Point getPointOfIntersectionOfAPlaneAndALine(Plane const& plane, Line const& line) {
    assert(!isLineInPlane(line, plane));
    // aplane(xinitial+aline*mult) + bplane(yinitial+bline*mult) + cplane(zinitial+cline*mult) + dplane = 0
    double const multiplierInLineNumeratorPart =
        plane.getACoefficient() * line.getXInitialValue() + plane.getBCoefficient() * line.getYInitialValue() +
        plane.getCCoefficient() * line.getZInitialValue() + plane.getDCoefficient();
    double const multiplierInLineDenominatorPart = plane.getACoefficient() * line.getACoefficient() +
                                                   plane.getBCoefficient() * line.getBCoefficient() +
                                                   plane.getCCoefficient() * line.getCCoefficient();
    double const multiplier = multiplierInLineNumeratorPart / multiplierInLineDenominatorPart;
    return Point(line.getXInitialValue(), line.getYInitialValue(), line.getZInitialValue()) -
           Point(
               multiplier * line.getACoefficient(), multiplier * line.getBCoefficient(),
               multiplier * line.getCCoefficient());
}

Vector constructVector(AlbaXYZ<double> const& xyz) { return Vector{xyz.getX(), xyz.getY(), xyz.getZ()}; }

Vector constructDeltaVector(Line const& line) {
    return Vector{line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient()};
}

Vector constructNormalVector(Plane const& plane) {
    return Vector{plane.getACoefficient(), plane.getBCoefficient(), plane.getCCoefficient()};
}

double getDistance(Point const& point1, Point const& point2) {
    Point const delta(point2 - point1);
    return getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(delta.getX(), delta.getY(), delta.getZ());
}

double getDistance(Line const& line, Point const& point) {
    Plane const perpendicularPlane(getPerpendicularPlaneOfALineAndUsingAPointInThePlane(line, point));
    Point const nearestPoint(getPointOfIntersectionOfAPlaneAndALine(perpendicularPlane, line));
    return getDistance(point, nearestPoint);
}

double getDistance(Line const& line1, Line const& line2) {
    double distance(0);
    if (areLinesParallel(line1, line2)) {
        Point const pointInLine1(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue());
        Plane const perpendicularPlane = getPerpendicularPlaneOfALineAndUsingAPointInThePlane(line1, pointInLine1);
        Point const pointInLine2 = getPointOfIntersectionOfAPlaneAndALine(perpendicularPlane, line2);
        distance = getDistance(pointInLine1, pointInLine2);
    } else {
        Vector const perpendicularVector(getCrossProduct(constructDeltaVector(line1), constructDeltaVector(line2)));
        Point const pointInLine1(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue());
        Point const pointInLine2(line2.getXInitialValue(), line2.getYInitialValue(), line2.getZInitialValue());

        Plane const plane1(
            perpendicularVector.getValueAt(0), perpendicularVector.getValueAt(1), perpendicularVector.getValueAt(2),
            pointInLine1);
        Plane const plane2(
            perpendicularVector.getValueAt(0), perpendicularVector.getValueAt(1), perpendicularVector.getValueAt(2),
            pointInLine2);

        distance = getDistance(plane1, plane2);
    }
    return distance;
}

double getDistance(Plane const& plane1, Plane const& plane2) {
    double distance(0);
    if (arePlanesParallel(plane1, plane2)) {
        Line const perpendicularLine(
            plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient(), Point(0, 0, 0));
        Point const point1(getPointOfIntersectionOfAPlaneAndALine(plane1, perpendicularLine));
        Point const point2(getPointOfIntersectionOfAPlaneAndALine(plane2, perpendicularLine));
        distance = getDistance(point1, point2);
    }
    return distance;
}

double getCosineOfAngleUsing2Deltas(Vector const& deltaVector1, Vector const& deltaVector2) {
    // from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
    double const numeratorPart = getDotProduct(deltaVector1, deltaVector2);
    double const denominatorPart = deltaVector1.getMagnitude() * deltaVector2.getMagnitude();
    return numeratorPart / denominatorPart;
}

// external functions
bool isPointInLine(Point const& point, Line const& line) {
    return isCoordinateValuesInLineEqual(
               point.getX(), line.calculateXFromY(point.getY()), point.getY(), line.getYInitialValue(),
               line.calculateXFromZ(point.getZ()), point.getZ(), line.getZInitialValue()) &&
           isCoordinateValuesInLineEqual(
               point.getY(), line.calculateYFromX(point.getX()), point.getX(), line.getXInitialValue(),
               line.calculateYFromZ(point.getZ()), point.getZ(), line.getZInitialValue()) &&
           isCoordinateValuesInLineEqual(
               point.getZ(), line.calculateZFromX(point.getX()), point.getX(), line.getXInitialValue(),
               line.calculateZFromY(point.getY()), point.getY(), line.getYInitialValue());
}

bool isPointInPlane(Point const& point, Plane const& plane) {
    return isCoordinateValuesInPlaneEqual(point.getX(), plane.calculateXFromYAndZ(point.getY(), point.getZ())) &&
           isCoordinateValuesInPlaneEqual(point.getY(), plane.calculateYFromXAndZ(point.getX(), point.getZ())) &&
           isCoordinateValuesInPlaneEqual(point.getZ(), plane.calculateZFromXAndY(point.getX(), point.getY()));
}

bool isLineInPlane(Line const& line, Plane const& plane) {
    Point const point1(line.getXInitialValue(), line.getYInitialValue(), line.getZInitialValue());
    Point const point2(point1 + Point(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient()));
    return isPointInPlane(point1, plane) && isPointInPlane(point2, plane);
}

bool areLinesParallel(Line const& line1, Line const& line2) {
    return areVectorsParallel(constructDeltaVector(line1), constructDeltaVector(line2));
}

bool arePlanesParallel(Plane const& plane1, Plane const& plane2) {
    return areVectorsParallel(constructNormalVector(plane1), constructNormalVector(plane2));
}

bool areLinesPerpendicular(Line const& line1, Line const& line2) {
    return areVectorsPerpendicular(constructDeltaVector(line1), constructDeltaVector(line2));
}

bool arePlanesPerpendicular(Plane const& plane1, Plane const& plane2) {
    return areVectorsPerpendicular(constructNormalVector(plane1), constructNormalVector(plane2));
}

}  // namespace alba::ThreeDimensions::threeDimensionsUtilities
