#include "OutwardCircleTraversal.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba::AprgBitmap {

OutwardCircleTraversal::Coordinate::Coordinate(int const firstValue, int const secondValue)
    : coordinate1(firstValue), coordinate2(secondValue) {}

OutwardCircleTraversal::OutwardCircleTraversal(int const maxRadius) : m_maxRadius(maxRadius) {
    constructRadiusToCoordinates();
}

OutwardCircleTraversal::RadiusToCoordinates const& OutwardCircleTraversal::getRadiusToCoordinates() const {
    return m_radiusToCoordinates;
}

void OutwardCircleTraversal::constructRadiusToCoordinates() {
    for (int i = 0; i <= m_maxRadius; ++i) {
        for (int j = i; j <= m_maxRadius; ++j) {
            double const radius(getSquareRootOfXSquaredPlusYSquared(static_cast<double>(i), static_cast<double>(j)));
            m_radiusToCoordinates.emplace(radius, Coordinate(i, j));
        }
    }
}

}  // namespace alba::AprgBitmap
