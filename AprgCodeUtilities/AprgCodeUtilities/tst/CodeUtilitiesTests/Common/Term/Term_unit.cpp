#include <CodeUtilities/Common/Term/Term.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(TermTest, OperatorEqualsWorks) {
    Term const term1(TermType::Identifier, "SomeIdentifier");
    Term const term2(TermType::Identifier, "SomeIdentifier");
    Term const term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term const term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(term1.operator==(term1));
    EXPECT_TRUE(term1.operator==(term2));
    EXPECT_FALSE(term1.operator==(term3));
    EXPECT_FALSE(term1.operator==(term4));
}

TEST(TermTest, OperatorNotEqualsWorks) {
    Term const term1(TermType::Identifier, "SomeIdentifier");
    Term const term2(TermType::Identifier, "SomeIdentifier");
    Term const term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term const term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(term1.operator!=(term1));
    EXPECT_FALSE(term1.operator!=(term2));
    EXPECT_TRUE(term1.operator!=(term3));
    EXPECT_TRUE(term1.operator!=(term4));
}

TEST(TermTest, GetTermTypeWorks) {
    Term const term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ(TermType::Identifier, term.getTermType());
}

TEST(TermTest, ConstructorWorks) {
    Term const term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ(TermType::Identifier, term.getTermType());
    EXPECT_EQ("SomeIdentifier", term.getContent());
}

TEST(TermTest, SetTermTypeWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    term.setTermType(TermType::Keyword);

    EXPECT_EQ(TermType::Keyword, term.getTermType());
}

TEST(TermTest, GetContentWorks) {
    Term const term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ("SomeIdentifier", term.getContent());
}

TEST(TermTest, SetContentWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    term.setContent("NewIdentifier");

    EXPECT_EQ("NewIdentifier", term.getContent());
}

TEST(TermTest, GetTermTypeStringWorks) {
    Term const term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ("TermType::Identifier", term.getTermTypeString());
}

}  // namespace alba::CodeUtilities
