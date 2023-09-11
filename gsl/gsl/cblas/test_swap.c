#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_swap (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int N = 1;
   float X[] = { 0.539F };
   int incX = 1;
   float Y[] = { -0.262F };
   int incY = -1;
   float expected1[] = { -0.262F };
   float expected2[] = { 0.539F };
   cblas_sswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected1[i], flteps, "sswap(case 88)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], expected2[i], flteps, "sswap(case 89)");
     }
   };
  };


  {
   int N = 1;
   double X[] = { 0.906 };
   int incX = 1;
   double Y[] = { 0.373 };
   int incY = -1;
   double expected1[] = { 0.373 };
   double expected2[] = { 0.906 };
   cblas_dswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected1[i], dbleps, "dswap(case 90)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], expected2[i], dbleps, "dswap(case 91)");
     }
   };
  };


  {
   int N = 1;
   float X[] = { -0.316F, -0.529F };
   int incX = 1;
   float Y[] = { -0.313F, 0.363F };
   int incY = -1;
   float expected1[] = { -0.313F, 0.363F };
   float expected2[] = { -0.316F, -0.529F };
   cblas_cswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected1[2*i], flteps, "cswap(case 92) real");
       gsl_test_rel(X[2*i+1], expected1[2*i+1], flteps, "cswap(case 92) imag");
     };
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[2*i], expected2[2*i], flteps, "cswap(case 93) real");
       gsl_test_rel(Y[2*i+1], expected2[2*i+1], flteps, "cswap(case 93) imag");
     };
   };
  };


  {
   int N = 1;
   double X[] = { 0.512, -0.89 };
   int incX = 1;
   double Y[] = { -0.225, -0.511 };
   int incY = -1;
   double expected1[] = { -0.225, -0.511 };
   double expected2[] = { 0.512, -0.89 };
   cblas_zswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected1[2*i], dbleps, "zswap(case 94) real");
       gsl_test_rel(X[2*i+1], expected1[2*i+1], dbleps, "zswap(case 94) imag");
     };
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[2*i], expected2[2*i], dbleps, "zswap(case 95) real");
       gsl_test_rel(Y[2*i+1], expected2[2*i+1], dbleps, "zswap(case 95) imag");
     };
   };
  };


  {
   int N = 1;
   float X[] = { 0.336F };
   int incX = -1;
   float Y[] = { -0.431F };
   int incY = 1;
   float expected1[] = { -0.431F };
   float expected2[] = { 0.336F };
   cblas_sswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected1[i], flteps, "sswap(case 96)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], expected2[i], flteps, "sswap(case 97)");
     }
   };
  };


  {
   int N = 1;
   double X[] = { 0.764 };
   int incX = -1;
   double Y[] = { -0.293 };
   int incY = 1;
   double expected1[] = { -0.293 };
   double expected2[] = { 0.764 };
   cblas_dswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected1[i], dbleps, "dswap(case 98)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], expected2[i], dbleps, "dswap(case 99)");
     }
   };
  };


  {
   int N = 1;
   float X[] = { -0.239F, 0.361F };
   int incX = -1;
   float Y[] = { 0.149F, 0.347F };
   int incY = 1;
   float expected1[] = { 0.149F, 0.347F };
   float expected2[] = { -0.239F, 0.361F };
   cblas_cswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected1[2*i], flteps, "cswap(case 100) real");
       gsl_test_rel(X[2*i+1], expected1[2*i+1], flteps, "cswap(case 100) imag");
     };
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[2*i], expected2[2*i], flteps, "cswap(case 101) real");
       gsl_test_rel(Y[2*i+1], expected2[2*i+1], flteps, "cswap(case 101) imag");
     };
   };
  };


  {
   int N = 1;
   double X[] = { -0.171, -0.936 };
   int incX = -1;
   double Y[] = { 0.495, -0.835 };
   int incY = 1;
   double expected1[] = { 0.495, -0.835 };
   double expected2[] = { -0.171, -0.936 };
   cblas_zswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected1[2*i], dbleps, "zswap(case 102) real");
       gsl_test_rel(X[2*i+1], expected1[2*i+1], dbleps, "zswap(case 102) imag");
     };
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[2*i], expected2[2*i], dbleps, "zswap(case 103) real");
       gsl_test_rel(Y[2*i+1], expected2[2*i+1], dbleps, "zswap(case 103) imag");
     };
   };
  };


  {
   int N = 1;
   float X[] = { -0.405F };
   int incX = -1;
   float Y[] = { -0.213F };
   int incY = -1;
   float expected1[] = { -0.213F };
   float expected2[] = { -0.405F };
   cblas_sswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected1[i], flteps, "sswap(case 104)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], expected2[i], flteps, "sswap(case 105)");
     }
   };
  };


  {
   int N = 1;
   double X[] = { -0.761 };
   int incX = -1;
   double Y[] = { -0.585 };
   int incY = -1;
   double expected1[] = { -0.585 };
   double expected2[] = { -0.761 };
   cblas_dswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected1[i], dbleps, "dswap(case 106)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], expected2[i], dbleps, "dswap(case 107)");
     }
   };
  };


  {
   int N = 1;
   float X[] = { 0.853F, 0.146F };
   int incX = -1;
   float Y[] = { 0.009F, -0.178F };
   int incY = -1;
   float expected1[] = { 0.009F, -0.178F };
   float expected2[] = { 0.853F, 0.146F };
   cblas_cswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected1[2*i], flteps, "cswap(case 108) real");
       gsl_test_rel(X[2*i+1], expected1[2*i+1], flteps, "cswap(case 108) imag");
     };
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[2*i], expected2[2*i], flteps, "cswap(case 109) real");
       gsl_test_rel(Y[2*i+1], expected2[2*i+1], flteps, "cswap(case 109) imag");
     };
   };
  };


  {
   int N = 1;
   double X[] = { -0.228, 0.386 };
   int incX = -1;
   double Y[] = { 0.988, -0.084 };
   int incY = -1;
   double expected1[] = { 0.988, -0.084 };
   double expected2[] = { -0.228, 0.386 };
   cblas_zswap(N, X, incX, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected1[2*i], dbleps, "zswap(case 110) real");
       gsl_test_rel(X[2*i+1], expected1[2*i+1], dbleps, "zswap(case 110) imag");
     };
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[2*i], expected2[2*i], dbleps, "zswap(case 111) real");
       gsl_test_rel(Y[2*i+1], expected2[2*i+1], dbleps, "zswap(case 111) imag");
     };
   };
  };


}
