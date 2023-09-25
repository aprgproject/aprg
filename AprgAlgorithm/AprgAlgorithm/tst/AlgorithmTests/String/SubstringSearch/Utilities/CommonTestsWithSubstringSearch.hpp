#pragma once

#include <gtest/gtest.h>

#include <string>

namespace alba::algorithm::CommonTestsWithSubstringSearch {

template <typename SubstringSearch, typename Index>
void testSearchUsingEmptyStringsAndDoesNotCrash() {
    std::string const emptyString;
    std::string const nonEmptyString("NonEmptyString");
    SubstringSearch emptyStringSearch(emptyString);
    SubstringSearch nonEmptyStringSearch(nonEmptyString);

    EXPECT_EQ(Index(0), emptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), emptyStringSearch.search(nonEmptyString));
    EXPECT_EQ(Index(std::string::npos), nonEmptyStringSearch.search(emptyString));
    EXPECT_EQ(Index(0), nonEmptyStringSearch.search(nonEmptyString));
}

template <typename SubstringSearch, typename Index>
void testSearchUsingExample1() {
    SubstringSearch substringSearchWithHit("AACAA");
    SubstringSearch substringSearchWithoutHit("BBB");
    std::string const searchSpace("AABRAACADABRAACAADABRA");

    EXPECT_EQ(Index(12), substringSearchWithHit.search(searchSpace));
    EXPECT_EQ(Index(std::string::npos), substringSearchWithoutHit.search(searchSpace));
}

template <typename SubstringSearch, typename Index>
void testSearchUsingExample2() {
    SubstringSearch substringSearchWithHit("blue");
    SubstringSearch substringSearchWithoutHit("red");
    std::string const searchSpace("Mr. Blue has a blue house");

    EXPECT_EQ(Index(15), substringSearchWithHit.search(searchSpace));
    EXPECT_EQ(Index(std::string::npos), substringSearchWithoutHit.search(searchSpace));
}

}  // namespace alba::algorithm::CommonTestsWithSubstringSearch
