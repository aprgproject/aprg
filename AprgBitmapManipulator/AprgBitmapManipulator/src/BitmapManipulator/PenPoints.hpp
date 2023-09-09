#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <set>

namespace alba::AprgBitmap {

class PenPoints {
public:
    using PenPointsSet = std::set<BitmapXY>;
    [[nodiscard]] PenPointsSet const& getPenPoints() const;
    [[nodiscard]] bool isPenPoint(BitmapXY const& penPoint) const;
    void addAsPenPoint(BitmapXY const& penPoint);
    void addAsPenPoints(BitmapXYs const& bitmapPoints);
    void removePenPoint(BitmapXY const& penPoint);
    void clear();

private:
    PenPointsSet m_penPoints;
};

}  // namespace alba::AprgBitmap
