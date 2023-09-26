#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseLinearProbingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/Array/OrderedArraySymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/Common/BaseSymbolTableWithBaseLinearProbingHash.hpp>

namespace alba::algorithm {

template <typename Key, typename Value, typename HashFunction>
class BaseLinearProbingHashSymbolTable
    : public BaseSymbolTableWithBaseLinearProbingHash<
          Value, BaseLinearProbingHash<
                     Key, HashTableEntryWithValue<Key, Value>, HashFunction, OrderedArraySymbolTable<Key, Value>,
                     BaseSymbolTable<Key, Value>>> {
public:
    BaseLinearProbingHashSymbolTable() = default;
    // no need for virtual destructor because base destructor
    // is virtual (similar to other virtual functions)
    ~BaseLinearProbingHashSymbolTable() override = default;
    BaseLinearProbingHashSymbolTable(BaseLinearProbingHashSymbolTable const &) = default;
    BaseLinearProbingHashSymbolTable(BaseLinearProbingHashSymbolTable &&) noexcept = default;
    BaseLinearProbingHashSymbolTable &operator=(BaseLinearProbingHashSymbolTable const &) = default;
    BaseLinearProbingHashSymbolTable &operator=(BaseLinearProbingHashSymbolTable &&) noexcept = default;
};

}  // namespace alba::algorithm
