#include <CodeUtilities/Common/TermMatcher.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(TermMatcherTest, OperatorEqualsWorksWithBothTermTypeAndIdentifier) {
    TermMatcher matcher(TermType::Identifier, "SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(operator==(matcher, term2));
    EXPECT_FALSE(operator==(matcher, term3));
    EXPECT_FALSE(operator==(matcher, term4));
    EXPECT_TRUE(operator==(term2, matcher));
    EXPECT_FALSE(operator==(term3, matcher));
    EXPECT_FALSE(operator==(term4, matcher));
}

TEST(TermMatcherTest, OperatorEqualsWorksWithTermType) {
    TermMatcher matcher(TermType::Identifier);
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(operator==(matcher, term2));
    EXPECT_TRUE(operator==(matcher, term3));
    EXPECT_FALSE(operator==(matcher, term4));
    EXPECT_TRUE(operator==(term2, matcher));
    EXPECT_TRUE(operator==(term3, matcher));
    EXPECT_FALSE(operator==(term4, matcher));
}

TEST(TermMatcherTest, OperatorEqualsWorksWithContent) {
    TermMatcher matcher("SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(operator==(matcher, term2));
    EXPECT_FALSE(operator==(matcher, term3));
    EXPECT_TRUE(operator==(matcher, term4));
    EXPECT_TRUE(operator==(term2, matcher));
    EXPECT_FALSE(operator==(term3, matcher));
    EXPECT_TRUE(operator==(term4, matcher));
}

TEST(TermMatcherTest, OperatorNotEqualsWorksWithBothTermTypeAndIdentifier) {
    TermMatcher matcher(TermType::Identifier, "SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(operator!=(matcher, term2));
    EXPECT_TRUE(operator!=(matcher, term3));
    EXPECT_TRUE(operator!=(matcher, term4));
    EXPECT_FALSE(operator!=(term2, matcher));
    EXPECT_TRUE(operator!=(term3, matcher));
    EXPECT_TRUE(operator!=(term4, matcher));
}

TEST(TermMatcherTest, OperatorNotEqualsWorksWithTermType) {
    TermMatcher matcher(TermType::Identifier);
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(operator!=(matcher, term2));
    EXPECT_FALSE(operator!=(matcher, term3));
    EXPECT_TRUE(operator!=(matcher, term4));
    EXPECT_FALSE(operator!=(term2, matcher));
    EXPECT_FALSE(operator!=(term3, matcher));
    EXPECT_TRUE(operator!=(term4, matcher));
}

TEST(TermMatcherTest, OperatorNotEqualsWorksWithContent) {
    TermMatcher matcher("SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(operator!=(matcher, term2));
    EXPECT_TRUE(operator!=(matcher, term3));
    EXPECT_FALSE(operator!=(matcher, term4));
    EXPECT_FALSE(operator!=(term2, matcher));
    EXPECT_TRUE(operator!=(term3, matcher));
    EXPECT_FALSE(operator!=(term4, matcher));
}

}  // namespace alba::CodeUtilities
