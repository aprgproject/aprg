#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_tpmv (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.179133F, -0.549315F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 974)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.213F, 0.85518F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 975)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.055233F, -0.519495F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 976)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.0891F, 0.885F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 977)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.179133F, -0.549315F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 978)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.213F, 0.85518F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 979)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.055233F, -0.519495F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 980)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { -0.587F, 0.14F, 0.841F };
   float X[] = { -0.213F, 0.885F };
   int incX = -1;
   float x_expected[] = { -0.0891F, 0.885F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 981)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { -0.49754F, 0.20961F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 982)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { -0.022232F, -0.274F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 983)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { -0.232308F, 0.444834F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 984)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { 0.243F, -0.038776F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 985)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { -0.49754F, 0.20961F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 986)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { -0.022232F, -0.274F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 987)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { -0.232308F, 0.444834F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 988)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { -0.765F, 0.968F, -0.956F };
   float X[] = { 0.243F, -0.274F };
   int incX = -1;
   float x_expected[] = { 0.243F, -0.038776F };
   cblas_stpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stpmv(case 989)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { -0.022072, -0.073151 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 990)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { -0.062, -0.207298 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 991)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { 0.026769, -0.086853 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 992)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { -0.013159, -0.221 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 993)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { -0.022072, -0.073151 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 994)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { -0.062, -0.207298 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 995)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { 0.026769, -0.086853 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 996)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.393, -0.221, 0.356 };
   double X[] = { -0.062, -0.221 };
   int incX = -1;
   double x_expected[] = { -0.013159, -0.221 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 997)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { 0.165233, 0.25331 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 998)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { -0.745135, 0.365 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 999)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { -0.017632, -0.211618 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 1000)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { -0.928, -0.099928 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 1001)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { 0.165233, 0.25331 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 1002)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { -0.745135, 0.365 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 1003)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { -0.017632, -0.211618 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 1004)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.694, 0.501, 0.019 };
   double X[] = { -0.928, 0.365 };
   int incX = -1;
   double x_expected[] = { -0.928, -0.099928 };
   cblas_dtpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtpmv(case 1005)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 0.880215F, -0.602509F, -0.225207F, -0.564235F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1006) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1006) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 0.904F, 0.461F, -0.58925F, -0.778204F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1007) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1007) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 1.21467F, -0.432639F, -0.002957F, 0.366969F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1008) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1008) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 1.23846F, 0.63087F, -0.367F, 0.153F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1009) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1009) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 0.880215F, -0.602509F, -0.225207F, -0.564235F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1010) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1010) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 0.904F, 0.461F, -0.58925F, -0.778204F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1011) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1011) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 1.21467F, -0.432639F, -0.002957F, 0.366969F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1012) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1012) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { 0.362F, -0.849F, -0.612F, -0.718F, 0.503F, -0.923F };
   float X[] = { 0.904F, 0.461F, -0.367F, 0.153F };
   int incX = -1;
   float x_expected[] = { 1.23846F, 0.63087F, -0.367F, 0.153F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1013) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1013) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { -0.281591F, -0.161308F, -0.9103F, 0.34578F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1014) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1014) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { -0.05924F, -0.5178F, 0.444F, -0.748F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1015) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1015) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { 0.115649F, -0.450508F, -1.26568F, 0.689239F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1016) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1016) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { 0.338F, -0.807F, 0.088617F, -0.404541F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1017) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1017) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { -0.281591F, -0.161308F, -0.9103F, 0.34578F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1018) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1018) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { -0.05924F, -0.5178F, 0.444F, -0.748F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1019) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1019) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { 0.115649F, -0.450508F, -1.26568F, 0.689239F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1020) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1020) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { -0.876F, -0.697F, -0.519F, -0.223F, 0.526F, -0.077F };
   float X[] = { 0.338F, -0.807F, 0.444F, -0.748F };
   int incX = -1;
   float x_expected[] = { 0.338F, -0.807F, 0.088617F, -0.404541F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1021) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1021) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { -0.295592F, 1.11591F, 0.610498F, -0.779458F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1022) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1022) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { -0.646798F, 0.455824F, 0.602F, -0.96F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1023) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1023) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { 0.229206F, 0.296082F, 0.712384F, -0.465806F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1024) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1024) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { -0.122F, -0.364F, 0.703886F, -0.646348F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1025) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1025) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { -0.295592F, 1.11591F, 0.610498F, -0.779458F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1026) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1026) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { -0.646798F, 0.455824F, 0.602F, -0.96F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1027) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1027) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { 0.229206F, 0.296082F, 0.712384F, -0.465806F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1028) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1028) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   float A[] = { 0.869F, -0.091F, -0.859F, 0.008F, -0.921F, -0.321F };
   float X[] = { -0.122F, -0.364F, 0.602F, -0.96F };
   int incX = -1;
   float x_expected[] = { -0.122F, -0.364F, 0.703886F, -0.646348F };
   cblas_ctpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctpmv(case 1029) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctpmv(case 1029) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.466116, 0.156534, -0.248261, -0.067936 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1030) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1030) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.042, -0.705, -0.663093, -0.637955 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1031) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1031) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.905141, 0.539693, 0.159832, -0.283981 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1032) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1032) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.481025, -0.321841, -0.255, -0.854 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1033) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1033) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.466116, 0.156534, -0.248261, -0.067936 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1034) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1034) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.042, -0.705, -0.663093, -0.637955 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1035) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1035) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.905141, 0.539693, 0.159832, -0.283981 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1036) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1036) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.254, 0.263, -0.271, -0.595, -0.182, -0.672 };
   double X[] = { -0.042, -0.705, -0.255, -0.854 };
   int incX = -1;
   double x_expected[] = { -0.481025, -0.321841, -0.255, -0.854 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1037) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1037) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { 0.590302, 1.473768, -0.566422, -0.005436 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1038) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1038) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { 0.139182, 1.574648, -0.689, -0.679 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1039) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1039) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { 0.44312, 0.80312, -0.211814, -0.54022 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1040) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1040) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { -0.008, 0.904, -0.334392, -1.213784 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1041) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1041) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { 0.590302, 1.473768, -0.566422, -0.005436 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1042) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1042) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { 0.139182, 1.574648, -0.689, -0.679 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1043) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1043) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { 0.44312, 0.80312, -0.211814, -0.54022 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1044) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1044) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { 0.421, -0.407, -0.595, -0.387, 0.884, -0.498 };
   double X[] = { -0.008, 0.904, -0.689, -0.679 };
   int incX = -1;
   double x_expected[] = { -0.008, 0.904, -0.334392, -1.213784 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1045) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1045) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -1.449087, -1.068251, 0.375602, 0.672696 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1046) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1046) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -1.43236, 0.04007, -0.406, -0.948 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1047) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1047) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -0.657727, -0.543321, 0.167357, 1.431451 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1048) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1048) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -0.641, 0.565, -0.614245, -0.189245 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1049) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1049) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 131;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -1.449087, -1.068251, 0.375602, 0.672696 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1050) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1050) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 121;
   int diag = 132;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -1.43236, 0.04007, -0.406, -0.948 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1051) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1051) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 131;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -0.657727, -0.543321, 0.167357, 1.431451 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1052) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1052) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int uplo = 122;
   int diag = 132;
   int N = 2;
   double A[] = { -0.743, -0.078, 0.77, 0.505, 0.157, -0.986 };
   double X[] = { -0.641, 0.565, -0.406, -0.948 };
   int incX = -1;
   double x_expected[] = { -0.641, 0.565, -0.614245, -0.189245 };
   cblas_ztpmv(order, uplo, trans, diag, N, A, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztpmv(case 1053) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztpmv(case 1053) imag");
     };
   };
  };


}
