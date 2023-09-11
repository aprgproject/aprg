#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_sbmv (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { -0.236236F, -0.215242F, 0.266757F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1102)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { -0.236236F, -0.215242F, 0.266757F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1103)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { 0.187592F, -0.01232F, -0.040176F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1104)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { 0.187592F, -0.01232F, -0.040176F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1105)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { 0.187592F, -0.01232F, -0.040176F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1106)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { 0.187592F, -0.01232F, -0.040176F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1107)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { -0.236236F, -0.215242F, 0.266757F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1108)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   float alpha = 1.0F;
   float beta = 0.0F;
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.627F, -0.312F, 0.031F, 0.308F, 0.323F, -0.578F, 0.797F, 0.545F, -0.476F };
   float X[] = { -0.542F, 0.606F, 0.727F };
   int incX = -1;
   float Y[] = { 0.755F, 0.268F, -0.99F };
   int incY = -1;
   float y_expected[] = { -0.236236F, -0.215242F, 0.266757F };
   cblas_ssbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "ssbmv(case 1109)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1110)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1111)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1112)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1113)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1114)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1115)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1116)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   double alpha = 0;
   double beta = 1;
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.83, -0.568, -0.888, 0.281, -0.779, -0.148, 0.138, 0.053, -0.757 };
   double X[] = { 0.166, 0.808, 0.723 };
   int incX = -1;
   double Y[] = { 0.9, 0.99, -0.578 };
   int incY = -1;
   double y_expected[] = { 0.9, 0.99, -0.578 };
   cblas_dsbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dsbmv(case 1117)");
     }
   };
  };


}
