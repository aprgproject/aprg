#include <Algorithm/String/SubstringSearch/RabinKarpSubstringSearchWithSubstringHash.hpp>
#include <AlgorithmTests/String/SubstringSearch/Utilities/CommonTestsWithSubstringSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSubstringSearch;
using namespace std;

namespace alba::algorithm {

namespace {
using Index = int;
using HashValue = uint64_t;
using SubstringSearchForTest = RabinKarpSubstringSearchWithSubstringHash<Index, HashValue>;
}  // namespace

TEST(RabinKarpSubstringSearchWithSubstringHashTest, SearchWorksUsingExample1) {
    testSearchUsingExample1<SubstringSearchForTest, Index>();
}

TEST(RabinKarpSubstringSearchWithSubstringHashTest, SearchWorksUsingExample2) {
    testSearchUsingExample2<SubstringSearchForTest, Index>();
}

TEST(RabinKarpSubstringSearchWithSubstringHashTest, SearchWorksUsingEmptyStringsAndDoesNotCrash) {
    // SubstringSearchUsingZAlgorithm has unique results of handling empty strings
    string const emptyString;
    string const nonEmptyString("NonEmptyString");
    SubstringSearchForTest const emptyStringSearch(emptyString);
    SubstringSearchForTest const nonEmptyStringSearch(nonEmptyString);

    EXPECT_EQ(Index(string::npos), emptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(string::npos), emptyStringSearch.search(nonEmptyString));
    EXPECT_EQ(Index(string::npos), nonEmptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), nonEmptyStringSearch.search(nonEmptyString));
}

}  // namespace alba::algorithm
