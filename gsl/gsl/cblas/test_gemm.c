#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_gemm (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = 1.0F;
   float beta = 0.0F;
   float A[] = { 0.199F, 0.237F, 0.456F, 0.377F };
   int lda = 4;
   float B[] = { 0.842F, -0.734F, 0.323F, -0.957F, -0.303F, -0.873F, -0.871F, -0.819F };
   int ldb = 2;
   float C[] = { 0.498F, -0.925F };
   int ldc = 2;
   float C_expected[] = { -0.222426F, -1.07973F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1466)");
     }
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = 1.0F;
   float beta = 0.0F;
   float A[] = { -0.83F, 0.922F, -0.228F, -0.003F };
   int lda = 1;
   float B[] = { 0.072F, 0.345F, 0.944F, -0.39F, -0.577F, 0.656F, -0.693F, -0.453F };
   int ldb = 4;
   float C[] = { 0.583F, 0.522F };
   int ldc = 1;
   float C_expected[] = { 0.044268F, 1.24311F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1467)");
     }
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = 0.1F;
   float beta = 0.1F;
   float A[] = { -0.838F, 0.622F, -0.494F, 0.304F };
   int lda = 4;
   float B[] = { 0.147F, 0.134F, 0.169F, 0.734F, -0.7F, 0.541F, -0.794F, -0.256F };
   int ldb = 4;
   float C[] = { -0.632F, -0.559F };
   int ldc = 2;
   float C_expected[] = { -0.0532188F, 0.0678514F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1468)");
     }
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = 0.1F;
   float beta = 0.1F;
   float A[] = { -0.937F, 0.635F, 0.596F, -0.51F };
   int lda = 1;
   float B[] = { -0.688F, -0.265F, 0.049F, 0.133F, -0.918F, -0.147F, 0.977F, -0.21F };
   int ldb = 2;
   float C[] = { 0.844F, 0.999F };
   int ldc = 1;
   float C_expected[] = { 0.0474373F, 0.135125F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1469)");
     }
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = -0.3F;
   float beta = 0.1F;
   float A[] = { -0.165F, 0.638F, 0.346F, -0.697F };
   int lda = 1;
   float B[] = { 0.499F, -0.73F, 0.262F, 0.759F, 0.664F, 0.997F, -0.702F, -0.839F };
   int ldb = 2;
   float C[] = { 0.17F, 0.425F };
   int ldc = 2;
   float C_expected[] = { -0.224158F, -0.417831F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1470)");
     }
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = -0.3F;
   float beta = 0.1F;
   float A[] = { -0.603F, -0.714F, -0.893F, 0.046F };
   int lda = 4;
   float B[] = { 0.859F, -0.694F, -0.868F, -0.98F, -0.103F, 0.567F, -0.277F, -0.734F };
   int ldb = 4;
   float C[] = { 0.517F, -0.622F };
   int ldc = 1;
   float C_expected[] = { -0.160575F, -0.0234604F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1471)");
     }
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { -0.087F, -0.047F, -0.051F, -0.615F };
   int lda = 1;
   float B[] = { -0.722F, -0.077F, 0.563F, 0.501F, 0.855F, 0.605F, 0.556F, -0.627F };
   int ldb = 4;
   float C[] = { -0.181F, -0.89F };
   int ldc = 2;
   float C_expected[] = { -0.208039F, -0.864557F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1472)");
     }
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { -0.753F, -0.074F, -0.247F, -0.19F };
   int lda = 4;
   float B[] = { 0.061F, 0.743F, 0.22F, -0.682F, 0.733F, 0.417F, 0.772F, 0.665F };
   int ldb = 2;
   float C[] = { -0.253F, 0.972F };
   int ldc = 1;
   float C_expected[] = { -0.291994F, 0.898164F };
   cblas_sgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "sgemm(case 1473)");
     }
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = 0;
   double beta = 0;
   double A[] = { 0.017, 0.191, 0.863, -0.97 };
   int lda = 4;
   double B[] = { -0.207, -0.916, -0.278, 0.403, 0.885, 0.409, -0.772, -0.27 };
   int ldb = 2;
   double C[] = { -0.274, -0.858 };
   int ldc = 2;
   double C_expected[] = { 0.0, 0.0 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1474)");
     }
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = 0;
   double beta = 0;
   double A[] = { 0.571, 0.081, 0.109, 0.988 };
   int lda = 1;
   double B[] = { -0.048, -0.753, -0.8, -0.89, -0.535, -0.017, -0.018, -0.544 };
   int ldb = 4;
   double C[] = { -0.876, -0.792 };
   int ldc = 1;
   double C_expected[] = { 0.0, 0.0 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1475)");
     }
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { 0.939, 0.705, 0.977, 0.4 };
   int lda = 4;
   double B[] = { -0.089, -0.822, 0.937, 0.159, 0.789, -0.413, -0.172, 0.88 };
   int ldb = 4;
   double C[] = { -0.619, 0.063 };
   int ldc = 2;
   double C_expected[] = { -0.7137904, -0.1270986 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1476)");
     }
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { -0.795, 0.81, 0.388, 0.09 };
   int lda = 1;
   double B[] = { -0.847, 0.031, -0.938, 0.09, -0.286, -0.478, -0.981, 0.881 };
   int ldb = 2;
   double C[] = { -0.242, -0.02 };
   int ldc = 1;
   double C_expected[] = { -0.1562981, -0.0026243 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1477)");
     }
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = -1;
   double beta = 0;
   double A[] = { -0.556, 0.532, 0.746, 0.673 };
   int lda = 1;
   double B[] = { -0.525, 0.967, 0.687, -0.024, 0.527, 0.485, 0.109, -0.46 };
   int ldb = 2;
   double C[] = { -0.495, 0.859 };
   int ldc = 2;
   double C_expected[] = { -1.123883, 0.49819 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1478)");
     }
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = -1;
   double beta = 0;
   double A[] = { -0.358, 0.224, -0.941, 0.513 };
   int lda = 4;
   double B[] = { -0.201, -0.159, -0.586, -0.016, -0.324, 0.411, 0.115, -0.229 };
   int ldb = 4;
   double C[] = { 0.558, 0.596 };
   int ldc = 1;
   double C_expected[] = { -0.57956, 0.017636 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1479)");
     }
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { -0.586, 0.809, 0.709, -0.524 };
   int lda = 1;
   double B[] = { 0.768, 0.7, 0.619, -0.478, -0.129, -0.778, -0.432, 0.454 };
   int ldb = 4;
   double C[] = { 0.042, 0.252 };
   int ldc = 2;
   double C_expected[] = { -0.1996785, 0.5813976 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1480)");
     }
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { -0.164, 0.522, 0.948, -0.624 };
   int lda = 4;
   double B[] = { -0.142, 0.778, 0.359, 0.622, -0.637, -0.757, -0.282, -0.805 };
   int ldb = 2;
   double C[] = { -0.09, 0.183 };
   int ldc = 1;
   double C_expected[] = { -0.0248334, 0.1884672 };
   cblas_dgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dgemm(case 1481)");
     }
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.082F, -0.281F, -0.096F, 0.913F, 0.974F, -0.706F, -0.773F, 0.522F };
   int lda = 4;
   float B[] = { 0.745F, -0.664F, 0.352F, -0.733F, 0.304F, -0.555F, -0.493F, -0.089F, 0.188F, 0.631F, 0.235F, 0.152F, -0.299F, -0.731F, -0.686F, -0.332F };
   int ldb = 2;
   float C[] = { -0.179F, -0.284F, -0.996F, -0.414F };
   int ldc = 2;
   float C_expected[] = { -1.06679F, 1.47116F, 0.599689F, 0.933532F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1482) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1482) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { 0.044F, -0.33F, 0.279F, 0.712F, -0.363F, -0.788F, -0.768F, -0.551F };
   int lda = 1;
   float B[] = { 0.138F, 0.927F, -0.178F, -0.864F, 0.888F, 0.844F, -0.199F, 0.706F, -0.034F, 0.483F, 0.499F, 0.664F, 0.648F, 0.324F, 0.97F, 0.609F };
   int ldb = 4;
   float C[] = { -0.129F, 0.842F, 0.214F, -0.626F };
   int ldc = 1;
   float C_expected[] = { 1.81122F, 1.76205F, 1.0574F, -0.564966F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1483) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1483) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.812F, -0.471F, 0.241F, 0.795F, 0.439F, 0.131F, -0.636F, 0.531F };
   int lda = 4;
   float B[] = { 0.062F, 0.807F, 0.873F, 0.372F, 0.239F, 0.804F, 0.537F, -0.954F, -0.396F, 0.838F, 0.081F, 0.15F, 0.489F, -0.438F, 0.165F, 0.429F };
   int ldb = 4;
   float C[] = { 0.868F, 0.329F, -0.509F, 0.724F };
   int ldc = 2;
   float C_expected[] = { -0.868F, -0.329F, 0.509F, -0.724F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1484) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1484) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.832F, 0.198F, 0.794F, -0.522F, -0.319F, 0.578F, 0.332F, 0.746F };
   int lda = 1;
   float B[] = { -0.361F, 0.187F, -0.163F, -0.781F, 0.536F, 0.888F, -0.969F, 0.899F, 0.961F, -0.583F, 0.753F, 0.29F, -0.997F, 0.729F, -0.352F, -0.2F };
   int ldb = 2;
   float C[] = { 0.864F, 0.735F, -0.074F, -0.228F };
   int ldc = 1;
   float C_expected[] = { -0.864F, -0.735F, 0.074F, 0.228F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1485) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1485) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { 0.149F, 0.187F, 0.263F, -0.715F, -0.882F, -0.907F, 0.87F, -0.527F };
   int lda = 4;
   float B[] = { -0.915F, -0.249F, -0.986F, -0.799F, -0.136F, 0.712F, 0.964F, 0.799F, -0.569F, 0.686F, 0.603F, 0.758F, 0.161F, -0.698F, -0.263F, -0.256F };
   int ldb = 4;
   float C[] = { 0.622F, -0.824F, -0.482F, -0.161F };
   int ldc = 2;
   float C_expected[] = { -0.246901F, 0.083044F, 1.25556F, 0.009106F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1486) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1486) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { 0.963F, -0.943F, -0.734F, -0.253F, 0.832F, 0.545F, -0.815F, -0.434F };
   int lda = 1;
   float B[] = { 0.23F, -0.211F, 0.906F, 0.232F, -0.339F, 0.597F, -0.919F, 0.793F, 0.535F, 0.526F, 0.119F, 0.053F, 0.751F, 0.044F, 0.752F, -0.469F };
   int ldb = 2;
   float C[] = { 0.483F, -0.266F, -0.224F, -0.692F };
   int ldc = 1;
   float C_expected[] = { -0.047537F, 0.667177F, 1.02025F, 0.823778F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1487) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1487) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {-0.3F, 0.1F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { -0.657F, -0.497F, -0.293F, -0.168F, -0.943F, -0.181F, 0.569F, 0.91F };
   int lda = 1;
   float B[] = { -0.047F, 0.796F, -0.913F, 0.998F, 0.365F, 0.467F, -0.627F, -0.523F, 0.885F, 0.234F, -0.494F, 0.071F, -0.361F, -0.154F, -0.055F, -0.32F };
   int ldb = 2;
   float C[] = { 0.956F, 0.268F, 0.152F, 0.717F };
   int ldc = 2;
   float C_expected[] = { -0.668685F, 0.134477F, -0.715786F, -0.478065F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1488) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1488) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {-0.3F, 0.1F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.394F, -0.482F, 0.631F, -0.833F, 0.221F, 0.672F, 0.2F, 0.967F };
   int lda = 4;
   float B[] = { 0.708F, 0.695F, 0.111F, -0.912F, 0.376F, 0.606F, -0.997F, -0.741F, 0.349F, 0.543F, 0.372F, -0.563F, 0.129F, -0.295F, -0.672F, -0.95F };
   int ldb = 4;
   float C[] = { 0.436F, 0.752F, 0.074F, 0.209F };
   int ldc = 1;
   float C_expected[] = { -0.325083F, -0.301952F, -0.283022F, 0.339919F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1489) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1489) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {1.0F, 0.0F};
   float beta[2] = {-0.3F, 0.1F};
   float A[] = { 0.827F, -0.862F, 0.373F, -0.265F, -0.9F, 0.892F, -0.319F, 0.151F };
   int lda = 1;
   float B[] = { 0.603F, 0.816F, -0.511F, 0.831F, -0.36F, -0.954F, -0.978F, 0.485F, 0.675F, 0.186F, 0.463F, 0.144F, 0.851F, -0.458F, 0.766F, -0.213F };
   int ldb = 4;
   float C[] = { -0.335F, 0.333F, -0.4F, 0.422F };
   int ldc = 2;
   float C_expected[] = { 2.7126F, 0.702111F, 0.437661F, 0.691294F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1490) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1490) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {1.0F, 0.0F};
   float beta[2] = {-0.3F, 0.1F};
   float A[] = { 0.966F, 0.476F, -0.013F, -0.655F, 0.773F, -0.543F, -0.231F, -0.353F };
   int lda = 4;
   float B[] = { -0.684F, 0.144F, 0.018F, -0.77F, -0.688F, 0.909F, -0.094F, -0.938F, -0.757F, 0.574F, -0.479F, 0.473F, 0.0F, 0.064F, -0.168F, 0.858F };
   int ldb = 2;
   float C[] = { -0.912F, 0.54F, 0.756F, 0.024F };
   int ldc = 1;
   float C_expected[] = { -0.156236F, 0.839112F, -0.230206F, -0.106256F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1491) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1491) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {1.0F, 0.0F};
   float A[] = { 0.66F, -0.113F, -0.663F, -0.856F, 0.614F, -0.344F, -0.964F, -0.532F };
   int lda = 1;
   float B[] = { -0.606F, -0.965F, -0.279F, -0.312F, 0.63F, 0.967F, 0.041F, -0.557F, 0.663F, 0.619F, -0.134F, 0.261F, -0.388F, 0.525F, 0.222F, 0.538F };
   int ldb = 4;
   float C[] = { 0.114F, -0.376F, -0.851F, -0.682F };
   int ldc = 2;
   float C_expected[] = { 0.114F, -0.376F, -0.851F, -0.682F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1492) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1492) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {1.0F, 0.0F};
   float A[] = { 0.212F, -0.752F, 0.679F, 0.49F, -0.029F, -0.488F, 0.567F, 0.374F };
   int lda = 4;
   float B[] = { -0.914F, 0.734F, -0.845F, 0.059F, -0.297F, 0.152F, -0.417F, -0.669F, 0.831F, -0.544F, 0.022F, 0.102F, -0.379F, -0.357F, -0.394F, -0.588F };
   int ldb = 2;
   float C[] = { -0.584F, 0.373F, 0.235F, 0.521F };
   int ldc = 1;
   float C_expected[] = { -0.584F, 0.373F, 0.235F, 0.521F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1493) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1493) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 113;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.135F, 0.128F, 0.909F, -0.963F, 0.299F, -0.944F, 0.944F, 0.942F };
   int lda = 1;
   float B[] = { 0.924F, -0.317F, -0.992F, -0.854F, -0.435F, 0.102F, 0.126F, 0.862F, 0.952F, 0.68F, 0.545F, 0.168F, 0.752F, 0.549F, 0.687F, -0.76F };
   int ldb = 2;
   float C[] = { -0.369F, -0.33F, 0.849F, -0.632F };
   int ldc = 2;
   float C_expected[] = { 0.326537F, 0.37603F, -0.86067F, 0.529817F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1494) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1494) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 113;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.061F, -0.271F, -0.043F, -0.023F, 0.694F, 0.333F, 0.733F, -0.967F };
   int lda = 4;
   float B[] = { 0.088F, -0.607F, 0.589F, 0.375F, -0.897F, -0.954F, -0.216F, -0.195F, -0.865F, -0.511F, -0.219F, 0.535F, 0.976F, 0.582F, 0.464F, -0.041F };
   int ldb = 4;
   float C[] = { 0.533F, -0.63F, 0.405F, 0.667F };
   int ldc = 1;
   float C_expected[] = { -0.459906F, 0.552595F, -0.425391F, -0.533626F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1495) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1495) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 113;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {1.0F, 0.0F};
   float A[] = { -0.676F, -0.116F, 0.707F, -0.256F, -0.893F, -0.966F, 0.159F, -0.246F };
   int lda = 1;
   float B[] = { 0.059F, 0.281F, -0.93F, -0.263F, 0.583F, -0.11F, 0.639F, -0.96F, -0.878F, 0.984F, 0.058F, 0.977F, -0.567F, 0.561F, -0.048F, -0.798F };
   int ldb = 4;
   float C[] = { 0.362F, -0.808F, 0.428F, -0.112F };
   int ldc = 2;
   float C_expected[] = { 0.362F, -0.808F, 0.428F, -0.112F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1496) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1496) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 113;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {1.0F, 0.0F};
   float A[] = { -0.915F, 0.439F, 0.171F, -0.019F, 0.843F, 0.944F, -0.581F, 0.856F };
   int lda = 4;
   float B[] = { -0.284F, 0.207F, -0.27F, 0.832F, 0.894F, -0.626F, -0.305F, -0.006F, 0.562F, -0.744F, -0.533F, 0.126F, -0.375F, -0.333F, 0.275F, 0.748F };
   int ldb = 2;
   float C[] = { -0.763F, -0.829F, 0.708F, -0.613F };
   int ldc = 1;
   float C_expected[] = { -0.763F, -0.829F, 0.708F, -0.613F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1497) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1497) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 113;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { 0.496F, -0.9F, 0.825F, -0.678F, 0.41F, -0.585F, -0.264F, 0.308F };
   int lda = 1;
   float B[] = { 0.907F, 0.972F, -0.724F, 0.745F, -0.601F, 0.589F, 0.759F, -0.521F, -0.161F, -0.321F, 0.341F, -0.981F, -0.378F, -0.671F, -0.314F, -0.878F };
   int ldb = 4;
   float C[] = { -0.293F, 0.07F, 0.087F, -0.542F };
   int ldc = 2;
   float C_expected[] = { 0.10357F, -0.163927F, 0.444626F, -0.0076744F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1498) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1498) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 113;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { -0.225F, -0.629F, -0.939F, -0.836F, -0.841F, -0.794F, 0.836F, -0.65F };
   int lda = 4;
   float B[] = { 0.869F, -0.453F, 0.8F, -0.947F, 0.545F, 0.716F, -0.507F, -0.228F, 0.722F, 0.372F, 0.77F, 0.317F, -0.153F, -0.524F, -0.465F, -0.684F };
   int ldb = 2;
   float C[] = { -0.896F, 0.91F, -0.973F, -0.269F };
   int ldc = 1;
   float C_expected[] = { -1.18974F, -1.0134F, 0.189027F, -1.14494F };
   cblas_cgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cgemm(case 1499) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cgemm(case 1499) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {1, 0};
   double beta[2] = {-1, 0};
   double A[] = { -0.33, 0.457, 0.428, -0.19, 0.86, -0.53, 0.058, -0.942 };
   int lda = 4;
   double B[] = { 0.434, 0.653, -0.124, 0.191, -0.112, -0.84, -0.72, 0.075, -0.503, -0.109, 0.3, -0.898, 0.489, 0.384, 0.993, -0.804 };
   int ldb = 2;
   double C[] = { -0.792, -0.155, -0.608, -0.243 };
   int ldc = 2;
   double C_expected[] = { 0.042563, -0.465908, -0.649991, -1.621116 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1500) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1500) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {1, 0};
   double beta[2] = {-1, 0};
   double A[] = { 0.726, -0.438, -0.23, -0.054, -0.019, 0.902, -0.883, -0.235 };
   int lda = 1;
   double B[] = { 0.159, -0.18, 0.386, -0.167, 0.971, -0.072, 0.87, -0.839, 0.474, 0.956, -0.235, 0.332, 0.826, -0.056, -0.941, 0.01 };
   int ldb = 4;
   double C[] = { -0.799, 0.973, -0.549, -0.177 };
   int ldc = 1;
   double C_expected[] = { -0.181084, 0.257841, 2.251901, 1.558195 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1501) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1501) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {1, 0};
   double A[] = { 0.109, 0.892, -0.723, 0.793, 0.109, -0.419, -0.534, 0.448 };
   int lda = 4;
   double B[] = { -0.875, -0.31, -0.027, 0.067, 0.274, -0.126, -0.548, 0.497, 0.681, 0.388, 0.909, 0.889, 0.982, -0.074, -0.788, 0.233 };
   int ldb = 4;
   double C[] = { 0.503, 0.067, 0.239, 0.876 };
   int ldc = 2;
   double C_expected[] = { 0.6553584, 0.0864583, 0.2559136, 0.7518389 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1502) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1502) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {1, 0};
   double A[] = { 0.334, 0.192, -0.992, -0.168, 0.154, -0.75, -0.797, -0.76 };
   int lda = 1;
   double B[] = { -0.82, 0.147, -0.237, 0.68, 0.317, 0.257, -0.406, -0.802, 0.058, 0.012, -0.832, 0.949, -0.263, -0.085, -0.064, 0.492 };
   int ldb = 2;
   double C[] = { 0.079, -0.602, -0.392, 0.316 };
   int ldc = 1;
   double C_expected[] = { 0.0980569, -0.6430449, -0.539207, 0.4226848 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1503) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1503) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 111;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0};
   double beta[2] = {-1, 0};
   double A[] = { -0.305, -0.698, -0.072, -0.383, 0.364, -0.656, 0.819, 0.194 };
   int lda = 4;
   double B[] = { 0.682, 0.498, -0.389, 0.923, -0.853, -0.558, -0.722, -0.085, -0.27, 0.026, -0.107, -0.036, 0.644, -0.327, -0.894, 0.34 };
   int ldb = 4;
   double C[] = { 0.981, -0.336, -0.377, -0.41 };
   int ldc = 2;
   double C_expected[] = { -0.981, 0.336, 0.377, 0.41 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1504) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1504) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 111;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0};
   double beta[2] = {-1, 0};
   double A[] = { -0.306, -0.709, -0.196, 0.285, 0.873, -0.802, 0.715, -0.179 };
   int lda = 1;
   double B[] = { 0.028, 0.109, 0.87, -0.446, 0.735, 0.731, 0.021, -0.186, 0.541, 0.97, -0.333, 0.002, -0.089, -0.01, 0.331, 0.851 };
   int ldb = 2;
   double C[] = { 0.902, -0.584, -0.695, -0.607 };
   int ldc = 1;
   double C_expected[] = { -0.902, 0.584, 0.695, 0.607 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1505) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1505) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {-1, 0};
   double beta[2] = {1, 0};
   double A[] = { 0.517, -0.136, 0.72, -0.237, 0.121, -0.66, 0.005, 0.759 };
   int lda = 1;
   double B[] = { -0.606, 0.049, 0.807, -0.236, -0.258, -0.412, 0.75, -0.659, 0.993, -0.029, -0.968, 0.707, -0.362, -0.005, 0.096, -0.241 };
   int ldb = 2;
   double C[] = { 0.63, 0.922, 0.025, -0.535 };
   int ldc = 2;
   double C_expected[] = { 1.117044, 1.983417, -1.276831, -0.447092 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1506) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1506) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {-1, 0};
   double beta[2] = {1, 0};
   double A[] = { 0.064, 0.371, -0.01, -0.262, 0.143, -0.081, 0.1, -0.062 };
   int lda = 4;
   double B[] = { -0.749, 0.289, -0.239, -0.226, 0.284, 0.668, 0.305, 0.075, -0.36, 0.166, -0.416, 0.234, -0.267, 0.525, 0.116, -0.561 };
   int ldb = 4;
   double C[] = { 0.671, 0.763, 0.444, -0.246 };
   int ldc = 1;
   double C_expected[] = { 0.753107, 0.896395, 0.481996, -0.263126 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1507) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1507) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {1, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.956, -0.751, 0.671, -0.633, 0.648, -0.042, 0.948, 0.826 };
   int lda = 1;
   double B[] = { 0.921, 0.506, -0.609, 0.817, -0.686, 0.991, 0.616, -0.482, -0.02, -0.34, 0.559, 0.976, 0.431, 0.385, -0.164, -0.778 };
   int ldb = 4;
   double C[] = { 0.074, -0.01, 0.165, 0.166 };
   int ldc = 2;
   double C_expected[] = { 0.166046, 0.491557, 1.473191, -0.033821 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1508) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1508) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {1, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.698, -0.062, 0.023, 0.704, 0.443, -0.46, 0.541, 0.296 };
   int lda = 4;
   double B[] = { 0.787, -0.199, 0.835, -0.276, -0.515, 0.467, -0.76, -0.483, 0.015, -0.394, -0.748, 0.02, 0.573, 0.3, -0.088, -0.238 };
   int ldb = 2;
   double C[] = { 0.935, -0.655, -0.797, 0.071 };
   int ldc = 1;
   double C_expected[] = { -1.070679, 0.178755, -0.344714, -0.308137 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1509) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1509) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 112;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.202, -0.219, 0.741, 0.527, 0.054, 0.16, -0.359, 0.338 };
   int lda = 1;
   double B[] = { -0.872, 0.995, 0.722, 0.618, -0.27, 0.939, -0.743, 0.547, -0.864, 0.376, -0.997, -0.63, 0.887, -0.454, 0.436, -0.039 };
   int ldb = 4;
   double C[] = { -0.684, 0.463, -0.386, -0.524 };
   int ldc = 2;
   double C_expected[] = { 0.1423153, -0.066679, 0.1175618, 0.0012949 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1510) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1510) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 112;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.855, -0.173, -0.679, 0.824, 0.469, 0.786, 0.757, -0.109 };
   int lda = 4;
   double B[] = { 0.483, -0.888, -0.757, 0.551, -0.81, 0.23, -0.078, 0.725, -0.592, 0.394, 0.884, 0.802, -0.813, -0.016, -0.853, 0.783 };
   int ldb = 2;
   double C[] = { 0.181, -0.368, -0.864, -0.784 };
   int ldc = 1;
   double C_expected[] = { 0.1728438, 0.1183508, 0.2526999, 0.3004174 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1511) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1511) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 113;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {-1, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { 0.446, -0.65, -0.724, 0.014, 0.792, -0.695, -0.81, -0.358 };
   int lda = 1;
   double B[] = { -0.08, 0.216, 0.689, 0.699, 0.073, -0.346, 0.821, -0.668, -0.798, 0.869, 0.451, -0.061, -0.41, 0.316, 0.104, -0.514 };
   int ldb = 2;
   double C[] = { -0.476, 0.211, -0.912, -0.243 };
   int ldc = 2;
   double C_expected[] = { 1.372475, -0.135616, 0.549353, -1.968747 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1512) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1512) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 113;
   int transB = 111;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {-1, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { 0.669, 0.046, -0.094, 0.666, 0.23, 0.448, -0.795, -0.142 };
   int lda = 4;
   double B[] = { 0.037, -0.154, -0.739, 0.905, 0.793, -0.53, -0.34, 0.428, 0.072, -0.263, -0.603, -0.905, 0.681, -0.083, -0.511, -0.337 };
   int ldb = 4;
   double C[] = { 0.247, 0.575, -0.836, -0.883 };
   int ldc = 1;
   double C_expected[] = { -0.975939, 0.415528, 0.275533, 0.002716 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1513) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1513) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 113;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0};
   double beta[2] = {-1, 0};
   double A[] = { 0.369, 0.506, 0.217, -0.739, -0.395, 0.16, -0.329, -0.954 };
   int lda = 1;
   double B[] = { -0.622, -0.945, 0.416, -0.884, 0.797, -0.74, 0.519, -0.789, -0.348, 0.563, -0.398, -0.956, 0.227, 0.84, -0.079, 0.847 };
   int ldb = 4;
   double C[] = { 0.833, 0.761, 0.074, -0.448 };
   int ldc = 2;
   double C_expected[] = { -0.833, -0.761, -0.074, 0.448 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1514) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1514) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 113;
   int transB = 112;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {0, 0};
   double beta[2] = {-1, 0};
   double A[] = { -0.141, 0.275, 0.717, 0.775, -0.701, -0.689, -0.883, -0.077 };
   int lda = 4;
   double B[] = { -0.526, -0.437, 0.133, -0.209, -0.83, 0.328, 0.916, -0.337, 0.762, -0.664, -0.566, 0.955, 0.168, 0.488, -0.172, -0.535 };
   int ldb = 2;
   double C[] = { -0.88, 0.945, 0.416, 0.99 };
   int ldc = 1;
   double C_expected[] = { 0.88, -0.945, -0.416, -0.99 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1515) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1515) imag");
     };
   };
  };


  {
   int order = 101;
   int transA = 113;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {0, 0.1};
   double A[] = { -0.534, -0.013, -0.258, -0.31, -0.211, -0.883, -0.89, -0.499 };
   int lda = 1;
   double B[] = { -0.185, -0.798, -0.34, 0.716, 0.035, 0.968, -0.26, 0.784, -0.889, -0.344, -0.685, -0.647, -0.764, 0.03, 0.626, -0.989 };
   int ldb = 4;
   double C[] = { -0.793, -0.551, 0.182, 0.838 };
   int ldc = 2;
   double C_expected[] = { -0.5507177, -0.0286821, 0.2222276, 0.5197398 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1516) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1516) imag");
     };
   };
  };


  {
   int order = 102;
   int transA = 113;
   int transB = 113;
   int M = 1;
   int N = 2;
   int K = 4;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {0, 0.1};
   double A[] = { 0.575, -0.128, -0.702, 0.758, 0.383, -0.914, 0.157, 0.368 };
   int lda = 4;
   double B[] = { 0.572, -0.841, 0.223, -0.334, -0.823, -0.84, 0.671, -0.871, 0.241, 0.927, -0.344, 0.281, -0.034, -0.104, 0.587, -0.329 };
   int ldb = 2;
   double C[] = { -0.612, 0.167, 0.647, 0.447 };
   int ldc = 1;
   double C_expected[] = { -0.7876717, 0.0341179, -0.0800018, 0.5717566 };
   cblas_zgemm(order, transA, transB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zgemm(case 1517) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zgemm(case 1517) imag");
     };
   };
  };


}
