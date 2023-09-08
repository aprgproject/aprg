#include "Fsp.hpp"

namespace alba {
Fsp::Fsp(FspDetails const& fspDetails) : m_fspDetails(fspDetails) {}
bool Fsp::isMasterTcom() const { return m_fspDetails.isMasterTcom; }
unsigned int Fsp::getAddress() const { return m_fspDetails.address; }
SmType Fsp::getSmType() const { return m_fspDetails.smType; }
DspAddresses const& Fsp::getDspAddresses() const { return m_fspDetails.dspAddresses; }
FspDetails::FspDetails() = default;
Fsp::Fsp() = default;
}  // namespace alba
