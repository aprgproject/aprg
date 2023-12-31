#include <Algorithm/String/Tries/TernarySearchSuffixTrie.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using TrieForTest = TernarySearchSuffixTrie;
}  // namespace

TEST(TernarySearchSuffixTrieTest, GetIndexOfFirstOccurrenceWorks) {
    TrieForTest const trie("ABCDEF");

    EXPECT_EQ(0, trie.getIndexOfFirstOccurrence("ABCDEF"));
    EXPECT_EQ(1, trie.getIndexOfFirstOccurrence("BCDEF"));
    EXPECT_EQ(2, trie.getIndexOfFirstOccurrence("CDEF"));
    EXPECT_EQ(3, trie.getIndexOfFirstOccurrence("DEF"));
    EXPECT_EQ(4, trie.getIndexOfFirstOccurrence("EF"));
    EXPECT_EQ(5, trie.getIndexOfFirstOccurrence("F"));
    EXPECT_EQ(-1, trie.getIndexOfFirstOccurrence(""));
    EXPECT_EQ(0, trie.getIndexOfFirstOccurrence("ABC"));
    EXPECT_EQ(3, trie.getIndexOfFirstOccurrence("DE"));
    EXPECT_EQ(-1, trie.getIndexOfFirstOccurrence("ABCH"));
    EXPECT_EQ(-1, trie.getIndexOfFirstOccurrence("DEH"));
}

}  // namespace alba::algorithm
