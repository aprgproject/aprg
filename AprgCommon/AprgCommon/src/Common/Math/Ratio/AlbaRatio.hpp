#pragma once

namespace alba {

class AlbaRatio {
public:
    enum class Type { BothValuesZero, FirstValueIsZero, SecondValueIsZero, WithValidRatio };

    AlbaRatio(double const firstValue, double const secondValue);
    [[nodiscard]] bool isBothZero() const;
    [[nodiscard]] bool isOnlyOneValueZero() const;
    [[nodiscard]] bool hasValidRatio() const;
    [[nodiscard]] double getValidRatioIfPossible() const;
    [[nodiscard]] Type getType() const;

private:
    static double calculateValidRatio(double const firstValue, double const secondValue, Type const type);
    static Type determineTypeFrom2Values(double const firstValue, double const secondValue);
    Type m_type;
    double m_ratio;
};

}  // namespace alba
