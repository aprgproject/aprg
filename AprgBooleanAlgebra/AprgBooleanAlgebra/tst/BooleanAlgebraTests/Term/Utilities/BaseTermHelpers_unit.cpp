#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

#include <gtest/gtest.h>

namespace alba::booleanAlgebra {

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromTermWorks) {
    Term const originalTerm(true);

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromTerm(originalTerm));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermConstReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(true)));

    BaseTerm const& baseTerm(getBaseTermConstReferenceFromUniquePointer(uniquePointer));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromTermWorks) {
    Term originalTerm(true);

    BaseTerm& baseTerm(getBaseTermReferenceFromTerm(originalTerm));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term&>(baseTerm));
    originalTerm = Term(true);

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetBaseTermReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(true)));

    BaseTerm const& baseTerm(getBaseTermReferenceFromUniquePointer(uniquePointer));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    Term const& termToVerify(static_cast<Term const&>(baseTerm));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, DuplicateUniquePointerWorks) {
    BaseTermUniquePointer const originalPointer(createBasePointer(Term(true)));

    BaseTermUniquePointer const duplicatedPointer(duplicateUniquePointer(originalPointer));

    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(duplicatedPointer));
}

TEST(BaseTermHelpersTest, CreateBasePointerWorksForLValue) {
    Term const originalTerm(true);

    BaseTermUniquePointer const uniquePointer(createBasePointer(originalTerm));

    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, CreateBasePointerWorksForRValue) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(true)));

    EXPECT_EQ(Term(true), getTermConstReferenceFromUniquePointer(uniquePointer));
}

TEST(BaseTermHelpersTest, CreateAUniquePointerFromTermWorks) {
    BaseTermUniquePointer const uniquePointerToVerify(createBasePointer(Term(true)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointerToVerify));
    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer const uniquePointer(createBasePointer(Term(true)));

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromUniquePointerWorks) {
    BaseTermUniquePointer uniquePointer(createBasePointer(Term(true)));

    Term& termToChange(getTermReferenceFromUniquePointer(uniquePointer));
    termToChange.getConstantReference().setValue(true);

    Term const& termToVerify(getTermConstReferenceFromUniquePointer(uniquePointer));
    EXPECT_EQ(Term(763), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermConstReferenceFromBaseTermWorks) {
    Term const originalTerm(true);

    Term const& termToVerify(getTermConstReferenceFromBaseTerm(static_cast<BaseTerm const&>(originalTerm)));

    EXPECT_EQ(Term(true), termToVerify);
}

TEST(BaseTermHelpersTest, GetTermReferenceFromBaseTermWorks) {
    Term originalTerm(true);

    Term const& termToVerify(getTermReferenceFromBaseTerm(static_cast<BaseTerm&>(originalTerm)));
    originalTerm = Term(true);

    EXPECT_EQ(Term(true), termToVerify);
}

}  // namespace alba::booleanAlgebra
