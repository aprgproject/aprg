#include "Hyperbola.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba::TwoDimensions {

Hyperbola::Hyperbola() : m_aValue(0), m_bValue(0) {}

Hyperbola::Hyperbola(Point const& center, double const aCoefficient, double const bCoefficient)
    : m_center(center), m_aValue(aCoefficient), m_bValue(bCoefficient) {}

bool Hyperbola::operator==(Hyperbola const& hyperbola) const {
    return (m_center == hyperbola.m_center) && isAlmostEqual(m_aValue, hyperbola.m_aValue) &&
           isAlmostEqual(m_bValue, hyperbola.m_bValue);
}

bool Hyperbola::operator!=(Hyperbola const& hyperbola) const { return !((*this) == hyperbola); }

Lines Hyperbola::getAsymptotes() const {
    Lines result;
    result.emplace_back(m_bValue, m_aValue, -m_bValue * m_center.getX() - m_aValue * m_center.getY());
    result.emplace_back(m_bValue, -m_aValue, -m_bValue * m_center.getX() + m_aValue * m_center.getY());
    return result;
}

Point Hyperbola::getCenter() const { return m_center; }

Points Hyperbola::getFoci() const {
    Points foci;
    if (m_aValue > 0) {
        double const c(getCValue());
        foci.emplace_back(m_center + Point(c, 0));
        foci.emplace_back(m_center - Point(c, 0));
    } else {
        double const c(getCValue());
        foci.emplace_back(m_center + Point(0, c));
        foci.emplace_back(m_center - Point(0, c));
    }
    return foci;
}

Points Hyperbola::getVertices() const {
    Points vertices;
    if (m_aValue > 0) {
        vertices.emplace_back(m_center + Point(m_aValue, 0));
        vertices.emplace_back(m_center - Point(m_aValue, 0));
    } else {
        double const bPositive = getAbsoluteValue(m_bValue);
        vertices.emplace_back(m_center + Point(0, bPositive));
        vertices.emplace_back(m_center - Point(0, bPositive));
    }
    return vertices;
}

Points Hyperbola::getPointsForShape(double const interval) const {
    Points result;
    if (m_aValue != 0 && m_bValue != 0) {
        Points const pointsInFirstQuarter(getPointsInTraversingXAndY(1, 1, interval));
        Points const pointsInFourthQuarter(getPointsInTraversingXAndY(1, -1, interval));
        Points const pointsInSecondQuarter(getPointsInTraversingXAndY(-1, 1, interval));
        Points const pointsInThirdQuarter(getPointsInTraversingXAndY(-1, -1, interval));
        result.reserve(
            pointsInFirstQuarter.size() + pointsInSecondQuarter.size() + pointsInThirdQuarter.size() +
            pointsInFourthQuarter.size());
        copy(pointsInFirstQuarter.cbegin(), pointsInFirstQuarter.cend() - 1, back_inserter(result));
        copy(pointsInFourthQuarter.cbegin(), pointsInFourthQuarter.cend(), back_inserter(result));
        copy(pointsInSecondQuarter.cbegin(), pointsInSecondQuarter.cend() - 1, back_inserter(result));
        copy(pointsInThirdQuarter.cbegin(), pointsInThirdQuarter.cend(), back_inserter(result));
    }
    return result;
}

double Hyperbola::getAValue() const { return m_aValue; }
double Hyperbola::getBValue() const { return m_bValue; }
double Hyperbola::getCValue() const { return getSquareRootOfXSquaredPlusYSquared(m_aValue, m_bValue); }
double Hyperbola::getEccentricity() const { return pow(1 + (pow(m_bValue, 2) / pow(m_aValue, 2)), 0.5); }
double Hyperbola::getSemiLactusRectum() const { return pow(m_bValue, 2) / m_aValue; }

double Hyperbola::calculateYFromX(double const x, double const signOfRoot) const {
    return pow(pow((x - m_center.getX()) / m_aValue, 2) - 1, 0.5) * signOfRoot * m_bValue + m_center.getY();
}

double Hyperbola::calculateXFromY(double const y, double const signOfRoot) const {
    return pow(1 + pow((y - m_center.getY()) / m_bValue, 2), 0.5) * signOfRoot * m_aValue + m_center.getX();
}

double Hyperbola::calculateYFromXWithoutCenter(double const x, double const signOfRoot) const {
    return pow(pow(x / m_aValue, 2) - 1, 0.5) * signOfRoot * m_bValue;
}

double Hyperbola::calculateXFromYWithoutCenter(double const y, double const signOfRoot) const {
    return pow(1 + pow(y / m_bValue, 2), 0.5) * signOfRoot * m_aValue;
}

Points Hyperbola::getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const {
    Points result;
    Points const pointsFromTraversingX(getPointsInTraversingX(signOfX, signOfY, interval));
    Points const pointsFromTraversingY(getPointsInTraversingY(signOfX, signOfY, interval));
    // NOLINTBEGIN(bugprone-branch-clone)
    if (signOfX > 0 && signOfY > 0) {
        // first quarter
        result = getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    } else if (signOfX > 0 && signOfY < 0) {
        // fourth quarter
        result = getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    } else if (signOfX < 0 && signOfY > 0) {
        // second quarter
        result = getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    } else if (signOfX < 0 && signOfY < 0) {
        // third quarter
        result = getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    // NOLINTEND(bugprone-branch-clone)
    return result;
}

Points Hyperbola::getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const {
    Points result;
    AlbaValueRange<double> const yRange(m_center.getY(), m_center.getY() + (m_bValue * signOfY), interval);
    yRange.traverse([&](double const yValue) { result.emplace_back(calculateXFromY(yValue, signOfX), yValue); });
    return result;
}

Points Hyperbola::getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const {
    Points result;
    double const stepValue(m_aValue * signOfX);
    AlbaValueRange<double> const xRange(
        m_center.getX() + stepValue, m_center.getX() + 2 * stepValue,
        interval);  // whats with the 2 step value? it should configurable
    xRange.traverse([&](double const xValue) { result.emplace_back(xValue, calculateYFromX(xValue, signOfY)); });
    return result;
}

ostream& operator<<(ostream& out, Hyperbola const& hyperbola) {
    out << "(center: " << hyperbola.m_center << " a: " << hyperbola.m_aValue << " b: " << hyperbola.m_bValue << ")";
    return out;
}

}  // namespace alba::TwoDimensions
