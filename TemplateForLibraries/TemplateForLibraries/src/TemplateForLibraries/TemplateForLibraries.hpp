#pragma once

namespace alba {

class TemplateForLibraries {
public:
    TemplateForLibraries() = default;
    [[nodiscard]] int getSample() const;

private:
    int m_sample{0};
};

}  // namespace alba
