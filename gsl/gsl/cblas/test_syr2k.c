#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_syr2k (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { -0.915F, 0.445F };
   int lda = 2;
   float B[] = { 0.213F, -0.194F };
   int ldb = 2;
   float C[] = { -0.117F };
   int ldc = 1;
   float C_expected[] = { -0.173245F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1614)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { 0.089F, -0.889F };
   int lda = 2;
   float B[] = { -0.384F, 0.518F };
   int ldb = 2;
   float C[] = { 0.069F };
   int ldc = 1;
   float C_expected[] = { -0.0299356F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1615)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { 0.492F, 0.021F };
   int lda = 1;
   float B[] = { -0.804F, -0.912F };
   int ldb = 1;
   float C[] = { -0.851F };
   int ldc = 1;
   float C_expected[] = { -0.933944F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1616)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { -0.376F, 0.689F };
   int lda = 1;
   float B[] = { 0.21F, 0.406F };
   int ldb = 1;
   float C[] = { -0.581F };
   int ldc = 1;
   float C_expected[] = { -0.540845F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1617)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha = 1.0F;
   float beta = -0.3F;
   float A[] = { 0.629F, -0.883F };
   int lda = 1;
   float B[] = { -0.165F, 0.02F };
   int ldb = 1;
   float C[] = { 0.236F };
   int ldc = 1;
   float C_expected[] = { -0.31369F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1618)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha = 1.0F;
   float beta = -0.3F;
   float A[] = { 0.412F, -0.411F };
   int lda = 1;
   float B[] = { 0.313F, 0.301F };
   int ldb = 1;
   float C[] = { 0.222F };
   int ldc = 1;
   float C_expected[] = { -0.05611F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1619)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha = 1.0F;
   float beta = -0.3F;
   float A[] = { -0.02F, 0.593F };
   int lda = 2;
   float B[] = { -0.144F, 0.846F };
   int ldb = 2;
   float C[] = { -0.645F };
   int ldc = 1;
   float C_expected[] = { 1.20262F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1620)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha = 1.0F;
   float beta = -0.3F;
   float A[] = { 0.253F, 0.937F };
   int lda = 2;
   float B[] = { 0.24F, -0.27F };
   int ldb = 2;
   float C[] = { 0.128F };
   int ldc = 1;
   float C_expected[] = { -0.42294F };
   cblas_ssyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyr2k(case 1621)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha = 0.1;
   double beta = 0;
   double A[] = { -0.225, 0.857 };
   int lda = 2;
   double B[] = { -0.933, 0.994 };
   int ldb = 2;
   double C[] = { 0.177 };
   int ldc = 1;
   double C_expected[] = { 0.2123566 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1622)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha = 0.1;
   double beta = 0;
   double A[] = { -0.955, 0.112 };
   int lda = 2;
   double B[] = { -0.695, 0.719 };
   int ldb = 2;
   double C[] = { 0.069 };
   int ldc = 1;
   double C_expected[] = { 0.1488506 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1623)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha = 0.1;
   double beta = 0;
   double A[] = { 0.216, 0.911 };
   int lda = 1;
   double B[] = { -0.074, -0.256 };
   int ldb = 1;
   double C[] = { -0.621 };
   int ldc = 1;
   double C_expected[] = { -0.04984 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1624)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha = 0.1;
   double beta = 0;
   double A[] = { -0.343, -0.381 };
   int lda = 1;
   double B[] = { -0.433, -0.087 };
   int ldb = 1;
   double C[] = { -0.889 };
   int ldc = 1;
   double C_expected[] = { 0.0363332 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1625)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha = 1;
   double beta = -1;
   double A[] = { -0.633, 0.219 };
   int lda = 1;
   double B[] = { 0.817, -0.683 };
   int ldb = 1;
   double C[] = { -0.294 };
   int ldc = 1;
   double C_expected[] = { -1.039476 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1626)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha = 1;
   double beta = -1;
   double A[] = { -0.887, -0.43 };
   int lda = 1;
   double B[] = { 0.557, 0.912 };
   int ldb = 1;
   double C[] = { 0.831 };
   int ldc = 1;
   double C_expected[] = { -2.603438 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1627)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha = 1;
   double beta = -1;
   double A[] = { 0.397, -0.173 };
   int lda = 2;
   double B[] = { 0.155, -0.99 };
   int ldb = 2;
   double C[] = { 0.621 };
   int ldc = 1;
   double C_expected[] = { -0.15539 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1628)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha = 1;
   double beta = -1;
   double A[] = { 0.833, -0.52 };
   int lda = 2;
   double B[] = { 0.28, 0.481 };
   int ldb = 2;
   double C[] = { 0.455 };
   int ldc = 1;
   double C_expected[] = { -0.48876 };
   cblas_dsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyr2k(case 1629)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.248F, -0.037F, -0.124F, 0.998F };
   int lda = 2;
   float B[] = { -0.608F, -0.115F, -0.718F, -0.551F };
   int ldb = 2;
   float C[] = { 0.187F, -0.329F };
   int ldc = 1;
   float C_expected[] = { 0.119445F, 0.157092F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1630) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1630) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { 0.068F, 0.751F, -0.449F, -0.598F };
   int lda = 2;
   float B[] = { 0.616F, 0.805F, -0.635F, 0.773F };
   int ldb = 2;
   float C[] = { -0.287F, 0.917F };
   int ldc = 1;
   float C_expected[] = { -0.110002F, 0.0369404F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1631) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1631) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.396F, -0.603F, -0.131F, -0.288F };
   int lda = 1;
   float B[] = { -0.64F, -0.444F, -0.085F, 0.936F };
   int ldb = 1;
   float C[] = { 0.375F, -0.434F };
   int ldc = 1;
   float C_expected[] = { -0.0927216F, 0.0532822F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1632) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1632) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { 0.655F, 0.16F, 0.45F, -0.747F };
   int lda = 1;
   float B[] = { 0.923F, 0.432F, -0.986F, 0.259F };
   int ldb = 1;
   float C[] = { 0.752F, 0.576F };
   int ldc = 1;
   float C_expected[] = { -0.256746F, 0.0570436F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1633) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1633) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.765F, 0.487F, 0.7F, 0.768F };
   int lda = 1;
   float B[] = { -0.529F, 0.056F, -0.584F, 0.928F };
   int ldb = 1;
   float C[] = { -0.426F, 0.836F };
   int ldc = 1;
   float C_expected[] = { 0.019875F, -0.148818F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1634) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1634) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { 0.25F, 0.489F, 0.8F, -0.642F };
   int lda = 1;
   float B[] = { -0.732F, -0.856F, -0.654F, 0.591F };
   int ldb = 1;
   float C[] = { -0.101F, 0.322F };
   int ldc = 1;
   float C_expected[] = { -0.064144F, 0.0183612F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1635) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1635) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.579F, -0.971F, 0.521F, -0.824F };
   int lda = 2;
   float B[] = { -0.227F, 0.907F, 0.457F, -0.274F };
   int ldb = 2;
   float C[] = { 0.21F, -0.718F };
   int ldc = 1;
   float C_expected[] = { 0.164812F, 0.20489F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1636) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1636) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.83F, -0.512F, -0.667F, -0.436F };
   int lda = 2;
   float B[] = { -0.443F, 0.82F, -0.259F, -0.618F };
   int ldb = 2;
   float C[] = { 0.583F, 0.668F };
   int ldc = 1;
   float C_expected[] = { -0.0142692F, 0.138167F };
   cblas_csyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyr2k(case 1637) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyr2k(case 1637) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.315, 0.03, 0.281, 0.175 };
   int lda = 2;
   double B[] = { -0.832, -0.964, 0.291, 0.476 };
   int ldb = 2;
   double C[] = { -0.341, 0.743 };
   int ldc = 1;
   double C_expected[] = { 0.028, -0.257 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1638) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1638) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.159, -0.489, -0.11, 0.611 };
   int lda = 2;
   double B[] = { -0.285, -0.048, -0.673, -0.492 };
   int ldb = 2;
   double C[] = { 0.496, -0.626 };
   int ldc = 1;
   double C_expected[] = { -0.0862, 0.2374 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1639) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1639) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { 0.796, 0.872, -0.919, 0.748 };
   int lda = 1;
   double B[] = { -0.945, 0.915, -0.252, -0.276 };
   int ldb = 1;
   double C[] = { 0.07, -0.957 };
   int ldc = 1;
   double C_expected[] = { 0.0747, 0.2941 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1640) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1640) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 1;
   int K = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { 0.984, 0.526, 0.284, 0.806 };
   int lda = 1;
   double B[] = { -0.509, -0.178, 0.188, -0.221 };
   int ldb = 1;
   double C[] = { -0.388, 0.795 };
   int ldc = 1;
   double C_expected[] = { 0.0369, -0.2773 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1641) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1641) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {0, 0.1};
   double A[] = { 0.628, 0.846, -0.645, 0.032 };
   int lda = 1;
   double B[] = { 0.545, -0.54, 0.493, -0.035 };
   int ldb = 1;
   double C[] = { -0.16, -0.06 };
   int ldc = 1;
   double C_expected[] = { 0.97047, 0.304602 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1642) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1642) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {0, 0.1};
   double A[] = { -0.556, -0.946, 0.177, -0.859 };
   int lda = 1;
   double B[] = { 0.423, -0.91, 0.736, -0.251 };
   int ldb = 1;
   double C[] = { -0.478, 0.519 };
   int ldc = 1;
   double C_expected[] = { -2.41467, -1.189498 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1643) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1643) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {0, 0.1};
   double A[] = { -0.582, 0.09, -0.176, 0.784 };
   int lda = 2;
   double B[] = { 0.687, -0.859, 0.945, 0.756 };
   int ldb = 2;
   double C[] = { -0.663, -0.186 };
   int ldc = 1;
   double C_expected[] = { -2.144496, 2.272884 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1644) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1644) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 1;
   int K = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {0, 0.1};
   double A[] = { 0.231, -0.452, -0.112, -0.837 };
   int lda = 2;
   double B[] = { -0.258, 0.464, -0.224, 0.893 };
   int ldb = 2;
   double C[] = { -0.448, 0.046 };
   int ldc = 1;
   double C_expected[] = { 1.840718, 0.577744 };
   cblas_zsyr2k(order, uplo, trans, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyr2k(case 1645) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyr2k(case 1645) imag");
     };
   };
  };


}
