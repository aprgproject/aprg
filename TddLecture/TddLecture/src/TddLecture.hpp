#pragma once

#include <vector>

namespace alba {

class TddLecture {
public:
    using UnsignedInts = std::vector<unsigned int>;
    TddLecture() = default;
    void functionality1() const {}
    void functionality2() const {}
    void functionality3() const {}

    static UnsignedInts getUnsignedIntsOneToTen();

    void functionality10() const {}
    void functionality11() const {}
    void functionality12() const {}

private:
    int m_sample{0};
};

}  // namespace alba
