#include "LabelForPoints.hpp"

#include <BitmapManipulator/ColorUtilities.hpp>
#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>

#include <cmath>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace alba::mathHelper;

namespace alba::AprgBitmap {

LabelForPoints::PixelsToLabelsMap const& LabelForPoints::getPixelsToLabels() const { return m_pixelsTolabelsMap; }

int LabelForPoints::getLabel(BitmapXY const& point) const {
    int label(INITIAL_LABEL_VALUE);
    auto it = m_pixelsTolabelsMap.find(point);
    if (it != m_pixelsTolabelsMap.cend()) {
        label = it->second;
    }
    return label;
}

void LabelForPoints::setLabel(BitmapXY const& point, int const label) { m_pixelsTolabelsMap[point] = label; }

uint32_t getLabelColor(int const label) {
    int const digits = static_cast<int>(getNumberOfBase10Digits(label));
    double const newValue = (static_cast<double>(1) / label) * pow(10, digits + 8);
    return getColorValueOnly(static_cast<uint32_t>(newValue) % 0xFFFFFF);
}

bool isInitialLabel(int const label) { return label == INITIAL_LABEL_VALUE; }
bool isInvalidLabel(int const label) { return label == INVALID_LABEL_VALUE; }
bool isInitialOrInvalidLabel(int const label) { return isInitialLabel(label) || isInvalidLabel(label); }

}  // namespace alba::AprgBitmap
