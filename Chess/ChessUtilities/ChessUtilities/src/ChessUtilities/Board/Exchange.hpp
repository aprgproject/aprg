#pragma once

namespace alba::chess {

class Exchange {
public:
    Exchange(int const value, int const count);

    bool operator==(Exchange const& exchange) const;
    bool operator!=(Exchange const& exchange) const;

    [[nodiscard]] int getValue() const;
    [[nodiscard]] int getCount() const;

private:
    int m_value;
    int m_count;
};

}  // namespace alba::chess
