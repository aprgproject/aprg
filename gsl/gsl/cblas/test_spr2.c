#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_spr2 (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int N = 2;
   float alpha = -1.0F;
   float Ap[] = { 0.493F, -0.175F, -0.831F };
   float X[] = { -0.163F, 0.489F };
   int incX = -1;
   float Y[] = { 0.154F, 0.769F };
   int incY = -1;
   float Ap_expected[] = { -0.259082F, -0.124959F, -0.780796F };
   cblas_sspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr2(case 1442)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 2;
   float alpha = -1.0F;
   float Ap[] = { 0.493F, -0.175F, -0.831F };
   float X[] = { -0.163F, 0.489F };
   int incX = -1;
   float Y[] = { 0.154F, 0.769F };
   int incY = -1;
   float Ap_expected[] = { -0.259082F, -0.124959F, -0.780796F };
   cblas_sspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr2(case 1443)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 2;
   float alpha = -1.0F;
   float Ap[] = { 0.493F, -0.175F, -0.831F };
   float X[] = { -0.163F, 0.489F };
   int incX = -1;
   float Y[] = { 0.154F, 0.769F };
   int incY = -1;
   float Ap_expected[] = { -0.259082F, -0.124959F, -0.780796F };
   cblas_sspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr2(case 1444)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 2;
   float alpha = -1.0F;
   float Ap[] = { 0.493F, -0.175F, -0.831F };
   float X[] = { -0.163F, 0.489F };
   int incX = -1;
   float Y[] = { 0.154F, 0.769F };
   int incY = -1;
   float Ap_expected[] = { -0.259082F, -0.124959F, -0.780796F };
   cblas_sspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], flteps, "sspr2(case 1445)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int N = 2;
   double alpha = 0;
   double Ap[] = { 0.938, 0.342, 0.74 };
   double X[] = { 0.216, -0.566 };
   int incX = -1;
   double Y[] = { -0.845, 0.282 };
   int incY = -1;
   double Ap_expected[] = { 0.938, 0.342, 0.74 };
   cblas_dspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr2(case 1446)");
     }
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int N = 2;
   double alpha = 0;
   double Ap[] = { 0.938, 0.342, 0.74 };
   double X[] = { 0.216, -0.566 };
   int incX = -1;
   double Y[] = { -0.845, 0.282 };
   int incY = -1;
   double Ap_expected[] = { 0.938, 0.342, 0.74 };
   cblas_dspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr2(case 1447)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int N = 2;
   double alpha = 0;
   double Ap[] = { 0.938, 0.342, 0.74 };
   double X[] = { 0.216, -0.566 };
   int incX = -1;
   double Y[] = { -0.845, 0.282 };
   int incY = -1;
   double Ap_expected[] = { 0.938, 0.342, 0.74 };
   cblas_dspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr2(case 1448)");
     }
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int N = 2;
   double alpha = 0;
   double Ap[] = { 0.938, 0.342, 0.74 };
   double X[] = { 0.216, -0.566 };
   int incX = -1;
   double Y[] = { -0.845, 0.282 };
   int incY = -1;
   double Ap_expected[] = { 0.938, 0.342, 0.74 };
   cblas_dspr2(order, uplo, N, alpha, X, incX, Y, incY, Ap);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Ap[i], Ap_expected[i], dbleps, "dspr2(case 1449)");
     }
   };
  };


}
