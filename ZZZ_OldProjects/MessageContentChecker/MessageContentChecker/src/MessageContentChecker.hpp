#pragma once

namespace alba {

class MessageContentChecker {
public:
    MessageContentChecker() = default;
    [[nodiscard]] int getSample() const;

private:
    int m_sample{0};
};

}  // namespace alba
