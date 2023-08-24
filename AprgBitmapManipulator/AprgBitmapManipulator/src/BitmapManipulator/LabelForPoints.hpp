#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <map>

namespace alba::AprgBitmap {

constexpr int INITIAL_LABEL_VALUE = 0;
constexpr int INVALID_LABEL_VALUE = 0x1FFFFFFF;

bool isInitialLabel(int const label);
bool isInvalidLabel(int const label);
bool isInitialOrInvalidLabel(int const label);
uint32_t getLabelColor(int const label);

class LabelForPoints {
public:
    using PixelsToLabelsMap = std::map<BitmapXY, int>;
    using PixelAndLabelPair = std::pair<BitmapXY, int>;
    [[nodiscard]] int getLabel(BitmapXY const& point) const;
    [[nodiscard]] PixelsToLabelsMap const& getPixelsToLabels() const;

    void setLabel(BitmapXY const& point, int const label);

private:
    PixelsToLabelsMap m_pixelsTolabelsMap;
};

}  // namespace alba::AprgBitmap
