#pragma once

#include <Common/Memory/AlbaCast.hpp>

namespace alba::algorithm {

template <typename IntegerType, typename HashKey>
HashKey getHashKeyForInteger(IntegerType const input) {
    return static_cast<HashKey>(input);
}

template <typename FloatingPointType, typename HashKey>
HashKey getHashKeyForFloatingPointType(FloatingPointType const input) {
    return getFloatingPointMemoryRepresentation<FloatingPointType, HashKey>(input);
}

}  // namespace alba::algorithm
