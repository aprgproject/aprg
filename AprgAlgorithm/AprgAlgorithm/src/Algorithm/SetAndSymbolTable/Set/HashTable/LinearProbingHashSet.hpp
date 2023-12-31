#pragma once

#include <Algorithm/SetAndSymbolTable/Set/HashTable/Common/BaseLinearProbingHashSet.hpp>

namespace alba::algorithm {

template <typename Key, typename HashFunction>
class LinearProbingHashSet : public BaseLinearProbingHashSet<Key, HashFunction> {};

}  // namespace alba::algorithm
