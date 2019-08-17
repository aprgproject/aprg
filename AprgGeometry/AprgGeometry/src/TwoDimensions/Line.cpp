#include "Line.hpp"

#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

Line::Line()
    : m_type(LineType::Invalid)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_yIntercept(0)
    , m_xIntercept(0)
{}

Line::Line(Point const& first, Point const& second)
    : m_type(LineType::Invalid)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_yIntercept(0)
    , m_xIntercept(0)
{
    double deltaY = second.getY() - first.getY();
    double deltaX = second.getX() - first.getX();    setLineParametersBasedOnDeltas(deltaX, deltaY, first);
}

Line::Line(double const aCoefficient, double const bCoefficient, double const cCoefficient)
    : m_type(LineType::Invalid)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_yIntercept(0)
    , m_xIntercept(0)
{
    setLineParametersBasedOnCoefficients(aCoefficient, bCoefficient, cCoefficient);
}

Line::Line(double const aCoefficient, double const bCoefficient, Point const& point)    : m_type(LineType::Invalid)
    , m_yIntercept(0)
    , m_xIntercept(0)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
{
    double deltaX = aCoefficient;
    double deltaY = bCoefficient;    setLineParametersBasedOnDeltas(deltaX, deltaY, point);
}

bool Line::operator==(Line const& line) const
{
    double commonFactor1 = (m_aCoefficient!=0) ? m_aCoefficient : (m_bCoefficient!=0) ? m_bCoefficient : (m_cCoefficient!=0) ? m_cCoefficient : 1;
    double commonFactor2 = (line.m_aCoefficient!=0) ? line.m_aCoefficient : (line.m_bCoefficient!=0) ? line.m_bCoefficient : (line.m_cCoefficient!=0) ? line.m_cCoefficient : 1;
    return (m_type == line.m_type)
            && isAlmostEqual(m_aCoefficient/commonFactor1, line.m_aCoefficient/commonFactor2)
            && isAlmostEqual(m_bCoefficient/commonFactor1, line.m_bCoefficient/commonFactor2)
            && isAlmostEqual(m_cCoefficient/commonFactor1, line.m_cCoefficient/commonFactor2);
}

bool Line::operator!=(Line const& line) const{
    return !((*this)==line);
}

LineType Line::getType() const
{
    return m_type;
}

double Line::getXIntercept() const
{
    return m_xIntercept;
}

double Line::getYIntercept() const
{
    return m_yIntercept;
}

double Line::getSlope() const
{
    return -m_aCoefficient/m_bCoefficient;
}

double Line::getInverseSlope() const
{
    return m_bCoefficient/m_aCoefficient;
}

double Line::getACoefficient() const{
    return m_aCoefficient;
}

double Line::getBCoefficient() const
{
    return m_bCoefficient;
}

double Line::getCCoefficient() const
{
    return m_cCoefficient;
}

double Line::getAUnitIncreaseInX() const
{
    return m_bCoefficient;
}

double Line::getAUnitIncreaseInY() const
{
    return -m_aCoefficient;
}

Points Line::getPoints(Point const& first, Point const& second, double const interval) const
{
    Points points;
    if(m_type == LineType::Vertical)
    {
        getPointsForVerticalLine(points, first, second, interval);
    }
    else if(m_type == LineType::Horizontal)
    {
        getPointsForHorizontalLine(points, first, second, interval);
    }
    else if(m_type == LineType::WithPositiveSlope || m_type == LineType::WithNegativeSlope)
    {
        getPointsForLineWithSlope(points, first, second, interval);
    }
    return points; //RVO
}

Points Line::getPointsWithoutLastPoint(Point const& first, Point const& second, double const interval) const
{
    Points pointsWithoutLastPoint(getPoints(first, second, interval));
    if(!pointsWithoutLastPoint.empty())
    {
        pointsWithoutLastPoint.pop_back();
    }
    return pointsWithoutLastPoint; //RVO
}

double Line::calculateYFromX(double const x) const
{
    return -1*(m_aCoefficient*x + m_cCoefficient)/m_bCoefficient; //form: y = -(a*x + c)/b
}

double Line::calculateXFromY(double const y) const
{
    return -1*(m_bCoefficient*y + m_cCoefficient)/m_aCoefficient; //form: x = -(b*y + c)/a
}

string Line::getDisplayableString() const{
    std::stringstream ss;
    ss << m_aCoefficient << "*x + "<< m_bCoefficient << "*y + " << m_cCoefficient << " = 0";
    return ss.str();
}

void Line::setLineParametersBasedOnDeltas(double const deltaX, double const deltaY, Point const& point)
{
    m_type = determineLineTypeUsingDeltaXandDeltaY(deltaY, deltaX);
    setCoefficientsUsingLineTypeAndDeltaXandDeltaYAndAPoint(deltaY, deltaX, point);
    setInterceptsBasedOnSavedCoefficients();
}

void Line::setLineParametersBasedOnCoefficients(double const aCoefficient, double const bCoefficient, double const cCoefficient)
{
    m_type = determineLineTypeUsingCoefficients(aCoefficient, bCoefficient);
    m_aCoefficient = aCoefficient;
    m_bCoefficient = bCoefficient;
    m_cCoefficient = cCoefficient;
    setInterceptsBasedOnSavedCoefficients();
}

void Line::setCoefficientsUsingLineTypeAndDeltaXandDeltaYAndAPoint(double const deltaY, double const deltaX, Point const& point)
{
    switch(m_type)
    {
    case LineType::Invalid:
        m_aCoefficient = 0;
        m_bCoefficient = 0;
        m_cCoefficient = 0;
        break;
    case LineType::Horizontal:
        m_aCoefficient = 0;
        m_bCoefficient = -deltaX;
        m_cCoefficient = point.getY()*deltaX;
        break;
    case LineType::Vertical:
        m_aCoefficient = deltaY;
        m_bCoefficient = 0;
        m_cCoefficient = -point.getX()*deltaY;
        break;
    default:
        m_aCoefficient = deltaY;
        m_bCoefficient = -deltaX;
        m_cCoefficient = (point.getY()*deltaX)-(point.getX()*deltaY);
        break;
    }

}

void Line::setInterceptsBasedOnSavedCoefficients()
{
    switch(m_type)
    {
    case LineType::Invalid:
        m_yIntercept = 0;
        m_xIntercept = 0;
        break;
    case LineType::Horizontal:
        m_yIntercept = -m_cCoefficient/m_bCoefficient;
        m_xIntercept = 0;
        break;
    case LineType::Vertical:
        m_yIntercept = 0;
        m_xIntercept = -m_cCoefficient/m_aCoefficient;
        break;
    default:
        m_yIntercept = -m_cCoefficient/m_bCoefficient;
        m_xIntercept = -m_cCoefficient/m_aCoefficient;
        break;
    }
}
void Line::getPointsForVerticalLine(Points & points, Point const& first, Point const& second, double const interval) const
{
    AlbaRange<double> range(first.getY(), second.getY(), interval);
    range.traverse([&](double traverseValue)
    {
        points.emplace_back(m_xIntercept, traverseValue);
    });
}

void Line::getPointsForHorizontalLine(Points & points, Point const& first, Point const& second, double const interval) const
{
    AlbaRange<double> range(first.getX(), second.getX(), interval);
    range.traverse([&](double traverseValue)
    {
        points.emplace_back(traverseValue, m_yIntercept);
    });
}

void Line::getPointsForLineWithSlope(Points & points, Point const& first, Point const& second, double const interval) const
{
    Point minimumXAndY;
    Point maximumXAndY;
    Points pointsAtBorder;
    minimumXAndY.saveMinimumXAndY(first);
    minimumXAndY.saveMinimumXAndY(second);
    maximumXAndY.saveMaximumXAndY(first);
    maximumXAndY.saveMaximumXAndY(second);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(first.getX(), calculateYFromX(first.getX())), minimumXAndY, maximumXAndY);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(calculateXFromY(first.getY()), first.getY()), minimumXAndY, maximumXAndY);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(second.getX(), calculateYFromX(second.getX())), minimumXAndY, maximumXAndY);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(calculateXFromY(second.getY()), second.getY()), minimumXAndY, maximumXAndY);
    if(pointsAtBorder.size()>=2)
    {
        Point startingPoint(twoDimensionsHelper::popNearestPoint(pointsAtBorder, first));
        Point endPoint(twoDimensionsHelper::popNearestPoint(pointsAtBorder, second));
        bool isDirectionAscendingForX = startingPoint.getX() <= endPoint.getX();

        Points pointsFromXCoordinate;
        AlbaRange<double> rangeForX(startingPoint.getX(), endPoint.getX(), interval);
        rangeForX.traverse([&](double traverseValueOfX)
        {
            pointsFromXCoordinate.emplace_back(traverseValueOfX, calculateYFromX(traverseValueOfX));
        });

        Points pointsFromYCoordinate;
        AlbaRange<double> rangeForY(startingPoint.getY(), endPoint.getY(), interval);
        rangeForY.traverse([&](double traverseValueOfY)
        {
            pointsFromYCoordinate.emplace_back(calculateXFromY(traverseValueOfY), traverseValueOfY);
        });

        if(isDirectionAscendingForX)
        {
            points = twoDimensionsHelper::getMergedPointsInIncreasingX(pointsFromXCoordinate, pointsFromYCoordinate);
        }
        else
        {
            points = twoDimensionsHelper::getMergedPointsInDecreasingX(pointsFromXCoordinate, pointsFromYCoordinate);
        }
    }
}


void Line::mergePointsFromPointsFromXAndY(Points & points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate, bool const isDirectionAscendingForX) const
{
    Points::const_iterator iteratorForX = pointsFromXCoordinate.cbegin();
    Points::const_iterator iteratorForY = pointsFromYCoordinate.cbegin();
    while(iteratorForX != pointsFromXCoordinate.cend() || iteratorForY != pointsFromYCoordinate.cend())
    {
        if(iteratorForX != pointsFromXCoordinate.cend() && iteratorForY != pointsFromYCoordinate.cend())
        {
            if(isDirectionAscendingForX)
            {
                if(isAlmostEqual(iteratorForX->getX(), iteratorForY->getX()))
                {
                    points.emplace_back(*iteratorForX++);
                    iteratorForY++;
                }
                else if(iteratorForX->getX() < iteratorForY->getX())
                {
                    points.emplace_back(*iteratorForX++);
                }
                else
                {
                    points.emplace_back(*iteratorForY++);
                }
            }
            else
            {
                if(isAlmostEqual(iteratorForX->getX(), iteratorForY->getX()))
                {
                    points.emplace_back(*iteratorForX++);
                    iteratorForY++;
                }
                else if(iteratorForX->getX() > iteratorForY->getX())
                {
                    points.emplace_back(*iteratorForX++);
                }
                else
                {
                    points.emplace_back(*iteratorForY++);
                }
            }
        }
        else if(iteratorForX != pointsFromXCoordinate.cend())
        {
            points.emplace_back(*iteratorForX++);
        }
        else if(iteratorForY != pointsFromYCoordinate.cend())
        {
            points.emplace_back(*iteratorForY++);
        }
    }
}

LineType Line::determineLineTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const
{
    bool isNegativeDeltaY = (deltaY<0);
    bool isNegativeDeltaX = (deltaX<0);
    LineType lineType(LineType::Invalid);
    if(isAlmostEqual(deltaY, 0.0) && isAlmostEqual(deltaX, 0.0))
    {
        lineType = LineType::Invalid;
    }
    else if(isAlmostEqual(deltaY, 0.0))
    {
        lineType = LineType::Horizontal;
    }
    else if(isAlmostEqual(deltaX, 0.0))
    {
        lineType = LineType::Vertical;
    }
    else if(isNegativeDeltaY == isNegativeDeltaX)
    {
        lineType = LineType::WithPositiveSlope;
    }
    else
    {
        lineType = LineType::WithNegativeSlope;
    }
    return lineType;
}

LineType Line::determineLineTypeUsingCoefficients(double const aCoefficient, double const bCoefficient) const
{
    bool isNegativeA = (aCoefficient<0);
    bool isNegativeB = (bCoefficient<0);
    LineType lineType(LineType::Invalid);
    if(isAlmostEqual(aCoefficient, 0.0) && isAlmostEqual(bCoefficient, 0.0))
    {
        lineType = LineType::Invalid;
    }
    else if(isAlmostEqual(aCoefficient, 0.0))
    {
        lineType = LineType::Horizontal;
    }
    else if(isAlmostEqual(bCoefficient, 0.0))
    {
        lineType = LineType::Vertical;
    }
    else if(isNegativeA == isNegativeB)
    {
        lineType = LineType::WithNegativeSlope;
    }
    else
    {
        lineType = LineType::WithPositiveSlope;
    }
    return lineType;
}

}
}
