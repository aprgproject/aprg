#pragma once

#include <ostream>

namespace alba::algorithm {

class StabilityCheckObject {
public:
    StabilityCheckObject();
    StabilityCheckObject(char const visiblePart, int const notVisiblePart);
    explicit StabilityCheckObject(int const value);

    template <typename ValueType>
    explicit operator ValueType() const {
        return static_cast<ValueType>(m_visiblePart);
    }

    bool operator==(StabilityCheckObject const& object) const;
    bool operator!=(StabilityCheckObject const& object) const;
    bool operator<(StabilityCheckObject const& object) const;
    bool operator>(StabilityCheckObject const& object) const;
    bool operator<=(StabilityCheckObject const& object) const;
    bool operator>=(StabilityCheckObject const& object) const;
    StabilityCheckObject operator+(StabilityCheckObject const& second) const;
    StabilityCheckObject operator-(StabilityCheckObject const& second) const;
    StabilityCheckObject operator*(StabilityCheckObject const& second) const;
    StabilityCheckObject operator/(StabilityCheckObject const& second) const;
    StabilityCheckObject operator+(int const second) const;
    StabilityCheckObject operator-(int const second) const;
    StabilityCheckObject operator*(int const second) const;
    StabilityCheckObject operator/(int const second) const;

    double operator*(double const multiplier) const;

    [[nodiscard]] char getVisiblePart() const;
    [[nodiscard]] int getNotVisiblePart() const;

    friend double operator/(double const dividend, StabilityCheckObject const& divisor);
    friend bool areObjectsEqualOnVisibleAndNotVisiblePart(
        StabilityCheckObject const& object1, StabilityCheckObject const& object2);
    friend bool areObjectsEqualOnVisibleOnly(StabilityCheckObject const& object1, StabilityCheckObject const& object2);
    friend std::ostream& operator<<(std::ostream& out, StabilityCheckObject const& object);

private:
    char m_visiblePart;
    int m_notVisiblePart;
};

bool areObjectsEqualOnVisibleAndNotVisiblePart(
    StabilityCheckObject const& object1, StabilityCheckObject const& object2);
bool areObjectsEqualOnVisibleOnly(StabilityCheckObject const& object1, StabilityCheckObject const& object2);

}  // namespace alba::algorithm
