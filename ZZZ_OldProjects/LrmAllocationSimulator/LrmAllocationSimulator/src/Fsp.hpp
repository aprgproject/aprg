#pragma once

#include <Dsp.hpp>

#include <set>
#include <vector>

namespace alba {

enum class SmType { MSM, ESM, BOTH_SM };

struct FspDetails {
    FspDetails();
    SmType smType{SmType::MSM};
    bool isMasterTcom{false};
    unsigned int address{0};
    DspAddresses dspAddresses;
};

class Fsp {
public:
    Fsp();
    explicit Fsp(FspDetails const& fspDetails);
    SmType getSmType() const;
    bool isMasterTcom() const;
    unsigned int getAddress() const;
    DspAddresses const& getDspAddresses() const;

private:
    FspDetails m_fspDetails;
};

using FspAddresses = std::vector<unsigned int>;
using UniqueFspAddresses = std::set<unsigned int>;

}  // namespace alba
