#include "Dsp.hpp"

using namespace std;

namespace alba {

Dsp::Dsp(DspDetails const& dspDetails) : m_dspDetails(dspDetails) {}
DspMode Dsp::getMode() const { return m_dspDetails.mode; }
NyquistType Dsp::getNyquistType() const { return m_dspDetails.nyquistType; }

string Dsp::getModeString() const {
    string result;
    switch (m_dspDetails.mode) {
        case DspMode::NyquistMixedChannelDevice:
            result = "MCD";
            break;
        case DspMode::NyquistCommonChannelDeviceSmall:
            result = "CCDs";
            break;
        case DspMode::NyquistCommonChannelDeviceNormal:
            result = "CCDn";
            break;
        case DspMode::NyquistDedicatedChannelDevice:
            result = "DCD";
            break;
        case DspMode::NyquistPicDevice:
            result = "PIC";
            break;
        default:
            result = "Unknown";
            break;
    }
    return result;
}

string Dsp::getNbicString() const { return isNbicAllocated() ? "NBIC " : ""; }
unsigned int Dsp::getAddress() const { return m_dspDetails.address; }
unsigned int Dsp::getFspAddress() const { return m_dspDetails.address & 0xFF00; }
unsigned int Dsp::getLcgId() const { return m_dspDetails.lcgId; }
unsigned int Dsp::getNumberOfDchUsers() const { return m_dspDetails.numberOfDchUsers; }

unsigned int Dsp::getNumberOfHsupaCfs() const {
    return m_dspDetails.numberOfPreservedHsupaCfs + m_dspDetails.numberOfDynamicallyAllocatedHsupaCfs;
}

unsigned int Dsp::getNumberOfPreservedHsupaCfs() const { return m_dspDetails.numberOfPreservedHsupaCfs; }

unsigned int Dsp::getNumberOfDynamicallyAllocatedHsupaCfs() const {
    return m_dspDetails.numberOfDynamicallyAllocatedHsupaCfs;
}

unsigned int Dsp::getNumberOfHsRachCfs() const { return m_dspDetails.numberOfHsRachCfs; }
unsigned int Dsp::getOrderCountOfCfAllocation() const { return m_dspDetails.orderCountOfCfAllocation; }
unsigned int Dsp::getDliPool() const { return m_dspDetails.dliPool; }

bool Dsp::isEmpty() const {
    // For the allocation of the MCD, Telecom will first try to find a free DCD without any users nor HSPA/HS-RACH
    // resources allocated. If such free DCD is not found, then either a DSP with already allocated users or
    // HSPA/HS-RACH resources or a PIC device is selected. how about other allocations?
    return !hasEmergencyCalls() && getMode() == DspMode::NyquistDedicatedChannelDevice && getNumberOfDchUsers() == 0 &&
           getNumberOfHsupaCfs() == 0 && getNumberOfHsRachCfs() == 0;
}

bool Dsp::hasEmergencyCalls() const { return m_dspDetails.hasEmergencyCalls; }
bool Dsp::hasFreeDli() const { return m_dspDetails.dliPool == 0; }
bool Dsp::isNbicAllocated() const { return m_dspDetails.isNbicAllocated; }
void Dsp::setMode(DspMode const mode) { m_dspDetails.mode = mode; }
void Dsp::setNumberOfUsers(unsigned int const numberOfUsers) { m_dspDetails.numberOfDchUsers = numberOfUsers; }
void Dsp::setLcgId(unsigned int const lcgId) { m_dspDetails.lcgId = lcgId; }
void Dsp::setDliPool(unsigned int const dliPool) { m_dspDetails.dliPool = dliPool; }
void Dsp::setIsNbicAllocated(bool const isNbicAllocated) { m_dspDetails.isNbicAllocated = isNbicAllocated; }
DspDetails& Dsp::getDspDetailsReference() { return m_dspDetails; }

}  // namespace alba
