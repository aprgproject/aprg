#include <Algorithm/String/SubstringSearch/AhoCorasickMultipleSubstringsSearch.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba::algorithm {

namespace {
using Index = int;
using SubstringSearchForTest = AhoCorasickMultipleSubstringsSearch<Index>;
}  // namespace

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    string const emptyString;
    string const nonEmptyString("NonEmptyString");
    SubstringSearchForTest::Strings const queries{emptyString, nonEmptyString};
    SubstringSearchForTest substringSearch(queries);

    SubstringSearchForTest::SearchResult const expectedResult1;
    SubstringSearchForTest::SearchResult const expectedResult2{{"NonEmptyString", {0}}};
    EXPECT_EQ(expectedResult1, substringSearch.search(emptyString));
    EXPECT_EQ(expectedResult2, substringSearch.search(nonEmptyString));
}

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingExample1) {
    SubstringSearchForTest::Strings const queries{"AACAA", "BBB"};
    SubstringSearchForTest substringSearch(queries);
    string const searchSpace("AABRAACADABRAACAADABRA");

    SubstringSearchForTest::SearchResult const expectedResult{{"AACAA", {12}}};
    EXPECT_EQ(expectedResult, substringSearch.search(searchSpace));
}

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingExample2) {
    SubstringSearchForTest::Strings const queries{"blue", "red"};
    SubstringSearchForTest substringSearch(queries);
    string const searchSpace("Mr. Blue has a blue house");

    SubstringSearchForTest::SearchResult const expectedResult{{"blue", {15}}};
    EXPECT_EQ(expectedResult, substringSearch.search(searchSpace));
}

TEST(AhoCorasickMultipleSubstringsSearchTest, SearchWorksUsingExample3) {
    SubstringSearchForTest::Strings const queries{"lets", "Dance", "Too", "his", "Song", "T"};
    SubstringSearchForTest substringSearch(queries);
    string const searchSpace("LetsDanceToThisSong");

    SubstringSearchForTest::SearchResult const expectedResult{
        {"Dance", {4}}, {"Song", {15}}, {"T", {9, 11}}, {"his", {12}}};
    EXPECT_EQ(expectedResult, substringSearch.search(searchSpace));
}

}  // namespace alba::algorithm
