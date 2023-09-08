#pragma once

namespace alba {

class TemplateForPrograms {
public:
    TemplateForPrograms() = default;
    [[nodiscard]] int getSample() const;

private:
    int m_sample{0};
};

}  // namespace alba
