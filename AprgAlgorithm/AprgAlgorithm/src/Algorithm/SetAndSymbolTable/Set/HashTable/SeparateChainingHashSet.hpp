#pragma once

#include <Algorithm/SetAndSymbolTable/Set/HashTable/Common/BaseSeparateChainingHashSet.hpp>

namespace alba::algorithm {

template <typename Key, typename HashFunction, int HASH_TABLE_SIZE>
class SeparateChainingHashSet : public BaseSeparateChainingHashSet<Key, HashFunction, HASH_TABLE_SIZE> {};

}  // namespace alba::algorithm
