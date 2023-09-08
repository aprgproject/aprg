#pragma once

#include <functional>
#include <map>

namespace alba::AprgBitmap {

class OutwardCircleTraversal {
public:
    struct Coordinate {
        Coordinate(int const firstValue, int const secondValue);
        int coordinate1;
        int coordinate2;
    };

    using RadiusToCoordinates = std::multimap<double, Coordinate>;
    using RadiusAndCoordinatesPair = std::pair<double, Coordinate>;
    explicit OutwardCircleTraversal(int const maxRadius);
    [[nodiscard]] RadiusToCoordinates const& getRadiusToCoordinates() const;

private:
    void constructRadiusToCoordinates();
    int const m_maxRadius;
    RadiusToCoordinates m_radiusToCoordinates;
};

}  // namespace alba::AprgBitmap
