#pragma once

namespace alba::algorithm {

template <typename Value, typename BaseLinearProbingHash>
class BaseSymbolTableWithBaseLinearProbingHash : public BaseLinearProbingHash {
public:
    using Key = typename BaseLinearProbingHash::Key;
    using Entry = typename BaseLinearProbingHash::Entry;
    using EntryUniquePointer = typename BaseLinearProbingHash::EntryUniquePointer;
    using EntryPointers = typename BaseLinearProbingHash::EntryPointers;

    BaseSymbolTableWithBaseLinearProbingHash()
        : b_size(BaseLinearProbingHash::m_size), b_entryPointers(BaseLinearProbingHash::m_entryPointers) {}

    // no need for virtual destructor because base destructor is virtual (similar to other virtual)
    ~BaseSymbolTableWithBaseLinearProbingHash() override = default;
    BaseSymbolTableWithBaseLinearProbingHash(BaseSymbolTableWithBaseLinearProbingHash const&) = default;
    BaseSymbolTableWithBaseLinearProbingHash(BaseSymbolTableWithBaseLinearProbingHash&&) noexcept = default;
    BaseSymbolTableWithBaseLinearProbingHash& operator=(BaseSymbolTableWithBaseLinearProbingHash const&) = default;
    BaseSymbolTableWithBaseLinearProbingHash& operator=(BaseSymbolTableWithBaseLinearProbingHash&&) noexcept = default;

    // functions)
    [[nodiscard]] Value get(Key const& key) const override {
        Value result{};
        for (int i(this->getHash(key)); b_entryPointers[i]; this->incrementHashTableIndexWithWrapAround(i)) {
            EntryUniquePointer const& entryPointer(b_entryPointers[i]);
            if (key == entryPointer->key) {
                result = entryPointer->value;
                break;
            }
        }
        return result;
    }

    void put(Key const& key, Value const& value) override {
        this->resizeOnPutIfNeeded();
        bool isFound(false);
        int i(this->getHash(key));
        for (; b_entryPointers[i]; this->incrementHashTableIndexWithWrapAround(i)) {
            EntryUniquePointer const& entryPointer(b_entryPointers[i]);
            if (key == entryPointer->key) {
                entryPointer->value = value;
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            b_entryPointers[i] = EntryUniquePointer(new Entry{key, value});
        }
        ++b_size;
    }

protected:
    void putEntry(Entry const& entry) override {
        // overrides in BaseLinearProbingHash
        put(entry.key, entry.value);
    }

private:
    int& b_size;
    EntryPointers& b_entryPointers;
};

}  // namespace alba::algorithm
