#pragma once

#include <vector>

namespace alba::algorithm {

template <typename Key, typename Value>
class BaseSymbolTable {
public:
    using Keys = std::vector<Key>;
    virtual ~BaseSymbolTable() = default;
    BaseSymbolTable() = default;
    BaseSymbolTable(BaseSymbolTable const&) = default;
    BaseSymbolTable(BaseSymbolTable&&) = default;
    BaseSymbolTable& operator=(BaseSymbolTable const&) = default;
    BaseSymbolTable& operator=(BaseSymbolTable&&) = default;
    [[nodiscard]] virtual Key getMinimum() const = 0;                // get smallest key
    [[nodiscard]] virtual Key getMaximum() const = 0;                // get largest key
    [[nodiscard]] virtual Key selectAt(int const rank) const = 0;    // get key at rank
    [[nodiscard]] virtual Key getFloor(Key const& key) const = 0;    // get largest key less than or equal to key
    [[nodiscard]] virtual Key getCeiling(Key const& key) const = 0;  // get smallest key greater than or equal to key
    [[nodiscard]] virtual Keys getKeys() const = 0;                  // get all keys in sorted order

    [[nodiscard]] virtual Keys getKeysInRangeInclusive(
        Key const& low, Key const& high) const = 0;  // get all keys that fall in range in sorted order

    [[nodiscard]] virtual Value get(Key const& key) const = 0;         // get value paired with key
    [[nodiscard]] virtual int getSize() const = 0;                     // get number of key-value pairs
    [[nodiscard]] virtual int getRank(Key const& key) const = 0;       // get number of keys less than key
    [[nodiscard]] virtual bool isEmpty() const = 0;                    // is the symbol table empty
    [[nodiscard]] virtual bool doesContain(Key const& key) const = 0;  // is key exists on symbol table
    virtual void put(Key const& key, Value const& value) = 0;          // put key-value pair
    virtual void deleteBasedOnKey(Key const& key) = 0;  // remove key (and its value) from the symbol table
    virtual void deleteMinimum() = 0;                   // remove smallest key (and its value) from the symbol table
    virtual void deleteMaximum() = 0;                   // remove largest key (and its value) from the symbol table
};

}  // namespace alba::algorithm
