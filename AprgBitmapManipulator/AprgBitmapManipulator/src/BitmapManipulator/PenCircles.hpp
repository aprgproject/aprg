#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <map>
#include <set>

namespace alba::AprgBitmap {

class PenCircles {
public:
    struct PenCircleDetails {
        PenCircleDetails();
        PenCircleDetails(double const radiusParameter, uint32_t const colorParameter);
        double radius;
        uint32_t color;
    };

    using PointToPenCircleDetailsMap = std::map<BitmapXY, PenCircleDetails>;
    using PointAndPenCircleDetailsPair = std::pair<BitmapXY, PenCircleDetails>;
    using PointAndPenCircleDetailsPairs = std::vector<PointAndPenCircleDetailsPair>;
    using CircleCenterConnection = std::pair<BitmapXY, BitmapXY>;
    using CircleCenterConnections = std::set<CircleCenterConnection>;
    [[nodiscard]] CircleCenterConnections const& getCenterConnections() const;
    [[nodiscard]] PenCircleDetails getPenCircleDetails(BitmapXY const& point) const;

    [[nodiscard]] PointAndPenCircleDetailsPairs getNearestPenCirclesToAPoint(
        BitmapXY const& point, int const distance) const;

    [[nodiscard]] PointToPenCircleDetailsMap const& getPenCircles() const;
    [[nodiscard]] bool isPenCircle(BitmapXY const& point) const;
    void addAsPenCircle(BitmapXY const& point, double const radius, uint32_t const color);
    void removePenCircleAt(BitmapXY const& circleCenter);
    void connectCircles(BitmapXY const& circle1Center, BitmapXY const& circle2Center);
    void clear();
    PointToPenCircleDetailsMap& getPenCirclesReference();

private:
    PointToPenCircleDetailsMap m_penCircles;
    CircleCenterConnections m_centerConnections;
};

}  // namespace alba::AprgBitmap
