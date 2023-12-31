#include <Algorithm/String/SuffixArray/KeywordInContextIndexing.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algorithm {

namespace {
using KeywordInContextIndexingForTest = KeywordInContextIndexing<int>;
}  // namespace

TEST(KeywordInContextIndexingTest, GetKeywordInContextIndexingWorks) {
    string const searchSpace(
        "it was the best of times it was the worst of times "
        "it was the age of wisdom it was the age of foolishness "
        "it was the epoch of belief if was the epoch of incredulity "
        "it was the season of light it was the season of darkness "
        "it was the spring of hope it was the winter of despair ");
    KeywordInContextIndexingForTest keywordInContextIndexing(searchSpace);

    strings const stringsToExpect{"om it was the age of foolis", "es it was the age of wisdom"};
    EXPECT_EQ(stringsToExpect, keywordInContextIndexing.getKeywordInContextIndexing("the age", 10));
}

}  // namespace alba::algorithm
