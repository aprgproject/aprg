#include "PenCircles.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;

namespace alba::AprgBitmap {

PenCircles::PenCircleDetails::PenCircleDetails() : radius(0), color(0U) {}

PenCircles::PenCircleDetails::PenCircleDetails(double const radiusParameter, uint32_t const colorParameter)
    : radius(radiusParameter), color(colorParameter) {}

PenCircles::CircleCenterConnections const& PenCircles::getCenterConnections() const { return m_centerConnections; }

PenCircles::PenCircleDetails PenCircles::getPenCircleDetails(BitmapXY const& point) const {
    PenCircleDetails penCircleDetails;
    auto it = m_penCircles.find(point);
    if (it != m_penCircles.cend()) {
        penCircleDetails = it->second;
    }
    return penCircleDetails;
}

PenCircles::PointAndPenCircleDetailsPairs PenCircles::getNearestPenCirclesToAPoint(
    BitmapXY const& point, int const distance) const {
    PointAndPenCircleDetailsPairs result;
    int const minX = static_cast<int>(clampLowerBound(convertToSignedThenSubtract<int>(point.getX(), distance), 0));
    int const maxX = point.getX() + distance;
    int const minY = static_cast<int>(clampLowerBound(convertToSignedThenSubtract<int>(point.getY(), distance), 0));
    int const maxY = point.getY() + distance;
    for (auto const& pointAndPenCircleDetailsPair : m_penCircles) {
        BitmapXY const& centerPoint(pointAndPenCircleDetailsPair.first);
        if (minX <= centerPoint.getX() && centerPoint.getX() <= maxX && minY <= centerPoint.getY() &&
            centerPoint.getY() <= maxY) {
            result.emplace_back(pointAndPenCircleDetailsPair);
        }
    }
    return result;
}

PenCircles::PointToPenCircleDetailsMap const& PenCircles::getPenCircles() const { return m_penCircles; }
bool PenCircles::isPenCircle(BitmapXY const& point) const { return m_penCircles.find(point) != m_penCircles.cend(); }

void PenCircles::addAsPenCircle(BitmapXY const& point, double const radius, uint32_t const color) {
    m_penCircles[point] = PenCircleDetails(radius, color);
}

void PenCircles::removePenCircleAt(BitmapXY const& circleCenter) { m_penCircles.erase(circleCenter); }

void PenCircles::connectCircles(BitmapXY const& circle1Center, BitmapXY const& circle2Center) {
    if (circle1Center < circle2Center) {
        m_centerConnections.emplace(circle1Center, circle2Center);
    } else if (circle2Center < circle1Center) {
        m_centerConnections.emplace(circle2Center, circle1Center);
    }
}

void PenCircles::clear() { m_penCircles.clear(); }
PenCircles::PointToPenCircleDetailsMap& PenCircles::getPenCirclesReference() { return m_penCircles; }

}  // namespace alba::AprgBitmap
