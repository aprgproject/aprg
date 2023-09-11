#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_tbmv (void) {
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { 0.017088F, 0.315595F, 0.243875F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 894)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { -0.089F, -0.721909F, 0.129992F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 895)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { 0.156927F, -0.159004F, 0.098252F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 896)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { 0.043096F, -0.584876F, -0.203F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 897)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { 0.024831F, -0.24504F, 0.447756F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 898)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { -0.089F, -0.670912F, 0.146504F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 899)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { -0.24504F, 0.447756F, -0.089117F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 900)");
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
   float A[] = { 0.439F, -0.484F, -0.952F, -0.508F, 0.381F, -0.889F, -0.192F, -0.279F, -0.155F };
   float X[] = { -0.089F, -0.688F, -0.203F };
   int incX = -1;
   float x_expected[] = { -0.351128F, -0.589748F, -0.203F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 901)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { 0.156047F, 0.189418F, -0.52828F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 902)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { 0.194342F, -0.449858F, -0.562F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 903)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { -0.0046F, 0.156047F, 0.189418F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 904)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { 0.023F, -0.516295F, -0.423724F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 905)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { 0.328565F, 0.326454F, 0.051142F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 906)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { 0.356165F, -0.345888F, -0.562F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 907)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { -0.015295F, 0.13041F, -0.482689F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 908)");
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
   float A[] = { 0.94F, -0.091F, 0.984F, -0.276F, -0.342F, -0.484F, -0.665F, -0.2F, 0.349F };
   float X[] = { 0.023F, -0.501F, -0.562F };
   int incX = -1;
   float x_expected[] = { 0.023F, -0.508866F, -0.516409F };
   cblas_stbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "stbmv(case 909)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { 0.50204, 0.563918, -0.590448 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 910)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { -0.77, -0.95429, -0.44419 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 911)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { 1.214016, -0.433258, 0.321835 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 912)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { -0.236664, -1.106472, 0.337 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 913)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { 0.68068, 0.357254, 1.022043 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 914)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { -0.77, -0.31596, 1.037208 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 915)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { 0.357254, 1.022043, 0.190742 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 916)");
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
   double A[] = { 0.566, 0.955, -0.086, -0.856, 0.177, 0.974, -0.652, -0.884, 0.77 };
   double X[] = { -0.77, -0.818, 0.337 };
   int incX = -1;
   double x_expected[] = { -0.914786, -0.496165, 0.337 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 917)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { 0.610833, -0.293243, 0.02914 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 918)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { -0.635031, 0.574, 0.155 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 919)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { 0.024679, 0.610833, -0.293243 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 920)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { -0.851, 0.875864, -0.231243 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 921)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { -0.198505, 0.091504, 0.093 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 922)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { -1.074184, 0.356535, 0.155 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 923)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { 0.394864, -0.768342, 0.31774 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 924)");
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
   double A[] = { 0.188, 0.6, -0.743, -0.803, 0.449, -0.681, -0.464, -0.029, 0.553 };
   double X[] = { -0.851, 0.481, 0.155 };
   int incX = -1;
   double x_expected[] = { -0.851, 0.098901, 0.4436 };
   cblas_dtbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "dtbmv(case 925)");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.113114F, -0.051704F, -0.403567F, -0.288349F, -0.223936F, 0.841145F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 926) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 926) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.46F, 0.069F, -0.14027F, -0.23208F, -0.537722F, 0.841425F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 927) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 927) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.099689F, 0.487805F, 0.353793F, 0.325411F, -0.225658F, -0.776023F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 928) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 928) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.39057F, 0.113296F, 0.388863F, 0.131011F, -0.236F, 0.605F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 929) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 929) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.169119F, 0.443509F, 0.159816F, 0.139696F, -0.180955F, -0.835292F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 930) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 930) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.46F, 0.069F, 0.194886F, -0.054704F, -0.191297F, 0.545731F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 931) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 931) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { 0.159816F, 0.139696F, -0.180955F, -0.835292F, 0.077786F, 0.60472F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 932) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 932) imag");
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
   float A[] = { 0.824F, -0.45F, -0.987F, 0.758F, 0.42F, -0.357F, 0.147F, -0.191F, 0.88F, 0.63F, 0.155F, -0.573F, 0.224F, 0.146F, 0.501F, -0.889F, 0.456F, 0.796F };
   float X[] = { -0.46F, 0.069F, 0.308F, -0.003F, -0.236F, 0.605F };
   int incX = -1;
   float x_expected[] = { -0.18707F, 0.2604F, 0.082342F, -0.779023F, -0.236F, 0.605F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 933) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 933) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 0.647885F, 0.621535F, -0.104407F, 0.05309F, 0.732704F, 0.055982F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 934) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 934) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 1.2955F, 0.190774F, -0.247934F, 0.982616F, -0.894F, -0.116F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 935) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 935) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 0.096482F, -0.071661F, 0.647885F, 0.621535F, -0.104407F, 0.05309F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 936) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 936) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 0.411F, -0.308F, -1.14861F, 0.933761F, -1.66247F, -0.234526F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 937) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 937) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 0.632361F, -0.409373F, 0.578489F, 0.012724F, 0.664066F, 0.171616F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 938) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 938) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 0.946879F, -0.645712F, -1.21801F, 0.32495F, -0.894F, -0.116F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 939) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 939) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { -0.236612F, 0.122761F, -1.12184F, -0.358823F, 1.4975F, -0.470595F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 940) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 940) imag");
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
   float A[] = { -0.814F, 0.043F, -0.755F, -0.094F, 0.876F, 0.257F, 0.406F, 0.491F, -0.27F, -0.787F, 0.545F, 0.732F, -0.512F, -0.085F, 0.234F, 0.001F, -0.225F, -0.002F };
   float X[] = { 0.411F, -0.308F, -0.912F, 0.811F, -0.894F, -0.116F };
   int incX = -1;
   float x_expected[] = { 0.411F, -0.308F, -1.26537F, 0.570703F, -0.129206F, -0.642577F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 941) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 941) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { 0.413357F, 0.178267F, -0.114618F, -1.35595F, -0.513288F, 0.611332F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 942) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 942) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { 0.368428F, 0.071217F, -0.954366F, -0.390486F, 0.694F, -0.954F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 943) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 943) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { -0.084786F, -0.059464F, 0.413357F, 0.178267F, -0.114618F, -1.35595F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 944) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 944) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { 0.065F, -0.082F, -0.636071F, 0.80005F, 0.787748F, -1.14446F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 945) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 945) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { -1.18498F, -0.424201F, 0.230196F, 0.374209F, -0.208366F, -1.16549F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 946) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 946) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { -1.03519F, -0.446737F, -0.819232F, 0.995992F, 0.694F, -0.954F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 947) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 947) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { 0.109929F, 0.02505F, 0.062939F, -0.202464F, -0.470658F, 1.69006F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 948) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 948) imag");
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
   float A[] = { -0.675F, 0.047F, 0.695F, 0.724F, -0.438F, 0.991F, -0.188F, -0.06F, -0.093F, 0.302F, 0.842F, -0.753F, 0.465F, -0.972F, -0.058F, 0.988F, 0.093F, 0.164F };
   float X[] = { 0.065F, -0.082F, -0.746F, 0.775F, 0.694F, -0.954F };
   int incX = -1;
   float x_expected[] = { 0.065F, -0.082F, -0.776809F, 0.762996F, 0.73663F, 0.124729F };
   cblas_ctbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], flteps, "ctbmv(case 949) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], flteps, "ctbmv(case 949) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { -0.010019, -0.1678, -0.042017, -1.112094, 0.010004, -0.480427 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 950) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 950) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { 0.064, 0.169, -0.80842, -0.715637, -0.829924, -0.212971 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 951) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 951) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { 0.634014, 0.796937, -0.585538, -0.895375, -0.125887, 0.010019 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 952) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 952) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { 0.567497, 1.085122, -1.217792, -1.322566, -0.641, -0.103 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 953) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 953) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { 0.130517, -0.119185, -0.187765, -0.519609, -0.169484, -1.165438 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 954) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 954) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { 0.064, 0.169, -0.820019, -0.9468, -0.684597, -1.278457 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 955) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 955) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { -0.187765, -0.519609, -0.169484, -1.165438, 0.198928, -0.370456 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 956) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 956) imag");
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
   double A[] = { -0.212, 0.612, 0.189, -0.046, -0.124, 0.82, 0.753, 0.727, 0.331, 0.116, 0.504, -0.673, -0.888, -0.277, -0.361, -0.909, 0.982, -0.124 };
   double X[] = { 0.064, 0.169, -0.81, -0.779, -0.641, -0.103 };
   int incX = -1;
   double x_expected[] = { -0.113746, -0.182809, -0.935887, -0.768981, -0.641, -0.103 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 957) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 957) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { -0.436746, 0.963714, -1.087615, -0.018695, 0.30063, 0.12958 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 958) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 958) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { 0.895682, 1.407174, 0.2408, -0.14282, -0.649, 0.188 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 959) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 959) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { 0.785744, -0.3966, -0.436746, 0.963714, -1.087615, -0.018695 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 960) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 960) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { 0.884, 0.636, 0.472572, 0.47454, -1.056415, 0.594125 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 961) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 961) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { 0.464705, -0.108078, 0.094975, 0.376323, -0.6802, -0.42482 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 962) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 962) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { 0.562961, 0.924522, 1.004293, -0.112851, -0.649, 0.188 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 963) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 963) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { -0.448428, 0.19254, -0.674583, 1.236189, 0.780774, 1.167088 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 964) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 964) imag");
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
   double A[] = { -0.374, -0.308, 0.792, 0.884, -0.794, -0.055, -0.281, 0.527, 0.246, 0.762, 0.853, 0.891, -0.231, 0.384, 0.373, -0.717, -0.957, -0.338 };
   double X[] = { 0.884, 0.636, 0.921, 0.282, -0.649, 0.188 };
   int incX = -1;
   double x_expected[] = { 0.884, 0.636, 0.653832, 1.112064, -0.168856, 1.225508 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 965) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 965) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -0.59515, 0.077106, -0.27658, -0.637356, 0.407252, -0.308844 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 966) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 966) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -1.46131, 0.537642, 0.624614, 0.762252, 0.326, 0.428 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 967) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 967) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -0.536274, 0.421806, -0.59515, 0.077106, -0.27658, -0.637356 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 968) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 968) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -0.591, -0.084, 0.98216, 0.400464, 0.131806, -0.026608 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 969) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 969) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -1.68293, 0.796222, -0.96062, 0.415172, -0.082386, -0.182748 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 970) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 970) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -1.737656, 0.290416, 0.61669, 0.73853, 0.326, 0.428 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 971) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 971) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { 0.27516, -0.544536, -0.10627, -0.988374, 0.229991, -0.711267 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 972) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 972) imag");
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
   double A[] = { 0.002, 0.95, -0.363, 0.084, -0.646, 0.816, -0.407, 0.099, -0.02, -0.906, -0.874, 0.191, -0.328, -0.968, 0.79, 0.826, -0.795, 0.277 };
   double X[] = { -0.591, -0.084, 0.707, 0.945, 0.326, 0.428 };
   int incX = -1;
   double x_expected[] = { -0.591, -0.084, 0.794924, 0.411234, 0.148739, 0.025577 };
   cblas_ztbmv(order, uplo, trans, diag, N, K, A, lda, X, incX);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(X[2*i], x_expected[2*i], dbleps, "ztbmv(case 973) real");
       gsl_test_rel(X[2*i+1], x_expected[2*i+1], dbleps, "ztbmv(case 973) imag");
     };
   };
  };


}
