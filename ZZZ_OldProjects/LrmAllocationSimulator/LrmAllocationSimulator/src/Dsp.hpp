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
    DspDetails() = default;
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
    DspMode mode{DspMode::NyquistDedicatedChannelDevice};
    NyquistType nyquistType{NyquistType::Nyquist};
};

class Dsp {
public:
    Dsp() = default;
    explicit Dsp(DspDetails const& dspDetails);
    [[nodiscard]] DspMode getMode() const;
    [[nodiscard]] NyquistType getNyquistType() const;
    [[nodiscard]] std::string getModeString() const;
    [[nodiscard]] std::string getNbicString() const;
    [[nodiscard]] unsigned int getAddress() const;
    [[nodiscard]] unsigned int getFspAddress() const;
    [[nodiscard]] unsigned int getLcgId() const;
    [[nodiscard]] unsigned int getNumberOfDchUsers() const;
    [[nodiscard]] unsigned int getNumberOfHsupaCfs() const;
    [[nodiscard]] unsigned int getNumberOfPreservedHsupaCfs() const;
    [[nodiscard]] unsigned int getNumberOfDynamicallyAllocatedHsupaCfs() const;
    [[nodiscard]] unsigned int getNumberOfHsRachCfs() const;
    [[nodiscard]] unsigned int getOrderCountOfCfAllocation() const;
    [[nodiscard]] unsigned int getDliPool() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool hasEmergencyCalls() const;
    [[nodiscard]] bool hasFreeDli() const;
    [[nodiscard]] bool isNbicAllocated() const;
    void setMode(DspMode const mode);
    void setNumberOfUsers(unsigned int const numberOfUsers);
    void setLcgId(unsigned int const lcgId);
    void setDliPool(unsigned int const dliPool);
    void setIsNbicAllocated(bool const isNbicAllocated);
    DspDetails& getDspDetailsReference();

private:
    DspDetails m_dspDetails;
};

using DspAddresses = std::vector<unsigned int>;

}  // namespace alba
