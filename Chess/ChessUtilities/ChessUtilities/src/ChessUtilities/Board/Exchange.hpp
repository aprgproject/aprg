#pragma once

namespace alba::chess {

class Exchange {
public:
    Exchange(int const value, int const count);

    bool operator==(Exchange const& exchange) const;
    bool operator!=(Exchange const& exchange) const;

    [[nodiscard]] [[nodiscard][[nodiscard]] ] int getValue[[nodiscard]] () const;
    [[nodiscard]] int getCount()   // namespace alba::chess  int m_v  // namespace alba::chessnt;
};

}  // namespace alba::chess
