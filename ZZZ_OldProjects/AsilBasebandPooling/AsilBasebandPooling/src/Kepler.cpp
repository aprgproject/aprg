#include "Kepler.hpp"

#include <iterator>

using namespace std;

namespace alba {
Kepler::Kepler(uint16_t const nid) : m_nid(nid) {}
bool Kepler::operator<(Kepler const& kepler) const { return m_nid < kepler.m_nid; }
unsigned int Kepler::getNid() const { return m_nid; }
}  // namespace alba
