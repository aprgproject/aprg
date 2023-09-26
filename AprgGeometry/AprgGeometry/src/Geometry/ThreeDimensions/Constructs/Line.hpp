#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

#include <optional>
#include <vector>

namespace alba::ThreeDimensions {

class Line {
public:
    Line() = default;
    Line(Point const& first, Point const& second);

    Line(
        double const aCoefficient, double const bCoefficient, double const cCoefficient, double const xInitialValue,
        double const yInitialValue, double const zInitialValue);

    Line(double const aCoefficient, double const bCoefficient, double const cCoefficient, Point const& point);
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
    [[nodiscard]] std::optional<double> calculateXFromY(double const y) const;
    [[nodiscard]] std::optional<double> calculateXFromZ(double const z) const;
    [[nodiscard]] std::optional<double> calculateYFromX(double const x) const;
    [[nodiscard]] std::optional<double> calculateYFromZ(double const z) const;
    [[nodiscard]] std::optional<double> calculateZFromX(double const x) const;
    [[nodiscard]] std::optional<double> calculateZFromY(double const y) const;
    [[nodiscard]] double getXInitialValue() const;
    [[nodiscard]] double getYInitialValue() const;
    [[nodiscard]] double getZInitialValue() const;
    [[nodiscard]] double getACoefficient() const;
    [[nodiscard]] double getBCoefficient() const;
    [[nodiscard]] double getCCoefficient() const;
    [[nodiscard]] bool isInvalid() const;

private:
    [[nodiscard]] bool areAllCoefficientsZero() const;
    void calculateAndSaveInitialValuesIfPossible(Point const& first);

    static std::optional<double> calculateOtherCoordinate(
        double const& initialValue1, double const coefficient1, double const& initialValue2, double const coefficient2,
        double const coordinate2);

    friend std::ostream& operator<<(std::ostream& out, Line const& line);
    double m_aCoefficient{0};   // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_bCoefficient{0};   // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_cCoefficient{0};   // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_xInitialValue{0};  // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_yInitialValue{0};  // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_zInitialValue{0};  // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
};

using Lines = std::vector<Line>;

}  // namespace alba::ThreeDimensions
