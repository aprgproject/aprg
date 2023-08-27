#include "Fsp.hpp"

namespace alba {

FspDetails::FspDetails() = default;

Fsp::Fsp() = default;

Fsp::Fsp(FspDetails const& fspDetails) : m_fspDetails(fspDetails) {}

SmType Fsp::getSmType() const { return m_fspDetails.smType; }

bool Fsp::isMasterTcom() const { return m_fspDetails.isMasterTcom; }

unsigned int Fsp::getAddress() const { return m_fspDetails.address; }

DspAddresses const& Fsp::getDspAddresses() const { return m_fspDetails.dspAddresses; }

}  // namespace alba
