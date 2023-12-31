#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>
#include <math.h>

#include "tests.h"

void
test_dot (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int N = 1;
   float alpha = 0.0F;
   float X[] = { 0.733F };
   float Y[] = { 0.825F };
   int incX = 1;
   int incY = -1;
   float expected = 0.604725F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 1)");
  };


  {
   int N = 1;
   float alpha = 0.1F;
   float X[] = { 0.733F };
   float Y[] = { 0.825F };
   int incX = 1;
   int incY = -1;
   float expected = 0.704725F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 2)");
  };


  {
   int N = 1;
   float alpha = 1.0F;
   float X[] = { 0.733F };
   float Y[] = { 0.825F };
   int incX = 1;
   int incY = -1;
   float expected = 1.604725F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 3)");
  };


  {
   int N = 1;
   float alpha = 0.0F;
   float X[] = { -0.812F };
   float Y[] = { -0.667F };
   int incX = -1;
   int incY = 1;
   float expected = 0.541604F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 4)");
  };


  {
   int N = 1;
   float alpha = 0.1F;
   float X[] = { -0.812F };
   float Y[] = { -0.667F };
   int incX = -1;
   int incY = 1;
   float expected = 0.641604F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 5)");
  };


  {
   int N = 1;
   float alpha = 1.0F;
   float X[] = { -0.812F };
   float Y[] = { -0.667F };
   int incX = -1;
   int incY = 1;
   float expected = 1.541604F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 6)");
  };


  {
   int N = 1;
   float alpha = 0.0F;
   float X[] = { 0.481F };
   float Y[] = { 0.523F };
   int incX = -1;
   int incY = -1;
   float expected = 0.251563F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 7)");
  };


  {
   int N = 1;
   float alpha = 0.1F;
   float X[] = { 0.481F };
   float Y[] = { 0.523F };
   int incX = -1;
   int incY = -1;
   float expected = 0.351563F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 8)");
  };


  {
   int N = 1;
   float alpha = 1.0F;
   float X[] = { 0.481F };
   float Y[] = { 0.523F };
   int incX = -1;
   int incY = -1;
   float expected = 1.251563F;
   float f = NAN;
   f = cblas_sdsdot (N, alpha, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdsdot(case 9)");
  };


  {
   int N = 1;
   float X[] = { 0.785F };
   float Y[] = { -0.7F };
   int incX = 1;
   int incY = -1;
   float expected = -0.5495F;
   float f = NAN;
   f = cblas_sdot(N, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdot(case 10)");
  };


  {
   int N = 1;
   double X[] = { 0.79 };
   double Y[] = { -0.679 };
   int incX = 1;
   int incY = -1;
   double expected = -0.53641;
   double f = NAN;
   f = cblas_ddot(N, X, incX, Y, incY);
   gsl_test_rel(f, expected, dbleps, "ddot(case 11)");
  };


  {
   int N = 1;
   float X[] = { 0.474F, -0.27F };
   float Y[] = { -0.144F, -0.392F };
   int incX = 1;
   int incY = -1;
   float expected[2] = {-0.174096F, -0.146928F};
   float f[2];
   cblas_cdotu_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], flteps, "cdotu(case 12) real");
   gsl_test_rel(f[1], expected[1], flteps, "cdotu(case 12) imag");
  };


  {
   int N = 1;
   float X[] = { 0.474F, -0.27F };
   float Y[] = { -0.144F, -0.392F };
   int incX = 1;
   int incY = -1;
   float expected[2] = {0.037584F, -0.224688F};
   float f[2];
   cblas_cdotc_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], flteps, "cdotc(case 13) real");
   gsl_test_rel(f[1], expected[1], flteps, "cdotc(case 13) imag");
  };


  {
   int N = 1;
   double X[] = { -0.87, -0.631 };
   double Y[] = { -0.7, -0.224 };
   int incX = 1;
   int incY = -1;
   double expected[2] = {0.467656, 0.63658};
   double f[2];
   cblas_zdotu_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], dbleps, "zdotu(case 14) real");
   gsl_test_rel(f[1], expected[1], dbleps, "zdotu(case 14) imag");
  };


  {
   int N = 1;
   double X[] = { -0.87, -0.631 };
   double Y[] = { -0.7, -0.224 };
   int incX = 1;
   int incY = -1;
   double expected[2] = {0.750344, -0.24682};
   double f[2];
   cblas_zdotc_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], dbleps, "zdotc(case 15) real");
   gsl_test_rel(f[1], expected[1], dbleps, "zdotc(case 15) imag");
  };


  {
   int N = 1;
   float X[] = { -0.457F };
   float Y[] = { 0.839F };
   int incX = -1;
   int incY = 1;
   float expected = -0.383423F;
   float f = NAN;
   f = cblas_sdot(N, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdot(case 16)");
  };


  {
   int N = 1;
   double X[] = { 0.949 };
   double Y[] = { -0.873 };
   int incX = -1;
   int incY = 1;
   double expected = -0.828477;
   double f = NAN;
   f = cblas_ddot(N, X, incX, Y, incY);
   gsl_test_rel(f, expected, dbleps, "ddot(case 17)");
  };


  {
   int N = 1;
   float X[] = { 0.852F, -0.045F };
   float Y[] = { 0.626F, -0.164F };
   int incX = -1;
   int incY = 1;
   float expected[2] = {0.525972F, -0.167898F};
   float f[2];
   cblas_cdotu_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], flteps, "cdotu(case 18) real");
   gsl_test_rel(f[1], expected[1], flteps, "cdotu(case 18) imag");
  };


  {
   int N = 1;
   float X[] = { 0.852F, -0.045F };
   float Y[] = { 0.626F, -0.164F };
   int incX = -1;
   int incY = 1;
   float expected[2] = {0.540732F, -0.111558F};
   float f[2];
   cblas_cdotc_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], flteps, "cdotc(case 19) real");
   gsl_test_rel(f[1], expected[1], flteps, "cdotc(case 19) imag");
  };


  {
   int N = 1;
   double X[] = { -0.786, -0.341 };
   double Y[] = { -0.271, -0.896 };
   int incX = -1;
   int incY = 1;
   double expected[2] = {-0.09253, 0.796667};
   double f[2];
   cblas_zdotu_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], dbleps, "zdotu(case 20) real");
   gsl_test_rel(f[1], expected[1], dbleps, "zdotu(case 20) imag");
  };


  {
   int N = 1;
   double X[] = { -0.786, -0.341 };
   double Y[] = { -0.271, -0.896 };
   int incX = -1;
   int incY = 1;
   double expected[2] = {0.518542, 0.611845};
   double f[2];
   cblas_zdotc_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], dbleps, "zdotc(case 21) real");
   gsl_test_rel(f[1], expected[1], dbleps, "zdotc(case 21) imag");
  };


  {
   int N = 1;
   float X[] = { -0.088F };
   float Y[] = { -0.165F };
   int incX = -1;
   int incY = -1;
   float expected = 0.01452F;
   float f = NAN;
   f = cblas_sdot(N, X, incX, Y, incY);
   gsl_test_rel(f, expected, flteps, "sdot(case 22)");
  };


  {
   int N = 1;
   double X[] = { -0.434 };
   double Y[] = { -0.402 };
   int incX = -1;
   int incY = -1;
   double expected = 0.174468;
   double f = NAN;
   f = cblas_ddot(N, X, incX, Y, incY);
   gsl_test_rel(f, expected, dbleps, "ddot(case 23)");
  };


  {
   int N = 1;
   float X[] = { -0.347F, 0.899F };
   float Y[] = { -0.113F, -0.858F };
   int incX = -1;
   int incY = -1;
   float expected[2] = {0.810553F, 0.196139F};
   float f[2];
   cblas_cdotu_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], flteps, "cdotu(case 24) real");
   gsl_test_rel(f[1], expected[1], flteps, "cdotu(case 24) imag");
  };


  {
   int N = 1;
   float X[] = { -0.347F, 0.899F };
   float Y[] = { -0.113F, -0.858F };
   int incX = -1;
   int incY = -1;
   float expected[2] = {-0.732131F, 0.399313F};
   float f[2];
   cblas_cdotc_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], flteps, "cdotc(case 25) real");
   gsl_test_rel(f[1], expected[1], flteps, "cdotc(case 25) imag");
  };


  {
   int N = 1;
   double X[] = { -0.897, -0.204 };
   double Y[] = { -0.759, 0.557 };
   int incX = -1;
   int incY = -1;
   double expected[2] = {0.794451, -0.344793};
   double f[2];
   cblas_zdotu_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], dbleps, "zdotu(case 26) real");
   gsl_test_rel(f[1], expected[1], dbleps, "zdotu(case 26) imag");
  };


  {
   int N = 1;
   double X[] = { -0.897, -0.204 };
   double Y[] = { -0.759, 0.557 };
   int incX = -1;
   int incY = -1;
   double expected[2] = {0.567195, -0.654465};
   double f[2];
   cblas_zdotc_sub(N, X, incX, Y, incY, &f);
   gsl_test_rel(f[0], expected[0], dbleps, "zdotc(case 27) real");
   gsl_test_rel(f[1], expected[1], dbleps, "zdotc(case 27) imag");
  };


}
