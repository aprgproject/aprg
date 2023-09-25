#include <CodeUtilities/Common/CommonUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(CommonUtilitiesTest, ReplaceAllForwardsWorks) {
    Terms terms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier3"), Term(TermType::Identifier, "identifier4"),
        Term(TermType::Identifier, "identifier5")};
    Patterns const patterns{{M("identifier2"), M("identifier3"), M("identifier4")}};
    Terms const replacementTerms{Term(TermType::Identifier, "identifier7")};

    replaceAllForwards(terms, 0, patterns, replacementTerms);

    ASSERT_EQ(3U, terms.size());
    auto itTerms = terms.cbegin();
    EXPECT_EQ(Term(TermType::Identifier, "identifier1"), *itTerms++);
    EXPECT_EQ(Term(TermType::Identifier, "identifier7"), *itTerms++);
    EXPECT_EQ(Term(TermType::Identifier, "identifier5"), *itTerms++);
}

TEST(CommonUtilitiesTest, CombineTermsInPlaceWorks) {
    Terms terms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier3"), Term(TermType::Identifier, "identifier4"),
        Term(TermType::Identifier, "identifier5")};

    combineTermsInPlace(terms, TermType::Keyword, 1, 3);

    Terms const expectedTerms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Keyword, "identifier2identifier3identifier4"),
        Term(TermType::Identifier, "identifier5")};

    EXPECT_EQ(expectedTerms, terms);
}

TEST(CommonUtilitiesTest, SearchForPatternsForwardsWorksInTheMiddleOfMatch) {
    Terms const terms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier3"), Term(TermType::Identifier, "identifier4"),
        Term(TermType::Identifier, "identifier5")};
    Patterns const patterns{{M("identifier2"), M("identifier3"), M("identifier4")}};

    Indexes const hitIndexes = searchForwardsForPatterns(terms, 0, patterns);
    ASSERT_EQ(3U, hitIndexes.size());
    auto itPatterns = hitIndexes.cbegin();
    EXPECT_EQ(1, *itPatterns++);
    EXPECT_EQ(2, *itPatterns++);
    EXPECT_EQ(3, *itPatterns++);
}

TEST(CommonUtilitiesTest, SearchForPatternsForwardsWorksWithIgnoringComments) {
    Terms const terms{Term(TermType::Identifier, "identifier1"), Term(TermType::CommentMultiline, "/*Comment*/"),
                      Term(TermType::Identifier, "identifier2"), Term(TermType::CommentMultiline, "/*Comment*/"),
                      Term(TermType::Identifier, "identifier3"), Term(TermType::CommentMultiline, "/*Comment*/"),
                      Term(TermType::Identifier, "identifier4"), Term(TermType::CommentMultiline, "/*Comment*/"),
                      Term(TermType::Identifier, "identifier5"), Term(TermType::CommentMultiline, "/*Comment*/")};
    Patterns const patterns{{M("identifier2"), M("identifier3"), M("identifier4")}};

    Indexes const hitIndexes = searchForwardsForPatterns(terms, 0, patterns);
    ASSERT_EQ(3U, hitIndexes.size());
    auto itPatterns = hitIndexes.cbegin();
    EXPECT_EQ(2, *itPatterns++);
    EXPECT_EQ(4, *itPatterns++);
    EXPECT_EQ(6, *itPatterns++);
}

TEST(CommonUtilitiesTest, SearchForPatternsForwardsWorksWithSpaces) {
    Terms const terms{Term(TermType::Identifier, "identifier1"), Term(TermType::WhiteSpace, "\t"),
                      Term(TermType::Identifier, "identifier2"), Term(TermType::WhiteSpace, "\t"),
                      Term(TermType::Identifier, "identifier3"), Term(TermType::WhiteSpace, "\t"),
                      Term(TermType::Identifier, "identifier4"), Term(TermType::WhiteSpace, "\t"),
                      Term(TermType::Identifier, "identifier5"), Term(TermType::WhiteSpace, "\t")};
    Patterns const patterns{{M("identifier2"), M("identifier3"), M("identifier4")}};

    Indexes const hitIndexes = searchForwardsForPatterns(terms, 0, patterns);
    ASSERT_EQ(3U, hitIndexes.size());
    auto itPatterns = hitIndexes.cbegin();
    EXPECT_EQ(2, *itPatterns++);
    EXPECT_EQ(4, *itPatterns++);
    EXPECT_EQ(6, *itPatterns++);
}

TEST(CommonUtilitiesTest, SearchForPatternsForwardsWorksAsGoingForward) {
    Terms const terms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier2"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier1")};
    Patterns const patterns{{M("identifier2")}};

    Indexes const hitIndexes = searchForwardsForPatterns(terms, 0, patterns);
    ASSERT_EQ(1U, hitIndexes.size());
    auto itPatterns = hitIndexes.cbegin();
    EXPECT_EQ(1, *itPatterns++);
}

TEST(CommonUtilitiesTest, SearchForPatternsBackwardsWorksAsGoingBackward) {
    Terms const terms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier2"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier1")};
    Patterns const patterns{{M("identifier2")}};

    Indexes const hitIndexes = searchBackwardsForPatterns(terms, static_cast<int>(terms.size()) - 1, patterns);
    ASSERT_EQ(1U, hitIndexes.size());
    auto itPatterns = hitIndexes.cbegin();
    EXPECT_EQ(3, *itPatterns++);
}

TEST(CommonUtilitiesTest, ConvertToStringWorks) {
    EXPECT_EQ("TermType::Boolean", convertToString(TermType::Boolean));
    EXPECT_EQ("TermType::CharacterLiteral", convertToString(TermType::CharacterLiteral));
    EXPECT_EQ("TermType::CommentMultiline", convertToString(TermType::CommentMultiline));
    EXPECT_EQ("TermType::CommentSingleLine", convertToString(TermType::CommentSingleLine));
    EXPECT_EQ("TermType::Identifier", convertToString(TermType::Identifier));
    EXPECT_EQ("TermType::Keyword", convertToString(TermType::Keyword));
    EXPECT_EQ("TermType::Macro", convertToString(TermType::Macro));
    EXPECT_EQ("TermType::Number", convertToString(TermType::Number));
    EXPECT_EQ("TermType::Operator", convertToString(TermType::Operator));
    EXPECT_EQ("TermType::PrimitiveType", convertToString(TermType::PrimitiveType));
    EXPECT_EQ("TermType::StringLiteral", convertToString(TermType::StringLiteral));
    EXPECT_EQ("TermType::Unknown", convertToString(TermType::Unknown));
    EXPECT_EQ("TermType::WhiteSpace", convertToString(TermType::WhiteSpace));
}

TEST(CommonUtilitiesTest, IsCommentWorks) {
    EXPECT_FALSE(isComment(Term(TermType::Boolean, "")));
    EXPECT_FALSE(isComment(Term(TermType::CharacterLiteral, "")));
    EXPECT_TRUE(isComment(Term(TermType::CommentMultiline, "")));
    EXPECT_TRUE(isComment(Term(TermType::CommentSingleLine, "")));
    EXPECT_FALSE(isComment(Term(TermType::Identifier, "")));
    EXPECT_FALSE(isComment(Term(TermType::Keyword, "")));
    EXPECT_FALSE(isComment(Term(TermType::Macro, "")));
    EXPECT_FALSE(isComment(Term(TermType::Number, "")));
    EXPECT_FALSE(isComment(Term(TermType::Operator, "")));
    EXPECT_FALSE(isComment(Term(TermType::PrimitiveType, "")));
    EXPECT_FALSE(isComment(Term(TermType::StringLiteral, "")));
    EXPECT_FALSE(isComment(Term(TermType::Unknown, "")));
    EXPECT_FALSE(isComment(Term(TermType::WhiteSpace, "")));
}

TEST(CommonUtilitiesTest, IsWhiteSpaceWorks) {
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Boolean, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::CharacterLiteral, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::CommentMultiline, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::CommentSingleLine, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Identifier, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Keyword, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Macro, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Number, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Operator, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::PrimitiveType, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::StringLiteral, "")));
    EXPECT_FALSE(isWhiteSpace(Term(TermType::Unknown, "")));
    EXPECT_TRUE(isWhiteSpace(Term(TermType::WhiteSpace, "")));
}

TEST(CommonUtilitiesTest, IsCommentOrWhiteSpaceWorks) {
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Boolean, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::CharacterLiteral, "")));
    EXPECT_TRUE(isCommentOrWhiteSpace(Term(TermType::CommentMultiline, "")));
    EXPECT_TRUE(isCommentOrWhiteSpace(Term(TermType::CommentSingleLine, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Identifier, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Keyword, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Macro, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Number, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Operator, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::PrimitiveType, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::StringLiteral, "")));
    EXPECT_FALSE(isCommentOrWhiteSpace(Term(TermType::Unknown, "")));
    EXPECT_TRUE(isCommentOrWhiteSpace(Term(TermType::WhiteSpace, "")));
}

}  // namespace alba::CodeUtilities
