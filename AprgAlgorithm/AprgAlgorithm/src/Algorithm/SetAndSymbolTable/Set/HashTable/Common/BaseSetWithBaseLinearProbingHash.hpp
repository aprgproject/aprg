#pragma once

namespace alba::algorithm {

template <typename BaseLinearProbingHash>
class BaseSetWithBaseLinearProbingHash : public BaseLinearProbingHash {
public:
    using Key = typename BaseLinearProbingHash::Key;
    using Entry = typename BaseLinearProbingHash::Entry;
    using EntryUniquePointer = typename BaseLinearProbingHash::EntryUniquePointer;
    using EntryPointers = typename BaseLinearProbingHash::EntryPointers;
    // no need for virtual destructor because base destructor
    ~BaseSetWithBaseLinearProbingHash() override = default;
    BaseSetWithBaseLinearProbingHash(BaseSetWithBaseLinearProbingHash const&) = default;
    BaseSetWithBaseLinearProbingHash(BaseSetWithBaseLinearProbingHash&&) = default;
    BaseSetWithBaseLinearProbingHash& operator=(BaseSetWithBaseLinearProbingHash const&) = default;
    BaseSetWithBaseLinearProbingHash& operator=(BaseSetWithBaseLinearProbingHash&&) = default;
    BaseSetWithBaseLinearProbingHash()
        : b_size(BaseLinearProbingHash::m_size), b_entryPointers(BaseLinearProbingHash::m_entryPointers) {}

    // is virtual (similar to other virtual functions)
    void put(Key const& key) override {
        // overrides in BaseSet
        this->resizeOnPutIfNeeded();
        bool isFound(false);
        int i = this->getHash(key);
        for (; b_entryPointers[i]; this->incrementHashTableIndexWithWrapAround(i)) {
            EntryUniquePointer const& entryPointer(b_entryPointers[i]);
            if (key == entryPointer->key) {
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            b_entryPointers[i] = EntryUniquePointer(new Entry{key});
        }
        ++b_size;
    }

protected:
    // overrides in BaseLinearProbingHash
    void putEntry(Entry const& entry) override { put(entry.key); }

private:
    int& b_size;
    EntryPointers& b_entryPointers;
};

}  // namespace alba::algorithm
