#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <map>

namespace alba::AprgBitmap {

inline constexpr int INITIAL_LABEL_VALUE = 0;
inline constexpr int INVALID_LABEL_VALUE = 0x1FFFFFFF;

class LabelForPoints {
public:
    using PixelsToLabelsMap = std::map<BitmapXY, int>;
    using PixelAndLabelPair = std::pair<BitmapXY, int>;
    [[nodiscard]] PixelsToLabelsMap const& getPixelsToLabels() const;
    [[nodiscard]] int getLabel(BitmapXY const& point) const;
    void setLabel(BitmapXY const& point, int const label);

private:
    PixelsToLabelsMap m_pixelsTolabelsMap;
};

uint32_t getLabelColor(int const label);
bool isInitialLabel(int const label);
bool isInvalidLabel(int const label);
bool isInitialOrInvalidLabel(int const label);

}  // namespace alba::AprgBitmap
