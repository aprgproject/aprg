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
    explicit Fsp(FspDetails const& fspDetails);
    Fsp();
    [[nodiscard]] bool isMasterTcom() const;
    [[nodiscard]] unsigned int getAddress() const;
    [[nodiscard]] SmType getSmType() const;
    [[nodiscard]] DspAddresses const& getDspAddresses() const;

private:
    FspDetails m_fspDetails;
};

using FspAddresses = std::vector<unsigned int>;
using UniqueFspAddresses = std::set<unsigned int>;

}  // namespace alba
