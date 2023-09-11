#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_syrk (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = -1.0F;
   float beta = 0.1F;
   float A[] = { 0.412F, -0.229F };
   int lda = 1;
   float C[] = { 0.628F, -0.664F, -0.268F, 0.096F };
   int ldc = 2;
   float C_expected[] = { -0.106944F, 0.027948F, -0.268F, -0.042841F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1566)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = -1.0F;
   float beta = 0.1F;
   float A[] = { 0.101F, -0.653F };
   int lda = 2;
   float C[] = { 0.432F, 0.107F, -0.952F, -0.532F };
   int ldc = 2;
   float C_expected[] = { 0.032999F, 0.107F, -0.029247F, -0.479609F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1567)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha = 1.0F;
   float beta = 0.1F;
   float A[] = { 0.79F, 0.595F };
   int lda = 2;
   float C[] = { 0.257F, 0.183F, -0.021F, -0.053F };
   int ldc = 2;
   float C_expected[] = { 0.6498F, 0.48835F, -0.021F, 0.348725F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1568)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha = 1.0F;
   float beta = 0.1F;
   float A[] = { -0.181F, -0.654F };
   int lda = 1;
   float C[] = { -0.4F, 0.615F, 0.147F, -0.163F };
   int ldc = 2;
   float C_expected[] = { -0.007239F, 0.615F, 0.133074F, 0.411416F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1569)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = 0.0F;
   float beta = -1.0F;
   float A[] = { -0.191F, 0.584F };
   int lda = 1;
   float C[] = { -0.719F, -0.681F, -0.003F, 0.544F };
   int ldc = 2;
   float C_expected[] = { 0.719F, -0.681F, 0.003F, -0.544F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1570)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = 0.0F;
   float beta = -1.0F;
   float A[] = { 0.788F, 0.041F };
   int lda = 2;
   float C[] = { 0.029F, 0.365F, 0.739F, -0.769F };
   int ldc = 2;
   float C_expected[] = { -0.029F, -0.365F, 0.739F, 0.769F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1571)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha = -0.3F;
   float beta = -1.0F;
   float A[] = { 0.733F, 0.678F };
   int lda = 2;
   float C[] = { -0.941F, 0.96F, 0.07F, -0.295F };
   int ldc = 2;
   float C_expected[] = { 0.779813F, 0.96F, -0.219092F, 0.157095F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1572)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha = -0.3F;
   float beta = -1.0F;
   float A[] = { -0.87F, 0.675F };
   int lda = 1;
   float C[] = { -0.602F, -0.432F, -0.984F, 0.384F };
   int ldc = 2;
   float C_expected[] = { 0.37493F, 0.608175F, -0.984F, -0.520687F };
   cblas_ssyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssyrk(case 1573)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 0.1;
   double beta = -0.3;
   double A[] = { 0.169, -0.875 };
   int lda = 1;
   double C[] = { 0.159, 0.277, 0.865, 0.346 };
   int ldc = 2;
   double C_expected[] = { -0.0448439, -0.0978875, 0.865, -0.0272375 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1574)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 0.1;
   double beta = -0.3;
   double A[] = { 0.536, -0.725 };
   int lda = 2;
   double C[] = { 0.154, -0.445, -0.841, -0.91 };
   int ldc = 2;
   double C_expected[] = { -0.0174704, -0.445, 0.21344, 0.3255625 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1575)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha = 0;
   double beta = -1;
   double A[] = { -0.07, 0.8 };
   int lda = 2;
   double C[] = { 0.823, -0.88, -0.136, 0.793 };
   int ldc = 2;
   double C_expected[] = { -0.823, 0.88, -0.136, -0.793 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1576)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha = 0;
   double beta = -1;
   double A[] = { -0.058, 0.649 };
   int lda = 1;
   double C[] = { -0.187, 0.294, -0.004, -0.933 };
   int ldc = 2;
   double C_expected[] = { 0.187, 0.294, 0.004, 0.933 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1577)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 1;
   double beta = -1;
   double A[] = { 0.263, -0.289 };
   int lda = 1;
   double C[] = { 0.554, -0.679, 0.993, 0.758 };
   int ldc = 2;
   double C_expected[] = { -0.484831, -0.679, -1.069007, -0.674479 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1578)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 1;
   double beta = -1;
   double A[] = { -0.265, -0.837 };
   int lda = 2;
   double C[] = { -0.994, 0.967, -0.34, -0.069 };
   int ldc = 2;
   double C_expected[] = { 1.064225, -0.745195, -0.34, 0.769569 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1579)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { -0.464, 0.394 };
   int lda = 2;
   double C[] = { -0.45, -0.447, 0.649, 0.055 };
   int ldc = 2;
   double C_expected[] = { -0.5145888, -0.447, 0.7038448, 0.0084292 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1580)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { 0.815, 0.168 };
   int lda = 1;
   double C[] = { 0.817, -0.957, -0.395, -0.382 };
   int ldc = 2;
   double C_expected[] = { 0.6177325, -0.998076, -0.395, -0.3904672 };
   cblas_dsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsyrk(case 1581)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {-0.3F, 0.1F};
   float A[] = { 0.447F, -0.507F, -0.425F, 0.701F };
   int lda = 1;
   float C[] = { 0.16F, -0.245F, 0.922F, -0.437F, 0.24F, 0.008F, -0.095F, 0.749F };
   int ldc = 2;
   float C_expected[] = { -0.0235F, 0.0895F, -0.2329F, 0.2233F, 0.24F, 0.008F, -0.0464F, -0.2342F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1582) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1582) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha[2] = {0.0F, 0.0F};
   float beta[2] = {-0.3F, 0.1F};
   float A[] = { -0.421F, -0.435F, -0.914F, -0.493F };
   int lda = 2;
   float C[] = { -0.761F, -0.38F, 0.043F, -0.999F, 0.779F, 0.238F, 0.082F, 0.394F };
   int ldc = 2;
   float C_expected[] = { 0.2663F, 0.0379F, 0.043F, -0.999F, -0.2575F, 0.0065F, -0.064F, -0.11F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1583) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1583) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {-0.3F, 0.1F};
   float A[] = { 0.827F, -0.896F, 0.417F, 0.865F };
   int lda = 2;
   float C[] = { -0.349F, -0.31F, 0.972F, 0.794F, -0.906F, -0.595F, -0.089F, -0.333F };
   int ldc = 2;
   float C_expected[] = { 0.254587F, 1.54008F, -1.4909F, -0.482723F, -0.906F, -0.595F, 0.634336F, -0.63041F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1584) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1584) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {-0.3F, 0.1F};
   float A[] = { 0.607F, 0.747F, -0.889F, 0.333F };
   int lda = 1;
   float C[] = { 0.244F, 0.564F, 0.009F, 0.578F, -0.827F, 0.558F, -0.337F, 0.731F };
   int ldc = 2;
   float C_expected[] = { 0.05996F, -1.05166F, 0.009F, 0.578F, 0.980674F, 0.211852F, -0.651432F, 0.339074F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1585) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1585) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha[2] = {1.0F, 0.0F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { 0.784F, -0.281F, -0.88F, 0.479F };
   int lda = 1;
   float C[] = { 0.491F, 0.531F, 0.805F, -0.097F, 0.728F, 0.674F, -0.705F, -0.754F };
   int ldc = 2;
   float C_expected[] = { 0.004695F, 0.050392F, 0.805F, -0.097F, -1.22932F, 1.35082F, 1.29896F, -1.54804F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1586) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1586) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha[2] = {1.0F, 0.0F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { 0.272F, -0.146F, 0.155F, 0.038F };
   int lda = 2;
   float C[] = { 0.533F, -0.41F, -0.904F, 0.301F, -0.836F, 0.57F, -0.374F, -0.293F };
   int ldc = 2;
   float C_expected[] = { 0.462668F, 0.453576F, -0.253292F, -0.916294F, -0.836F, 0.57F, 0.315581F, -0.36222F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1587) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1587) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { -0.055F, -0.127F, -0.896F, -0.625F };
   int lda = 2;
   float C[] = { -0.619F, 0.511F, -0.877F, 0.557F, -0.801F, -0.437F, -0.922F, 0.332F };
   int ldc = 2;
   float C_expected[] = { 0.60503F, -0.524104F, -0.877F, 0.557F, 0.652833F, 0.406905F, -0.198F, 0.080191F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1588) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1588) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { -0.528F, 0.759F, -0.079F, 0.952F };
   int lda = 1;
   float C[] = { 0.775F, 0.855F, 0.786F, 0.525F, 0.85F, 0.044F, 0.658F, 0.947F };
   int ldc = 2;
   float C_expected[] = { 0.026504F, -1.1523F, -0.223383F, -1.20586F, 0.85F, 0.044F, -0.507584F, -1.84706F };
   cblas_csyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csyrk(case 1589) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csyrk(case 1589) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   double A[] = { -0.049, -0.687, -0.434, 0.294 };
   int lda = 1;
   double C[] = { 0.937, -0.113, 0.796, 0.293, 0.876, -0.199, -0.757, -0.103 };
   int ldc = 2;
   double C_expected[] = { 0.467432, -0.045674, 1.019244, 0.576752, 0.876, -0.199, -0.65508, -0.358192 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1590) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1590) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   double A[] = { 0.359, -0.364, 0.926, -0.69 };
   int lda = 2;
   double C[] = { 0.306, 0.249, 0.28, 0.229, 0.866, 0.092, 0.886, -0.283 };
   int ldc = 2;
   double C_expected[] = { 0.302385, -0.012352, 0.28, 0.229, 0.947274, -0.492774, 1.267376, -1.56088 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1591) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1591) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {0, 0};
   double A[] = { 0.607, 0.555, -0.85, 0.831 };
   int lda = 2;
   double C[] = { 0.069, 0.368, 0.551, -0.912, -0.243, -0.063, -0.924, 0.192 };
   int ldc = 2;
   double C_expected[] = { -0.0855042, -0.1960886, 0.2898798, -0.1075156, -0.243, -0.063, 0.1316883, 0.4270039 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1592) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1592) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {0, 0};
   double A[] = { 0.427, 0.86, -0.136, 0.002 };
   int lda = 1;
   double C[] = { 0.398, -0.47, 0.011, -0.547, -0.106, 0.016, 0.681, 0.246 };
   int ldc = 2;
   double C_expected[] = { 0.0937373, -0.2760591, 0.011, -0.547, 0.0295482, 0.0288526, -0.0054932, 0.0020124 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1593) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1593) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {1, 0};
   double A[] = { 0.718, 0.023, 0.355, -0.492 };
   int lda = 1;
   double C[] = { -0.637, -0.727, -0.475, -0.776, 0.802, -0.55, -0.837, 0.222 };
   int ldc = 2;
   double C_expected[] = { -0.7948013, -0.6854089, -0.475, -0.776, 0.7566473, -0.4198521, -0.7672563, 0.3151921 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1594) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1594) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {1, 0};
   double A[] = { 0.209, 0.139, -0.202, -0.223 };
   int lda = 2;
   double C[] = { -0.695, 0.524, 0.212, -0.88, -0.752, 0.291, 0.684, -0.124 };
   int ldc = 2;
   double C_expected[] = { -0.7081182, 0.5090054, 0.2228348, -0.8587166, -0.752, 0.291, 0.6776683, -0.1519201 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1595) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1595) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {1, 0};
   double A[] = { -0.365, -0.624, 0.632, 0.348 };
   int lda = 2;
   double C[] = { 0.877, 0.927, -0.377, 0.967, 0.008, 0.292, -0.779, 0.794 };
   int ldc = 2;
   double C_expected[] = { 0.9082933, 0.7647289, -0.377, 0.967, 0.0641972, 0.4470636, -0.9064832, 0.6898704 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1596) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1596) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 112;
   int N = 2;
   int K = 1;
   double alpha[2] = {-0.3, 0.1};
   double beta[2] = {1, 0};
   double A[] = { -0.067, -0.586, 0.208, 0.331 };
   int lda = 1;
   double C[] = { 0.584, -0.454, 0.93, 0.782, 0.489, -0.278, 0.081, -0.919 };
   int ldc = 2;
   double C_expected[] = { 0.6778197, -0.5114479, 0.8903975, 0.8432225, 0.489, -0.278, 0.0871195, -0.9669385 };
   cblas_zsyrk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsyrk(case 1597) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsyrk(case 1597) imag");
     };
   };
  };


}
