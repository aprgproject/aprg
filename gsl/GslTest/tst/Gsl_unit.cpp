#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_bspline.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_combination.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_filter.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_vegas.h>
#include <gsl/gsl_movstat.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_multilarge.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_multiset.h>
#include <gsl/gsl_ntuple.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_qrng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_rstat.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_siman.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_sort_double.h>
#include <gsl/gsl_splinalg.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_sum.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_wavelet.h>
#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <iterator>
#include <vector>

using namespace alba::mathHelper;
using namespace alba::matrix;
using namespace std;

namespace alba {

TEST(GslTest, GettingTheBesselFunctionInGslWorks) {
    constexpr double xValue = 5.0;
    double const yValue = gsl_sf_bessel_J0(xValue);

    EXPECT_DOUBLE_EQ(-0.17759677131433830434739701, yValue);
}

TEST(GslTest, PolynomialRootFindingInGslWorks) {
    // To demonstrate the use of the general polynomial solver we will take the polynomial P(x) = x^5 - 1
    // which has these roots: 1; e^(2*pi*index/5); e^(4*pi*index/5); e^(6*pi*index/5); e^(8*pi*index/5)
    // coefficients of P(x) = -1 + x^5
    constexpr int NUMBER_OF_COEFFICIENTS = 6;
    array<double, NUMBER_OF_COEFFICIENTS> coefficients = {-1, 0, 0, 0, 0, 1};
    array<double, 10> rootArray{};

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
    using PermutationVector = vector<int>;
    constexpr int NUMBER_OF_DIGITS = 5;
    gsl_permutation *permutation1 = gsl_permutation_alloc(NUMBER_OF_DIGITS);
    gsl_permutation *permutation2 = gsl_permutation_alloc(NUMBER_OF_DIGITS);

    gsl_permutation_init(permutation1);
    PermutationVector const initialPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector const expectedInitialPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedInitialPermutation, initialPermutation);

    gsl_permutation_next(permutation1);
    PermutationVector const nextPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector const expectedNextPermutation{0, 1, 2, 4, 3};
    EXPECT_EQ(expectedNextPermutation, nextPermutation);

    gsl_permutation_prev(permutation1);
    PermutationVector const prevPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector const expectedPrevPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedPrevPermutation, prevPermutation);

    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_inverse(permutation2, permutation1);
    // The inverse of a permutation is another permutation that,
    // when composed with the original permutation, results in the identity permutation
    PermutationVector const inversePermutation(permutation2->data, permutation2->data + permutation2->size);
    PermutationVector const expectedInversePermutation{0, 1, 4, 2, 3};
    EXPECT_EQ(expectedInversePermutation, inversePermutation);

    gsl_permutation_free(permutation1);
    gsl_permutation_free(permutation2);
}

TEST(GslTest, GettingRandomPermutationsInGslWorks) {
    constexpr int NUMBER_OF_DIGITS = 5;
    gsl_permutation *permutation1 = gsl_permutation_alloc(NUMBER_OF_DIGITS);

    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);

    gsl_permutation_init(permutation1);
    gsl_ran_shuffle(randomGenerator, permutation1->data, NUMBER_OF_DIGITS, sizeof(int));
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
    constexpr int stride = 1;
    array<double, NUMBER_OF_VALUES> values{3, 8, 4, 5, 1, 7, 9, 0, 2, 6};
    array<double, NUMBER_OF_SMALLEST_VALUES> smallestValues{};

    gsl_sort_smallest(smallestValues.data(), NUMBER_OF_SMALLEST_VALUES, values.data(), stride, NUMBER_OF_VALUES);

    decltype(smallestValues) const expectedSmallestValues{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedSmallestValues, smallestValues);
}

TEST(GslTest, MatrixMultiplicationInGslWorks) {
    // Thi computes the product of two matrices using the Level-3 BLAS function DGEMM.
    // Create two matrices.
    AlbaMatrix<double> matrixA(3, 2, {0.11, 0.12, 0.13, 0.21, 0.22, 0.23});
    AlbaMatrix<double> matrixB(2, 3, {1011, 1012, 1021, 1022, 1031, 1032});
    AlbaMatrix<double> matrixC(2, 2, {0.00, 0.00, 0.00, 0.00});
    gsl_matrix_view const matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), 2, 3);
    gsl_matrix_view const matrixViewB = gsl_matrix_view_array(matrixB.getMatrixDataReference().data(), 3, 2);
    gsl_matrix_view matrixViewC = gsl_matrix_view_array(matrixC.getMatrixDataReference().data(), 2, 2);

    // Compute C = A * B
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &matrixViewA.matrix, &matrixViewB.matrix, 0.0, &matrixViewC.matrix);

    AlbaMatrix<double> const expectedMatrixC(2, 2, {367.76, 368.12, 674.06, 674.72});
    EXPECT_EQ(expectedMatrixC, matrixC);
}

TEST(GslTest, MatrixMultiplicationWithRandomNumbersInGslWorks) {
    constexpr int SIDE_SIZE = 3;
    AlbaMatrix<double> matrixA(SIDE_SIZE, SIDE_SIZE, {0.11, 0.12, 0.13, 0.21, 0.22, 0.23});
    AlbaMatrix<double> matrixB(SIDE_SIZE, SIDE_SIZE, {1011, 1012, 1021, 1022, 1031, 1032});
    AlbaMatrix<double> matrixC(SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view const matrixViewA =
        gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view const matrixViewB =
        gsl_matrix_view_array(matrixB.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
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
    array<double, 4> vectorB{1.0, 2.0, 3.0, 4.0};
    array<double, 4> vectorX{0.0, 0.0, 0.0, 0.0};
    gsl_matrix_view matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), 4, 4);
    gsl_vector_view const vectorViewB = gsl_vector_view_array(vectorB.data(), 4);
    gsl_vector_view vectorViewX = gsl_vector_view_array(vectorX.data(), 4);
    int signum{};
    gsl_permutation *permutation = gsl_permutation_alloc(4);

    gsl_linalg_LU_decomp(&matrixViewA.matrix, permutation, &signum);
    gsl_linalg_LU_solve(&matrixViewA.matrix, permutation, &vectorViewB.vector, &vectorViewX.vector);

    array<double, 4> const expectedVectorX{
        -4.0520502295739744, -12.605611395906907, 1.6609116267088422, 8.6937669287952293};
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
    array<double, 4> eigenValues{0.0, 0.0, 0.0, 0.0};
    AlbaMatrix<double> eigenVectors(4, 4);
    gsl_matrix_view matrixViewHilbert = gsl_matrix_view_array(matrixHilbert.getMatrixDataReference().data(), 4, 4);
    gsl_vector_view eigenValuesView = gsl_vector_view_array(eigenValues.data(), 4);
    gsl_matrix_view eigenVectorsView = gsl_matrix_view_array(eigenVectors.getMatrixDataReference().data(), 4, 4);

    gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(4);
    gsl_eigen_symmv(&matrixViewHilbert.matrix, &eigenValuesView.vector, &eigenVectorsView.matrix, workspace);
    gsl_eigen_symmv_free(workspace);
    gsl_eigen_symmv_sort(&eigenValuesView.vector, &eigenVectorsView.matrix, GSL_EIGEN_SORT_ABS_ASC);

    array<double, 4> const expectedEigenValues{
        9.6702304022603313e-05, 0.0067382736057606408, 0.16914122022144978, 1.5002142800592426};
    AlbaMatrix<double> const expectedEigenVectors(
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

namespace {

double function1ToIntegrate(double const inputValue, void *parameters) {
    double const alpha = *static_cast<double *>(parameters);
    return log(alpha * inputValue) / sqrt(inputValue);
}

}  // namespace

TEST(GslTest, NumericalAdaptiveIntegrationInGslWorks) {
    // This uses adaptive integration to integrate.
    // The integrator QAGS will handle a large class of definite integrals.
    // For example, consider the following integral, which has an algebraic-logarithmic singularity at the origin,
    // integrate(x^(-1/2) * log(x) dx) evaluated from 1 to 0 = -4
    // The program below computes this integral to a relative accuracy bound of 1e-7.
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(100);
    double estimatedError{};
    double alpha = 1.0;
    gsl_function gslFunction{};
    gslFunction.function = &function1ToIntegrate;
    gslFunction.params = &alpha;

    double actualValue{};
    gsl_integration_qags(&gslFunction, 0, 1, 0, 1e-7, 100, workspace, &actualValue, &estimatedError);

    double const expectedValue = -4.0;
    cout << "actualValue = " << actualValue << "\n";
    cout << "expectedValue = " << expectedValue << "\n";
    cout << "estimatedError = " << estimatedError << "\n";
    cout << "actualError = " << actualValue - expectedValue << "\n";
    cout << "intervals = " << workspace->size << "\n";
    EXPECT_TRUE(isAlmostEqual(expectedValue, actualValue, AlbaMathConstants::COMPARISON_TOLERANCE_FOR_FLOAT));

    gsl_integration_workspace_free(workspace);
}

namespace {

double function2ToIntegrate(double const inputValue, void *parameters) {
    int const mFunctionInput = *static_cast<int *>(parameters);
    return gsl_pow_int(inputValue, mFunctionInput) + 1.0;
}

}  // namespace

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

    double const expectedValue =
        (mFunctionInput % 2 == 0) ? M_SQRTPI + gsl_sf_gamma(0.5 * (1.0 + mFunctionInput)) : M_SQRTPI;
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
    constexpr int NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << gsl_rng_uniform(randomGenerator) << ",";
    }
    cout << "\n";

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, UsingAQuasiRandomGeneratorInGslWorks) {
    // The following program prints the first 10 points of the 2-dimensional Sobol sequence.
    gsl_qrng *quasiRandomSequenceGenerator = gsl_qrng_alloc(gsl_qrng_sobol, 2);
    array<double, 2> randomValues{};
    for (int index = 0; index < 10; ++index) {
        gsl_qrng_get(quasiRandomSequenceGenerator, randomValues.data());
        cout << randomValues[0] << " " << randomValues[1] << ",";
    }
    cout << "\n";

    gsl_qrng_free(quasiRandomSequenceGenerator);
}

TEST(GslTest, UsingARandomGeneratorWithPoissonDistributionWorks) {
    // The following program demonstrates the use of a random number generator to produce variates from a distribution.
    // It prints 10 samples from the Poisson distribution with a mean of 3.
    constexpr double mu = 3.0;
    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    constexpr int NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << gsl_ran_poisson(randomGenerator, mu) << ",";
    }
    cout << "\n";

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, UsingARandomGeneratorWithTwoDimensionsWorks) {
    // This demonstrates the use of a random number generator to produce variates from a distribution.
    // It prints 10 samples from the Poisson distribution with a mean of 3.
    double x = 0;
    double y = 0;
    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    constexpr int NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        double dx = 0;
        double dy = 0;
        gsl_ran_dir_2d(randomGenerator, &dx, &dy);
        x += dx;
        y += dy;
        cout << "(" << x << "," << y << "), ";
    }
    cout << "\n";

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, GettingPdfAnCdfWorks) {
    // This computes the upper and lower cumulative distribution functions for the standard normal distribution at x
    // = 2.
    double x = 2.0;
    double const P = gsl_cdf_ugaussian_P(x);
    cout << "prob(x < " << x << ") = " << P << "\n";
    EXPECT_DOUBLE_EQ(0.97724986805182079, P);

    double const Q = gsl_cdf_ugaussian_Q(x);
    cout << "prob(x > " << x << ") = " << Q << "\n";
    EXPECT_DOUBLE_EQ(0.022750131948179212, Q);

    x = gsl_cdf_ugaussian_Pinv(P);
    cout << "Pinv(" << P << ") = " << x << "\n";
    EXPECT_DOUBLE_EQ(2, x);

    x = gsl_cdf_ugaussian_Qinv(Q);
    cout << "Qinv(" << Q << ") = " << x << "\n";
    EXPECT_DOUBLE_EQ(2, x);
}

TEST(GslTest, GettingStatisticsWorks) {
    // This is a basic example of how to use the statistical functions
    array<double, 5> values = {17.2, 18.1, 16.5, 18.3, 12.6};

    double const mean = gsl_stats_mean(values.data(), 1, 5);
    cout << "The sample mean is " << mean << "\n";
    EXPECT_DOUBLE_EQ(16.539999999999999, mean);

    double const variance = gsl_stats_variance(values.data(), 1, 5);
    cout << "The estimated variance is " << variance << "\n";
    EXPECT_DOUBLE_EQ(5.373, variance);

    double const largest = gsl_stats_max(values.data(), 1, 5);
    cout << "The largest value is " << largest << "\n";
    EXPECT_DOUBLE_EQ(18.3, largest);

    double const smallest = gsl_stats_min(values.data(), 1, 5);
    cout << "The smallest value is " << smallest << "\n";
    EXPECT_DOUBLE_EQ(12.6, smallest);
}

TEST(GslTest, GettingStatisticsInSortedDAtaWorks) {
    // This is an example using sorted data
    array<double, 5> values = {17.2, 18.1, 16.5, 18.3, 12.6};
    gsl_sort(values.data(), 1, 5);

    double const median = gsl_stats_median_from_sorted_data(values.data(), 1, 5);
    cout << "The median is " << median << "\n";
    EXPECT_DOUBLE_EQ(17.199999999999999, median);

    double const upperq = gsl_stats_quantile_from_sorted_data(values.data(), 1, 5, 0.75);
    cout << "The upper quartile is " << upperq << "\n";
    EXPECT_DOUBLE_EQ(18.100000000000001, upperq);

    double const lowerq = gsl_stats_quantile_from_sorted_data(values.data(), 1, 5, 0.25);
    cout << "The lower quartile is " << lowerq << "\n";
    EXPECT_DOUBLE_EQ(16.5, lowerq);
}

TEST(GslTest, GettingRunningStatisticsWorks) {
    // This is a basic example of how to use the running statistical functions
    array<double, 5> const values = {17.2, 18.1, 16.5, 18.3, 12.6};

    gsl_rstat_workspace *runningStatistics = gsl_rstat_alloc();

    // add data to rstat accumulator
    for (double const value : values) {
        gsl_rstat_add(value, runningStatistics);
    }

    double const mean = gsl_rstat_mean(runningStatistics);
    cout << "The sample mean is " << mean << "\n";
    EXPECT_DOUBLE_EQ(16.539999999999999, mean);

    double const variance = gsl_rstat_variance(runningStatistics);
    cout << "The estimated variance is " << variance << "\n";
    EXPECT_DOUBLE_EQ(5.3729999999999984, variance);

    double const largest = gsl_rstat_max(runningStatistics);
    cout << "The largest value is " << largest << "\n";
    EXPECT_DOUBLE_EQ(18.300000000000001, largest);

    double const smallest = gsl_rstat_min(runningStatistics);
    cout << "The smallest value is " << smallest << "\n";
    EXPECT_DOUBLE_EQ(12.6, smallest);

    double const median = gsl_rstat_median(runningStatistics);
    cout << "The median is " << median << "\n";
    EXPECT_DOUBLE_EQ(17.199999999999999, median);

    double const sd = gsl_rstat_sd(runningStatistics);
    cout << "The standard deviation is " << sd << "\n";
    EXPECT_DOUBLE_EQ(2.3179732526498227, sd);

    double const sdMean = gsl_rstat_sd_mean(runningStatistics);
    cout << "The standard devation of the mean is " << sdMean << "\n";
    EXPECT_DOUBLE_EQ(1.0366291525902596, sdMean);

    double const skew = gsl_rstat_skew(runningStatistics);
    cout << "The skew is " << skew << "\n";
    EXPECT_DOUBLE_EQ(-0.82905750003696543, skew);

    double const rms = gsl_rstat_rms(runningStatistics);
    cout << "The root mean square is " << rms << "\n";
    EXPECT_DOUBLE_EQ(16.669433103738111, rms);

    double const kurtosis = gsl_rstat_kurtosis(runningStatistics);
    cout << "The kurtosis " << kurtosis << "\n";
    EXPECT_DOUBLE_EQ(-1.2217029020861698, kurtosis);

    auto n = gsl_rstat_n(runningStatistics);
    cout << "There are " << n << " items in the accumulator\n";
    gsl_rstat_reset(runningStatistics);
    EXPECT_DOUBLE_EQ(5, n);

    n = gsl_rstat_n(runningStatistics);
    cout << "There are " << n << " items in the accumulator\n";
    gsl_rstat_free(runningStatistics);
    EXPECT_DOUBLE_EQ(0, n);
}

TEST(GslTest, GettingMovingStatisticsWorks) {
    // The following example program computes the moving mean, minimum and maximum of a noisy sinusoid signal of
    // length N = 500 with a symmetric moving window of size K = 11.
    constexpr int LENGTH_OF_TIME = 100;  // length of time series
    constexpr int WINDOW_SIZE = 6;       // window size
    array<double, LENGTH_OF_TIME> x{};
    array<double, LENGTH_OF_TIME> xMean{};
    array<double, LENGTH_OF_TIME> xMin{};
    array<double, LENGTH_OF_TIME> xMax{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view xMeanView = gsl_vector_view_array(xMean.data(), LENGTH_OF_TIME);
    gsl_vector_view xMinView = gsl_vector_view_array(xMin.data(), LENGTH_OF_TIME);
    gsl_vector_view xMaxView = gsl_vector_view_array(xMax.data(), LENGTH_OF_TIME);
    gsl_movstat_workspace *workspace = gsl_movstat_alloc(WINDOW_SIZE);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);

    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const xi = cos(4.0 * M_PI * i / static_cast<double>(LENGTH_OF_TIME));
        double const ei = gsl_ran_gaussian(randomGenerator, 0.1);
        gsl_vector_set(&xView.vector, i, xi + ei);
    }
    // compute moving statistics
    gsl_movstat_mean(GSL_MOVSTAT_END_PADVALUE, &xView.vector, &xMeanView.vector, workspace);
    gsl_movstat_minmax(GSL_MOVSTAT_END_PADVALUE, &xView.vector, &xMinView.vector, &xMaxView.vector, workspace);
    // print results
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        cout << i << "u " << gsl_vector_get(&xView.vector, i) << " " << gsl_vector_get(&xMeanView.vector, i) << " "
             << gsl_vector_get(&xMinView.vector, i) << " " << gsl_vector_get(&xMaxView.vector, i) << "\n";
    }

    gsl_rng_free(randomGenerator);
    gsl_movstat_free(workspace);
}

TEST(GslTest, GettingMovingStatisticsWorksOnGaussianRandomVariates) {
    // The following example program analyzes a time series of length N = 1000 composed of Gaussian random variates
    // with zero mean whose standard deviation changes in a piecewise constant fashion
    constexpr int LENGTH_OF_TIME = 100;                              // length of time series
    constexpr int WINDOW_SIZE = 6;                                   // window size
    constexpr array<double, 5> sigma = {1.0, 5.0, 1.0, 3.0, 5.0};    // variances
    constexpr array<double, 5> sigmaN = {200, 450, 600, 850, 1000};  // samples where variance, changes
    array<double, LENGTH_OF_TIME> x{};
    array<double, LENGTH_OF_TIME> xMedian{};
    array<double, LENGTH_OF_TIME> xMad{};
    array<double, LENGTH_OF_TIME> xIqr{};
    array<double, LENGTH_OF_TIME> xSn{};
    array<double, LENGTH_OF_TIME> xQn{};
    array<double, LENGTH_OF_TIME> xSd{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view xMedianView = gsl_vector_view_array(xMedian.data(), LENGTH_OF_TIME);
    gsl_vector_view xMadView = gsl_vector_view_array(xMad.data(), LENGTH_OF_TIME);
    gsl_vector_view xIqrView = gsl_vector_view_array(xIqr.data(), LENGTH_OF_TIME);
    gsl_vector_view xSnView = gsl_vector_view_array(xSn.data(), LENGTH_OF_TIME);
    gsl_vector_view xQnView = gsl_vector_view_array(xQn.data(), LENGTH_OF_TIME);
    gsl_vector_view xSdView = gsl_vector_view_array(xSd.data(), LENGTH_OF_TIME);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    gsl_movstat_workspace *workspace = gsl_movstat_alloc(WINDOW_SIZE);

    int idx = 0;
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const gi = gsl_ran_gaussian(randomGenerator, sigma[idx]);
        double const u = gsl_rng_uniform(randomGenerator);
        double const outlier = (u < 0.01) ? 15.0 * GSL_SIGN(gi) : 0.0;
        double const xi = gi + outlier;
        gsl_vector_set(&xView.vector, i, xi);
        if (i == sigmaN[idx] - 1) {
            ++idx;
        }
    }
    // compute moving statistics
    gsl_movstat_mad(GSL_MOVSTAT_END_TRUNCATE, &xView.vector, &xMedianView.vector, &xMadView.vector, workspace);
    gsl_movstat_qqr(GSL_MOVSTAT_END_TRUNCATE, &xView.vector, 0.25, &xIqrView.vector, workspace);
    gsl_movstat_Sn(GSL_MOVSTAT_END_TRUNCATE, &xView.vector, &xSnView.vector, workspace);
    gsl_movstat_Qn(GSL_MOVSTAT_END_TRUNCATE, &xView.vector, &xQnView.vector, workspace);
    gsl_movstat_sd(GSL_MOVSTAT_END_TRUNCATE, &xView.vector, &xSdView.vector, workspace);
    // scale IQR by factor to approximate standard deviation
    gsl_vector_scale(&xIqrView.vector, 0.7413);
    // print results
    idx = 0;
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        cout << i << "u " << gsl_vector_get(&xView.vector, i) << " " << sigma[idx] << " "
             << gsl_vector_get(&xMadView.vector, i) << " " << gsl_vector_get(&xIqrView.vector, i) << " "
             << gsl_vector_get(&xSnView.vector, i) << " " << gsl_vector_get(&xQnView.vector, i) << " "
             << gsl_vector_get(&xSdView.vector, i) << "\n";
        if (i == sigmaN[idx] - 1) {
            ++idx;
        }
    }

    gsl_rng_free(randomGenerator);
    gsl_movstat_free(workspace);
}

namespace {

double func(const size_t n, double x[], void *params) {
    double const alpha = *static_cast<double *>(params);
    gsl_sort(x, 1, n);
    return gsl_stats_trmean_from_sorted_data(alpha, x, 1, n);
}

}  // namespace

TEST(GslTest, GettingMovingStatisticsWorksOnUserDefinedMovingWindow) {
    // This example program illustrates how a user can define their own moving window function to apply to an input
    // vector. It constructs a random noisy time series of length N = 1000 with some outliers added. Then it applies a
    // moving window trimmed mean to the time series with trim parameter  = 0:1. The length of the moving window is K =
    // 11, so the smallest and largest sample of each window is discarded prior to computing the mean.
    constexpr int LENGTH_OF_TIME = 100;  // length of time series
    constexpr int WINDOW_SIZE = 6;       // window size
    double alpha = 0.1;                  // trimmed mean parameter
    array<double, LENGTH_OF_TIME> x{};   // input vector
    array<double, LENGTH_OF_TIME> y{};   // filtered output vector for alpha1
    gsl_vector_view xView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view yView = gsl_vector_view_array(y.data(), LENGTH_OF_TIME);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    gsl_movstat_workspace *workspace = gsl_movstat_alloc(WINDOW_SIZE);
    gsl_movstat_function F;

    double sum = 0.0;
    // generate input signal
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const ui = gsl_ran_gaussian(randomGenerator, 1.0);
        double const outlier = (gsl_rng_uniform(randomGenerator) < 0.01) ? 10.0 * GSL_SIGN(ui) : 0.0;
        sum += ui;
        gsl_vector_set(&xView.vector, i, sum + outlier);
    }
    // apply moving window function
    F.function = func;
    F.params = &alpha;
    gsl_movstat_apply(GSL_MOVSTAT_END_PADVALUE, &F, &xView.vector, &yView.vector, workspace);
    // print results
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const xi = gsl_vector_get(&xView.vector, i);
        double const yi = gsl_vector_get(&yView.vector, i);
        cout << xi << " " << yi << "\n";
    }

    gsl_rng_free(randomGenerator);
    gsl_movstat_free(workspace);
}

TEST(GslTest, GettingRunningStatisticsForQuantileWorks) {
    // This estimates the lower quartile, median and upper quartile from 100 samples of a random Rayleigh
    // distribution. This uses the P2 algorithm of Jain and Chlamtec. For comparison, the exact values are also computed
    // from the sorted dataset.
    array<double, 100> values = {};

    gsl_rstat_quantile_workspace *workspaceFor25 = gsl_rstat_quantile_alloc(0.25);
    gsl_rstat_quantile_workspace *workspaceFor50 = gsl_rstat_quantile_alloc(0.5);
    gsl_rstat_quantile_workspace *workspaceFor75 = gsl_rstat_quantile_alloc(0.75);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);

    // add data to quantile accumulators; also store data for exact comparisons
    for (double &value : values) {
        value = gsl_ran_rayleigh(randomGenerator, 1.0);
        gsl_rstat_quantile_add(value, workspaceFor25);
        gsl_rstat_quantile_add(value, workspaceFor50);
        gsl_rstat_quantile_add(value, workspaceFor75);
    }

    // exact values
    gsl_sort(values.data(), 1, values.size());
    double const exactFor25 =
        gsl_stats_quantile_from_sorted_data(values.data(), 1, static_cast<int>(values.size()), 0.25);
    double const exactFor50 =
        gsl_stats_quantile_from_sorted_data(values.data(), 1, static_cast<int>(values.size()), 0.5);
    double const exactFor75 =
        gsl_stats_quantile_from_sorted_data(values.data(), 1, static_cast<int>(values.size()), 0.75);

    // estimated values
    double const actualFor25 = gsl_rstat_quantile_get(workspaceFor25);
    double const actualFor50 = gsl_rstat_quantile_get(workspaceFor50);
    double const actualFor75 = gsl_rstat_quantile_get(workspaceFor75);
    cout << "0.25 quartile: exact = " << exactFor25 << ", estimated = " << actualFor25
         << ", error = " << (actualFor25 - exactFor25) / exactFor25 << "\n";
    cout << "0.50 quartile: exact = " << exactFor50 << ", estimated = " << actualFor50
         << ", error = " << (actualFor50 - exactFor50) / exactFor50 << "\n";
    cout << "0.75 quartile: exact = " << exactFor75 << ", estimated = " << actualFor75
         << ", error = " << (actualFor75 - exactFor75) / exactFor75 << "\n";

    gsl_rstat_quantile_free(workspaceFor25);
    gsl_rstat_quantile_free(workspaceFor50);
    gsl_rstat_quantile_free(workspaceFor75);
    gsl_rng_free(randomGenerator);
}

TEST(GslTest, GaussianFilterWorksInExample1) {
    // This illustrates the Gaussian filter applied to smoothing a time series of lengthN = 500 with a
    // kernel size of K = 51. Three filters are applied with parameters  = 0:5; 3; 10. We see that the filter
    // corresponding to  = 0:5 applies the most smoothing, while  = 10 corresponds to the least amount of smoothing.
    constexpr int LENGTH_OF_TIME = 100;                   // length of time series
    constexpr int WINDOW_SIZE = 11;                       // window size
    constexpr array<double, 3> alpha = {0.5, 3.0, 10.0};  // alpha values
    array<double, LENGTH_OF_TIME> x{};                    // input vector
    array<double, LENGTH_OF_TIME> y1{};                   // filtered output vector for alpha1
    array<double, LENGTH_OF_TIME> y2{};                   // filtered output vector for alpha2
    array<double, LENGTH_OF_TIME> y3{};                   // filtered output vector for alpha3
    array<double, LENGTH_OF_TIME> k1{};                   // Gaussian kernel for alpha1
    array<double, LENGTH_OF_TIME> k2{};                   // Gaussian kernel for alpha2
    array<double, LENGTH_OF_TIME> k3{};                   // Gaussian kernel for alpha3
    gsl_vector_view xView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view y1View = gsl_vector_view_array(y1.data(), LENGTH_OF_TIME);
    gsl_vector_view y2View = gsl_vector_view_array(y2.data(), LENGTH_OF_TIME);
    gsl_vector_view y3View = gsl_vector_view_array(y3.data(), LENGTH_OF_TIME);
    gsl_vector_view k1View = gsl_vector_view_array(k1.data(), LENGTH_OF_TIME);
    gsl_vector_view k2View = gsl_vector_view_array(k2.data(), LENGTH_OF_TIME);
    gsl_vector_view k3View = gsl_vector_view_array(k3.data(), LENGTH_OF_TIME);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    gsl_filter_gaussian_workspace *gaussWorkspace = gsl_filter_gaussian_alloc(WINDOW_SIZE);

    double sum = 0.0;
    // generate input signal
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const ui = gsl_ran_gaussian(randomGenerator, 1.0);
        sum += ui;
        gsl_vector_set(&xView.vector, i, sum);
    }
    // compute kernels without normalization
    gsl_filter_gaussian_kernel(alpha[0], 0, 0, &k1View.vector);
    gsl_filter_gaussian_kernel(alpha[1], 0, 0, &k2View.vector);
    gsl_filter_gaussian_kernel(alpha[2], 0, 0, &k3View.vector);
    // apply filters
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[0], 0, &xView.vector, &y1View.vector, gaussWorkspace);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[1], 0, &xView.vector, &y2View.vector, gaussWorkspace);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[2], 0, &xView.vector, &y3View.vector, gaussWorkspace);
    // print kernels
    for (int i = 0; i < WINDOW_SIZE; ++i) {
        double const k1i = gsl_vector_get(&k1View.vector, i);
        double const k2i = gsl_vector_get(&k2View.vector, i);
        double const k3i = gsl_vector_get(&k3View.vector, i);
        cout << k1i << " " << k2i << " " << k3i << "\n";
    }
    cout << "\n\n";
    // print filter results
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const xi = gsl_vector_get(&xView.vector, i);
        double const y1i = gsl_vector_get(&y1View.vector, i);
        double const y2i = gsl_vector_get(&y2View.vector, i);
        double const y3i = gsl_vector_get(&y3View.vector, i);
        cout << xi << " " << y1i << " " << y2i << " " << y3i << "\n";
    }

    gsl_rng_free(randomGenerator);
    gsl_filter_gaussian_free(gaussWorkspace);
}

TEST(GslTest, GaussianFilterWorksInExample2) {
    // A common application of the Gaussian filter is to detect edges, or sudden jumps, in a noisy input signal.
    // It is used both for 1D edge detection in time series, as well as 2D edge detection in images.
    // Here we will examine a noisy time series of length N = 1000 with a single edge.
    constexpr int LENGTH_OF_TIME = 100;   // length of time series
    constexpr int WINDOW_SIZE = 11;       // window size
    constexpr double alpha = 3.0;         // Gaussian kernel has +/- 3 standard deviations
    array<double, LENGTH_OF_TIME> x{};    // input vector
    array<double, LENGTH_OF_TIME> y{};    // filtered output vector
    array<double, LENGTH_OF_TIME> dy{};   // first derivative filtered vector
    array<double, LENGTH_OF_TIME> d2y{};  // second derivative filtered vector
    gsl_vector_view xView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view yView = gsl_vector_view_array(y.data(), LENGTH_OF_TIME);
    gsl_vector_view dyView = gsl_vector_view_array(dy.data(), LENGTH_OF_TIME);
    gsl_vector_view d2yView = gsl_vector_view_array(d2y.data(), LENGTH_OF_TIME);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    gsl_filter_gaussian_workspace *gaussWorkspace = gsl_filter_gaussian_alloc(WINDOW_SIZE);

    // generate input signal
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const xi = (i > LENGTH_OF_TIME / 2) ? 0.5 : 0.0;
        double const ei = gsl_ran_gaussian(randomGenerator, 0.1);
        gsl_vector_set(&xView.vector, i, xi + ei);
    }
    // apply filters
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 0, &xView.vector, &yView.vector, gaussWorkspace);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 1, &xView.vector, &dyView.vector, gaussWorkspace);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 2, &xView.vector, &d2yView.vector, gaussWorkspace);
    // print results
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const xi = gsl_vector_get(&xView.vector, i);
        double const yi = gsl_vector_get(&yView.vector, i);
        double const dyi = gsl_vector_get(&dyView.vector, i);
        double const d2yi = gsl_vector_get(&d2yView.vector, i);
        double dxi = NAN;
        // compute finite difference of x vector
        if (i == 0) {
            dxi = gsl_vector_get(&xView.vector, i + 1) - xi;
        } else if (i == LENGTH_OF_TIME - 1) {
            dxi = gsl_vector_get(&xView.vector, i) - gsl_vector_get(&xView.vector, i - 1);
        } else {
            dxi = 0.5 * (gsl_vector_get(&xView.vector, i + 1) - gsl_vector_get(&xView.vector, i - 1));
        }
        cout << xi << " " << yi << " " << dxi << " " << dyi << " " << d2yi << "\n";
    }

    gsl_rng_free(randomGenerator);
    gsl_filter_gaussian_free(gaussWorkspace);
}

TEST(GslTest, MedianFilterWorksInSquareWaveSignalExample) {
    // The following example program illustrates the median filters on a noisy square wave signal. Median filters are
    // well known for preserving sharp edges in the input signal while reducing noise. The program constructs a 5 Hz
    // square wave signal with Gaussian noise added. Then the signal is filtered with a standard median filter and
    // recursive median filter using a symmetric window of length K = 7.
    constexpr int LENGTH_OF_TIME = 100;  // length of time series
    constexpr int WINDOW_SIZE = 7;       // window size
    constexpr double FREQUENCY = 5.0;    // frequency of square wave in Hz
    gsl_filter_median_workspace *medianWorkspace = gsl_filter_median_alloc(WINDOW_SIZE);
    gsl_filter_rmedian_workspace *rmedianWorkspace = gsl_filter_rmedian_alloc(WINDOW_SIZE);
    array<double, LENGTH_OF_TIME> t{};         // time
    array<double, LENGTH_OF_TIME> x{};         // input vector
    array<double, LENGTH_OF_TIME> yMedian{};   // median filtered output
    array<double, LENGTH_OF_TIME> yRMedian{};  // recursive median filtered output
    gsl_vector_view tView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view xView = gsl_vector_view_array(t.data(), LENGTH_OF_TIME);
    gsl_vector_view yMedianView = gsl_vector_view_array(yMedian.data(), LENGTH_OF_TIME);
    gsl_vector_view yRMedianView = gsl_vector_view_array(yRMedian.data(), LENGTH_OF_TIME);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);

    // generate input signal
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const ti = static_cast<double>(i) / (LENGTH_OF_TIME - 1.0);
        double const tmp = sin(2.0 * M_PI * FREQUENCY * ti);
        double const xi = (tmp >= 0.0) ? 1.0 : -1.0;
        double const ei = gsl_ran_gaussian(randomGenerator, 0.1);
        gsl_vector_set(&tView.vector, i, ti);
        gsl_vector_set(&xView.vector, i, xi + ei);
    }
    gsl_filter_median(GSL_FILTER_END_PADVALUE, &xView.vector, &yMedianView.vector, medianWorkspace);
    gsl_filter_rmedian(GSL_FILTER_END_PADVALUE, &xView.vector, &yRMedianView.vector, rmedianWorkspace);
    // print results
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const ti = gsl_vector_get(&tView.vector, i);
        double const xi = gsl_vector_get(&xView.vector, i);
        double const medi = gsl_vector_get(&yMedianView.vector, i);
        double const rmedi = gsl_vector_get(&yRMedianView.vector, i);
        cout << ti << " " << xi << " " << medi << " " << rmedi << "\n";
    }
    gsl_rng_free(randomGenerator);
    gsl_filter_rmedian_free(rmedianWorkspace);
    gsl_filter_median_free(medianWorkspace);
}

TEST(GslTest, ImpulseDetectionFilterWorksInSquareWaveSignalExample) {
    // The following example program illustrates the impulse detection filter.
    // First, it constructs a sinusoid signal of length N = 1000 with Gaussian noise added.
    // Then, about 1% of the data are perturbed to represent large outliers.
    // An impulse detecting filter is applied with a window size K = 25 and tuning parameter t = 4, using the Qn
    // statistic as the robust measure of scale.
    constexpr int LENGTH_OF_TIME = 100;       // length of time series
    constexpr int WINDOW_SIZE = 25;           // window size
    constexpr double t = 4.0;                 // number of scale factors for outlier detection
    array<double, LENGTH_OF_TIME> x{};        // input vector
    array<double, LENGTH_OF_TIME> y{};        // output (filtered) vector
    array<double, LENGTH_OF_TIME> xMedian{};  // window medians
    array<double, LENGTH_OF_TIME> xSigma{};   // window scale estimates
    gsl_vector_view xView = gsl_vector_view_array(x.data(), LENGTH_OF_TIME);
    gsl_vector_view yView = gsl_vector_view_array(y.data(), LENGTH_OF_TIME);
    gsl_vector_view xMedianView = gsl_vector_view_array(xMedian.data(), LENGTH_OF_TIME);
    gsl_vector_view xSigmaView = gsl_vector_view_array(xSigma.data(), LENGTH_OF_TIME);
    gsl_vector_int *ioutlier = gsl_vector_int_alloc(LENGTH_OF_TIME);  // outlier detected?
    gsl_filter_impulse_workspace *workspace = gsl_filter_impulse_alloc(WINDOW_SIZE);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);

    size_t noutlier = 0;
    // generate input signal
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double xi = 10.0 * sin(2.0 * M_PI * i / static_cast<double>(LENGTH_OF_TIME));
        double const ei = gsl_ran_gaussian(randomGenerator, 2.0);
        double const u = gsl_rng_uniform(randomGenerator);
        double const outlier = (u < 0.01) ? 15.0 * GSL_SIGN(ei) : 0.0;
        gsl_vector_set(&xView.vector, i, xi + ei + outlier);
    }
    // apply impulse detection filter
    gsl_filter_impulse(
        GSL_FILTER_END_TRUNCATE, GSL_FILTER_SCALE_QN, t, &xView.vector, &yView.vector, &xMedianView.vector,
        &xSigmaView.vector, &noutlier, ioutlier, workspace);
    // print results
    for (int i = 0; i < LENGTH_OF_TIME; ++i) {
        double const xi = gsl_vector_get(&xView.vector, i);
        double const yi = gsl_vector_get(&yView.vector, i);
        double const xmedi = gsl_vector_get(&xMedianView.vector, i);
        double const xsigmai = gsl_vector_get(&xSigmaView.vector, i);
        int const outlier = gsl_vector_int_get(ioutlier, i);
        cout << i << "u " << xi << " " << yi << " " << xmedi + t * xsigmai << " " << xmedi - t * xsigmai << " "
             << outlier << "\n";
    }

    gsl_vector_int_free(ioutlier);
    gsl_filter_impulse_free(workspace);
    gsl_rng_free(randomGenerator);
}

TEST(GslTest, DISABLED_OneDimensionalHistogramWorks) {
    // The following program shows how to make a simple histogram of a column of numerical data supplied on stdin. The
    // program takes three arguments, specifying the upper and lower bounds of the histogram and the number of bins. It
    // then reads numbers from stdin, one line at a time, and adds them to the histogram. When there is no more data to
    // read it prints out the accumulated histogram using gsl_histogram_fprintf().
    constexpr double MINIMUM_VALUE = -100;
    constexpr double MAXIMUM_VALUE = 100;
    constexpr size_t NUMBER_OF_BINS = 10;

    double x = 1;
    gsl_histogram *h = gsl_histogram_alloc(NUMBER_OF_BINS);
    gsl_histogram_set_ranges_uniform(h, MINIMUM_VALUE, MAXIMUM_VALUE);
    while (x == 1) {
        cin >> x;
        gsl_histogram_increment(h, x);
    }

    gsl_histogram_fprintf(stdout, h, "%g", "%g");
    gsl_histogram_free(h);
}

TEST(GslTest, TwoDimensionalHistogramWorks) {
    // This demonstrates two features of two-dimensional histograms.
    // First a 10-by-10 two-dimensional histogram is created with x and y running from 0 to 1.
    // Then a few sample points are added to the histogram, at (0.3,0.3) with a height of 1, at (0.8,0.1) with a height
    // of 5 and at (0.7,0.9) with a height of 0.5. This histogram with three events is used to generate a random sample
    // of 1000 simulated events, which are printed out.
    gsl_histogram2d *h = gsl_histogram2d_alloc(10, 10);
    gsl_histogram2d_set_ranges_uniform(h, 0.0, 1.0, 0.0, 1.0);
    gsl_histogram2d_accumulate(h, 0.3, 0.3, 1);
    gsl_histogram2d_accumulate(h, 0.8, 0.1, 5);
    gsl_histogram2d_accumulate(h, 0.7, 0.9, 0.5);

    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    {
        gsl_histogram2d_pdf *pdf = gsl_histogram2d_pdf_alloc(h->nx, h->ny);
        gsl_histogram2d_pdf_init(pdf, h);
        for (int i = 0; i < 100; ++i) {
            double x = NAN;
            double y = NAN;
            double const u = gsl_rng_uniform(randomGenerator);
            double const v = gsl_rng_uniform(randomGenerator);
            gsl_histogram2d_pdf_sample(pdf, u, v, &x, &y);
            cout << x << " " << y << "\n";
        }
        gsl_histogram2d_pdf_free(pdf);
    }

    gsl_histogram2d_free(h);
    gsl_rng_free(randomGenerator);
}

namespace {

struct nTupleData {
    double x;
    double y;
    double z;
};

double val_func(void *ntuple_data, void *) {
    auto *data = static_cast<struct nTupleData *>(ntuple_data);
    double x = NAN;
    double y = NAN;
    double z = NAN;
    x = data->x;
    y = data->y;
    z = data->z;
    return x * x + y * y + z * z;
}

int sel_func(void *ntuple_data, void *params) {
    auto *data = static_cast<struct nTupleData *>(ntuple_data);
    double x = NAN;
    double y = NAN;
    double z = NAN;
    double E2 = NAN;
    double scale = NAN;
    scale = *static_cast<double *>(params);
    x = data->x;
    y = data->y;
    z = data->z;
    E2 = x * x + y * y + z * z;
    return static_cast<int>(E2 > scale);
}

}  // namespace

TEST(GslTest, DISABLED_NTuplesWorks) {
    {
        // creates a set of 10,000 simulated “events”, each with 3 associated values (x; y; z).
        // These are generated from a Gaussian distribution with unit variance, for demonstration purposes, and written
        // to the ntuple file test.dat. This demonstrate the use of ntuples in managing a large dataset. The first
        // program
        nTupleData ntuple_row{};
        gsl_ntuple *ntuple = gsl_ntuple_create(const_cast<char *>("test.dat"), &ntuple_row, sizeof(ntuple_row));
        gsl_rng_env_setup();
        const gsl_rng_type *randomGeneratorType = gsl_rng_default;
        gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
        for (int i = 0; i < 100; ++i) {
            ntuple_row.x = gsl_ran_ugaussian(randomGenerator);
            ntuple_row.y = gsl_ran_ugaussian(randomGenerator);
            ntuple_row.z = gsl_ran_ugaussian(randomGenerator);
            gsl_ntuple_write(ntuple);
        }
        gsl_ntuple_close(ntuple);
        gsl_rng_free(randomGenerator);
    }

    {
        // squared magnitude of each event, E2 = x2 + y2 + z2, and select only those which exceed a lower limit of 1.5.
        // The selected events are then histogrammed using their E2 values.
        // This analyses the ntuple data in the file test.dat. The analysis procedure is to compute the
        nTupleData ntuple_row{};
        gsl_ntuple *ntuple = gsl_ntuple_open(const_cast<char *>("test.dat"), &ntuple_row, sizeof(ntuple_row));
        double lower = 1.5;
        gsl_ntuple_select_fn S;
        gsl_ntuple_value_fn V;
        gsl_histogram *h = gsl_histogram_alloc(100);
        gsl_histogram_set_ranges_uniform(h, 0.0, 10.0);
        S.function = &sel_func;
        S.params = &lower;
        V.function = &val_func;
        V.params = nullptr;
        gsl_ntuple_project(h, ntuple, &V, &S);
        gsl_histogram_fprintf(stdout, h, "%f", "%f");
        gsl_histogram_free(h);
        gsl_ntuple_close(ntuple);
    }
}

namespace {

// Computation of the integral,
// I = int (dx dy dz)/(2pi)^3 1/(1-cos(x)cos(y)cos(z))
// over (-pi,-pi,-pi) to (+pi, +pi, +pi). The exact answer
// is Gamma(1/4)^4/(4 pi^3). This example is taken from
// C.Itzykson, J.M.Drouffe, "Statistical Field Theory -
// Volume 1", Section 1.1, p21, which cites the original
// paper M.L.Glasser, I.J.Zucker, Proc.Natl.Acad.Sci.USA 74
// 1800 (1977)
// For simplicity we compute the integral over the region (0,0,0) -> (pi,pi,pi) and multiply by 8
double exact = 1.3932039296856768591842462603255;

double g(double *k, size_t const, void *) {
    double A = 1.0 / (M_PI * M_PI * M_PI);
    return A / (1.0 - cos(k[0]) * cos(k[1]) * cos(k[2]));
}

void display_results(char *title, double const result, double const error) {
    cout << title << " ==================\n";
    cout << "result = " << result << "\n";
    cout << "sigma = " << error << "\n";
    cout << "exact = " << exact << "\n";
    cout << "error = " << result - exact << " = " << fabs(result - exact) / error << " sigma\n";
}

}  // namespace

TEST(GslTest, MonteCarloRoutinesForIntegralWorks) {
    /// This uses the Monte Carlo routines to estimate the value of the following 3-dimensional integral from the theory
    /// of random walks.
    double res = 0, err = 0;
    array<double, 3> xl = {0, 0, 0};
    array<double, 3> xu = {M_PI, M_PI, M_PI};
    gsl_monte_function G = {&g, 3, nullptr};
    size_t calls = 100;
    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    {
        gsl_monte_plain_state *s = gsl_monte_plain_alloc(3);
        gsl_monte_plain_integrate(&G, xl.data(), xu.data(), 3, calls, randomGenerator, s, &res, &err);
        gsl_monte_plain_free(s);
        display_results(const_cast<char *>("plain"), res, err);
    }
    {
        gsl_monte_miser_state *s = gsl_monte_miser_alloc(3);
        gsl_monte_miser_integrate(&G, xl.data(), xu.data(), 3, calls, randomGenerator, s, &res, &err);
        gsl_monte_miser_free(s);
        display_results(const_cast<char *>("miser"), res, err);
    }
    {
        gsl_monte_vegas_state *s = gsl_monte_vegas_alloc(3);
        gsl_monte_vegas_integrate(&G, xl.data(), xu.data(), 3, 100, randomGenerator, s, &res, &err);
        display_results(const_cast<char *>("vegas warm-up"), res, err);
        cout << "converging...\n";
        bool isAcceptable = true;
        while (isAcceptable) {
            gsl_monte_vegas_integrate(&G, xl.data(), xu.data(), 3, calls / 5, randomGenerator, s, &res, &err);
            cout << "result = "
                 << "chisq/dof = %.1f\n"
                 << " sigma = " << res << " " << err << gsl_monte_vegas_chisq(s);
            isAcceptable = fabs(gsl_monte_vegas_chisq(s) - 1.0) > 0.5;
        }
        display_results(const_cast<char *>("vegas final"), res, err);
        gsl_monte_vegas_free(s);
    }
    gsl_rng_free(randomGenerator);
}

namespace {

// set up parameters for this simulated annealing run
constexpr int N_TRIES = 10;                    // how many points do we try before stepping
constexpr int ITERS_FIXED_T = 100;             // how many iterations for each T?
constexpr double STEP_SIZE = 1.0;              // max step size in random walk
constexpr double BOLTZMANN_CONSTANT = 1.0;     // Boltzmann constant
constexpr double INITIAL_TEMPERATURE = 0.008;  // initial temperature
constexpr double DUMPING_FACTOR = 1.003;       // damping factor for temperature
constexpr double MINIMUM_TEMPERATURE = 2.0e-6;

gsl_siman_params_t params = {N_TRIES,        ITERS_FIXED_T,      STEP_SIZE, BOLTZMANN_CONSTANT, INITIAL_TEMPERATURE,
                             DUMPING_FACTOR, MINIMUM_TEMPERATURE};

// now some functions to test in one dimension
double E1(void *xp) {
    double x = *static_cast<double *>(xp);
    return exp(-pow((x - 1.0), 2.0)) * sin(8 * x);
}

double M1(void *xp, void *yp) {
    double x = *static_cast<double *>(xp);
    double y = *static_cast<double *>(yp);
    return fabs(x - y);
}

void S1(const gsl_rng *randomGenerator, void *xp, double const step_size) {
    double old_x = *static_cast<double *>(xp);
    double new_x{};
    double u = gsl_rng_uniform(randomGenerator);
    new_x = u * 2 * step_size - step_size + old_x;
    memcpy(xp, &new_x, sizeof(new_x));
}

void P1(void *xp) { cout << *static_cast<double *>(xp) << ""; }

}  // namespace

TEST(GslTest, DISABLED_SimulatedAnnealingWorks) {
    // The goal is to find a point in the space at which a real valued energy function (or cost function) is minimized.
    // Simulated annealing is a minimization technique which has given good results in avoiding local minima; it is
    // based on the idea of taking a random walk through the space at successively lower temperatures, where the
    // probability of taking a step is given by a Boltzmann distribution.
    // This example, in one dimensional Cartesian space, sets up an energy function which is a damped sine wave; this
    // has many local minima, but only one global minimum, somewhere between 1.0 and 1.5. The initial guess given
    // is 15.5, which is several local minima away from the global minimum.
    double x_initial = 15.5;
    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    gsl_rng_free(randomGenerator);
    gsl_siman_solve(randomGenerator, &x_initial, E1, S1, M1, P1, nullptr, nullptr, nullptr, sizeof(double), params);
    gsl_rng_free(randomGenerator);
}

namespace {

int func(double const, double const y[], double f[], void *params) {
    double mu = *static_cast<double *>(params);
    f[0] = y[1];
    f[1] = -y[0] - mu * y[1] * (y[0] * y[0] - 1);
    return GSL_SUCCESS;
}

int jac(double const, double const y[], double *dfdy, double dfdt[], void *params) {
    double mu = *static_cast<double *>(params);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -2.0 * mu * y[0] * y[1] - 1.0);
    gsl_matrix_set(m, 1, 1, -mu * (y[0] * y[0] - 1.0));
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}

}  // namespace

TEST(GslTest, DifferentialEquationsWorksOnVanDerPolOscillator) {
    // This solves the second-order nonlinear Van der Pol oscillator equation
    double mu = 10;
    gsl_odeiv2_system sys = {func, jac, 2, &mu};
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);
    double t = 0.0, t1 = 100.0;
    array<double, 2> y = {1.0, 0.0};
    for (int i = 1; i <= 100; ++i) {
        double ti = i * t1 / 100.0;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y.data());
        if (status != GSL_SUCCESS) {
            cout << "error, return value=" << status << "\n";
            break;
        }
        cout << t << " " << y[0] << " " << y[1] << "\n";
    }
    gsl_odeiv2_driver_free(d);
}

TEST(GslTest, OneDimensionalInterpolationWorks) {
    // The following program demonstrates the use of the interpolation and spline functions.
    // It computes a cubic spline interpolation of the 10-point dataset
    array<double, 10> x{};
    array<double, 10> y{};
    cout << "#m=0,S=17\n";
    for (int i = 0; i < 10; ++i) {
        x[i] = i + 0.5 * sin(i);
        y[i] = i + cos(i * i);
        cout << x[i] << " " << y[i] << "\n";
    }
    cout << "#m=1,S=0\n";
    {
        gsl_interp_accel *acc = gsl_interp_accel_alloc();
        gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, 10);
        gsl_spline_init(spline, x.data(), y.data(), 10);
        double yi = 0;
        for (double xi = x[0]; xi < x[9]; xi += 0.1) {
            yi = gsl_spline_eval(spline, xi, acc);
            cout << xi << " " << yi << "\n";
        }
        gsl_spline_free(spline);
        gsl_interp_accel_free(acc);
    }
}

TEST(GslTest, TwoDimensionalInterpolationWorks) {
    // The following example performs bilinear interpolation on the unit square,
    // using z values of (0; 1; 0:5; 1) going clockwise around the square.
    const gsl_interp2d_type *T = gsl_interp2d_bilinear;
    constexpr int NUMBER_OF_POINTS = 10;         // number of points to interpolate
    constexpr array<double, 2> xa = {0.0, 1.0};  // define unit square
    constexpr array<double, 2> ya = {0.0, 1.0};
    size_t const nx = sizeof(xa) / sizeof(double);  // x grid points
    size_t const ny = sizeof(ya) / sizeof(double);  // y grid points
    vector<double> za(nx * ny);
    gsl_spline2d *spline = gsl_spline2d_alloc(T, nx, ny);
    gsl_interp_accel *xacc = gsl_interp_accel_alloc();
    gsl_interp_accel *yacc = gsl_interp_accel_alloc();

    // set z grid values
    gsl_spline2d_set(spline, za.data(), 0, 0, 0.0);
    gsl_spline2d_set(spline, za.data(), 0, 1, 1.0);
    gsl_spline2d_set(spline, za.data(), 1, 1, 0.5);
    gsl_spline2d_set(spline, za.data(), 1, 0, 1.0);
    // initialize interpolation
    gsl_spline2d_init(spline, xa.data(), ya.data(), za.data(), nx, ny);
    // interpolate N values in x and y and print out grid for plotting
    for (int i = 0; i < NUMBER_OF_POINTS; ++i) {
        double xi = i / (NUMBER_OF_POINTS - 1.0);
        for (int j = 0; j < NUMBER_OF_POINTS; ++j) {
            double yj = j / (NUMBER_OF_POINTS - 1.0);
            double zij = gsl_spline2d_eval(spline, xi, yj, xacc, yacc);
            cout << xi << " " << yj << " " << zij << "\n";
        }
        cout << "\n";
    }

    gsl_spline2d_free(spline);
    gsl_interp_accel_free(xacc);
    gsl_interp_accel_free(yacc);
}

namespace {
double functionToDifferentiate(double const x, void *) { return pow(x, 1.5); }
}  // namespace

TEST(GslTest, NumericalDifferentiationWorks) {
    // The following code estimates the derivative of the function f(x) = x^(3/2) at x = 2 and at x = 0.
    // The function f(x) is undefined for x < 0 so the derivative at x = 0 is computed using gsl_deriv_forward()..
    gsl_function F;
    double result = 0;
    double abserr = 0;
    F.function = &functionToDifferentiate;
    F.params = nullptr;
    cout << "f(x) = x^(3/2)\n";
    gsl_deriv_central(&F, 2.0, 1e-8, &result, &abserr);
    cout << "x = 2.0\n";
    cout << "f'(x) = " << result << " +/- " << abserr << "\n";
    cout << "exact = " << 1.5 * sqrt(2.0) << "\n\n";
    gsl_deriv_forward(&F, 0.0, 1e-8, &result, &abserr);
    cout << "x = 0.0\n";
    cout << "f'(x) = " << result << " +/- " << abserr << "\n";
    cout << "exact = " << 0.0 << "\n";
}

namespace {
double functionToChebyshevApproximate(double const x, void *) { return (x < 0.5) ? 0.25 : 0.75; }
}  // namespace

TEST(GslTest, ChebyshevApproximationsWorks) {
    // The following example program computes Chebyshev approximations to a step function.
    // This is an extremely difficult approximation to make, due to the discontinuity,
    // and was chosen as an example where approximation error is visible.
    // For smooth functions the Chebyshev approximation converges extremely rapidly and errors would not be visible.
    int n = 100;
    gsl_cheb_series *cs = gsl_cheb_alloc(40);
    gsl_function F;
    F.function = functionToChebyshevApproximate;
    F.params = nullptr;
    gsl_cheb_init(cs, &F, 0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        double x = i / static_cast<double>(n);
        double r10 = gsl_cheb_eval_n(cs, 10, x);
        double r40 = gsl_cheb_eval(cs, x);
        cout << x << " " << GSL_FN_EVAL(&F, x) << " " << r10 << " " << r40 << "\n";
    }
    gsl_cheb_free(cs);
}

TEST(GslTest, SeriesAccelerationWorks) {
    // The following code calculates an estimate of(2) = 2=6 using a series
    // After N terms the error in the sum is O(1=N), making direct summation of the series converge slowly.
    constexpr int NUMBER_OF_TERMS = 20;
    array<double, NUMBER_OF_TERMS> terms{};
    double sum_accel = 0;
    double err = 0;
    double sum = 0;
    gsl_sum_levin_u_workspace *workspace = gsl_sum_levin_u_alloc(NUMBER_OF_TERMS);
    double const zeta_2 = M_PI * M_PI / 6.0;

    // terms for zeta(2) = \sum_{n=1}^{\infty} 1/n^2
    for (int n = 0; n < NUMBER_OF_TERMS; ++n) {
        double np1 = n + 1.0;
        terms[n] = 1.0 / (np1 * np1);
        sum += terms[n];
    }
    gsl_sum_levin_u_accel(terms.data(), NUMBER_OF_TERMS, workspace, &sum_accel, &err);
    cout << "term-by-term sum = " << sum << " using " << NUMBER_OF_TERMS << " terms\n";
    cout << "term-by-term sum = " << workspace->sum_plain << " using " << workspace->terms_used << "u terms\n";
    cout << "exact value = " << zeta_2 << "\n";
    cout << "accelerated sum = " << sum_accel << " using " << workspace->terms_used << "u terms\n";
    cout << "estimated error = " << err << "\n";
    cout << "actual error = " << sum_accel - zeta_2 << "\n";

    gsl_sum_levin_u_free(workspace);
}

TEST(GslTest, DISABLED_WaveletTransformFunctionWorks) {
    // The following program demonstrates the use of the one-dimensional wavelet transform functions.
    // It computes an approximation to an input signal (of length 256) using the 20 largest components of the wavelet
    // transform, while setting the others to zero.
    constexpr int NUMBER_OF_ITEMS = 256;
    int nc = 20;
    array<double, NUMBER_OF_ITEMS> originalData{};
    array<double, NUMBER_OF_ITEMS> data{};
    array<double, NUMBER_OF_ITEMS> abscoeff{};
    array<size_t, NUMBER_OF_ITEMS> p{};
    gsl_wavelet *workspace = gsl_wavelet_alloc(gsl_wavelet_daubechies, 4);
    gsl_wavelet_workspace *work = gsl_wavelet_workspace_alloc(NUMBER_OF_ITEMS);
    FILE *f = fopen("test.dat", "randomGenerator");
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        cin >> originalData[i];
        data[i] = originalData[i];
    }
    if (fclose(f) != 0) {
        cout << "Closing the file is not successful\n";
    }

    gsl_wavelet_transform_forward(workspace, data.data(), 1, NUMBER_OF_ITEMS, work);
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        abscoeff[i] = fabs(data[i]);
    }
    gsl_sort_index(p.data(), abscoeff.data(), 1, NUMBER_OF_ITEMS);
    for (int i = 0; (i + nc) < NUMBER_OF_ITEMS; ++i) {
        data[p[i]] = 0;
    }
    gsl_wavelet_transform_inverse(workspace, data.data(), 1, NUMBER_OF_ITEMS, work);
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        cout << originalData[i] << " " << data[i] << "\n";
    }

    gsl_wavelet_free(workspace);
    gsl_wavelet_workspace_free(work);
}

namespace {

struct quadratic_params {
    double a, b, c;
};

double quadratic(double const x, void *parameters) {
    auto *quadraticParameters = static_cast<quadratic_params *>(parameters);
    double a = quadraticParameters->a;
    double b = quadraticParameters->b;
    double c = quadraticParameters->c;
    return (a * x + b) * x + c;
}

}  // namespace

TEST(GslTest, OneDimensionRootFindingWorks) {
    // For any root finding algorithm we need to prepare the function to be solved.
    // For this example we will use the general quadratic equation described earlier.
    // We first need a header file (demo_fn.h) to define the function parameters
    double randomGenerator = 0, randomGenerator_expected = sqrt(5.0);
    double x_lo = 0.0, x_hi = 5.0;
    gsl_function F;
    struct quadratic_params params = {1.0, 0.0, -5.0};
    F.function = &quadratic;
    F.params = &params;
    const gsl_root_fsolver_type *T = gsl_root_fsolver_brent;
    gsl_root_fsolver *s = gsl_root_fsolver_alloc(T);

    gsl_root_fsolver_set(s, &F, x_lo, x_hi);
    cout << "using " << gsl_root_fsolver_name(s) << " method\n";
    cout << "iter [lower, upper] root err err(est)\n";
    int status = GSL_CONTINUE;
    int iter = 0, max_iter = 100;
    while (status == GSL_CONTINUE && iter < max_iter) {
        ++iter;
        status = gsl_root_fsolver_iterate(s);
        if (status != GSL_SUCCESS) {
            break;
        }
        randomGenerator = gsl_root_fsolver_root(s);
        x_lo = gsl_root_fsolver_x_lower(s);
        x_hi = gsl_root_fsolver_x_upper(s);
        status = gsl_root_test_interval(x_lo, x_hi, 0, 0.001);
        if (status == GSL_SUCCESS) {
            cout << "Converged:\n";
        }
        cout << iter << " [" << x_lo << ", " << x_hi << "] " << randomGenerator << " "
             << randomGenerator - randomGenerator_expected << " " << x_hi - x_lo << "\n";
    }

    gsl_root_fsolver_free(s);
}

namespace {
double fn1(double const x, void *) { return cos(x) + 1.0; }
}  // namespace

TEST(GslTest, OneDimensionalMinimizationWorks) {
    // The following program uses the Brent algorithm to find the minimum of the function f(x) = cos(x)+1, which occurs
    // at x = pi. The starting interval is (0; 6), with an initial guess for the minimum of 2.
    double m = 2.0, m_expected = M_PI;
    double a = 0.0, b = 6.0;
    gsl_function F;
    F.function = &fn1;
    F.params = nullptr;
    const gsl_min_fminimizer_type *T = gsl_min_fminimizer_brent;
    gsl_min_fminimizer *s = gsl_min_fminimizer_alloc(T);

    gsl_min_fminimizer_set(s, &F, m, a, b);
    cout << "using " << gsl_min_fminimizer_name(s) << " method\n";
    cout << "iter [lower, upper] min err err(est)\n";
    int iter = 0, max_iter = 100;
    cout << iter << " [" << a << ", " << b << "] " << m << " " << m - m_expected << " " << b - a << "\n";
    int status = GSL_CONTINUE;
    while (status == GSL_CONTINUE && iter < max_iter) {
        ++iter;
        status = gsl_min_fminimizer_iterate(s);
        if (status != GSL_SUCCESS) {
            break;
        }
        m = gsl_min_fminimizer_x_minimum(s);
        a = gsl_min_fminimizer_x_lower(s);
        b = gsl_min_fminimizer_x_upper(s);
        status = gsl_min_test_interval(a, b, 0.001, 0.0);
        if (status == GSL_SUCCESS) {
            cout << "Converged:\n";
        }
        cout << " [" << iter << ", " << a << "] " << b << m << m - m_expected << b - a;
    }

    gsl_min_fminimizer_free(s);
}

namespace {

struct rparams {
    double a;
    double b;
};

int rosenbrock_f(const gsl_vector *x, void *params, gsl_vector *f) {
    double a = static_cast<rparams *>(params)->a;
    double b = static_cast<rparams *>(params)->b;
    double const x0 = gsl_vector_get(x, 0);
    double const x1 = gsl_vector_get(x, 1);
    double const y0 = a * (1 - x0);
    double const y1 = b * (x1 - x0 * x0);
    gsl_vector_set(f, 0, y0);
    gsl_vector_set(f, 1, y1);
    return GSL_SUCCESS;
}

}  // namespace

TEST(GslTest, MultiDimensionalRootFindingWorks) {
    // The MultiDimensional solvers are used in a similar way to the one-dimensional root finding algorithms.
    // This first example demonstrates the HYBRIDS scaled-hybrid algorithm, which does not require derivatives.
    // The program solves the Rosenbrock system of equations.
    // This begins by creating the function object f, with the arguments (x,y) and parameters (a,b).
    // The solver s is initialized to use this function, with the gsl_multiroot_fsolver_hybrids method.
    constexpr size_t DIMENSION = 2;
    struct rparams p = {1.0, 10.0};
    gsl_multiroot_function f = {&rosenbrock_f, DIMENSION, &p};
    array<double, 2> x_init = {-10.0, -5.0};
    array<double, DIMENSION> x{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), DIMENSION);
    gsl_vector_set(&xView.vector, 0, x_init[0]);
    gsl_vector_set(&xView.vector, 1, x_init[1]);
    const gsl_multiroot_fsolver_type *T = gsl_multiroot_fsolver_hybrids;
    gsl_multiroot_fsolver *s = gsl_multiroot_fsolver_alloc(T, 2);

    gsl_multiroot_fsolver_set(s, &f, &xView.vector);
    int status = GSL_CONTINUE;
    int iter = 0;
    while (status == GSL_CONTINUE && iter < 100) {
        ++iter;
        status = gsl_multiroot_fsolver_iterate(s);
        if (status != GSL_SUCCESS) {
            // check if solver is stuck
            break;
        }
        status = gsl_multiroot_test_residual(s->f, 1e-7);
    }
    cout << "status = " << gsl_strerror(status) << "\n";

    gsl_multiroot_fsolver_free(s);
}

namespace {

int rosenbrock_df(const gsl_vector *x, void *params, gsl_matrix *J) {
    double const a = static_cast<rparams *>(params)->a;
    double const b = static_cast<rparams *>(params)->b;
    double const x0 = gsl_vector_get(x, 0);
    double const df00 = -a;
    constexpr double df01 = 0;
    double const df10 = -2 * b * x0;
    double const df11 = b;
    gsl_matrix_set(J, 0, 0, df00);
    gsl_matrix_set(J, 0, 1, df01);
    gsl_matrix_set(J, 1, 0, df10);
    gsl_matrix_set(J, 1, 1, df11);
    return GSL_SUCCESS;
}

int rosenbrock_fdf(const gsl_vector *x, void *params, gsl_vector *f, gsl_matrix *J) {
    rosenbrock_f(x, params, f);
    rosenbrock_df(x, params, J);
    return GSL_SUCCESS;
}

}  // namespace

TEST(GslTest, MultiDimensionalRootFindingWithAccelerationWorks) {
    // The next example program adds derivative information, in order to accelerate the solution.
    // There are two derivative functions rosenbrock_df and rosenbrock_fdf.
    // The latter computes both the function and its derivative simultaneously.
    // This allows the optimization of any common terms.
    // For simplicity we substitute calls to the separate f and df functions at this point in the code below
    int iter = 0;
    constexpr size_t DIMENSION = 2;
    struct rparams p = {1.0, 10.0};
    gsl_multiroot_function_fdf f = {&rosenbrock_f, &rosenbrock_df, &rosenbrock_fdf, DIMENSION, &p};
    array<double, 2> x_init = {-10.0, -5.0};
    array<double, DIMENSION> x{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), DIMENSION);
    gsl_vector_set(&xView.vector, 0, x_init[0]);
    gsl_vector_set(&xView.vector, 1, x_init[1]);
    const gsl_multiroot_fdfsolver_type *T = gsl_multiroot_fdfsolver_gnewton;
    gsl_multiroot_fdfsolver *s = gsl_multiroot_fdfsolver_alloc(T, DIMENSION);
    gsl_multiroot_fdfsolver_set(s, &f, &xView.vector);
    int status = GSL_CONTINUE;
    while (status == GSL_CONTINUE && iter < 100) {
        ++iter;
        status = gsl_multiroot_fdfsolver_iterate(s);
        if (status != GSL_SUCCESS) {
            // check if solver is stuck
            break;
        }
        status = gsl_multiroot_test_residual(s->f, 1e-7);
    }
    cout << "status = " << gsl_strerror(status) << "\n";

    gsl_multiroot_fdfsolver_free(s);
}

namespace {

// Paraboloid centered on (p[0],p[1]), with scale factors (p[2],p[3]) and minimum p[4]
double my_f(const gsl_vector *v, void *params) {
    auto *p = static_cast<double *>(params);
    double x = gsl_vector_get(v, 0);
    double y = gsl_vector_get(v, 1);
    return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}

// The gradient of f, df = (df/dx, df/dy).
void my_df(const gsl_vector *v, void *params, gsl_vector *df) {
    auto *p = static_cast<double *>(params);
    double x = gsl_vector_get(v, 0);
    double y = gsl_vector_get(v, 1);
    gsl_vector_set(df, 0, 2.0 * p[2] * (x - p[0]));
    gsl_vector_set(df, 1, 2.0 * p[3] * (y - p[1]));
}

// Compute both f and df together.
void my_fdf(const gsl_vector *x, void *params, double *f, gsl_vector *df) {
    *f = my_f(x, params);
    my_df(x, params, df);
}

}  // namespace

TEST(GslTest, MultiDimensionalMinimizationWorks) {
    // This finds the minimum of the paraboloid function defined earlier.
    // The location of the minimum is offset from the origin in x and y, and the function value at the minimum is
    // non-zero.
    // Position of the minimum (1,2), scale factors 10,20, height 30.
    array<double, 5> par = {1.0, 2.0, 10.0, 20.0, 30.0};
    ;
    gsl_multimin_function_fdf my_func;
    my_func.n = 2;
    my_func.f = my_f;
    my_func.df = my_df;
    my_func.fdf = my_fdf;
    my_func.params = par.data();
    // Starting point, x = (5,7)
    array<double, 2> x{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), 2);
    gsl_vector_set(&xView.vector, 0, 5.0);
    gsl_vector_set(&xView.vector, 1, 7.0);
    const gsl_multimin_fdfminimizer_type *T = gsl_multimin_fdfminimizer_conjugate_fr;
    gsl_multimin_fdfminimizer *s = gsl_multimin_fdfminimizer_alloc(T, 2);

    gsl_multimin_fdfminimizer_set(s, &my_func, &xView.vector, 0.01, 1e-4);
    int status = GSL_CONTINUE;
    int iter = 0;
    while (status == GSL_CONTINUE && iter < 100) {
        ++iter;
        status = gsl_multimin_fdfminimizer_iterate(s);
        if (status != GSL_SUCCESS) {
            // check if solver is stuck
            break;
        }
        status = gsl_multimin_test_gradient(s->gradient, 1e-3);
        if (status == GSL_SUCCESS) {
            cout << "Minimum found at:\n";
        }
        cout << iter << " " << gsl_vector_get(s->x, 0) << " " << gsl_vector_get(s->x, 1) << " " << s->f << "\n";
    }

    gsl_multimin_fdfminimizer_free(s);
}

TEST(GslTest, MultiDimensionalMinimizationWorksWithNelderMeadSimplexAlgorithm) {
    // This uses Nelder-Mead Simplex algorithm to minimize the same example object function, as above.
    array<double, 5> par = {1.0, 2.0, 10.0, 20.0, 30.0};
    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
    gsl_multimin_function minex_func;
    // Starting point
    array<double, 2> x{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), 2);
    gsl_vector_set(&xView.vector, 0, 5.0);
    gsl_vector_set(&xView.vector, 1, 7.0);
    // Set initial step sizes to 1
    array<double, 2> ss{};
    gsl_vector_view ssView = gsl_vector_view_array(ss.data(), 2);
    gsl_vector_set_all(&ssView.vector, 1.0);
    // Initialize method and iterate
    minex_func.n = 2;
    minex_func.f = my_f;
    minex_func.params = par.data();
    gsl_multimin_fminimizer *s = gsl_multimin_fminimizer_alloc(T, 2);
    gsl_multimin_fminimizer_set(s, &minex_func, &xView.vector, &ssView.vector);
    int status = GSL_CONTINUE;
    int iter = 0;
    while (status == GSL_CONTINUE && iter < 100) {
        ++iter;
        status = gsl_multimin_fminimizer_iterate(s);
        if (status != GSL_SUCCESS) {
            break;
        }
        double size = gsl_multimin_fminimizer_size(s);
        status = gsl_multimin_test_size(size, 1e-2);
        if (status == GSL_SUCCESS) {
            cout << "converged to minimum at\n";
        }
        cout << iter << " " << gsl_vector_get(s->x, 0) << " " << gsl_vector_get(s->x, 1) << " f() = " << s->fval
             << " size = " << size << "\n";
    }

    gsl_multimin_fminimizer_free(s);
}

TEST(GslTest, SimpleLinearRegressionExampleWorks) {
    // The following program computes a least squares straight-line fit to a simple dataset,
    // and outputs the best-fit line and its associated one standard-deviation error bars.
    int n = 4;
    array<double, 4> x = {1970, 1980, 1990, 2000};
    array<double, 4> y = {12, 11, 14, 13};
    array<double, 4> w = {0.1, 0.2, 0.3, 0.4};
    double c0 = 0, c1 = 0, cov00 = 0, cov01 = 0, cov11 = 0, chisq = 0;

    gsl_fit_wlinear(x.data(), 1, w.data(), 1, y.data(), 1, n, &c0, &c1, &cov00, &cov01, &cov11, &chisq);
    cout << "# best fit: Y = " << c0 << " + " << c1 << " X\n";
    cout << "# covariance matrix:\n";
    cout << "# [ " << cov00 << ", " << cov01 << "\n# " << cov01 << ", " << cov11 << "]\n";
    cout << "# chisq = " << chisq << "\n";
    for (int i = 0; i < n; ++i) {
        cout << "data: " << x[i] << " " << y[i] << " " << 1 / sqrt(w[i]) << "\n";
    }
    cout << "\n";
    for (int i = -30; i < 130; ++i) {
        double xf = x[0] + (i / 100.0) * (x[n - 1] - x[0]);
        double yf = 0, yf_err = 0;
        gsl_fit_linear_est(xf, c0, c1, cov00, cov01, cov11, &yf, &yf_err);
        cout << "fit: " << xf << " " << yf << "\n";
        cout << "hi : " << xf << " " << yf + yf_err << "\n";
        cout << "lo : " << xf << " " << yf - yf_err << "\n";
    }
}

TEST(GslTest, RegularizedLinearRegressionExampleWorks) {
    // The next program demonstrates the difference between ordinary and regularized least squares when the design
    // matrix is near-singular. In this program, we generate two random normally distributed variables u and v, with v =
    // u+noise so that u and v are nearly colinear. We then set a third dependent variable y = u+v+noise and solve for
    // the coefficients c1; c2 of the model Y (c1; c2) = c1u + c2v. Since u  v, the design matrix X is nearly singular,
    // leading to unstable ordinary least squares solutions.
    constexpr int NUMBER_OF_OBSERVATIONS = 100;    // number of observations
    constexpr int NUMBER_OF_MODEL_PARAMETERS = 2;  // number of model parameters

    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    AlbaMatrix<double> x(NUMBER_OF_OBSERVATIONS, NUMBER_OF_MODEL_PARAMETERS, {});
    gsl_matrix_view xView =
        gsl_matrix_view_array(x.getMatrixDataReference().data(), NUMBER_OF_OBSERVATIONS, NUMBER_OF_MODEL_PARAMETERS);
    array<double, NUMBER_OF_OBSERVATIONS> y{};
    gsl_vector_view yView = gsl_vector_view_array(y.data(), NUMBER_OF_OBSERVATIONS);
    for (int i = 0; i < NUMBER_OF_OBSERVATIONS; ++i) {
        // generate first random variable u
        double ui = 5.0 * gsl_ran_gaussian(randomGenerator, 1.0);
        // set v = u + noise
        double vi = ui + gsl_ran_gaussian(randomGenerator, 0.001);
        // set y = u + v + noise
        double yi = ui + vi + gsl_ran_gaussian(randomGenerator, 1.0);
        // since u =~ v, the matrix X is ill-conditioned
        gsl_matrix_set(&xView.matrix, i, 0, ui);
        gsl_matrix_set(&xView.matrix, i, 1, vi);
        // rhs vector
        gsl_vector_set(&yView.vector, i, yi);
    }
    {
        constexpr int NUMBER_OF_POINTS = 200;  // number of points on L-curve and GCV curve
        gsl_multifit_linear_workspace *workspace =
            gsl_multifit_linear_alloc(NUMBER_OF_OBSERVATIONS, NUMBER_OF_MODEL_PARAMETERS);

        array<double, NUMBER_OF_MODEL_PARAMETERS> c{};        // OLS solution
        array<double, NUMBER_OF_MODEL_PARAMETERS> cLCurve{};  // regularized solution (L-curve)
        array<double, NUMBER_OF_MODEL_PARAMETERS> cGcv{};     // regularized solution (GCV)
        array<double, NUMBER_OF_POINTS> regParam{};
        array<double, NUMBER_OF_POINTS> rho{};  // residual norms
        array<double, NUMBER_OF_POINTS> eta{};  // solution norms
        array<double, NUMBER_OF_POINTS> G{};    // GCV function values
        gsl_vector_view cView = gsl_vector_view_array(c.data(), NUMBER_OF_MODEL_PARAMETERS);
        gsl_vector_view cLCurveView = gsl_vector_view_array(cLCurve.data(), NUMBER_OF_MODEL_PARAMETERS);
        gsl_vector_view cGcvView = gsl_vector_view_array(cGcv.data(), NUMBER_OF_MODEL_PARAMETERS);
        gsl_vector_view regParamView = gsl_vector_view_array(regParam.data(), NUMBER_OF_POINTS);
        gsl_vector_view rhoView = gsl_vector_view_array(rho.data(), NUMBER_OF_POINTS);
        gsl_vector_view etaView = gsl_vector_view_array(eta.data(), NUMBER_OF_POINTS);
        gsl_vector_view GView = gsl_vector_view_array(G.data(), NUMBER_OF_POINTS);
        double lambda_l = 0;    // optimal regularization parameter (L- curve)
        double lambda_gcv = 0;  // optimal regularization parameter (GCV)
        double G_gcv = 0;       // G(lambda_gcv)
        size_t reg_idx = 0;     // index of optimal lambda
        double rcond = 0;       // reciprocal condition number of X
        double chisq = 0;
        double rnorm = 0;
        double snorm = 0;
        // compute SVD of X
        gsl_multifit_linear_svd(&xView.matrix, workspace);
        rcond = gsl_multifit_linear_rcond(workspace);
        cout << "matrix condition number = " << 1.0 / rcond << "\n\n";
        // unregularized (standard) least squares fit, lambda = 0
        gsl_multifit_linear_solve(0.0, &xView.matrix, &yView.vector, &cView.vector, &rnorm, &snorm, workspace);
        chisq = pow(rnorm, 2.0);
        cout << "=== Unregularized fit ===\n";
        cout << "best fit: y = " << gsl_vector_get(&cView.vector, 0) << " u + " << gsl_vector_get(&cView.vector, 1)
             << " v\n";
        cout << "residual norm = " << rnorm << "\n";
        cout << "solution norm = " << snorm << "\n";
        cout << "chisq/dof = " << chisq / (NUMBER_OF_OBSERVATIONS - NUMBER_OF_MODEL_PARAMETERS) << "\n";
        // calculate L-curve and find its corner
        gsl_multifit_linear_lcurve(&yView.vector, &regParamView.vector, &rhoView.vector, &etaView.vector, workspace);
        gsl_multifit_linear_lcorner(&rhoView.vector, &etaView.vector, &reg_idx);
        // store optimal regularization parameter
        lambda_l = gsl_vector_get(&regParamView.vector, reg_idx);
        // regularize with lambda_l
        gsl_multifit_linear_solve(
            lambda_l, &xView.matrix, &yView.vector, &cLCurveView.vector, &rnorm, &snorm, workspace);
        chisq = pow(rnorm, 2.0) + pow(lambda_l * snorm, 2.0);
        cout << "\n=== Regularized fit (L-curve) ===\n";
        cout << "optimal lambda: " << lambda_l << "\n";
        cout << "best fit: y = " << gsl_vector_get(&cLCurveView.vector, 0) << " u + "
             << gsl_vector_get(&cLCurveView.vector, 1) << " v\n";
        cout << "residual norm = " << rnorm << "\n";
        cout << "solution norm = " << snorm << "\n";
        cout << "chisq/dof = " << chisq / (NUMBER_OF_OBSERVATIONS - NUMBER_OF_MODEL_PARAMETERS) << "\n";
        // calculate GCV curve and find its minimum
        gsl_multifit_linear_gcv(&yView.vector, &regParamView.vector, &GView.vector, &lambda_gcv, &G_gcv, workspace);
        // regularize with lambda_gcv
        gsl_multifit_linear_solve(
            lambda_gcv, &xView.matrix, &yView.vector, &cGcvView.vector, &rnorm, &snorm, workspace);
        chisq = pow(rnorm, 2.0) + pow(lambda_gcv * snorm, 2.0);
        cout << "\n=== Regularized fit (GCV) ===\n";
        cout << "optimal lambda: " << lambda_gcv << "\n";
        cout << "best fit: y = " << gsl_vector_get(&cGcvView.vector, 0) << " u + "
             << gsl_vector_get(&cGcvView.vector, 1) << " v\n";
        cout << "residual norm = " << rnorm << "\n";
        cout << "solution norm = " << snorm << "\n";
        cout << "chisq/dof = " << chisq / (NUMBER_OF_OBSERVATIONS - NUMBER_OF_MODEL_PARAMETERS) << "\n";
        // output L-curve and GCV curve
        for (int i = 0; i < NUMBER_OF_POINTS; ++i) {
            cout << gsl_vector_get(&regParamView.vector, i) << " " << gsl_vector_get(&rhoView.vector, i) << " "
                 << gsl_vector_get(&etaView.vector, i) << " " << gsl_vector_get(&GView.vector, i) << "\n";
        }
        // output L-curve corner point
        cout << "\n\n"
             << gsl_vector_get(&rhoView.vector, reg_idx) << " " << gsl_vector_get(&etaView.vector, reg_idx) << "\n";
        // output GCV curve corner minimum
        cout << "\n\n" << lambda_gcv << " " << G_gcv << "\n";
        gsl_multifit_linear_free(workspace);
    }

    gsl_rng_free(randomGenerator);
}

namespace {

int doFitInRobust(
    const gsl_multifit_robust_type *T, const gsl_matrix *X, const gsl_vector *y, gsl_vector *c, gsl_matrix *cov) {
    gsl_multifit_robust_workspace *work = gsl_multifit_robust_alloc(T, X->size1, X->size2);
    int s = gsl_multifit_robust(X, y, c, cov, work);
    gsl_multifit_robust_free(work);
    return s;
}

}  // namespace

TEST(GslTest, RobustLinearRegressionExampleWorks) {
    // The next program demonstrates the advantage of robust least squares on a dataset with outliers. The program
    // generates linear (x; y) data pairs on the line y = 1:45x + 3:88, adds some random noise, and inserts 3 outliers
    // into the dataset. Both the robust and ordinary least squares (OLS) coefficients are computed for comparison.
    constexpr double a = 1.45;  // slope
    constexpr double b = 3.88;  // intercept
    constexpr int n = 10;
    constexpr size_t p = 2;  // linear fit
    AlbaMatrix<double> matrixX(n, p, {});
    AlbaMatrix<double> matrixCov(p, p, {});
    gsl_matrix_view matrixXView = gsl_matrix_view_array(matrixX.getMatrixDataReference().data(), n, p);
    gsl_matrix_view matrixCovView = gsl_matrix_view_array(matrixCov.getMatrixDataReference().data(), p, p);
    array<double, n> x{};
    array<double, n> y{};
    array<double, p> c{};
    array<double, p> cOls{};
    gsl_vector_view xView = gsl_vector_view_array(x.data(), n);
    gsl_vector_view yView = gsl_vector_view_array(y.data(), n);
    gsl_vector_view cView = gsl_vector_view_array(c.data(), p);
    gsl_vector_view cOlsView = gsl_vector_view_array(cOls.data(), p);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    // generate linear dataset
    for (int i = 0; i < n - 3; ++i) {
        double dx = 10.0 / (n - 1.0);
        double ei = gsl_rng_uniform(randomGenerator);
        double xi = -5.0 + i * dx;
        double yi = a * xi + b;
        gsl_vector_set(&xView.vector, i, xi);
        gsl_vector_set(&yView.vector, i, yi + ei);
    }
    // add a few outliers
    gsl_vector_set(&xView.vector, n - 3, 4.7);
    gsl_vector_set(&yView.vector, n - 3, -8.3);
    gsl_vector_set(&xView.vector, n - 2, 3.5);
    gsl_vector_set(&yView.vector, n - 2, -6.7);
    gsl_vector_set(&xView.vector, n - 1, 4.1);
    gsl_vector_set(&yView.vector, n - 1, -6.0);
    // construct design matrix X for linear fit
    for (int i = 0; i < n; ++i) {
        double xi = gsl_vector_get(&xView.vector, i);
        gsl_matrix_set(&matrixXView.matrix, i, 0, 1.0);
        gsl_matrix_set(&matrixXView.matrix, i, 1, xi);
    }
    // perform robust and OLS fit
    doFitInRobust(gsl_multifit_robust_ols, &matrixXView.matrix, &yView.vector, &cOlsView.vector, &matrixCovView.matrix);
    doFitInRobust(
        gsl_multifit_robust_bisquare, &matrixXView.matrix, &yView.vector, &cView.vector, &matrixCovView.matrix);
    // output data and model
    for (int i = 0; i < n; ++i) {
        double xi = gsl_vector_get(&xView.vector, i);
        double yi = gsl_vector_get(&yView.vector, i);
        gsl_vector_view v = gsl_matrix_row(&matrixXView.matrix, i);
        double yOls = 0, yRob = 0, yErr = 0;
        gsl_multifit_robust_est(&v.vector, &cView.vector, &matrixCovView.matrix, &yRob, &yErr);
        gsl_multifit_robust_est(&v.vector, &cOlsView.vector, &matrixCovView.matrix, &yOls, &yErr);
        cout << xi << " " << yi << " " << yRob << " " << yOls << "\n";
    }
#define C(i) (gsl_vector_get(&cView.vector, (i)))
#define COV(i, j) (gsl_matrix_get(&matrixCovView.matrix, (i), (j)))
    {
        cout << "# best fit: Y = " << C(0) << " + " << C(1) << " X\n";
        cout << "# covariance matrix:\n";
        cout << "# [ " << COV(0, 0) << ", " << COV(0, 1) << "\n";
        cout << "# " << COV(1, 0) << ", " << COV(1, 1) << "\n";
    }
    gsl_rng_free(randomGenerator);
}

namespace {

// function to be fitted
double func(double const t) {
    double x = sin(10.0 * t);
    return exp(x * x * x);
}

// construct a row of the least squares matrix
int build_row(double const t, gsl_vector *row) {
    int const p = static_cast<int>(row->size);
    double Xj = 1.0;
    for (int j = 0; j < p; ++j) {
        gsl_vector_set(row, j, Xj);
        Xj *= t;
    }
    return 0;
}

int solve_system(
    int const print_data, const gsl_multilarge_linear_type *T, double const lambda, int const numberOfObservations,
    int const polynomialOrder, gsl_vector *c) {
    constexpr int nblock = 5;                         // number of blocks to accumulate
    int const nrows = numberOfObservations / nblock;  // number of rows per block
    gsl_multilarge_linear_workspace *workspace = gsl_multilarge_linear_alloc(T, polynomialOrder);

    AlbaMatrix<double> matrixX(numberOfObservations, polynomialOrder, {});
    gsl_matrix_view matrixXView =
        gsl_matrix_view_array(matrixX.getMatrixDataReference().data(), numberOfObservations, polynomialOrder);
    vector<double> y(nrows, {});
    gsl_vector_view yView = gsl_vector_view_array(y.data(), nrows);

    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    constexpr int NL_CURVE = 100;
    array<double, NL_CURVE> regParam{};
    array<double, NL_CURVE> rho{};  // residual norms
    array<double, NL_CURVE> eta{};  // solution norms
    gsl_vector_view regParamView = gsl_vector_view_array(regParam.data(), NL_CURVE);
    gsl_vector_view rhoView = gsl_vector_view_array(rho.data(), NL_CURVE);
    gsl_vector_view etaView = gsl_vector_view_array(eta.data(), NL_CURVE);
    int rowidx = 0;
    double t = 0.0;
    double dt = 1.0 / (numberOfObservations - 1.0);
    while (rowidx < numberOfObservations) {
        int nleft = numberOfObservations - rowidx;  // number of rows left to accumulate
        int nr = GSL_MIN(nrows, nleft);             // number of rows in this block
        gsl_matrix_view Xv = gsl_matrix_submatrix(&matrixXView.matrix, 0, 0, nr, polynomialOrder);
        gsl_vector_view yv = gsl_vector_subvector(&yView.vector, 0, nr);
        // build (X,y) block with 'nr' rows
        for (int i = 0; i < nr; ++i) {
            gsl_vector_view row = gsl_matrix_row(&Xv.matrix, i);
            double fi = func(t);
            double ei = gsl_ran_gaussian(randomGenerator, 0.1 * fi);  // noise
            double yi = fi + ei;
            // construct this row of LS matrix
            build_row(t, &row.vector);
            // set right hand side value with added noise
            gsl_vector_set(&yv.vector, i, yi);
            if (print_data != 0 && (i % 100 == 0)) {
                cout << t << " " << yi << "\n";
            }
            t += dt;
        }
        // accumulate (X,y) block into LS system
        gsl_multilarge_linear_accumulate(&Xv.matrix, &yv.vector, workspace);
        rowidx += nr;
    }
    if (print_data != 0) {
        cout << "\n\n";
    }
    // compute L-curve
    gsl_multilarge_linear_lcurve(&regParamView.vector, &rhoView.vector, &etaView.vector, workspace);
    // solve large LS system and store solution in c
    double rnorm = 0, snorm = 0, rcond = 0;
    gsl_multilarge_linear_solve(lambda, c, &rnorm, &snorm, workspace);
    // compute reciprocal condition number
    gsl_multilarge_linear_rcond(&rcond, workspace);
    cout << "=== Method " << gsl_multilarge_linear_name(workspace) << " ===\n";
    cout << "condition number = " << 1.0 / rcond << "\n";
    cout << "residual norm = " << rnorm << "\n";
    cout << "solution norm = " << snorm << "\n";
    {
        // output L-curve
        for (int i = 0; i < NL_CURVE; ++i) {
            cout << gsl_vector_get(&regParamView.vector, i) << " " << gsl_vector_get(&rhoView.vector, i) << " "
                 << gsl_vector_get(&etaView.vector, i) << "\n";
        }
        cout << "\n\n";
    }
    gsl_multilarge_linear_free(workspace);
    gsl_rng_free(randomGenerator);
    return 0;
}

}  // namespace

TEST(GslTest, LargeDenseLinearRegressionExampleWorks) {
    // This  demonstrates the large dense linear least squares solvers.
    constexpr size_t NUMBER_OF_OBSERVATIONS = 100;  // number of observations
    constexpr size_t POLYNOMIAL_ORDER = 16;         // polynomial order + 1
    double lambda = 0.0;                            // regularization parameter
    array<double, POLYNOMIAL_ORDER> cTsqr{};
    array<double, POLYNOMIAL_ORDER> cNormal{};  // residual norms
    gsl_vector_view cTsqrView = gsl_vector_view_array(cTsqr.data(), POLYNOMIAL_ORDER);
    gsl_vector_view cNormalView = gsl_vector_view_array(cNormal.data(), POLYNOMIAL_ORDER);
    lambda = 1;
    // turn off error handler so normal equations method won't abort
    gsl_set_error_handler_off();
    // solve system with TSQR method
    solve_system(1, gsl_multilarge_linear_tsqr, lambda, NUMBER_OF_OBSERVATIONS, POLYNOMIAL_ORDER, &cTsqrView.vector);
    // solve system with Normal equations method
    solve_system(
        0, gsl_multilarge_linear_normal, lambda, NUMBER_OF_OBSERVATIONS, POLYNOMIAL_ORDER, &cNormalView.vector);
    {
        // output solutions
        array<double, POLYNOMIAL_ORDER> v{};
        gsl_vector_view vView = gsl_vector_view_array(v.data(), POLYNOMIAL_ORDER);
        for (double t = 0.0; t <= 1.0; t += 0.1) {
            double fExact = func(t);
            double fTsqr = 0, fNormal = 0;
            build_row(t, &vView.vector);
            gsl_blas_ddot(&vView.vector, &cTsqrView.vector, &fTsqr);
            gsl_blas_ddot(&vView.vector, &cNormalView.vector, &fNormal);
            cout << t << " " << fExact << " " << fTsqr << " " << fNormal << "\n";
        }
    }
}

namespace {

struct ExponentialFittingData {
    int n;
    double *t;
    double *y;
};

int expb_f(const gsl_vector *x, void *data, gsl_vector *f) {
    int n = static_cast<ExponentialFittingData *>(data)->n;
    double *t = static_cast<ExponentialFittingData *>(data)->t;
    double *y = static_cast<ExponentialFittingData *>(data)->y;
    double A = gsl_vector_get(x, 0);
    double lambda = gsl_vector_get(x, 1);
    double b = gsl_vector_get(x, 2);
    for (int i = 0; i < n; ++i) {
        // Model Yi = A * exp(-lambda * t_i) + b
        double Yi = A * exp(-lambda * t[i]) + b;
        gsl_vector_set(f, i, Yi - y[i]);
    }
    return GSL_SUCCESS;
}

int expb_df(const gsl_vector *x, void *data, gsl_matrix *J) {
    int n = static_cast<ExponentialFittingData *>(data)->n;
    double *t = static_cast<ExponentialFittingData *>(data)->t;
    double A = gsl_vector_get(x, 0);
    double lambda = gsl_vector_get(x, 1);
    for (int i = 0; i < n; ++i) {
        // Jacobian matrix J(i,j) = dfi / dxj,
        // where fi = (Yi - yi)/sigma[i],
        // Yi = A * exp(-lambda * t_i) + b
        // and the xj are the parameters (A,lambda,b)
        double e = exp(-lambda * t[i]);
        gsl_matrix_set(J, i, 0, e);
        gsl_matrix_set(J, i, 1, -t[i] * A * e);
        gsl_matrix_set(J, i, 2, 1.0);
    }
    return GSL_SUCCESS;
}

void callback(const size_t iter, void *, const gsl_multifit_nlinear_workspace *workspace) {
    gsl_vector *f = gsl_multifit_nlinear_residual(workspace);
    gsl_vector *x = gsl_multifit_nlinear_position(workspace);
    double rcond = 0;
    // compute reciprocal condition number of J(x)
    gsl_multifit_nlinear_rcond(&rcond, workspace);
    cout << "iter " << iter << "u: A = " << gsl_vector_get(x, 0) << ", lambda = " << gsl_vector_get(x, 1)
         << ", b = " << gsl_vector_get(x, 2) << ", cond(J) = " << 1.0 / rcond << ", |f(x)|!= " << gsl_blas_dnrm2(f)
         << "\n ";
}

}  // namespace

TEST(GslTest, ExponentialFittingExampleWorks) {
    // The following example program fits a weighted exponential model with background to experimental
    // ExponentialFittingData, Y = Aexp(􀀀t) + b. The first part of the program sets up the functions expb_f() and
    // expb_df() to calculate the model and its Jacobian.
    constexpr int NUMBER_OF_DATA_POINTS = 100;  // number of data points to fit
    constexpr int NUMBER_OF_INDEPENDENT_VARIABLES = 3;
    constexpr double TIME_MAX = 3.0;  // time variable in [0,TMAX]
    const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
    gsl_multifit_nlinear_fdf fdf;
    gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();
    AlbaMatrix<double> covar(NUMBER_OF_INDEPENDENT_VARIABLES, NUMBER_OF_INDEPENDENT_VARIABLES, {});
    gsl_matrix_view covarView = gsl_matrix_view_array(
        covar.getMatrixDataReference().data(), NUMBER_OF_INDEPENDENT_VARIABLES, NUMBER_OF_INDEPENDENT_VARIABLES);
    array<double, NUMBER_OF_DATA_POINTS> t = {};
    array<double, NUMBER_OF_DATA_POINTS> y = {};
    array<double, NUMBER_OF_DATA_POINTS> weights = {};
    ExponentialFittingData d = {NUMBER_OF_DATA_POINTS, t.data(), y.data()};
    array<double, 3> x_init = {1.0, 1.0, 0.0};  // starting values
    gsl_vector_view x = gsl_vector_view_array(x_init.data(), NUMBER_OF_INDEPENDENT_VARIABLES);
    gsl_vector_view wts = gsl_vector_view_array(weights.data(), NUMBER_OF_DATA_POINTS);
    constexpr double xtol = 1e-8;
    constexpr double gtol = 1e-8;
    constexpr double ftol = 0.0;
    gsl_rng_env_setup();
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);
    // define the function to be minimized
    fdf.f = expb_f;
    fdf.df = expb_df;   // set to nullptr for finite-difference Jacobian
    fdf.fvv = nullptr;  // not using geodesic acceleration
    fdf.n = NUMBER_OF_DATA_POINTS;
    fdf.p = NUMBER_OF_INDEPENDENT_VARIABLES;
    fdf.params = &d;
    // this is the ExponentialFittingData to be fitted
    for (int i = 0; i < NUMBER_OF_DATA_POINTS; ++i) {
        double ti = i * TIME_MAX / (NUMBER_OF_DATA_POINTS - 1.0);
        double yi = 1.0 + 5 * exp(-1.5 * ti);
        double si = 0.1 * yi;
        double dy = gsl_ran_gaussian(randomGenerator, si);
        t[i] = ti;
        y[i] = yi + dy;
        weights[i] = 1.0 / (si * si);
        cout << "ExponentialFittingData: " << ti << " " << y[i] << " " << si << "\n";
    };
    // allocate workspace with default parameters
    gsl_multifit_nlinear_workspace *workspace =
        gsl_multifit_nlinear_alloc(T, &fdf_params, NUMBER_OF_DATA_POINTS, NUMBER_OF_INDEPENDENT_VARIABLES);
    // initialize solver with starting point and weights
    gsl_multifit_nlinear_winit(&x.vector, &wts.vector, &fdf, workspace);
    // compute initial cost function
    gsl_vector *f = gsl_multifit_nlinear_residual(workspace);
    double chisq0 = 0;
    gsl_blas_ddot(f, f, &chisq0);
    // solve the system with a maximum of 100 iterations
    int info = 0;
    int status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol, callback, nullptr, &info, workspace);
    // compute covariance of best fit parameters
    gsl_matrix *J = gsl_multifit_nlinear_jac(workspace);
    gsl_multifit_nlinear_covar(J, 0.0, &covarView.matrix);
    // compute final cost
    double chisq = 0;
    gsl_blas_ddot(f, f, &chisq);
#define FIT(i) gsl_vector_get(workspace->x, i)
#define ERR(i) sqrt(gsl_matrix_get(&covarView.matrix, i, i))
    cout << "summary from method '" << gsl_multifit_nlinear_name(workspace) << "/"
         << gsl_multifit_nlinear_trs_name(workspace) << "'\n";
    cout << "number of iterations: " << gsl_multifit_nlinear_niter(workspace) << "u\n";
    cout << "function evaluations: " << fdf.nevalf << "u\n";
    cout << "Jacobian evaluations: " << fdf.nevaldf << "u\n";
    cout << "reason for stopping: " << ((info == 1) ? "small step size"s : "small gradient"s) << "\n";
    cout << "initial |f(x)| = " << sqrt(chisq0) << "\n";
    cout << "final |f(x)| = " << sqrt(chisq) << "\n";
    {
        double dof = NUMBER_OF_DATA_POINTS - NUMBER_OF_INDEPENDENT_VARIABLES;
        double c = GSL_MAX_DBL(1, sqrt(chisq / dof));
        cout << "chisq/dof = " << chisq / dof << "\n";
        cout << "A = " << FIT(0) << " +/- " << c * ERR(0) << "\n";
        cout << "lambda = " << FIT(1) << " +/- " << c * ERR(1) << "\n";
        cout << "b = " << FIT(2) << " +/- " << c * ERR(2) << "\n";
    }
    cout << "status = " << gsl_strerror(status) << "\n";

    gsl_multifit_nlinear_free(workspace);
    gsl_rng_free(randomGenerator);
}

TEST(GslTest, DerivativesOfBasisSplinesWorks) {
    // This computes and outputs cubic B-splines and their derivatives using 6 breakpoints and uniform
    // knots on the interval [0; 1]. All derivatives up to order 3 are computed.
    constexpr int nbreak = 6;
    constexpr int spline_order = 4;
    constexpr int n = 100;
    constexpr double a = 0.0;
    constexpr double b = 1.0;
    gsl_bspline_workspace *workspace = gsl_bspline_alloc(spline_order, nbreak);
    int const p = static_cast<int>(gsl_bspline_ncoeffs(workspace));
    double const dx = (b - a) / (n - 1.0);
    gsl_matrix *dB = gsl_matrix_alloc(p, spline_order);
    // uniform breakpoints on [a, b]
    gsl_bspline_knots_uniform(a, b, workspace);
    // output knot vector
    gsl_vector_fprintf(stdout, workspace->knots, "%f");
    cout << "\n\n";
    for (int i = 0; i < spline_order; ++i) {
        for (int j = 0; j < n; ++j) {
            double xj = j * dx;
            gsl_bspline_deriv_eval(xj, i, dB, workspace);
            cout << xj << " ";
            for (int k = 0; k < p; ++k) {
                cout << gsl_matrix_get(dB, k, i) << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    gsl_matrix_free(dB);
    gsl_bspline_free(workspace);
}

TEST(GslTest, SparseMatricesWorks) {
    // The following example program builds a 5-by-4 sparse matrix and prints it in coordinate,
    // compressed column, and compressed row format.
    gsl_spmatrix *A = gsl_spmatrix_alloc(5, 4);  // triplet format
                                                 // build the sparse matrix
    gsl_spmatrix_set(A, 0, 2, 3.1);
    gsl_spmatrix_set(A, 0, 3, 4.6);
    gsl_spmatrix_set(A, 1, 0, 1.0);
    gsl_spmatrix_set(A, 1, 2, 7.2);
    gsl_spmatrix_set(A, 3, 0, 2.1);
    gsl_spmatrix_set(A, 3, 1, 2.9);
    gsl_spmatrix_set(A, 3, 3, 8.5);
    gsl_spmatrix_set(A, 4, 0, 4.1);
    cout << "printing all matrix elements:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << "A(" << i << "u," << j << "u) = " << gsl_spmatrix_get(A, i, j) << "\n";
        }
    }
    // print out elements in triplet format
    cout << "matrix in triplet format (i,j,Aij):\n";
    gsl_spmatrix_fprintf(stdout, A, "%.1f");
    // convert to compressed column format
    gsl_spmatrix *B = gsl_spmatrix_ccs(A);
    cout << "matrix in compressed column format:\n";
    cout << "i = [ ";
    for (int i = 0; i < static_cast<int>(B->nz); ++i) {
        cout << B->i[i] << ", ";
    }
    cout << "]\n";
    cout << "p = [ ";
    for (int i = 0; i < static_cast<int>(B->size2 + 1); ++i) {
        cout << B->p[i] << ", ";
    }
    cout << "]\n";
    cout << "d = [ ";
    for (int i = 0; i < static_cast<int>(B->nz); ++i) {
        cout << B->data[i] << ", ";
    }
    cout << "]\n";
    // convert to compressed row format
    gsl_spmatrix *C = gsl_spmatrix_crs(A);
    cout << "matrix in compressed row format:\n";
    cout << "i = [ ";
    for (int i = 0; i < static_cast<int>(C->nz); ++i) {
        cout << C->i[i] << ", ";
    }
    cout << "]\n";
    cout << "p = [ ";
    for (int i = 0; i < static_cast<int>(C->size1 + 1); ++i) {
        cout << C->p[i] << ", ";
    }
    cout << "]\n";
    cout << "d = [ ";
    for (int i = 0; i < static_cast<int>(C->nz); ++i) {
        cout << C->data[i] << ", ";
    }
    cout << "]\n";
    gsl_spmatrix_free(A);
    gsl_spmatrix_free(B);
    gsl_spmatrix_free(C);
}

TEST(GslTest, SparseLinearAlgebraWorks) {
    // This example program demonstrates the sparse linear algebra routines on the solution
    // of a simple 1D Poisson equation on [0; 1]:
    constexpr int NUMBER_OF_GRID_POINTS = 100;                                 // number of grid points
    constexpr int NUMBER_OF_POINTS = NUMBER_OF_GRID_POINTS - 2;                // subtract 2 to exclude boundaries
    constexpr double h = 1.0 / (NUMBER_OF_GRID_POINTS - 1.0);                  // grid spacing
    gsl_spmatrix *A = gsl_spmatrix_alloc(NUMBER_OF_POINTS, NUMBER_OF_POINTS);  // triplet format
    array<double, NUMBER_OF_POINTS> f{};                                       // right hand side vector
    array<double, NUMBER_OF_POINTS> u{};                                       // solution vector
    gsl_vector_view fView = gsl_vector_view_array(f.data(), NUMBER_OF_POINTS);
    gsl_vector_view uView = gsl_vector_view_array(u.data(), NUMBER_OF_POINTS);
    // construct the sparse matrix for the finite difference equation
    // construct first row
    gsl_spmatrix_set(A, 0, 0, -2.0);
    gsl_spmatrix_set(A, 0, 1, 1.0);
    // construct rows [1:n-2]
    for (int i = 1; i < NUMBER_OF_POINTS - 1; ++i) {
        gsl_spmatrix_set(A, i, i + 1, 1.0);
        gsl_spmatrix_set(A, i, i, -2.0);
        gsl_spmatrix_set(A, i, i - 1, 1.0);
    }
    // construct last row
    gsl_spmatrix_set(A, NUMBER_OF_POINTS - 1, NUMBER_OF_POINTS - 1, -2.0);
    gsl_spmatrix_set(A, NUMBER_OF_POINTS - 1, NUMBER_OF_POINTS - 2, 1.0);
    // scale by h^2
    gsl_spmatrix_scale(A, 1.0 / (h * h));
    // construct right hand side vector
    for (int i = 0; i < NUMBER_OF_POINTS; ++i) {
        double xi = (i + 1) * h;
        double fi = -M_PI * M_PI * sin(M_PI * xi);
        gsl_vector_set(&fView.vector, i, fi);
    }
    // convert to compressed column format
    gsl_spmatrix *C = gsl_spmatrix_ccs(A);
    {
        // compressed format
        // now solve the system with the GMRES iterative solver
        constexpr double tol = 1.0e-6;  // solution relative tolerance
        const gsl_splinalg_itersolve_type *T = gsl_splinalg_itersolve_gmres;
        gsl_splinalg_itersolve *work = gsl_splinalg_itersolve_alloc(T, NUMBER_OF_POINTS, 0);
        // initial guess u = 0
        gsl_vector_set_zero(&uView.vector);
        // solve the system A u = f
        int status = GSL_CONTINUE;
        int iter = 0, max_iter = 10;
        while (status == GSL_CONTINUE && ++iter < max_iter) {
            status = gsl_splinalg_itersolve_iterate(C, &fView.vector, tol, &uView.vector, work);
            // print out residual norm ||A*u - f||
            double residual = gsl_splinalg_itersolve_normr(work);
            cout << "iter " << iter << "u residual = " << residual << "\n";
            if (status == GSL_SUCCESS) {
                cout << "Converged\n";
            }
        }
        // output solution
        for (int i = 0; i < NUMBER_OF_POINTS; ++i) {
            double xi = (i + 1) * h;
            double u_exact = sin(M_PI * xi);
            double u_gsl = gsl_vector_get(&uView.vector, i);
            cout << xi << " " << u_gsl << " " << u_exact << "\n";
        }
        gsl_splinalg_itersolve_free(work);
    }
    gsl_spmatrix_free(A);
    gsl_spmatrix_free(C);
}

}  // namespace alba
