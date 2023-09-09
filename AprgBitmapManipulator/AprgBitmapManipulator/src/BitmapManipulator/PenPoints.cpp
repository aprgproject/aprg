#include "PenPoints.hpp"

namespace alba::AprgBitmap {

PenPoints::PenPointsSet const& PenPoints::getPenPoints() const { return m_penPoints; }
bool PenPoints::isPenPoint(BitmapXY const& penPoint) const { return m_penPoints.find(penPoint) != m_penPoints.cend(); }
void PenPoints::addAsPenPoint(BitmapXY const& penPoint) { m_penPoints.emplace(penPoint); }

void PenPoints::addAsPenPoints(BitmapXYs const& bitmapPoints) {
    for (BitmapXY const& bitmapPoint : bitmapPoints) {
        addAsPenPoint(bitmapPoint);
    }
}

void PenPoints::removePenPoint(BitmapXY const& penPoint) { m_penPoints.erase(penPoint); }
void PenPoints::clear() { m_penPoints.clear(); }

}  // namespace alba::AprgBitmap
