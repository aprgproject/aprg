#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_her (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   float alpha = 1.0F;
   float A[] = { 0.188F, 0.856F };
   float X[] = { -0.832F, -0.151F };
   int incX = -1;
   float A_expected[] = { 0.903025F, 0.0F };
   cblas_cher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher(case 1410) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher(case 1410) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   float alpha = 1.0F;
   float A[] = { 0.188F, 0.856F };
   float X[] = { -0.832F, -0.151F };
   int incX = -1;
   float A_expected[] = { 0.903025F, 0.0F };
   cblas_cher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher(case 1411) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher(case 1411) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   float alpha = 1.0F;
   float A[] = { 0.188F, 0.856F };
   float X[] = { -0.832F, -0.151F };
   int incX = -1;
   float A_expected[] = { 0.903025F, 0.0F };
   cblas_cher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher(case 1412) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher(case 1412) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   float alpha = 1.0F;
   float A[] = { 0.188F, 0.856F };
   float X[] = { -0.832F, -0.151F };
   int incX = -1;
   float A_expected[] = { 0.903025F, 0.0F };
   cblas_cher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], flteps, "cher(case 1413) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], flteps, "cher(case 1413) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   double alpha = 0.1;
   double A[] = { 0.257, 0.326 };
   double X[] = { 0.319, -0.009 };
   int incX = -1;
   double A_expected[] = { 0.2671842, 0.0 };
   cblas_zher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher(case 1414) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher(case 1414) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   double alpha = 0.1;
   double A[] = { 0.257, 0.326 };
   double X[] = { 0.319, -0.009 };
   int incX = -1;
   double A_expected[] = { 0.2671842, 0.0 };
   cblas_zher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher(case 1415) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher(case 1415) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 1;
   int lda = 1;
   double alpha = 0.1;
   double A[] = { 0.257, 0.326 };
   double X[] = { 0.319, -0.009 };
   int incX = -1;
   double A_expected[] = { 0.2671842, 0.0 };
   cblas_zher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher(case 1416) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher(case 1416) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 1;
   int lda = 1;
   double alpha = 0.1;
   double A[] = { 0.257, 0.326 };
   double X[] = { 0.319, -0.009 };
   int incX = -1;
   double A_expected[] = { 0.2671842, 0.0 };
   cblas_zher(order, uplo, N, alpha, X, incX, A, lda);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(A[2*i], A_expected[2*i], dbleps, "zher(case 1417) real");
       gsl_test_rel(A[2*i+1], A_expected[2*i+1], dbleps, "zher(case 1417) imag");
     };
   };
  };


}
