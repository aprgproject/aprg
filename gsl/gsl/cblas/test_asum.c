#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>
#include <math.h>

#include "tests.h"

void
test_asum (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int N = 1;
   float X[] = { 0.239F };
   int incX = -1;
   float expected = 0.0F;
   float f = NAN;
   f = cblas_sasum(N, X, incX);
   gsl_test_rel(f, expected, flteps, "sasum(case 40)");
  };


  {
   int N = 1;
   double X[] = { -0.413 };
   int incX = -1;
   double expected = 0;
   double f = NAN;
   f = cblas_dasum(N, X, incX);
   gsl_test_rel(f, expected, dbleps, "dasum(case 41)");
  };


  {
   int N = 1;
   float X[] = { 0.1F, 0.017F };
   int incX = -1;
   float expected = 0.0F;
   float f = NAN;
   f = cblas_scasum(N, X, incX);
   gsl_test_rel(f, expected, flteps, "scasum(case 42)");
  };


  {
   int N = 1;
   double X[] = { -0.651, 0.079 };
   int incX = -1;
   double expected = 0;
   double f = NAN;
   f = cblas_dzasum(N, X, incX);
   gsl_test_rel(f, expected, dbleps, "dzasum(case 43)");
  };


  {
   int N = 2;
   float X[] = { 0.899F, -0.72F };
   int incX = 1;
   float expected = 1.619F;
   float f = NAN;
   f = cblas_sasum(N, X, incX);
   gsl_test_rel(f, expected, flteps, "sasum(case 44)");
  };


  {
   int N = 2;
   double X[] = { 0.271, -0.012 };
   int incX = 1;
   double expected = 0.283;
   double f = NAN;
   f = cblas_dasum(N, X, incX);
   gsl_test_rel(f, expected, dbleps, "dasum(case 45)");
  };


  {
   int N = 2;
   float X[] = { -0.567F, -0.645F, 0.098F, 0.256F };
   int incX = 1;
   float expected = 1.566F;
   float f = NAN;
   f = cblas_scasum(N, X, incX);
   gsl_test_rel(f, expected, flteps, "scasum(case 46)");
  };


  {
   int N = 2;
   double X[] = { -0.046, -0.671, -0.323, 0.785 };
   int incX = 1;
   double expected = 1.825;
   double f = NAN;
   f = cblas_dzasum(N, X, incX);
   gsl_test_rel(f, expected, dbleps, "dzasum(case 47)");
  };


  {
   int N = 2;
   float X[] = { 0.169F, 0.833F };
   int incX = -1;
   float expected = 0.0F;
   float f = NAN;
   f = cblas_sasum(N, X, incX);
   gsl_test_rel(f, expected, flteps, "sasum(case 48)");
  };


  {
   int N = 2;
   double X[] = { -0.586, -0.486 };
   int incX = -1;
   double expected = 0;
   double f = NAN;
   f = cblas_dasum(N, X, incX);
   gsl_test_rel(f, expected, dbleps, "dasum(case 49)");
  };


  {
   int N = 2;
   float X[] = { -0.314F, -0.318F, -0.835F, -0.807F };
   int incX = -1;
   float expected = 0.0F;
   float f = NAN;
   f = cblas_scasum(N, X, incX);
   gsl_test_rel(f, expected, flteps, "scasum(case 50)");
  };


  {
   int N = 2;
   double X[] = { -0.927, 0.152, -0.554, -0.844 };
   int incX = -1;
   double expected = 0;
   double f = NAN;
   f = cblas_dzasum(N, X, incX);
   gsl_test_rel(f, expected, dbleps, "dzasum(case 51)");
  };


}
