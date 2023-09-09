#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <BitmapManipulator/AnimizeColor.hpp>
#include <BitmapManipulator/PenCircles.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

namespace alba::AprgBitmap {
void animeColorsInPenCircles(PenCircles& penCircles, AnimizeColor const& animizeColor);
BitmapXY convertPointToBitmapXY(TwoDimensions::Point const& pointPosition);
TwoDimensions::Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition);
}  // namespace alba::AprgBitmap
