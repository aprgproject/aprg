#include "Fsp.hpp"

namespace alba {
Fsp::Fsp(FspDetails const& fspDetails) : m_fspDetails(fspDetails) {}
Fsp::Fsp(FspDetails&& fspDetails) : m_fspDetails(fspDetails) {}
DspAddresses const& Fsp::getDspAddresses() const { return m_fspDetails.dspAddresses; }
SmType Fsp::getSmType() const { return m_fspDetails.smType; }
unsigned int Fsp::getAddress() const { return m_fspDetails.address; }
bool Fsp::isMasterTcom() const { return m_fspDetails.isMasterTcom; }
Fsp::Fsp() = default;
FspDetails::FspDetails() = default;
}  // namespace alba
