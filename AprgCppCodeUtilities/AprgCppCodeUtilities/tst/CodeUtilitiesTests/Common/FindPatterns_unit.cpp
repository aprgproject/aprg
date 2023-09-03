#include <CodeUtilities/Common/FindPatterns.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(FindPatternsTest, FindFirstPatternIgnoringSpacesAndCommentsWorksInAnExactMatch) {
    Terms terms{
        Term(TermType::Identifier, "identifier2"), Term(TermType::Identifier, "identifier3"),
        Term(TermType::Identifier, "identifier4")};
    TermMatchers matchers{TermMatcher("identifier2"), TermMatcher("identifier3"), TermMatcher("identifier4")};

    PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers);
    EXPECT_EQ(3U, patternIndexes.size());
    EXPECT_EQ(0, patternIndexes[0]);
    EXPECT_EQ(1, patternIndexes[1]);
    EXPECT_EQ(2, patternIndexes[2]);
}

TEST(FindPatternsTest, FindFirstPatternIgnoringSpacesAndCommentsWorksInTheMiddleOfMatch) {
    Terms terms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::Identifier, "identifier2"),
        Term(TermType::Identifier, "identifier3"), Term(TermType::Identifier, "identifier4"),
        Term(TermType::Identifier, "identifier5")};
    TermMatchers matchers{TermMatcher("identifier2"), TermMatcher("identifier3"), TermMatcher("identifier4")};

    PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers);
    EXPECT_EQ(3U, patternIndexes.size());
    EXPECT_EQ(1, patternIndexes[0]);
    EXPECT_EQ(2, patternIndexes[1]);
    EXPECT_EQ(3, patternIndexes[2]);
}

TEST(FindPatternsTest, FindFirstPatternIgnoringSpacesAndCommentsWorksWhileIgnoringComments) {
    Terms terms{Term(TermType::Identifier, "identifier1"), Term(TermType::CommentMultiline, "/*Comment*/"),
                Term(TermType::Identifier, "identifier2"), Term(TermType::CommentMultiline, "/*Comment*/"),
                Term(TermType::Identifier, "identifier3"), Term(TermType::CommentMultiline, "/*Comment*/"),
                Term(TermType::Identifier, "identifier4"), Term(TermType::CommentMultiline, "/*Comment*/"),
                Term(TermType::Identifier, "identifier5"), Term(TermType::CommentMultiline, "/*Comment*/")};
    TermMatchers matchers{TermMatcher("identifier2"), TermMatcher("identifier3"), TermMatcher("identifier4")};

    PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers);
    EXPECT_EQ(3U, patternIndexes.size());
    EXPECT_EQ(2, patternIndexes[0]);
    EXPECT_EQ(4, patternIndexes[1]);
    EXPECT_EQ(6, patternIndexes[2]);
}

TEST(FindPatternsTest, FindFirstPatternIgnoringSpacesAndCommentsWorksWhileSpaces) {
    Terms terms{Term(TermType::Identifier, "identifier1"), Term(TermType::WhiteSpace, "\t"),
                Term(TermType::Identifier, "identifier2"), Term(TermType::WhiteSpace, "\t"),
                Term(TermType::Identifier, "identifier3"), Term(TermType::WhiteSpace, "\t"),
                Term(TermType::Identifier, "identifier4"), Term(TermType::WhiteSpace, "\t"),
                Term(TermType::Identifier, "identifier5"), Term(TermType::WhiteSpace, "\t")};
    TermMatchers matchers{TermMatcher("identifier2"), TermMatcher("identifier3"), TermMatcher("identifier4")};

    PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers);
    EXPECT_EQ(3U, patternIndexes.size());
    EXPECT_EQ(2, patternIndexes[0]);
    EXPECT_EQ(4, patternIndexes[1]);
    EXPECT_EQ(6, patternIndexes[2]);
}

}  // namespace alba::CodeUtilities
