#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_sf_bessel.h>

#include <gtest/gtest.h>

#include <array>

using namespace std;

TEST(GslTest, PolynomialRootFindingInGslWorks) {
    // To demonstrate the use of the general polynomial solver we will take the polynomial P(x) = x^5 - 1 which has
    // these roots: 1; e^(2*pi*i/5); e^(4*pi*i/5); e^(6*pi*i/5); e^(8*pi*i/5)

    // coefficients of P(x) = -1 + x^5
    constexpr int NUMBER_OF_COEFFICIENTS = 6;
    std::array<double, NUMBER_OF_COEFFICIENTS> coefficients = {-1, 0, 0, 0, 0, 1};
    std::array<double, 10> rootArray{};

    gsl_poly_complex_workspace *workspace = gsl_poly_complex_workspace_alloc(NUMBER_OF_COEFFICIENTS);
    gsl_poly_complex_solve(coefficients.data(), NUMBER_OF_COEFFICIENTS, workspace, rootArray.data());
    gsl_poly_complex_workspace_free(workspace);

    EXPECT_DOUBLE_EQ(-0.809016994374947673, rootArray[0]);
    EXPECT_DOUBLE_EQ(+0.587785252292473359, rootArray[1]);
    EXPECT_DOUBLE_EQ(-0.809016994374947673, rootArray[2]);
    EXPECT_DOUBLE_EQ(-0.587785252292473359, rootArray[3]);
    EXPECT_DOUBLE_EQ(+0.309016994374947507, rootArray[4]);
    EXPECT_DOUBLE_EQ(+0.951056516295152976, rootArray[5]);
    EXPECT_DOUBLE_EQ(+0.309016994374947507, rootArray[6]);
    EXPECT_DOUBLE_EQ(-0.951056516295152976, rootArray[7]);
    EXPECT_DOUBLE_EQ(+0.999999999999999889, rootArray[8]);
    EXPECT_DOUBLE_EQ(+0.000000000000000000, rootArray[9]);
}

TEST(GslTest, GettingTheBesselFunctionInGslWorks) {
    double xValue = 5.0;
    double yValue = gsl_sf_bessel_J0(xValue);

    EXPECT_DOUBLE_EQ(-0.17759677131433830434739701, yValue);
}

TEST(GslTest, MatrixMultiplicationInGslWorks) {
    // Create two matrices.
    gsl_matrix *matrixA = gsl_matrix_alloc(3, 3);
    gsl_matrix *matrixB = gsl_matrix_alloc(3, 3);
    gsl_matrix *matrixC = gsl_matrix_alloc(3, 3);

    // Fill the matrices with random numbers.
    for (int i = 0; i < static_cast<int>(matrixA->size1); ++i) {
        for (int j = 0; j < static_cast<int>(matrixA->size2); ++j) {
            gsl_matrix_set(matrixA, i, j, static_cast<double>(rand()) / RAND_MAX);
            gsl_matrix_set(matrixB, i, j, static_cast<double>(rand()) / RAND_MAX);
        }
    }

    // Multiply the matrices.
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, matrixA, matrixB, 0.0, matrixC);

    // Check that the product is correct.
    for (int i = 0; i < static_cast<int>(matrixC->size1); ++i) {
        for (int j = 0; j < static_cast<int>(matrixC->size2); ++j) {
            double expected = 0.0;
            for (int k = 0; k < static_cast<int>(matrixA->size2); ++k) {
                expected += gsl_matrix_get(matrixA, i, k) * gsl_matrix_get(matrixB, k, j);
            }
            EXPECT_EQ(gsl_matrix_get(matrixC, i, j), expected);
        }
    }

    // Free the matrices.
    gsl_matrix_free(matrixA);
    gsl_matrix_free(matrixB);
    gsl_matrix_free(matrixC);
}
