#pragma once

#include <Dsp.hpp>
#include <Fsp.hpp>

#include <map>

namespace alba {

using LcgIds = std::vector<unsigned int>;
using AddressToDspPair = std::pair<unsigned int, Dsp>;
using AddressToFspPair = std::pair<unsigned int, Fsp>;
using AddressToDspMap = std::map<unsigned int, Dsp>;
using AddressToFspMap = std::map<unsigned int, Fsp>;

class HardwareConfiguration {
public:
    HardwareConfiguration();
    AddressToDspMap& getAddressToDspMapReference();
    AddressToFspMap& getAddressToFspMapReference();
    void clear();
    void changeConfigurationToOneFspOneLcgEvenDistribution();
    void changeConfigurationToOneFspTwoLcgEvenDistribution();
    void changeConfigurationToTwoFspOneLcgEvenDistribution();
    void changeConfigurationToTwoFspTwoLcgEvenDistribution();
    void changeConfigurationToTwoFspThreeLcgEvenDistribution();
    void changeConfigurationToTwoFspFourLcgEvenDistribution();
    void changeConfigurationToThreeFspOneLcgEvenDistribution();
    void changeConfigurationToThreeFspTwoLcgEvenDistribution();
    void changeConfigurationToThreeFspThreeLcgEvenDistribution();
    void changeConfigurationToThreeFspFourLcgEvenDistribution();
    void changeConfigurationToFourFspTwoLcgEvenDistribution();
    void changeConfigurationToFourFspThreeLcgEvenDistribution();
    void changeConfigurationToFourFspFourLcgEvenDistribution();
    void changeConfigurationToFiveFspTwoLcgEvenDistribution();
    void changeConfigurationToFiveFspThreeLcgEvenDistribution();
    void changeConfigurationToFiveFspFourLcgEvenDistribution();
    void changeConfigurationToSixFspTwoLcgEvenDistribution();
    void changeConfigurationToSixFspThreeLcgEvenDistribution();
    void changeConfigurationToSixFspFourLcgEvenDistribution();
    void changeConfigurationToSharedLcgWithOneDspInMsm();
    [[nodiscard]] unsigned int getTcomFspAddress() const;
    [[nodiscard]] unsigned int getSharedLcgId() const;
    void printDspAllocations(unsigned int const printFlags = 0);

private:
    void addFsp(unsigned int const fspAddress);
    void addDsp(unsigned int const dspAddress);
    void setLcgIdOfDsps(LcgIds const& lcgIds);
    static NyquistType computeNyquistTypeBasedOnDspAddress(unsigned int const dspAddress);
    static SmType getSmTypeBasedOnAddress(unsigned int const fspAddress);
    unsigned int m_sharedLcgId{0};
    unsigned int m_tcomFspAddress{0};
    AddressToDspMap m_dspAddressToDspMap;
    AddressToFspMap m_fspAddressToFspMap;
};

}  // namespace alba
