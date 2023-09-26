#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SetAndSymbolTable/Set/Array/OrderedArraySet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/Common/BaseSetWithBaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Set/LinkedList/UnorderedLinkedListSet.hpp>

namespace alba::algorithm {

template <typename Key, typename HashFunction, int HASH_TABLE_SIZE>
class BaseSeparateChainingHashSet : public BaseSetWithBaseSeparateChainingHash<BaseSeparateChainingHash<
                                        Key, HashTableEntry<Key>, HashFunction, HASH_TABLE_SIZE, OrderedArraySet<Key>,
                                        UnorderedLinkedListSet<Key>, BaseSet<Key>>> {
public:
    BaseSeparateChainingHashSet() = default;
    // no need for virtual destructor because base destructor is
    // virtual (similar to other virtual functions)
    ~BaseSeparateChainingHashSet() override = default;
    BaseSeparateChainingHashSet(BaseSeparateChainingHashSet const &) = default;
    BaseSeparateChainingHashSet(BaseSeparateChainingHashSet &&) noexcept = default;
    BaseSeparateChainingHashSet &operator=(BaseSeparateChainingHashSet const &) = default;
    BaseSeparateChainingHashSet &operator=(BaseSeparateChainingHashSet &&) noexcept = default;
};

}  // namespace alba::algorithm
