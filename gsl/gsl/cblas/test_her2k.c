#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_her2k (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta = -0.3F;
   float A[] = { 0.178F, 0.545F, -0.491F, 0.979F };
   int lda = 2;
   float B[] = { -0.665F, -0.531F, -0.4F, 0.227F };
   int ldb = 2;
   float C[] = { 0.115F, -0.193F };
   int ldc = 1;
   float C_expected[] = { -0.056236F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1646) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1646) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta = -0.3F;
   float A[] = { -0.808F, 0.447F, 0.145F, -0.226F };
   int lda = 2;
   float B[] = { -0.413F, 0.904F, -0.585F, 0.717F };
   int ldb = 2;
   float C[] = { -0.725F, -0.244F };
   int ldc = 1;
   float C_expected[] = { -0.76435F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1647) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1647) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta = -0.3F;
   float A[] = { 0.337F, -0.737F, -0.993F, 0.69F };
   int lda = 1;
   float B[] = { -0.39F, -0.836F, -0.32F, 0.368F };
   int ldb = 1;
   float C[] = { 0.844F, -0.763F };
   int ldc = 1;
   float C_expected[] = { -2.36596F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1648) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1648) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta = -0.3F;
   float A[] = { 0.386F, -0.465F, 0.719F, -0.378F };
   int lda = 1;
   float B[] = { 0.099F, -0.879F, 0.864F, 0.141F };
   int ldb = 1;
   float C[] = { -0.599F, -0.47F };
   int ldc = 1;
   float C_expected[] = { -1.85003F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1649) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1649) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 113;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta = -1.0F;
   float A[] = { 0.128F, 0.431F, -0.26F, 0.75F };
   int lda = 1;
   float B[] = { 0.276F, 0.058F, 0.904F, -0.116F };
   int ldb = 1;
   float C[] = { 0.914F, -0.262F };
   int ldc = 1;
   float C_expected[] = { 0.604744F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1650) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1650) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 113;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta = -1.0F;
   float A[] = { 0.72F, 0.783F, -0.737F, 0.375F };
   int lda = 1;
   float B[] = { 0.531F, 0.167F, 0.203F, -0.221F };
   int ldb = 1;
   float C[] = { 0.618F, 0.392F };
   int ldc = 1;
   float C_expected[] = { -0.200438F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1651) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1651) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 113;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta = -1.0F;
   float A[] = { -0.372F, -0.735F, -0.711F, 0.051F };
   int lda = 2;
   float B[] = { 0.257F, 0.097F, 0.338F, -0.484F };
   int ldb = 2;
   float C[] = { -0.142F, -0.197F };
   int ldc = 1;
   float C_expected[] = { -0.817394F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1652) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1652) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 113;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta = -1.0F;
   float A[] = { 0.1F, -0.878F, 0.28F, -0.381F };
   int lda = 2;
   float B[] = { -0.208F, 0.309F, -0.276F, 0.123F };
   int ldb = 2;
   float C[] = { 0.483F, -0.541F };
   int ldc = 1;
   float C_expected[] = { -0.03812F, 0.0F };
   cblas_cher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cher2k(case 1653) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cher2k(case 1653) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta = 1;
   double A[] = { 0.515, -0.034, 0.067, 0.66 };
   int lda = 2;
   double B[] = { 0.408, -0.85, -0.945, -0.799 };
   int ldb = 2;
   double C[] = { -0.918, -0.985 };
   int ldc = 1;
   double C_expected[] = { -1.62127, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1654) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1654) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta = 1;
   double A[] = { -0.009, 0.495, -0.008, -0.973 };
   int lda = 2;
   double B[] = { -0.239, -0.373, -0.032, -0.539 };
   int ldb = 2;
   double C[] = { 0.443, -0.245 };
   int ldc = 1;
   double C_expected[] = { 1.127438, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1655) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1655) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta = 1;
   double A[] = { 0.531, 0.721, -0.848, 0.826 };
   int lda = 1;
   double B[] = { -0.711, -0.2, -0.92, -0.676 };
   int ldb = 1;
   double C[] = { -0.447, 0.701 };
   int ldc = 1;
   double C_expected[] = { -1.046914, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1656) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1656) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta = 1;
   double A[] = { 0.68, 0.079, 0.837, -0.814 };
   int lda = 1;
   double B[] = { -0.986, 0.024, 0.584, -0.248 };
   int ldb = 1;
   double C[] = { 0.477, -0.551 };
   int ldc = 1;
   double C_expected[] = { 0.521192, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1657) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1657) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 113;
   int N = 1;
   int K = 2;
   double alpha[2] = {-1, 0};
   double beta = 0.1;
   double A[] = { -0.63, 0.787, 0.426, -0.568 };
   int lda = 1;
   double B[] = { -0.228, 0.302, 0.83, 0.023 };
   int ldb = 1;
   double C[] = { 0.354, -0.85 };
   int ldc = 1;
   double C_expected[] = { -1.40826, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1658) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1658) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 113;
   int N = 1;
   int K = 2;
   double alpha[2] = {-1, 0};
   double beta = 0.1;
   double A[] = { 0.224, -0.191, 0.46, 0.464 };
   int lda = 1;
   double B[] = { -0.815, 0.634, 0.066, -0.873 };
   int ldb = 1;
   double C[] = { -0.49, -0.606 };
   int ldc = 1;
   double C_expected[] = { 1.307732, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1659) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1659) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 113;
   int N = 1;
   int K = 2;
   double alpha[2] = {-1, 0};
   double beta = 0.1;
   double A[] = { 0.943, 0.075, 0.15, -0.141 };
   int lda = 2;
   double B[] = { -0.962, 0.422, -0.592, -0.789 };
   int ldb = 2;
   double C[] = { 0.728, 0.601 };
   int ldc = 1;
   double C_expected[] = { 1.778934, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1660) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1660) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 113;
   int N = 1;
   int K = 2;
   double alpha[2] = {-1, 0};
   double beta = 0.1;
   double A[] = { -0.93, -0.386, 0.565, 0.141 };
   int lda = 2;
   double B[] = { -0.801, 0.022, 0.558, -0.932 };
   int ldb = 2;
   double C[] = { 0.068, 0.501 };
   int ldc = 1;
   double C_expected[] = { -1.833792, 0.0 };
   cblas_zher2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zher2k(case 1661) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zher2k(case 1661) imag");
     };
   };
  };


}
