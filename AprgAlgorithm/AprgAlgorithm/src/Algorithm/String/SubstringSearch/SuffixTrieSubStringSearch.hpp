#pragma once

#include <Algorithm/String/Tries/TernarySearchSuffixTrie.hpp>

#include <string>

namespace alba::algorithm {

template <typename Index>
class SuffixTrieSubStringSearch {
public:
    explicit SuffixTrieSubStringSearch(std::string const& query) : m_query(query) {}
    explicit SuffixTrieSubStringSearch(std::string&& query) : m_query(query) {}

    [[nodiscard]] Index search(std::string const& searchSpace) const {
        if (!m_query.empty()) {
            return searchUsingTrie(searchSpace, m_query);
        }
        return 0;
    }

private:
    [[nodiscard]] int searchUsingTrie(std::string const& searchSpace, std::string const& query) const {
        TernarySearchSuffixTrie const trie(searchSpace);
        return trie.getIndexOfFirstOccurrence(query);
    }

    std::string m_query;
};

}  // namespace alba::algorithm
