#include "Utilities.hpp"

#include <cmath>

using namespace alba::TwoDimensions;

namespace alba::AprgBitmap {

Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition) {
    return {static_cast<double>(bitmapPosition.getX()), static_cast<double>(bitmapPosition.getY())};
}

BitmapXY convertPointToBitmapXY(Point const& pointPosition) {
    return {static_cast<int>(round(pointPosition.getX())), static_cast<int>(round(pointPosition.getY()))};
}

void animeColorsInPenCircles(PenCircles& penCircles, AnimizeColor const& animizeColor) {
    PenCircles::PointToPenCircleDetailsMap& map(penCircles.getPenCirclesReference());
    for (auto& pointAndPenCircleDetails : map) {
        pointAndPenCircleDetails.second.color = animizeColor.getNewColor(pointAndPenCircleDetails.second.color);
    }
}

}  // namespace alba::AprgBitmap
