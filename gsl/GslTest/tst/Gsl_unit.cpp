#include <Common/Debug/AlbaDebug.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_combination.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multiset.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_qrng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sort_double.h>

#include <gtest/gtest.h>

#include <array>
#include <iterator>
#include <vector>

using namespace alba;
using namespace alba::matrix;
using namespace alba::mathHelper;
using namespace std;

TEST(GslTest, GettingTheBesselFunctionInGslWorks) {
    double xValue = 5.0;
    double yValue = gsl_sf_bessel_J0(xValue);

    EXPECT_DOUBLE_EQ(-0.17759677131433830434739701, yValue);
}

TEST(GslTest, PolynomialRootFindingInGslWorks) {
    // To demonstrate the use of the general polynomial solver we will take the polynomial P(x) = x^5 - 1
    // which has these roots: 1; e^(2*pi*index/5); e^(4*pi*index/5); e^(6*pi*index/5); e^(8*pi*index/5)

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

TEST(GslTest, PermutationFunctionsInGslWorks) {
    // Th iscreates a random permutation (by shuffling the elements of the identity) and finds its inverse.

    using PermutationVector = vector<size_t>;
    constexpr size_t NUMBER_OF_DIGITS = 5;
    gsl_permutation *permutation1 = gsl_permutation_alloc(NUMBER_OF_DIGITS);
    gsl_permutation *permutation2 = gsl_permutation_alloc(NUMBER_OF_DIGITS);

    gsl_permutation_init(permutation1);
    PermutationVector initialPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector expectedInitialPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedInitialPermutation, initialPermutation);

    gsl_permutation_next(permutation1);
    PermutationVector nextPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector expectedNextPermutation{0, 1, 2, 4, 3};
    EXPECT_EQ(expectedNextPermutation, nextPermutation);

    gsl_permutation_prev(permutation1);
    PermutationVector prevPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector expectedPrevPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedPrevPermutation, prevPermutation);

    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_inverse(permutation2, permutation1);
    // The inverse of a permutation is another permutation that,
    // when composed with the original permutation, results in the identity permutation
    PermutationVector inversePermutation(permutation2->data, permutation2->data + permutation2->size);
    PermutationVector expectedInversePermutation{0, 1, 4, 2, 3};
    EXPECT_EQ(expectedInversePermutation, inversePermutation);

    gsl_permutation_free(permutation1);
    gsl_permutation_free(permutation2);
}

TEST(GslTest, GettingRandomPermutationsInGslWorks) {
    constexpr size_t NUMBER_OF_DIGITS = 5;
    gsl_permutation *permutation1 = gsl_permutation_alloc(NUMBER_OF_DIGITS);

    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);

    gsl_permutation_init(permutation1);
    gsl_ran_shuffle(randomGenerator, permutation1->data, NUMBER_OF_DIGITS, sizeof(size_t));
    cout << "random permutation:";
    gsl_permutation_fprintf(stdout, permutation1, " %u");
    cout << "\n";

    gsl_permutation_free(permutation1);
    gsl_rng_free(randomGenerator);
}

TEST(GslTest, GettingPermutationsInGslWorks) {
    // This steps forwards through all possible third order permutations, starting from the identity.

    gsl_permutation *permutation = gsl_permutation_alloc(3);
    gsl_permutation_init(permutation);
    int exitStatus = GSL_SUCCESS;
    while (exitStatus == GSL_SUCCESS) {
        gsl_permutation_fprintf(stdout, permutation, " %u");
        cout << "\n";
        exitStatus = gsl_permutation_next(permutation);
    }
    gsl_permutation_free(permutation);
}

TEST(GslTest, GettingCombinationsInGslWorks) {
    // This prints all subsets of the set 0, 1, 2, 3 ordered by size.

    constexpr int NUMBER_OF_DIGITS = 3;
    cout << "All subsets of {0,1,2,3} by size:\n";
    for (int index = 0; index <= NUMBER_OF_DIGITS; ++index) {
        gsl_combination *combination = gsl_combination_calloc(NUMBER_OF_DIGITS, index);
        int exitStatus = GSL_SUCCESS;
        while (exitStatus == GSL_SUCCESS) {
            cout << "{";
            gsl_combination_fprintf(stdout, combination, " %u");
            cout << " }\n";
            exitStatus = gsl_combination_next(combination);
        }
        gsl_combination_free(combination);
    }
}

TEST(GslTest, GettingMultisetsInGslWorks) {
    // This prints all multisets elements containing the values 0; 1; 2; 3 ordered by size.

    constexpr int NUMBER_OF_DIGITS = 3;
    cout << "All subsets of {0,1,2} by size:\n";
    for (int index = 0; index <= NUMBER_OF_DIGITS; ++index) {
        gsl_multiset *multiset = gsl_multiset_calloc(NUMBER_OF_DIGITS, index);
        int exitStatus = GSL_SUCCESS;
        while (exitStatus == GSL_SUCCESS) {
            cout << "{";
            gsl_multiset_fprintf(stdout, multiset, " %u");
            cout << " }\n";
            exitStatus = gsl_multiset_next(multiset);
        }
        gsl_multiset_free(multiset);
    }
}

TEST(GslTest, SortingAndGettingTheSmallestValuesInGslWorks) {
    // This uses the function gsl_sort_smallest() to select the 5 smallest numbers.

    constexpr int NUMBER_OF_VALUES = 10;
    constexpr int NUMBER_OF_SMALLEST_VALUES = 5;
    constexpr size_t stride = 1;
    std::array<double, NUMBER_OF_VALUES> values{3, 8, 4, 5, 1, 7, 9, 0, 2, 6};
    std::array<double, NUMBER_OF_SMALLEST_VALUES> smallestValues{};

    gsl_sort_smallest(smallestValues.data(), NUMBER_OF_SMALLEST_VALUES, values.data(), stride, NUMBER_OF_VALUES);

    decltype(smallestValues) expectedSmallestValues{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedSmallestValues, smallestValues);
}

TEST(GslTest, MatrixMultiplicationInGslWorks) {
    // Thi computes the product of two matrices using the Level-3 BLAS function DGEMM.

    // Create two matrices.
    AlbaMatrix<double> matrixA(3, 2, {0.11, 0.12, 0.13, 0.21, 0.22, 0.23});
    AlbaMatrix<double> matrixB(2, 3, {1011, 1012, 1021, 1022, 1031, 1032});
    AlbaMatrix<double> matrixC(2, 2, {0.00, 0.00, 0.00, 0.00});
    gsl_matrix_view matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), 2, 3);
    gsl_matrix_view matrixViewB = gsl_matrix_view_array(matrixB.getMatrixDataReference().data(), 3, 2);
    gsl_matrix_view matrixViewC = gsl_matrix_view_array(matrixC.getMatrixDataReference().data(), 2, 2);

    // Compute C = A * B
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &matrixViewA.matrix, &matrixViewB.matrix, 0.0, &matrixViewC.matrix);

    AlbaMatrix<double> expectedMatrixC(2, 2, {367.76, 368.12, 674.06, 674.72});
    EXPECT_EQ(expectedMatrixC, matrixC);
}

TEST(GslTest, MatrixMultiplicationWithRandomNumbersInGslWorks) {
    constexpr int SIDE_SIZE = 3;
    AlbaMatrix<double> matrixA(SIDE_SIZE, SIDE_SIZE, {0.11, 0.12, 0.13, 0.21, 0.22, 0.23});
    AlbaMatrix<double> matrixB(SIDE_SIZE, SIDE_SIZE, {1011, 1012, 1021, 1022, 1031, 1032});
    AlbaMatrix<double> matrixC(SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view matrixViewB = gsl_matrix_view_array(matrixB.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view matrixViewC = gsl_matrix_view_array(matrixC.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    // Fill the matrices with random numbers.
    AlbaUniformNonDeterministicRandomizer<double> randomizer(0, 100);
    for (int index = 0; index < SIDE_SIZE; ++index) {
        for (int index2 = 0; index2 < SIDE_SIZE; ++index2) {
            matrixA.setEntry(index, index2, randomizer.getRandomValue());
            matrixB.setEntry(index, index2, randomizer.getRandomValue());
        }
    }

    // Multiply the matrices.
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &matrixViewA.matrix, &matrixViewB.matrix, 0.0, &matrixViewC.matrix);

    // Check that the product is correct.
    for (int index = 0; index < SIDE_SIZE; ++index) {
        for (int index2 = 0; index2 < SIDE_SIZE; ++index2) {
            double expectedCEntry = 0.0;
            for (int k = 0; k < SIDE_SIZE; ++k) {
                expectedCEntry += matrixA.getEntry(k, index) * matrixB.getEntry(index2, k);
            }
            EXPECT_EQ(matrixC.getEntry(index2, index), expectedCEntry);
        }
    }
}

TEST(GslTest, SolvingLinearSystemInGslWorks) {
    // This solves the linear system Ax = b.

    AlbaMatrix<double> matrixA(
        4, 4, {0.18, 0.60, 0.57, 0.96, 0.41, 0.24, 0.99, 0.58, 0.14, 0.30, 0.97, 0.66, 0.51, 0.13, 0.19, 0.85});
    vector<double> vectorB{1.0, 2.0, 3.0, 4.0};
    vector<double> vectorX{0.0, 0.0, 0.0, 0.0};
    gsl_matrix_view matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), 4, 4);
    gsl_vector_view vectorViewB = gsl_vector_view_array(vectorB.data(), 4);
    gsl_vector_view vectorViewX = gsl_vector_view_array(vectorX.data(), 4);
    int signum{};
    gsl_permutation *permutation = gsl_permutation_alloc(4);

    gsl_linalg_LU_decomp(&matrixViewA.matrix, permutation, &signum);
    gsl_linalg_LU_solve(&matrixViewA.matrix, permutation, &vectorViewB.vector, &vectorViewX.vector);

    vector<double> expectedVectorX{-4.0520502295739744, -12.605611395906907, 1.6609116267088422, 8.6937669287952293};
    EXPECT_EQ(expectedVectorX, vectorX);
    gsl_permutation_free(permutation);
}

TEST(GslTest, GettingEigenValuesAndVectorInGslWorks) {
    // This computes the eigenvalues and eigenvectors of the 4-th order Hilbert matrix, H(index,index2) = 1/(index
    // +index2 + 1).

    AlbaMatrix<double> matrixHilbert(
        4, 4,
        {1.0, 1 / 2.0, 1 / 3.0, 1 / 4.0, 1 / 2.0, 1 / 3.0, 1 / 4.0, 1 / 5.0, 1 / 3.0, 1 / 4.0, 1 / 5.0, 1 / 6.0,
         1 / 4.0, 1 / 5.0, 1 / 6.0, 1 / 7.0});
    vector<double> eigenValues{0.0, 0.0, 0.0, 0.0};
    AlbaMatrix<double> eigenVectors(4, 4);
    gsl_matrix_view matrixViewHilbert = gsl_matrix_view_array(matrixHilbert.getMatrixDataReference().data(), 4, 4);
    gsl_vector_view eigenValuesView = gsl_vector_view_array(eigenValues.data(), 4);
    gsl_matrix_view eigenVectorsView = gsl_matrix_view_array(eigenVectors.getMatrixDataReference().data(), 4, 4);

    gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(4);
    gsl_eigen_symmv(&matrixViewHilbert.matrix, &eigenValuesView.vector, &eigenVectorsView.matrix, workspace);
    gsl_eigen_symmv_free(workspace);
    gsl_eigen_symmv_sort(&eigenValuesView.vector, &eigenVectorsView.matrix, GSL_EIGEN_SORT_ABS_ASC);

    vector<double> expectedEigenValues{
        9.6702304022603313e-05, 0.0067382736057606408, 0.16914122022144978, 1.5002142800592426};
    AlbaMatrix<double> expectedEigenVectors(
        4, 4,
        {-0.029193323164787031432, -0.17918629053545487295, 0.58207569949723725333, 0.79260829116376363412,
         0.32871205576319251218, 0.74191779062845186754, -0.37050218506709270416, 0.45192312090159986182,
         -0.79141114583312643926, -0.1002281369471880873, -0.50957863450179985421, 0.32241639858182497003,
         0.5145527499971501717, -0.63828252819361663839, -0.5140482722221645373, 0.25216116968824192623});
    EXPECT_EQ(expectedEigenVectors, eigenVectors);
    EXPECT_EQ(expectedEigenValues, eigenValues);
}

TEST(GslTest, FastFourierTransformInGslWorks) {
    // This is an using gsl_fft_real_transform() and gsl_fft_halfcomplex_inverse().
    // It generates a real signal in the shape of a square pulse.
    // The pulse is Fourier transformed to frequency space, and all but the lowest ten frequency components are removed
    // from the array of Fourier coefficients returned by gsl_fft_real_transform().
    // The remaining Fourier coefficients are transformed back to the time-domain,
    // to give a filtered version of the square pulse.
    // Since Fourier coefficients are stored using the half-complex symmetry both positive and negative
    // frequencies are removed and the final filtered signal is also real.

    constexpr int NUMBER_OF_ITEMS = 100;
    array<double, NUMBER_OF_ITEMS> inputData{};
    gsl_fft_real_workspace *workspace = gsl_fft_real_workspace_alloc(NUMBER_OF_ITEMS);
    int index{};
    for (index = 0; index < NUMBER_OF_ITEMS; ++index) {
        inputData[index] = 0.0;
    }
    for (index = NUMBER_OF_ITEMS / 3; index < 2 * NUMBER_OF_ITEMS / 3; ++index) {
        inputData[index] = 1.0;
    }
    for (index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << index << ": " << inputData[index] << ", ";
    }
    cout << "\n";

    gsl_fft_real_wavetable *real = gsl_fft_real_wavetable_alloc(NUMBER_OF_ITEMS);
    gsl_fft_real_transform(inputData.data(), 1, NUMBER_OF_ITEMS, real, workspace);
    gsl_fft_real_wavetable_free(real);
    for (index = 11; index < NUMBER_OF_ITEMS; ++index) {
        inputData[index] = 0;
    }

    gsl_fft_halfcomplex_wavetable *halfComplex = gsl_fft_halfcomplex_wavetable_alloc(NUMBER_OF_ITEMS);
    gsl_fft_halfcomplex_inverse(inputData.data(), 1, NUMBER_OF_ITEMS, halfComplex, workspace);
    gsl_fft_halfcomplex_wavetable_free(halfComplex);
    for (index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << index << ": " << inputData[index] << ", ";
    }
    cout << "\n";

    gsl_fft_real_workspace_free(workspace);
}

double function1ToIntegrate(double inputValue, void *parameters) {
    double alpha = *static_cast<double *>(parameters);
    return log(alpha * inputValue) / sqrt(inputValue);
}

TEST(GslTest, NumericalAdaptiveIntegrationInGslWorks) {
    // This uses adaptive integration to integrate.
    // The integrator QAGS will handle a large class of definite integrals.
    // For example, consider the following integral, which has an algebraic-logarithmic singularity at the origin,
    // integrate(x^(-1/2) * log(x) dx) evaluated from 1 to 0 = -4
    // The program below computes this integral to a relative accuracy bound of 1e-7.

    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(1000);
    double estimatedError{};
    double alpha = 1.0;
    gsl_function gslFunction{};
    gslFunction.function = &function1ToIntegrate;
    gslFunction.params = &alpha;

    double actualValue{};
    gsl_integration_qags(&gslFunction, 0, 1, 0, 1e-7, 1000, workspace, &actualValue, &estimatedError);

    double expectedValue = -4.0;
    cout << "actualValue = " << actualValue << "\n";
    cout << "expectedValue = " << expectedValue << "\n";
    cout << "estimatedError = " << estimatedError << "\n";
    cout << "actualError = " << actualValue - expectedValue << "\n";
    cout << "intervals = " << workspace->size << "\n";
    EXPECT_TRUE(isAlmostEqual(expectedValue, actualValue, AlbaMathConstants::COMPARISON_TOLERANCE_FOR_FLOAT));

    gsl_integration_workspace_free(workspace);
}

double function2ToIntegrate(double inputValue, void *parameters) {
    int mFunctionInput = *static_cast<int *>(parameters);
    return gsl_pow_int(inputValue, mFunctionInput) + 1.0;
}

TEST(GslTest, NumericalFixedPointQuadratureIntegrationInGslWorks) {
    // This uses a fixed-point quadrature rule to integrate.
    // Consulting our table of fixed point quadratures,
    // we see that this integral can be evaluated with a Hermite uadrature rule, setting  = 0; a = 0; b = 1.
    // Since we are integrating a polynomial of degree m,
    // we need to choose the number of nodes n  (m + 1) = 2 to achieve the best results.

    constexpr int numberOfQuadratureNodes = 6;
    const gsl_integration_fixed_type *integrationType = gsl_integration_fixed_hermite;
    gsl_integration_fixed_workspace *workspace =
        gsl_integration_fixed_alloc(integrationType, numberOfQuadratureNodes, 0.0, 1.0, 0.0, 0.0);
    int mFunctionInput = 10;
    double actualValue{};
    gsl_function gslFunction{};
    gslFunction.function = &function2ToIntegrate;
    gslFunction.params = &mFunctionInput;

    gsl_integration_fixed(&gslFunction, &actualValue, workspace);

    double expectedValue = (mFunctionInput % 2 == 0) ? M_SQRTPI + gsl_sf_gamma(0.5 * (1.0 + mFunctionInput)) : M_SQRTPI;
    cout << "mFunctionInput = " << mFunctionInput << "\n";
    cout << "intervals = " << gsl_integration_fixed_n(workspace) << "\n";
    cout << "actualValue = " << actualValue << "\n";
    cout << "expectedValue = " << expectedValue << "\n";
    cout << "actualError = " << actualValue - expectedValue << "\n";
    EXPECT_TRUE(isAlmostEqual(expectedValue, actualValue, AlbaMathConstants::COMPARISON_TOLERANCE_FOR_FLOAT));

    gsl_integration_fixed_free(workspace);
}

TEST(GslTest, UsingARandomGeneratorInGslWorks) {
    // This demonstrates the use of a random number generator
    // to produce uniform random numbers in the range [0.0, 1.0),

    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng_env_setup();
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    int NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << gsl_rng_uniform(randomGenerator) << ",";
    }
    cout << "\n";

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, UsingAQuasiRandomGeneratorInGslWorks) {
    // The following program prints the first 10 points of the 2-dimensional Sobol sequence.

    gsl_qrng *quasiRandomSequenceGenerator = gsl_qrng_alloc(gsl_qrng_sobol, 2);
    std::array<double, 2> randomValues{};
    for (int index = 0; index < 10; ++index) {
        gsl_qrng_get(quasiRandomSequenceGenerator, randomValues.data());
        cout << randomValues[0] << " " << randomValues[1] << ",";
    }
    cout << "\n";

    gsl_qrng_free(quasiRandomSequenceGenerator);
}
