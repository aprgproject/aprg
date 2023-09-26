#include <CodeUtilities/Common/Matcher/SingleMatcher.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(SingleMatcherTest, OperatorEqualsWorksWithBothTermTypeAndIdentifier) {
    SingleMatcher const matcher(TermType::Identifier, "SomeIdentifier");
    Term const term2(TermType::Identifier, "SomeIdentifier");
    Term const term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term const term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(matcher.isAMatch(term2));
    EXPECT_FALSE(matcher.isAMatch(term3));
    EXPECT_FALSE(matcher.isAMatch(term4));
}

TEST(SingleMatcherTest, OperatorEqualsWorksWithTermType) {
    SingleMatcher const matcher(TermType::Identifier);
    Term const term2(TermType::Identifier, "SomeIdentifier");
    Term const term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term const term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(matcher.isAMatch(term2));
    EXPECT_TRUE(matcher.isAMatch(term3));
    EXPECT_FALSE(matcher.isAMatch(term4));
}

TEST(SingleMatcherTest, OperatorEqualsWorksWithContent) {
    SingleMatcher const matcher("SomeIdentifier");
    Term const term2(TermType::Identifier, "SomeIdentifier");
    Term const term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term const term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(matcher.isAMatch(term2));
    EXPECT_FALSE(matcher.isAMatch(term3));
    EXPECT_TRUE(matcher.isAMatch(term4));
}

}  // namespace alba::CodeUtilities
