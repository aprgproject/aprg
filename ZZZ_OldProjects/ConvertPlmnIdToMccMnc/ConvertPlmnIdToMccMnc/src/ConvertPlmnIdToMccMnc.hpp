#pragma once

namespace alba {

using u32 = uint32_t;
using u16 = uint16_t;

struct MccMncPair {
    u16 mcc;
    u16 mnc;
};

MccMncPair convertPlmnIdToMccMnc(u32 const plmnId);

}  // namespace alba
