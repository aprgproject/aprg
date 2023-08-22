#pragma once

#include <memory>

namespace alba::algorithm {

template <typename Key>
struct HashTableEntry {
    Key key;
};

template <typename Key, typename Value>
struct HashTableEntryWithValue {
    Key key;
    Value value;
};

}  // namespace alba::algorithm
