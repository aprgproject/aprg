#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(TermRaiseToANumberTest, GetExponentWorks) {
    TermRaiseToANumber const termRaiseToANumber("x", 5);

    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(TermRaiseToANumberTest, ConstructionWorks) {
    TermRaiseToANumber const termRaiseToANumber("x", 5);

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
    EXPECT_EQ(AlbaNumber(5), termRaiseToANumber.getExponent());
}

TEST(TermRaiseToANumberTest, GetCombinedTermWorks) {
    TermRaiseToANumber const baseAndExponent1("x", 1);
    TermRaiseToANumber const baseAndExponent2(Monomial(5, {{"x", 6}}), 7);
    TermRaiseToANumber const baseAndExponent3(sin("x"), 7);

    string const stringToExpect1("x");
    string const stringToExpect2("78125[x^42]");
    string const stringToExpect3("(sin(x)^7)");
    EXPECT_EQ(stringToExpect1, convertToString(baseAndExponent1.getCombinedTerm()));
    EXPECT_EQ(stringToExpect2, convertToString(baseAndExponent2.getCombinedTerm()));
    EXPECT_EQ(stringToExpect3, convertToString(baseAndExponent3.getCombinedTerm()));
}

TEST(TermRaiseToANumberTest, GetBaseWorks) {
    TermRaiseToANumber const termRaiseToANumber("x", 5);

    EXPECT_EQ(Term("x"), termRaiseToANumber.getBase());
}

TEST(TermRaiseToANumberTest, GetBaseReferenceWorks) {
    TermRaiseToANumber termRaiseToANumber("x", 5);

    termRaiseToANumber.getBaseReference() = "y";

    EXPECT_EQ(Term("y"), termRaiseToANumber.getBase());
}

TEST(TermRaiseToANumberTest, IsEmptyWorks) {
    TermRaiseToANumber const empty;
    TermRaiseToANumber const nonEmpty("x", 5);

    EXPECT_TRUE(empty.isEmpty());
    EXPECT_FALSE(nonEmpty.isEmpty());
}

TEST(TermRaiseToANumberTest, IsRadicalWorks) {
    TermRaiseToANumber const termWithIntegerExponent("x", 5);
    TermRaiseToANumber const termWithFractionalExponent("x", AlbaNumber::createFraction(3, 4));
    TermRaiseToANumber const termWithDoubleExponent("x", 1.693);

    EXPECT_FALSE(termWithIntegerExponent.isRadical());
    EXPECT_TRUE(termWithFractionalExponent.isRadical());
    EXPECT_TRUE(termWithDoubleExponent.isRadical());
}

}  // namespace alba::algebra
