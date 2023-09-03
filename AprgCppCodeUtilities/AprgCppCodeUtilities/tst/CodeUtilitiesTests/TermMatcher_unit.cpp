#include <CodeUtilities/TermMatcher.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(TermMatcherTest, OperatorEqualsWorksWithBothTermTypeAndIdentifier) {
    TermMatcher termMatcher(TermType::Identifier, "SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(operator==(termMatcher, term2));
    EXPECT_FALSE(operator==(termMatcher, term3));
    EXPECT_FALSE(operator==(termMatcher, term4));
    EXPECT_TRUE(operator==(term2, termMatcher));
    EXPECT_FALSE(operator==(term3, termMatcher));
    EXPECT_FALSE(operator==(term4, termMatcher));
}

TEST(TermMatcherTest, OperatorEqualsWorksWithTermType) {
    TermMatcher termMatcher(TermType::Identifier);
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(operator==(termMatcher, term2));
    EXPECT_TRUE(operator==(termMatcher, term3));
    EXPECT_FALSE(operator==(termMatcher, term4));
    EXPECT_TRUE(operator==(term2, termMatcher));
    EXPECT_TRUE(operator==(term3, termMatcher));
    EXPECT_FALSE(operator==(term4, termMatcher));
}

TEST(TermMatcherTest, OperatorEqualsWorksWithContent) {
    TermMatcher termMatcher("SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(operator==(termMatcher, term2));
    EXPECT_FALSE(operator==(termMatcher, term3));
    EXPECT_TRUE(operator==(termMatcher, term4));
    EXPECT_TRUE(operator==(term2, termMatcher));
    EXPECT_FALSE(operator==(term3, termMatcher));
    EXPECT_TRUE(operator==(term4, termMatcher));
}

TEST(TermMatcherTest, OperatorNotEqualsWorksWithBothTermTypeAndIdentifier) {
    TermMatcher termMatcher(TermType::Identifier, "SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(operator!=(termMatcher, term2));
    EXPECT_TRUE(operator!=(termMatcher, term3));
    EXPECT_TRUE(operator!=(termMatcher, term4));
    EXPECT_FALSE(operator!=(term2, termMatcher));
    EXPECT_TRUE(operator!=(term3, termMatcher));
    EXPECT_TRUE(operator!=(term4, termMatcher));
}

TEST(TermMatcherTest, OperatorNotEqualsWorksWithTermType) {
    TermMatcher termMatcher(TermType::Identifier);
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(operator!=(termMatcher, term2));
    EXPECT_FALSE(operator!=(termMatcher, term3));
    EXPECT_TRUE(operator!=(termMatcher, term4));
    EXPECT_FALSE(operator!=(term2, termMatcher));
    EXPECT_FALSE(operator!=(term3, termMatcher));
    EXPECT_TRUE(operator!=(term4, termMatcher));
}

TEST(TermMatcherTest, OperatorNotEqualsWorksWithContent) {
    TermMatcher termMatcher("SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(operator!=(termMatcher, term2));
    EXPECT_TRUE(operator!=(termMatcher, term3));
    EXPECT_FALSE(operator!=(termMatcher, term4));
    EXPECT_FALSE(operator!=(term2, termMatcher));
    EXPECT_TRUE(operator!=(term3, termMatcher));
    EXPECT_FALSE(operator!=(term4, termMatcher));
}

}  // namespace alba::CodeUtilities
