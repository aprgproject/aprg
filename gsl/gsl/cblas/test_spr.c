#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_spr (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int N = 2;
   float alpha = -0.3F;
   float Ap[] = { -0.764F, -0.257F, -0.064F };
   float X[] = { 0.455F, -0.285F };
   int incX = -1;
   float Ap_expected[] = { -0.788367F, -0.218097F, -0.126108F };
   cblas_sspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr(case 1426)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 2;
   float alpha = -0.3F;
   float Ap[] = { -0.764F, -0.257F, -0.064F };
   float X[] = { 0.455F, -0.285F };
   int incX = -1;
   float Ap_expected[] = { -0.788367F, -0.218097F, -0.126108F };
   cblas_sspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr(case 1427)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 2;
   float alpha = -0.3F;
   float Ap[] = { -0.764F, -0.257F, -0.064F };
   float X[] = { 0.455F, -0.285F };
   int incX = -1;
   float Ap_expected[] = { -0.788367F, -0.218097F, -0.126108F };
   cblas_sspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr(case 1428)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 2;
   float alpha = -0.3F;
   float Ap[] = { -0.764F, -0.257F, -0.064F };
   float X[] = { 0.455F, -0.285F };
   int incX = -1;
   float Ap_expected[] = { -0.788367F, -0.218097F, -0.126108F };
   cblas_sspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr(case 1429)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int N = 2;
   double alpha = -1;
   double Ap[] = { 0.819, 0.175, -0.809 };
   double X[] = { -0.645, -0.222 };
   int incX = -1;
   double Ap_expected[] = { 0.769716, 0.03181, -1.225025 };
   cblas_dspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr(case 1430)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 2;
   double alpha = -1;
   double Ap[] = { 0.819, 0.175, -0.809 };
   double X[] = { -0.645, -0.222 };
   int incX = -1;
   double Ap_expected[] = { 0.769716, 0.03181, -1.225025 };
   cblas_dspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr(case 1431)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 2;
   double alpha = -1;
   double Ap[] = { 0.819, 0.175, -0.809 };
   double X[] = { -0.645, -0.222 };
   int incX = -1;
   double Ap_expected[] = { 0.769716, 0.03181, -1.225025 };
   cblas_dspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr(case 1432)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 2;
   double alpha = -1;
   double Ap[] = { 0.819, 0.175, -0.809 };
   double X[] = { -0.645, -0.222 };
   int incX = -1;
   double Ap_expected[] = { 0.769716, 0.03181, -1.225025 };
   cblas_dspr(order, uplo, N, alpha, X, incX, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr(case 1433)");
     }
   };
  };


}
