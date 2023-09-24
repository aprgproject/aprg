#pragma once

#include <vector>

namespace alba::algorithm {

template <typename Key>
class BaseSet {
public:
    using Keys = std::vector<Key>;
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseSet() = default;
    BaseSet() = default;
    BaseSet(BaseSet const&) = default;
    BaseSet(BaseSet&&) = default;
    BaseSet& operator=(BaseSet const&) = default;
    BaseSet& operator=(BaseSet&&) = default;
    [[nodiscard]] virtual Key getMinimum() const = 0;                // get smallest key
    [[nodiscard]] virtual Key getMaximum() const = 0;                // get largest key
    [[nodiscard]] virtual Key selectAt(int const rank) const = 0;    // get key at rank
    [[nodiscard]] virtual Key getFloor(Key const& key) const = 0;    // get largest key less than or equal to key
    [[nodiscard]] virtual Key getCeiling(Key const& key) const = 0;  // get smallest key greater than or equal to key
    [[nodiscard]] virtual Keys getKeys() const = 0;                  // get all keys in sorted order

    [[nodiscard]] virtual Keys getKeysInRangeInclusive(
        Key const& low, Key const& high) const = 0;  // get all keys that fall in range in sorted order

    [[nodiscard]] virtual int getSize() const = 0;                     // get number of keys
    [[nodiscard]] virtual int getRank(Key const& key) const = 0;       // get number of keys less than key
    [[nodiscard]] virtual bool isEmpty() const = 0;                    // is the set empty
    [[nodiscard]] virtual bool doesContain(Key const& key) const = 0;  // is key exists on set
    virtual void put(Key const& key) = 0;                              // put key
    virtual void deleteBasedOnKey(Key const& key) = 0;                 // remove key from the set
    virtual void deleteMinimum() = 0;                                  // remove smallest key from the set
    virtual void deleteMaximum() = 0;                                  // remove largest key from the set
};

}  // namespace alba::algorithm
