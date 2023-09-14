#include <Algorithm/String/SuffixArray/SuffixArray.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using SuffixArrayForTest = SuffixArray<int>;
}  // namespace

TEST(SuffixArrayTest, GetSizeWorks) {
    SuffixArrayForTest const suffixArray("LetsDanceToThisSong");

    EXPECT_EQ(19, suffixArray.getSize());
}

TEST(SuffixArrayTest, GetIndexOnMainStringOfSuffixAtWorks) {
    SuffixArrayForTest const suffixArray("LetsDanceToThisSong");

    EXPECT_EQ(5, suffixArray.getIndexOnMainStringOfSuffixAt(5));
    EXPECT_EQ(7, suffixArray.getIndexOnMainStringOfSuffixAt(6));
    EXPECT_EQ(8, suffixArray.getIndexOnMainStringOfSuffixAt(7));
}

TEST(SuffixArrayTest, GetRankWorks) {
    SuffixArrayForTest const suffixArray("LetsDanceToThisSong");

    EXPECT_EQ(2, suffixArray.getRank("LetsSingInstead"));
}

TEST(SuffixArrayTest, GetLongestCommonPrefixOfTwoSuffixesWorks) {
    SuffixArrayForTest const suffixArray("LetsDanceToThisSong");

    EXPECT_EQ("T", suffixArray.getLongestCommonPrefixOfTwoSuffixes(3, 4));
    EXPECT_TRUE(suffixArray.getLongestCommonPrefixOfTwoSuffixes(5, 6).empty());
    EXPECT_EQ("e", suffixArray.getLongestCommonPrefixOfTwoSuffixes(7, 8));
}

TEST(SuffixArrayTest, GetSuffixViewAtWorks) {
    SuffixArrayForTest const suffixArray("LetsDanceToThisSong");

    EXPECT_EQ("DanceToThisSong", suffixArray.getSuffixViewAt(0));
    EXPECT_EQ("LetsDanceToThisSong", suffixArray.getSuffixViewAt(1));
    EXPECT_EQ("Song", suffixArray.getSuffixViewAt(2));
    EXPECT_EQ("ThisSong", suffixArray.getSuffixViewAt(3));
    EXPECT_EQ("ToThisSong", suffixArray.getSuffixViewAt(4));
    EXPECT_EQ("anceToThisSong", suffixArray.getSuffixViewAt(5));
    EXPECT_EQ("ceToThisSong", suffixArray.getSuffixViewAt(6));
    EXPECT_EQ("eToThisSong", suffixArray.getSuffixViewAt(7));
    EXPECT_EQ("etsDanceToThisSong", suffixArray.getSuffixViewAt(8));
    EXPECT_EQ("g", suffixArray.getSuffixViewAt(9));
}

}  // namespace alba::algorithm
