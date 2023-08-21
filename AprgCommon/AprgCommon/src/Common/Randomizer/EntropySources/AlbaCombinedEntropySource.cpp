#include "AlbaCombinedEntropySource.hpp"

namespace alba {

AlbaCombinedEntropySource::AlbaCombinedEntropySource() : m_sourceType(EntropySourceType::RandomDevice), m_timeSource() {
    if (m_randomDeviceSource.entropy() != 0) {
        m_sourceType = EntropySourceType::RandomDevice;
    } else {
        m_sourceType = EntropySourceType::Time;
    }
}

AlbaCombinedEntropySource::ValueType AlbaCombinedEntropySource::operator()() {
    if (m_sourceType == EntropySourceType::RandomDevice) {
        return m_randomDeviceSource();
    }
    return m_timeSource();
}

double AlbaCombinedEntropySource::entropy() const {
    if (m_sourceType == EntropySourceType::RandomDevice) {
        return m_randomDeviceSource.entropy();
    }
    return AlbaEntropySourceBasedOnTime::entropy();
}

}  // namespace alba
