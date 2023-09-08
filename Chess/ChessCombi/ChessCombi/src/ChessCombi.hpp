#pragma once

namespace alba {

class ChessCombi {
public:
    ChessCombi() = default;
    [[nodiscard]] int getSample() const;

private:
    int m_sample{0};
};

}  // namespace alba
