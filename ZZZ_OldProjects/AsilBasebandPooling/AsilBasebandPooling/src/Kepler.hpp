#pragma once

#include <set>

namespace alba {

class Kepler {
public:
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    Kepler(unsigned short int const nid);
    bool operator<(Kepler const& kepler) const;
    [[nodiscard]] unsigned int getNid() const;

private:
    unsigned short int m_nid;
};
using KeplerInitializerList = std::initializer_list<Kepler>;
using SetOfKeplers = std::set<Kepler>;

}  // namespace alba
