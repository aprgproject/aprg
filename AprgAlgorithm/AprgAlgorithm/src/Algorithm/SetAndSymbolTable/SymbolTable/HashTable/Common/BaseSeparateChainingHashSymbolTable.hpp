#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/Array/OrderedArraySymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/Common/BaseSymbolTableWithBaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/LinkedList/UnorderedLinkedListSymbolTable.hpp>

namespace alba::algorithm {

template <typename Key, typename Value, typename HashFunction, int HASH_TABLE_SIZE>
class BaseSeparateChainingHashSymbolTable
    : public BaseSymbolTableWithBaseSeparateChainingHash<
          Value, BaseSeparateChainingHash<
                     Key, HashTableEntryWithValue<Key, Value>, HashFunction, HASH_TABLE_SIZE,
                     OrderedArraySymbolTable<Key, Value>, UnorderedLinkedListSymbolTable<Key, Value>,
                     BaseSymbolTable<Key, Value>>> {
public:
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    ~BaseSeparateChainingHashSymbolTable() override = default;
    BaseSeparateChainingHashSymbolTable() = default;
    BaseSeparateChainingHashSymbolTable(BaseSeparateChainingHashSymbolTable const &) = default;
    BaseSeparateChainingHashSymbolTable(BaseSeparateChainingHashSymbolTable &&) = default;
    BaseSeparateChainingHashSymbolTable &operator=(BaseSeparateChainingHashSymbolTable const &) = default;
    BaseSeparateChainingHashSymbolTable &operator=(BaseSeparateChainingHashSymbolTable &&) = default;
};

}  // namespace alba::algorithm
