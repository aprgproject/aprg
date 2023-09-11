#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_her2 (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.821F, 0.954F };
   float X[] = { 0.532F, 0.802F };
   int incX = -1;
   float Y[] = { 0.016F, -0.334F };
   int incY = -1;
   float A_expected[] = { -0.302288F, 0.0F };
   cblas_cher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher2(case 1450) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher2(case 1450) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.821F, 0.954F };
   float X[] = { 0.532F, 0.802F };
   int incX = -1;
   float Y[] = { 0.016F, -0.334F };
   int incY = -1;
   float A_expected[] = { -0.302288F, 0.0F };
   cblas_cher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher2(case 1451) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher2(case 1451) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.821F, 0.954F };
   float X[] = { 0.532F, 0.802F };
   int incX = -1;
   float Y[] = { 0.016F, -0.334F };
   int incY = -1;
   float A_expected[] = { -0.302288F, 0.0F };
   cblas_cher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher2(case 1452) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher2(case 1452) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.821F, 0.954F };
   float X[] = { 0.532F, 0.802F };
   int incX = -1;
   float Y[] = { 0.016F, -0.334F };
   int incY = -1;
   float A_expected[] = { -0.302288F, 0.0F };
   cblas_cher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher2(case 1453) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher2(case 1453) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   double alpha[2] = {-0.3, 0.1};
   double A[] = { -0.334, 0.286 };
   double X[] = { -0.14, -0.135 };
   int incX = -1;
   double Y[] = { 0.455, 0.358 };
   int incY = -1;
   double A_expected[] = { -0.264521, 0.0 };
   cblas_zher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher2(case 1454) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher2(case 1454) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   double alpha[2] = {-0.3, 0.1};
   double A[] = { -0.334, 0.286 };
   double X[] = { -0.14, -0.135 };
   int incX = -1;
   double Y[] = { 0.455, 0.358 };
   int incY = -1;
   double A_expected[] = { -0.264521, 0.0 };
   cblas_zher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher2(case 1455) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher2(case 1455) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   double alpha[2] = {-0.3, 0.1};
   double A[] = { -0.334, 0.286 };
   double X[] = { -0.14, -0.135 };
   int incX = -1;
   double Y[] = { 0.455, 0.358 };
   int incY = -1;
   double A_expected[] = { -0.264521, 0.0 };
   cblas_zher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher2(case 1456) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher2(case 1456) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   double alpha[2] = {-0.3, 0.1};
   double A[] = { -0.334, 0.286 };
   double X[] = { -0.14, -0.135 };
   int incX = -1;
   double Y[] = { 0.455, 0.358 };
   int incY = -1;
   double A_expected[] = { -0.264521, 0.0 };
   cblas_zher2(order, uplo, N, alpha, X, incX, Y, incY, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher2(case 1457) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher2(case 1457) imag");
     };
   };
  };


}
