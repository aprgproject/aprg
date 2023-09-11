#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_hemm (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.126F, 0.079F };
   int lda = 1;
   float B[] = { -0.954F, -0.059F, 0.296F, -0.988F };
   int ldb = 2;
   float C[] = { -0.859F, -0.731F, 0.737F, 0.593F };
   int ldc = 2;
   float C_expected[] = { 0.0723566F, -0.0738796F, -0.0717488F, 0.0699704F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1550) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1550) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {0.0F, 0.1F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { 0.652F, 0.584F };
   int lda = 1;
   float B[] = { -0.983F, -0.734F, -0.422F, -0.825F };
   int ldb = 1;
   float C[] = { 0.387F, 0.341F, -0.734F, 0.632F };
   int ldc = 1;
   float C_expected[] = { 0.0137568F, -0.0253916F, -0.00941F, -0.100914F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1551) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1551) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.78F, 0.885F, 0.507F, 0.765F, 0.911F, -0.461F, 0.707F, 0.508F };
   int lda = 2;
   float B[] = { -0.905F, 0.633F, 0.85F, -0.943F };
   int ldb = 2;
   float C[] = { 0.045F, -0.237F, 0.078F, -0.252F };
   int ldc = 2;
   float C_expected[] = { 0.589611F, -0.759345F, 0.960095F, -0.09013F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1552) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1552) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-1.0F, 0.0F};
   float A[] = { 0.947F, 0.939F, -0.267F, -0.819F, -0.827F, -0.937F, 0.991F, 0.838F };
   int lda = 2;
   float B[] = { 0.871F, -0.988F, -0.232F, -0.434F };
   int ldb = 1;
   float C[] = { -0.261F, 0.927F, -0.351F, -0.203F };
   int ldc = 1;
   float C_expected[] = { 1.0551F, 0.496359F, 0.780145F, -1.67298F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1553) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1553) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.593F, -0.9F };
   int lda = 1;
   float B[] = { -0.861F, 0.747F, -0.984F, 0.595F };
   int ldb = 2;
   float C[] = { -0.589F, -0.671F, -0.011F, -0.417F };
   int ldc = 2;
   float C_expected[] = { -0.510573F, 0.442971F, -0.583512F, 0.352835F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1554) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1554) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 0.0F};
   float A[] = { -0.79F, 0.132F };
   int lda = 1;
   float B[] = { -0.243F, -0.12F, 0.633F, -0.556F };
   int ldb = 1;
   float C[] = { -0.658F, -0.74F, -0.47F, 0.481F };
   int ldc = 1;
   float C_expected[] = { -0.19197F, -0.0948F, 0.50007F, -0.43924F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1555) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1555) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-0.3F, 0.1F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { -0.114F, -0.515F, -0.513F, -0.527F, -0.995F, 0.986F, 0.229F, -0.076F };
   int lda = 2;
   float B[] = { 0.084F, 0.522F, 0.61F, 0.694F };
   int ldb = 2;
   float C[] = { 0.802F, 0.136F, -0.161F, -0.364F };
   int ldc = 2;
   float C_expected[] = { 0.269101F, 0.716492F, 0.237088F, 0.0290666F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1556) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1556) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-0.3F, 0.1F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { 0.798F, -0.324F, -0.693F, -0.893F, -0.223F, 0.749F, 0.102F, -0.357F };
   int lda = 2;
   float B[] = { -0.572F, -0.569F, -0.391F, -0.938F };
   int ldb = 1;
   float C[] = { 0.152F, -0.834F, -0.633F, -0.473F };
   int ldc = 1;
   float C_expected[] = { 1.08642F, -0.113853F, 0.234826F, -0.48289F };
   cblas_chemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "chemm(case 1557) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "chemm(case 1557) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 0.1};
   double beta[2] = {0, 0.1};
   double A[] = { -0.359, 0.089 };
   int lda = 1;
   double B[] = { -0.451, -0.337, -0.901, -0.871 };
   int ldb = 2;
   double C[] = { 0.729, 0.631, 0.364, 0.246 };
   int ldc = 2;
   double C_expected[] = { -0.0751983, 0.0890909, -0.0558689, 0.0687459 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1558) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1558) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 0.1};
   double beta[2] = {0, 0.1};
   double A[] = { 0.044, -0.496 };
   int lda = 1;
   double B[] = { -0.674, 0.281, 0.366, 0.888 };
   int ldb = 1;
   double C[] = { -0.9, 0.919, 0.857, -0.049 };
   int ldc = 1;
   double C_expected[] = { -0.0931364, -0.0929656, 0.0009928, 0.0873104 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1559) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1559) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {0, 0.1};
   double A[] = { -0.314, 0.115, 0.114, 0.878, 0.961, -0.224, 0.973, 0.771 };
   int lda = 2;
   double B[] = { 0.5, -0.016, -0.5, 0.149 };
   int ldb = 2;
   double C[] = { -0.054, 0.064, 0.02, 0.245 };
   int ldc = 2;
   double C_expected[] = { -0.0064, -0.0054, -0.0245, 0.002 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1560) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1560) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {0, 0.1};
   double A[] = { 0.186, 0.578, 0.797, -0.957, -0.539, -0.969, -0.21, 0.354 };
   int lda = 2;
   double B[] = { 0.641, -0.968, 0.15, -0.569 };
   int ldb = 1;
   double C[] = { -0.556, -0.9, 0.197, 0.31 };
   int ldc = 1;
   double C_expected[] = { 0.09, -0.0556, -0.031, 0.0197 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1561) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1561) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   double A[] = { 0.323, 0.641 };
   int lda = 1;
   double B[] = { -0.188, 0.091, -0.235, 0.523 };
   int ldb = 2;
   double C[] = { 0.919, 0.806, 0.823, -0.94 };
   int ldc = 2;
   double C_expected[] = { 0.858276, 0.835393, 0.747095, -0.771071 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1562) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1562) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   double A[] = { -0.688, 0.915 };
   int lda = 1;
   double B[] = { 0.914, -0.204, 0.205, -0.476 };
   int ldb = 1;
   double C[] = { 0.27, -0.628, -0.079, 0.507 };
   int ldc = 1;
   double C_expected[] = { -0.358832, -0.487648, -0.22004, 0.834488 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1563) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1563) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 1};
   double beta[2] = {0, 0.1};
   double A[] = { 0.681, 0.574, -0.425, -0.64, 0.792, 0.661, -0.009, 0.005 };
   int lda = 2;
   double B[] = { -0.221, 0.554, -0.465, -0.95 };
   int ldb = 2;
   double C[] = { 0.331, -0.958, -0.826, -0.972 };
   int ldc = 2;
   double C_expected[] = { 0.778291, 0.142269, -0.496199, 0.112747 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1564) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1564) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 1};
   double beta[2] = {0, 0.1};
   double A[] = { 0.959, 0.34, -0.23, 0.064, 0.516, -0.275, 0.714, 0.899 };
   int lda = 2;
   double B[] = { -0.502, -0.987, -0.134, 0.215 };
   int ldb = 1;
   double C[] = { 0.929, 0.181, -0.16, -0.921 };
   int ldc = 1;
   double C_expected[] = { 0.986459, -0.371458, -0.320548, -0.059384 };
   cblas_zhemm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zhemm(case 1565) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zhemm(case 1565) imag");
     };
   };
  };


}
