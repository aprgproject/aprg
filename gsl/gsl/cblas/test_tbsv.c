#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_tbsv (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { -0.354651F, -2.40855F, 0.481076F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1230)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { -0.305F, 0.84973F, -1.00859F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1231)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { -2.71619F, -1.09055F, -3.97608F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1232)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { -0.56589F, 0.303361F, -0.831F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1233)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { 1.30901F, -0.656172F, -5.13458F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1234)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { -0.305F, 0.8723F, -0.509121F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1235)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { 0.524539F, -0.961964F, 1.22026F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1236)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.681F, 0.209F, 0.436F, -0.369F, 0.786F, -0.84F, 0.86F, -0.233F, 0.734F };
   float X[] = { -0.305F, 0.61F, -0.831F };
   int incX = -1;
   float x_expected[] = { -0.920972F, 0.783679F, -0.831F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1237)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 16.8676F, 17.3503F, 5.27273F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1238)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 0.209676F, 0.54278F, 0.116F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1239)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 0.212077F, -5.01482F, -1.14722F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1240)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 0.144F, 0.615848F, 0.242249F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1241)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 1.28844F, -5.49514F, 0.145912F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1242)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 0.0563823F, 0.65878F, 0.116F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1243)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 1.08271F, -3.73662F, 140.301F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1244)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.022F, 0.795F, -0.389F, -0.205F, -0.121F, 0.323F, 0.133F, 0.679F, 0.742F };
   float X[] = { 0.144F, 0.635F, 0.116F };
   int incX = -1;
   float x_expected[] = { 0.144F, 0.652424F, -0.402677F };
   cblas_stbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbsv(case 1245)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { -0.967930029155, 0.138412575592, 0.506166027443 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1246)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { 0.332, 0.819736, 0.615143048 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1247)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { -0.364842154056, -0.326531140246, -0.568848758465 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1248)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { 0.588397988, 0.747516, 0.252 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1249)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { -0.550580431177, -0.571849444278, 0.248263427151 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1250)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { 0.332, 0.701876, 0.696287508 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1251)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { 1.50217883761, -1.21382140588, 0.407108239095 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1252)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.619, -0.443, 0.957, -0.633, -0.698, 0.783, -0.343, -0.603, 0.735 };
   double X[] = { 0.332, 0.588, 0.252 };
   int incX = -1;
   double x_expected[] = { 0.820345928, 0.699636, 0.252 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1253)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { 18.994209959, 20.323927329, 2.7135678392 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1254)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { 1.06925836, 0.72162, -0.54 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1255)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { -3.27683615819, -4.47682615869, -1.97425326753 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1256)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { 0.58, 0.11952, -0.53844624 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1257)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { -6.6461072986, -0.788837290809, -1.78217821782 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1258)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { 0.16345912, 0.55098, -0.54 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1259)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { 0.767195767196, -82.9352869353, -123.564783625 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1260)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.199, 0.303, -0.705, -0.013, -0.678, 0.547, 0.756, -0.177, -0.079 };
   double X[] = { 0.58, 0.558, -0.54 };
   int incX = -1;
   double x_expected[] = { 0.58, 0.95124, -0.82822572 };
   cblas_dtbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbsv(case 1261)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { 1.28871F, 0.289887F, 1.76043F, 1.27481F, 1.56506F, -2.35181F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1262) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1262) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { 0.11F, 0.787F, -1.04259F, 0.18935F, 0.228474F, -0.564917F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1263) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1263) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { -0.0906249F, 3.09442F, -1.60036F, 1.28475F, -0.582941F, 0.0383898F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1264) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1264) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { 1.05233F, 0.79657F, -0.566883F, 1.46031F, -0.437F, 0.592F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1265) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1265) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { -0.735844F, 1.11782F, -0.28244F, 1.16117F, -0.66707F, 0.938302F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1266) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1266) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { 0.11F, 0.787F, -0.406239F, 0.580226F, -0.171935F, 1.2125F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1267) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1267) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { 1.70081F, 2.20477F, 1.32753F, -0.522112F, 0.0223652F, -0.62248F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1268) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1268) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { -0.975F, -0.667F, 0.813F, -0.962F, -0.961F, 0.226F, -0.503F, 0.809F, 0.81F, -0.162F, -0.027F, -0.044F, 0.212F, 0.563F, 0.446F, -0.392F, 0.798F, -0.07F };
   float X[] = { 0.11F, 0.787F, -0.826F, 0.809F, -0.437F, 0.592F };
   int incX = -1;
   float x_expected[] = { 0.967596F, 0.693563F, -1.04022F, -0.09269F, -0.437F, 0.592F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1269) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1269) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { -1.11985F, 0.801655F, 0.273814F, -1.09438F, -0.52531F, 0.166748F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1270) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1270) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { 0.266087F, 0.618557F, 0.031897F, -0.914419F, -0.134F, 0.179F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1271) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1271) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { -0.762749F, -0.016292F, 1.59299F, 0.158751F, -4.75603F, -1.78591F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1272) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1272) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { -0.509F, 0.608F, -0.332731F, -1.24444F, 0.262904F, 1.21961F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1273) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1273) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { -1.76046F, 0.0455463F, 1.38348F, 0.700097F, -0.669451F, 0.321896F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1274) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1274) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { 0.151523F, 0.78611F, 0.120309F, -1.01387F, -0.134F, 0.179F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1275) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1275) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { -1.00779F, -0.620278F, 0.81164F, -1.90759F, -1.32022F, 1.48356F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1276) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1276) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.33F, -0.236F, 0.267F, -0.139F, 0.25F, 0.509F, 0.86F, -0.089F, -0.018F, -0.847F, 0.424F, -0.573F, 0.097F, -0.663F, 0.65F, -0.811F, 0.283F, 0.032F };
   float X[] = { -0.509F, 0.608F, 0.021F, -0.848F, -0.134F, 0.179F };
   int incX = -1;
   float x_expected[] = { -0.509F, 0.608F, -0.503138F, -1.26818F, 0.176615F, 0.447668F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1277) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1277) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { -0.613838F, -1.13321F, -1.34847F, 0.0432903F, 0.0879552F, -0.479334F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1278) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1278) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { 0.76323F, -1.23595F, 0.943058F, -0.618694F, 0.296F, 0.034F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1279) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1279) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { -1.15557F, -2.50103F, -3.85402F, -1.04833F, 0.414582F, 5.91218F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1280) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1280) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { -0.037F, -0.599F, 1.39953F, -0.064424F, 1.0801F, -0.481747F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1281) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1281) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { -3.0802F, -9.09377F, -1.05845F, 0.99239F, 0.259763F, -0.687744F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1282) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1282) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { -0.513897F, 0.632031F, 1.14112F, -0.580648F, 0.296F, 0.034F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1283) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1283) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { 0.360899F, -0.456643F, -2.31803F, 0.257877F, 1.56928F, -0.922115F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1284) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1284) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   float A[] = { 0.041F, -0.61F, 0.099F, -0.393F, 0.357F, -0.984F, -0.576F, -0.342F, -0.903F, -0.083F, -0.157F, -0.694F, 0.768F, 0.688F, 0.203F, -0.079F, 0.298F, -0.424F };
   float X[] = { -0.037F, -0.599F, 0.959F, -0.499F, 0.296F, 0.034F };
   int incX = -1;
   float x_expected[] = { -0.037F, -0.599F, 0.875872F, -1.03683F, -0.198184F, -0.207572F };
   cblas_ctbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbsv(case 1285) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbsv(case 1285) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { 0.0490338308139, -0.158433417494, 0.261604043488, 1.28058846321, 1.77633350191, -1.07039599422 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1286) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1286) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { -0.123, 0.122, 0.96534, 0.346049, 1.067212328, 0.445330131 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1287) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1287) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { 72.7437666278, 10.4206532927, -4.34946941374, -14.8012581742, 2.01859491883, -1.53922125931 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1288) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1288) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { -0.464775024, 0.662224708, -0.0457, 0.610264, 0.942, 0.98 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1289) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1289) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { -0.591747295323, -0.534096923761, -4.60251824353, 1.70172936273, -4.94687072873, -3.32536493524 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1290) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1290) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { -0.123, 0.122, 0.807692, 0.373091, 0.384974988, 1.400879194 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1291) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1291) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { -0.129998778267, -0.116630230861, 0.993340886904, 0.530739563688, 1.55891621291, -0.284019181928 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1292) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1292) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.474, 0.715, 0.061, 0.532, 0.004, -0.318, 0.37, -0.692, -0.166, 0.039, -0.946, 0.857, -0.922, -0.491, 0.012, -0.217, -0.674, -0.429 };
   double X[] = { -0.123, 0.122, 0.981, 0.321, 0.942, 0.98 };
   int incX = -1;
   double x_expected[] = { 0.107496032, 0.025821594, 1.444898, -0.239924, 0.942, 0.98 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1293) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1293) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { -0.825842176606, 0.212941473892, -0.548817434511, -0.703261551538, 0.0746069436827, 0.425751789407 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1294) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1294) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { -0.619710352, 0.018225936, 1.211252, 0.891864, 0.293, -0.434 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1295) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1295) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { 0.203289119964, 1.58288482537, -1.7720160159, 0.479463518178, -0.511241930019, -1.79333888299 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1296) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1296) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { -0.373, 0.566, 0.618602, -0.084689, 0.887531803, -0.570220771 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1297) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1297) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { 1.72799012007, 13.4612400765, 4.46126528205, -0.0212528722047, 0.627282377919, 0.302760084926 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1298) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1298) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { -1.280839615, 1.560525655, 1.167331, 0.179227, 0.293, -0.434 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1299) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1299) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { -0.594503951847, 0.00287302167266, -1.08185265666, -0.859860374254, 0.0331027077244, 1.28233265933 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1300) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1300) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { -0.872, -0.841, 0.108, -0.744, 0.231, -0.513, -0.973, 0.087, 0.348, 0.196, 0.447, 0.307, 0.632, -0.949, 0.322, 0.277, 0.282, 0.831 };
   double X[] = { -0.373, 0.566, 0.92, 0.627, 0.293, -0.434 };
   int incX = -1;
   double x_expected[] = { -0.373, 0.566, 1.16074, 0.50314, -0.20669608, 0.37525144 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1301) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1301) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { 0.0654496252357, 0.224007771015, -0.752486084395, -0.554870892947, -0.587163401057, 0.166737652215 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1302) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1302) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { -0.595558802, -1.147174647, 0.589506, -0.500919, -0.126, 0.459 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1303) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1303) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { 3.39346077201, 0.652889512141, -2.33602680355, -2.7859245153, -5.04672104102, -0.334110541026 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1304) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1304) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { 0.028, -0.804, -0.109456, -0.217192, -0.41110804, 0.41693792 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1305) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1305) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { 7.16970224467, -0.772071373678, 0.833386981173, -0.673826630129, -0.26524050899, 0.465327628365 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1306) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1306) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { 0.471459157, -1.566755859, 0.940839, 0.357132, -0.126, 0.459 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1307) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1307) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { -0.909961830373, 0.118063054039, -0.0169425582229, -1.00055409731, -1.37205489923, 0.994032418785 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1308) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1308) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 3;
   int K = 1;
   int lda = 3;
   double A[] = { 0.404, 0.667, 0.861, 0.22, 0.298, -0.858, -0.682, -0.969, 0.327, -0.86, 0.125, 0.606, -0.143, -0.865, -0.036, 0.23, -0.776, 0.079 };
   double X[] = { 0.028, -0.804, 0.582, -0.078, -0.126, 0.459 };
   int incX = -1;
   double x_expected[] = { 0.028, -0.804, -0.118596, 0.160828, -0.059271004, 0.294435972 };
   cblas_ztbsv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbsv(case 1309) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbsv(case 1309) imag");
     };
   };
  };


}
