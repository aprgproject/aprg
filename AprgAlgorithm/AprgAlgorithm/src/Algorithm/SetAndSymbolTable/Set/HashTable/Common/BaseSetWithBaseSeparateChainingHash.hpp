#pragma once

namespace alba::algorithm {

template <typename BaseSeparateChainingHash>
class BaseSetWithBaseSeparateChainingHash : public BaseSeparateChainingHash {
public:
    using Key = typename BaseSeparateChainingHash::Key;
    using Entry = typename BaseSeparateChainingHash::Entry;
    using HashTable = typename BaseSeparateChainingHash::HashTable;

    BaseSetWithBaseSeparateChainingHash()
        : b_size(BaseSeparateChainingHash::m_size),
          b_smallerSymbolTables(BaseSeparateChainingHash::m_smallerSymbolTables) {}

    // no need for virtual destructor because base destructor is virtual (similar to other virtual
    ~BaseSetWithBaseSeparateChainingHash() override = default;
    BaseSetWithBaseSeparateChainingHash(BaseSetWithBaseSeparateChainingHash const &) = default;
    BaseSetWithBaseSeparateChainingHash(BaseSetWithBaseSeparateChainingHash &&) noexcept = default;
    BaseSetWithBaseSeparateChainingHash &operator=(BaseSetWithBaseSeparateChainingHash const &) = default;
    BaseSetWithBaseSeparateChainingHash &operator=(BaseSetWithBaseSeparateChainingHash &&) noexcept = default;

    // functions)
    void put(Key const &key) override {
        b_smallerSymbolTables[this->getHash(key)].put(key);
        ++b_size;
    }

private:
    int &b_size;
    HashTable &b_smallerSymbolTables;
};

}  // namespace alba::algorithm
