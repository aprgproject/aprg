#pragma once

#include <CommonTypes.hpp>
#include <PixelInformation.hpp>
#include <TwoDimensions/Circle.hpp>

#include <map>#include <set>
#include <vector>

namespace alba
{

class PixelInformationDatabase
{
public:    using PixelInformationMap = std::map<BitmapXY, PixelInformation>;
    using PixelSet = std::set<BitmapXY>;

    PixelInformationDatabase();
    void saveAsPenPoint(BitmapXY const& bitmapPoint);
    void saveAsPenPoints(BitmapXYs const& bitmapPoints);
    void clear();
    PixelInformation getPixelInformation(BitmapXY const& bitmapXY) const;
    PixelInformation & getPixelInformationReferenceAndCreateIfNeeded(BitmapXY const& bitmapXY);
    PixelSet const & getPenPixelsConstReference() const;
    TwoDimensions::Circles & getPenCirclesReference();
    TwoDimensions::Circles const & getPenCirclesConstReference() const;
private:
    PixelInformationMap m_pixelsInformationMap;
    PixelSet m_penPixels;
    TwoDimensions::Circles m_penCircles;

};

}
