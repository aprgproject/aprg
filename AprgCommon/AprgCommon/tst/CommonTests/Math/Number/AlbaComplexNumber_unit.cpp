#include <Common/Math/Number/AlbaComplexNumber.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba {

TEST(AlbaComplexNumberTest, OperatorEqualsWorks) {
    AlbaComplexNumber<double> const complex1(3, 4);
    AlbaComplexNumber<double> const complex2(3, 4);
    AlbaComplexNumber<double> const complex3(3, 3);
    AlbaComplexNumber<double> const complex4(4, 4);
    AlbaComplexNumber<double> const complex5(5, 5);
    AlbaComplexNumber<double> const complex6(static_cast<double>(1) / 3, static_cast<double>(4) / 3);

    EXPECT_TRUE(complex1 == complex1);
    EXPECT_TRUE(complex1 == complex2);
    EXPECT_FALSE(complex1 == complex3);
    EXPECT_FALSE(complex1 == complex4);
    EXPECT_FALSE(complex1 == complex5);
    EXPECT_TRUE(complex6 == complex6);
}

TEST(AlbaComplexNumberTest, OperatorBinaryAddWorks) {
    AlbaComplexNumber<double> const complex1(3, 4);
    AlbaComplexNumber<double> const complex2(5, 6);

    AlbaComplexNumber<double> const actualComplex(complex1 + complex2);

    AlbaComplexNumber<double> const expectedComplex(8, 10);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorBinaryMinusWorks) {
    AlbaComplexNumber<double> const complex1(7, 9);
    AlbaComplexNumber<double> const complex2(5, 6);

    AlbaComplexNumber<double> const actualComplex(complex1 - complex2);

    AlbaComplexNumber<double> const expectedComplex(2, 3);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorUnaryAddWorks) {
    AlbaComplexNumber<double> const complex(3, 4);

    AlbaComplexNumber<double> const actualComplex(+complex);

    AlbaComplexNumber<double> const expectedComplex(3, 4);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorUnaryMinusWorks) {
    AlbaComplexNumber<double> const complex(7, 9);

    AlbaComplexNumber<double> const actualComplex(-complex);

    AlbaComplexNumber<double> const expectedComplex(-7, -9);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorMultiplyWorks) {
    AlbaComplexNumber<double> const complex1(3, 4);
    AlbaComplexNumber<double> const complex2(5, 6);

    AlbaComplexNumber<double> const actualComplex(complex1 * complex2);

    AlbaComplexNumber<double> const expectedComplex(-9, 38);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorDivideWorks) {
    AlbaComplexNumber<double> const complex1(5, 6);
    AlbaComplexNumber<double> const complex2(3, 4);

    AlbaComplexNumber<double> const actualComplex(complex1 / complex2);

    AlbaComplexNumber<double> const expectedComplex(1.56, -0.08);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorRaiseToPowerWorks) {
    AlbaComplexNumber<double> const actualComplex1(AlbaComplexNumber<double>(-0.5, sqrt(3) / 2) ^ 3);
    AlbaComplexNumber<double> const actualComplex2(AlbaComplexNumber<double>(-8, 0) ^ (static_cast<double>(1) / 3));

    AlbaComplexNumber<double> const expectedComplex1(1, 0);
    AlbaComplexNumber<double> const expectedComplex2(-2, 0);
    EXPECT_EQ(expectedComplex1, actualComplex1);
    EXPECT_EQ(expectedComplex2, actualComplex2);
}

TEST(AlbaComplexNumberTest, OperatorRaiseToPowerWorksWithNegativeOneRaisedToOneHalf) {
    AlbaComplexNumber<double> const complex(-1, 0);

    AlbaComplexNumber<double> const actualComplex(complex ^ 0.5);

    AlbaComplexNumber<double> const expectedComplex(0, 1);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorAdditionAssignmentWorks) {
    AlbaComplexNumber<double> actualComplex(3, 4);
    AlbaComplexNumber<double> const anotherComplex(5, 6);

    actualComplex += anotherComplex;

    AlbaComplexNumber<double> const expectedComplex(8, 10);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorSubtractionAssignmentWorks) {
    AlbaComplexNumber<double> actualComplex(7, 9);
    AlbaComplexNumber<double> const anotherComplex(5, 6);

    actualComplex -= anotherComplex;

    AlbaComplexNumber<double> const expectedComplex(2, 3);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorMultiplicationAssignmentWorks) {
    AlbaComplexNumber<double> actualComplex(3, 4);
    AlbaComplexNumber<double> const anotherComplex(5, 6);

    actualComplex *= anotherComplex;

    AlbaComplexNumber<double> const expectedComplex(-9, 38);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OperatorDivisionAssignmentWorks) {
    AlbaComplexNumber<double> actualComplex(5, 6);
    AlbaComplexNumber<double> const anotherComplex(3, 4);

    actualComplex /= anotherComplex;

    AlbaComplexNumber<double> const expectedComplex(1.56, -0.08);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, OutputStreamOperatorWorks) {
    stringstream testStream;
    AlbaComplexNumber<double> const complex(3.5, 4.5);

    testStream << complex;

    EXPECT_EQ("(3.5 + 4.5i)", testStream.str());
}

TEST(AlbaComplexNumberTest, GetConjugateWorks) {
    AlbaComplexNumber<double> const complex1(3, 4);

    AlbaComplexNumber<double> const actualComplex(complex1.getConjugate());

    AlbaComplexNumber<double> const expectedComplex(3, -4);
    EXPECT_EQ(expectedComplex, actualComplex);
}

TEST(AlbaComplexNumberTest, GetNthRootWorks) {
    AlbaComplexNumber<double> const complex(1, 0);

    AlbaComplexNumber<double> const actualComplex1(complex.getNthRoot(0U, 4U));
    AlbaComplexNumber<double> const actualComplex2(complex.getNthRoot(1U, 4U));
    AlbaComplexNumber<double> const actualComplex3(complex.getNthRoot(2U, 4U));
    AlbaComplexNumber<double> const actualComplex4(complex.getNthRoot(3U, 4U));

    AlbaComplexNumber<double> const expectedComplex1(1, 0);
    AlbaComplexNumber<double> const expectedComplex2(0, 1);
    AlbaComplexNumber<double> const expectedComplex3(-1, 0);
    AlbaComplexNumber<double> const expectedComplex4(0, -1);
    EXPECT_EQ(expectedComplex1, actualComplex1);
    EXPECT_EQ(expectedComplex2, actualComplex2);
    EXPECT_EQ(expectedComplex3, actualComplex3);
    EXPECT_EQ(expectedComplex4, actualComplex4);
}

TEST(AlbaComplexNumberTest, GetRealPartWorks) {
    AlbaComplexNumber<double> const complex(3.5, 4.5);

    EXPECT_DOUBLE_EQ(3.5, complex.getRealPart());
}

TEST(AlbaComplexNumberTest, ConstructionWorks) {
    AlbaComplexNumber<double> const complex1;
    AlbaComplexNumber<double> const complex2(3, 4);

    EXPECT_DOUBLE_EQ(0, complex1.getRealPart());
    EXPECT_DOUBLE_EQ(0, complex1.getImaginaryPart());
    EXPECT_DOUBLE_EQ(3, complex2.getRealPart());
    EXPECT_DOUBLE_EQ(4, complex2.getImaginaryPart());
}

TEST(AlbaComplexNumberTest, OperatorDivideWorksWithZero) {
    AlbaComplexNumber<double> const complex1(5, 6);
    AlbaComplexNumber<double> const complex2(0, 0);

    AlbaComplexNumber<double> const actualComplex(complex1 / complex2);

    EXPECT_TRUE(isnan(actualComplex.getRealPart()));
    EXPECT_TRUE(isnan(actualComplex.getImaginaryPart()));
}

TEST(AlbaComplexNumberTest, GetImaginaryPartWorks) {
    AlbaComplexNumber<double> const complex(3.5, 4.5);

    EXPECT_DOUBLE_EQ(4.5, complex.getImaginaryPart());
}

TEST(AlbaComplexNumberTest, GetModulusWorks) {
    AlbaComplexNumber<double> const complex(3, 4);

    EXPECT_DOUBLE_EQ(5, complex.getModulus());
}

TEST(AlbaComplexNumberTest, GetModulusWithSignOfRealPartWorks) {
    AlbaComplexNumber<double> const complex(-3, 4);

    EXPECT_DOUBLE_EQ(-5, complex.getModulusWithSignOfRealPart());
}

TEST(AlbaComplexNumberTest, GetModulusSquaredWorks) {
    AlbaComplexNumber<double> const complex(3, 4);

    EXPECT_DOUBLE_EQ(25, complex.getModulusSquared());
}

TEST(AlbaComplexNumberTest, GetAngleInRadiansWorks) {
    AlbaComplexNumber<double> const complex(3, 4);

    EXPECT_DOUBLE_EQ(0.92729521800161219, complex.getAngleInRadians());
}

TEST(AlbaComplexNumberTest, GetBestAngleInRaiseToPowerInRadiansWorks) {
    AlbaComplexNumber<double> const complex(-8, 0);

    EXPECT_DOUBLE_EQ(3.1415926535897931, complex.getBestAngleInRaiseToPowerInRadians(static_cast<double>(1) / 3));
}

}  // namespace alba
