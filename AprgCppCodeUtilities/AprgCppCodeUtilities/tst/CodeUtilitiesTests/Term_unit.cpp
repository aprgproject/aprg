#include <CodeUtilities/Term.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(TermTest, ConstructorWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ(TermType::Identifier, term.getTermType());
    EXPECT_EQ("SomeIdentifier", term.getContent());
}

TEST(TermTest, GetTermTypeWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ(TermType::Identifier, term.getTermType());
}

TEST(TermTest, GetContentWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ("SomeIdentifier", term.getContent());
}

TEST(TermTest, GetTermTypeStringWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    EXPECT_EQ("TermType::Identifier", term.getTermTypeString());
}

TEST(TermTest, SetTermTypeWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    term.setTermType(TermType::Keyword);

    EXPECT_EQ(TermType::Keyword, term.getTermType());
}

TEST(TermTest, SetContentWorks) {
    Term term(TermType::Identifier, "SomeIdentifier");

    term.setContent("NewIdentifier");

    EXPECT_EQ("NewIdentifier", term.getContent());
}

TEST(TermTest, OperatorEqualsWorks) {
    Term term1(TermType::Identifier, "SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_TRUE(term1.operator==(term1));
    EXPECT_TRUE(term1.operator==(term2));
    EXPECT_FALSE(term1.operator==(term3));
    EXPECT_FALSE(term1.operator==(term4));
}

TEST(TermTest, OperatorNotEqualsWorks) {
    Term term1(TermType::Identifier, "SomeIdentifier");
    Term term2(TermType::Identifier, "SomeIdentifier");
    Term term3(TermType::Identifier, "SomeIdentifierDifferent");
    Term term4(TermType::Keyword, "SomeIdentifier");

    EXPECT_FALSE(term1.operator!=(term1));
    EXPECT_FALSE(term1.operator!=(term2));
    EXPECT_TRUE(term1.operator!=(term3));
    EXPECT_TRUE(term1.operator!=(term4));
}

}  // namespace alba::CodeUtilities
