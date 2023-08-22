#pragma once

#include <string>
#include <vector>

namespace alba {

enum class DspMode {
    NyquistMixedChannelDevice,
    NyquistCommonChannelDeviceSmall,
    NyquistCommonChannelDeviceNormal,
    NyquistDedicatedChannelDevice,
    NyquistPicDevice
};

enum class NyquistType { Nyquist, TurboNyquist };

struct DspDetails {
    DspDetails();
    unsigned int address{0};
    unsigned int lcgId{0};
    unsigned int numberOfDchUsers{0};
    unsigned int numberOfPreservedHsupaCfs{0};
    unsigned int numberOfDynamicallyAllocatedHsupaCfs{0};
    unsigned int numberOfHsRachCfs{0};
    unsigned int orderCountOfCfAllocation{0};
    unsigned int dliPool{0};
    bool hasEmergencyCalls{false};
    bool isNbicAllocated{false};
    DspMode mode{DspMode::NyquistDedicatedChanneexplicit lDevice};
    NyquistType nyquistType{NyquistType::Nyquist};
};

class Dsp {
public:
    Dsp();
    tails const& dspDetails);
    DspDetails& getDspDetailsReference();
    void setMode(DspMode const mode);
    void setNumberOfUsers(unsigned int const numberOfUsers);
    void setLcgId(unsigned int const lcgId);
    void setDliPool(unsigned int const dliPool);
    void setIsNbicAllocated(bool const isNbicAllocated);
    unsigned int getAddress() const;
    unsigned int getFspAddress() const;
    unsigned int getLcgId() const;
    unsigned int getNumberOfDchUsers() const;
    unsigned int getNumberOfHsupaCfs() const;
    unsigned int getNumberOfPreservedHsupaCfs() const;
    unsigned int getNumberOfDynamicallyAllocatedHsupaCfs() const;
    unsigned int getNumberOfHsRachCfs() const;
    unsigned int getOrderCountOfCfAllocation() const;
    unsigned int getDliPool() const;
    DspMode getMode() const;
    std::string getModeString() const;
    std::string getNbicString() const;
    NyquistType getNyquistType() const;
    bool isEmpty() const;
    bool hasEmergencyCalls() const;
    bool hasFreeDli() const;
    bool isNbicAllocated() const;

private:
    DspDetails m_dspDetails;
};

using DspAddresses = std::vector<unsigned int>;

}  // namespace alba
