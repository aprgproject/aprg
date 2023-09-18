#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

#include <memory>

using namespace std;

namespace alba::algebra {

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromTermWorks) {
    Term const originalTerm(7896);

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromTerm(originalTerm));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(6415)));

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromUniquePointer(uniquePointer));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromTermWorks) {
    Term originalTerm(7896);

    BaseTerm& baseTerm(getBaseTermReferenceFromTerm(originalTerm));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term&>(baseTerm));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(6415)));

    BaseTerm const& baseTerm(getBaseTermReferenceFromUniquePointer(uniquePointer));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(6415), termToVerify);
}

TEST(BaseTermHelpersTest, DuplicateUniquePointerWorks) {
    BaseTermUniquePointer const originalPointer(createBasePointer(Term(7896)));

    BaseTermUniquePointer const duplicatedPointer(duplicateUniquePointer(originalPointer));

    EXPECT_EQ(Term(7896), getTermConstReferenceFromUniquePointer(duplicatedPointer));
}

TEST(BaseTermHelpersTest, CreateBasePointerWorksForLValue) {
    Term const originalTerm(7896);

    BaseTermUniquePointer const uniquePointer(createBasePointer(originalTerm));

    EXPECT_EQ(Term(7896), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, CreateBasePointerWorksForRValue) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(7896)));

    EXPECT_EQ(Term(7896), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(9541)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));

    EXPECT_EQ(Term(9541), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(9652)));

    Term& termToChange(getTermReferenceFromUniquePointer(uniquePointer));
    termToChange.getAsConstantReference().setNumber(763);

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));
    EXPECT_EQ(Term(763), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromBaseTermWorks) {
    Term const originalTerm(7896);

    Term const& termToVerify(getTermConstReferenceFromBaseTerm(static_cast<BaseTerm const&>(originalTerm)));

    EXPECT_EQ(Term(7896), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromBaseTermWorks) {
    Term originalTerm(7896);

    Term const& termToVerify(getTermReferenceFromBaseTerm(static_cast<BaseTerm&>(originalTerm)));
    originalTerm = Term(854);

    EXPECT_EQ(Term(854), termToVerify);
}

}  // namespace alba::algebra
