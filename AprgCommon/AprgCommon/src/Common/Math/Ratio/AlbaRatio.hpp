#pragma once

namespace alba {

class AlbaRatio {
public:
    enum class Type { BothValuesZero, FirstValueIsZero, SecondValueIsZero, WithValidRatio };
    AlbaRatio(double const firstValue, double const secondValue);
    [[nodiscard]] Type getType() const;
    [[nodiscard]] double getValidRatioIfPossible() const;
    [[nodiscard]] bool isBothZero() const;
    [[nodiscard]] bool isOnlyOneValueZero() const;
    [[nodiscard]] bool hasValidRatio() const;

private:
    static Type determineTypeFrom2Values(double const firstValue, double const secondValue);
    static double calculateValidRatio(double const firstValue, double const secondValue, Type const type);
    Type m_type;
    double m_ratio;
};

}  // namespace alba
