#pragma once

#include <string_view>
#include <vector>

namespace alba::algorithm {

template <typename Value>
class BaseStringSymbolTable {
public:
    using Key = std::string_view;
    using Strings = std::vector<std::string>;
    BaseStringSymbolTable() = default;
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseStringSymbolTable() = default;
    BaseStringSymbolTable(BaseStringSymbolTable const&) = default;
    BaseStringSymbolTable(BaseStringSymbolTable&&) noexcept = default;
    BaseStringSymbolTable& operator=(BaseStringSymbolTable const&) = default;
    BaseStringSymbolTable& operator=(BaseStringSymbolTable&&) noexcept = default;

    [[nodiscard]] virtual Key getLongestPrefixOf(
        Key const& keyToCheck) const = 0;  // get the longest key that has a prefix

    [[nodiscard]] virtual Strings getKeys() const = 0;  // get all keys in sorted order

    [[nodiscard]] virtual Strings getAllKeysWithPrefix(
        Key const& prefix) const = 0;  // all the keys having s as a prefix

    [[nodiscard]] virtual Strings getAllKeysThatMatch(
        Key const& patternToMatch) const = 0;  // all the keys having s as a prefix

    [[nodiscard]] virtual Value get(Key const& key) const = 0;         // get value paired with key
    [[nodiscard]] virtual int getSize() const = 0;                     // get number of key-value pairs
    [[nodiscard]] virtual bool isEmpty() const = 0;                    // is the symbol table empty
    [[nodiscard]] virtual bool doesContain(Key const& key) const = 0;  // is key exists on symbol table
    virtual void put(Key const& key, Value const& value) = 0;          // put key-value pair
    virtual void deleteBasedOnKey(Key const& key) = 0;  // remove key (and its value) from the symbol table
};

}  // namespace alba::algorithm

// Can we do better than generic symbol tables?
// Yes, if we can avoid examining the entrie key, as with string sorting.
// So create a specialized string symbol table
// Applications:
// Character based operations
// -> Prefix match
// -> Wildcard match
// -> Longest prefix
