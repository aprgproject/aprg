#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>

#include <vector>

namespace alba::algorithm {

template <typename Key, typename BaseDataStructure>
class BaseOrderedArray : public BaseDataStructure {
public:
    using Keys = std::vector<Key>;
    BaseOrderedArray() = default;
    ~BaseOrderedArray() override = default;  // no need for virtual destructor because base destructor is virtual
    BaseOrderedArray(BaseOrderedArray const&) = default;
    BaseOrderedArray(BaseOrderedArray&&) noexcept = default;
    BaseOrderedArray& operator=(BaseOrderedArray const&) = default;
    BaseOrderedArray& operator=(BaseOrderedArray&&) noexcept = default;

    [[nodiscard]] Key getMinimum() const override {
        Key result{};
        if (!isEmpty()) {
            result = m_keys[0];
        }
        return result;
    }

    [[nodiscard]] Key getMaximum() const override {
        Key result{};
        if (!isEmpty()) {
            result = m_keys[m_size - 1];
        }
        return result;
    }

    [[nodiscard]] Key selectAt(int const index) const override { return selectAt(index, m_keys); }
    [[nodiscard]] Key getFloor(Key const& key) const override { return getFloor(key, m_keys); }
    [[nodiscard]] Key getCeiling(Key const& key) const override { return getCeiling(key, m_keys); }
    [[nodiscard]] Keys getKeys() const override { return m_keys; }

    [[nodiscard]] Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override {
        Keys result;
        for (Key const& currentKey : m_keys) {
            if (currentKey >= low && currentKey <= high) {
                result.emplace_back(currentKey);
            }
        }
        return result;
    }

    [[nodiscard]] int getSize() const override { return m_size; }
    [[nodiscard]] int getRank(Key const& key) const override { return getRank(key, m_keys); }
    // (similar to other virtual functions)
    [[nodiscard]] bool isEmpty() const override { return m_size == 0; }

    [[nodiscard]] bool doesContain(Key const& key) const override {
        bool result(false);
        if (!isEmpty()) {
            int const rank(getRank(key));
            if (rank < m_size && m_keys[rank] == key) {
                result = true;
            }
        }
        return result;
    }

    static Key selectAt(int const index, Keys const& keys) {
        Key result{};
        if (index < static_cast<int>(keys.size())) {
            result = keys[index];
        }
        return result;
    }

    static Key getFloor(Key const& key, Keys const& keys) {
        Key result{};
        int const rank(getRank(key, keys));
        if (rank < static_cast<int>(keys.size()) && keys[rank] == key) {
            result = key;
        } else if (rank > 0 && rank - 1 < static_cast<int>(keys.size()) && keys[rank - 1] < key) {
            result = keys[rank - 1];
        }
        return result;
    }

    static Key getCeiling(Key const& key, Keys const& keys) {
        Key result{};
        int const rank(getRank(key, keys));
        if (rank < static_cast<int>(keys.size())) {
            result = keys[rank];
        }
        return result;
    }

    static int getRank(Key const& key, Keys const& keys) {
        // this is binary search
        int result(0);
        int lowIndex = 0;
        int highIndex = keys.size() - 1;
        while (lowIndex <= highIndex) {
            int const middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            Key const& keyAtMiddleIndex(keys[middleIndex]);
            if (key < keyAtMiddleIndex) {
                highIndex = middleIndex - 1;
            } else if (key > keyAtMiddleIndex) {
                lowIndex = middleIndex + 1;
            } else {
                result = middleIndex;
                break;
            }
        }
        if (result == 0) {
            result = lowIndex;
        }
        return result;
    }

protected:
    int m_size{};
    Keys m_keys;
};

}  // namespace alba::algorithm
