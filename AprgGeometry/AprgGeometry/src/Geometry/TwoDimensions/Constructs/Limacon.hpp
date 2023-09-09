#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <functional>

namespace alba::TwoDimensions {

enum class LimaconType { Unknown, WithALoop, Cardioid, WithADent, Convex };

enum class LimaconTrigonometricFunctionType { Cosine, Sine };

class Limacon {
public:
    Limacon() = default;

    Limacon(
        double const aCoefficient, double const bCoefficient,
        LimaconTrigonometricFunctionType const trigonometricFunction);  // a + b*(cos or sin)(theta) = r
    bool operator==(Limacon const& limacon) const;
    bool operator!=(Limacon const& limacon) const;
    [[nodiscard]] AlbaAngle calculateThetaFromRadius(double const radius) const;
    [[nodiscard]] LimaconTrigonometricFunctionType getTrigonometricFunctionType() const;
    [[nodiscard]] LimaconType getLimaconType() const;
    [[nodiscard]] Points getPointsForShape(AlbaAngle const& angleInterval) const;
    [[nodiscard]] double getAValue() const;
    [[nodiscard]] double getBValue() const;
    [[nodiscard]] double calculateRadiusFromTheta(AlbaAngle const& theta) const;

private:
    [[nodiscard]] AlbaAngle performInverseTrigonometricFunction(double const ratio) const;
    [[nodiscard]] double performTrigonometricFunction(AlbaAngle const& theta) const;
    friend std::ostream& operator<<(std::ostream& out, Limacon const& limacon);
    double m_aValue{0};
    double m_bValue{0};
    LimaconTrigonometricFunctionType m_trigonometricFunctionType{LimaconTrigonometricFunctionType::Sine};
};

using Limacons = std::vector<Limacon>;

}  // namespace alba::TwoDimensions
