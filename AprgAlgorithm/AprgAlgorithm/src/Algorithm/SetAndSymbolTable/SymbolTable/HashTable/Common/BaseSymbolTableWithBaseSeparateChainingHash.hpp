#pragma once

namespace alba::algorithm {

template <typename Value, typename BaseSeparateChainingHash>
class BaseSymbolTableWithBaseSeparateChainingHash : public BaseSeparateChainingHash {
public:
    using Key = typename BaseSeparateChainingHash::Key;
    using Entry = typename BaseSeparateChainingHash::Entry;
    using HashTable = typename BaseSeparateChainingHash::HashTable;
    ~BaseSymbolTableWithBaseSeparateChainingHash() override =
        default;  // no need for virtual destructor because base destructor is virtual (similar to other virtual

    BaseSymbolTableWithBaseSeparateChainingHash()
        : b_size(BaseSeparateChainingHash::m_size),
          b_smallerSymbolTables(BaseSeparateChainingHash::m_smallerSymbolTables) {}

    // functions)
    [[nodiscard]] Value get(Key const& key) const override {
        return b_smallerSymbolTables[this->getHash(key)].get(key);
    }

    void put(Key const& key, Value const& value) override {
        b_smallerSymbolTables[this->getHash(key)].put(key, value);
        ++b_size;
    }

private:
    int& b_size;
    HashTable& b_smallerSymbolTables;
};

}  // namespace alba::algorithm
