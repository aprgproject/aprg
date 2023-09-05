#pragma once

namespace alba {

class TemplateForAllCases {
public:
    TemplateForAllCases() = default;

    [[nodiscard]] int getSample() const;

private:
    int m_sample{0};
};

}  // namespace alba
