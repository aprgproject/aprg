#pragma once

#include <ostream>

namespace alba::algorithm {

class StabilityCheckObject {
public:
    explicit StabilityCheckObject(int const value);
    StabilityCheckObject();
    StabilityCheckObject(char const visiblePart, int const notVisiblePart);

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
    double operator*(double const multiplier) const;
    StabilityCheckObject operator+(StabilityCheckObject const& second) const;
    StabilityCheckObject operator-(StabilityCheckObject const& second) const;
    StabilityCheckObject operator*(StabilityCheckObject const& second) const;
    StabilityCheckObject operator/(StabilityCheckObject const& second) const;
    StabilityCheckObject operator+(int const second) const;
    StabilityCheckObject operator-(int const second) const;
    StabilityCheckObject operator*(int const second) const;
    StabilityCheckObject operator/(int const second) const;
    [[nodiscard]] char getVisiblePart() const;
    [[nodiscard]] int getNotVisiblePart() const;
    friend double operator/(double const dividend, StabilityCheckObject const& divisor);
    friend std::ostream& operator<<(std::ostream& out, StabilityCheckObject const& object);
    friend bool areObjectsEqualOnVisibleAndNotVisiblePart(
        StabilityCheckObject const& object1, StabilityCheckObject const& object2);
    friend bool areObjectsEqualOnVisibleOnly(StabilityCheckObject const& object1, StabilityCheckObject const& object2);

private:
    char m_visiblePart;
    int m_notVisiblePart;
};

bool areObjectsEqualOnVisibleAndNotVisiblePart(
    StabilityCheckObject const& object1, StabilityCheckObject const& object2);
bool areObjectsEqualOnVisibleOnly(StabilityCheckObject const& object1, StabilityCheckObject const& object2);

}  // namespace alba::algorithm
