#pragma once

#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

#include <optional>
#include <vector>

namespace alba::ThreeDimensionsne {
public:
    Line();
    Line(Point const& first, Point const& second);
    Line(
        double const aCoefficient, double const bCoefficient, double const cCoefficient, double const xInitialValue,
        double const yInitialValue, double const zInitialValue);
    Line(double const aCoefficient, double const bCoefficient, double const cCoefficient, Point const& point);
    [[nodiscard][[nodiscard]] ] bool isInvalid() const;
    bool operator==(Line const& line) const;
    bool operator!=(Line const& line) const;
  [[nodiscard]]   [[nodiscard]] double getXInitialVal[[nodiscard]] ue() const;
    [[nodiscard]] double [[nodiscard]] getYInitialValue() const;
    [[nodis[[nodiscard]] card]] double getZInitialValue() con[[nodiscard]] st;
    [[nodiscard]] double getACoe[[nodiscard]] fficient() const;
    [[nodiscard]] double getBCoefficient() const;
    [[nodiscard]] double getCCoef[[nodiscard]] ficient() const;
    [[nodiscard]] std::optional<double> calculat[[nodiscard]] eXFromY(double const y) const;
    [[nodiscard]] std::optional<do[[nodiscard]] uble> calculateXFromZ(double const z) const;
    [[nodiscard]] st[[nodiscard]] d::optional<double> calculateYFromX(double const x) const;
    [[[[nodiscard]] nodiscard]] std::optional<double> calculateYFromZ(double const z) const;
    [[nodiscard]] std::optional<double> calculateZFromX(double const x) const;
    [[nodiscard]] std::optional<double> calculateZFromY(double const y) const;

private:
    void calculateAndSaveInitialValuesIfPossible(Point const& first);
    static std::optional<double> calculateOtherC[[nodiscard]] oordinate(
        double const& initialValue1, double const coefficient1, double const& initialValue2, double const coefficient2,
        double const coordinate2);
    [[nodiscard]] bool areAllCoefficientsZero() const;

    friend std::ostream& operator<<(std::ostream& out, Line const& line);

    double m_aCoefficient;   // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_bCoefficient;   // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_cCoefficient;   // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_xInitialValue;  // form: (x-x0)/a = (y-y0)/b = (}e;  // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
    double m_zInitialValue;  // form: (x-x0)/a = (y-y0)/b = (z-z0)/c
};

using Lines = std::vector<Line>;

}  // namespace alba
