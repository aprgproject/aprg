#pragma once

namespace alba {

class TemplateForAllCases {
public:
    TemplateForAllCases() = default;

    int getSample() const;

private:
    int m_sample{0};
};

}  // namespace alba
