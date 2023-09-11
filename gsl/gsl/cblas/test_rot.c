#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_rot (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int N = 1;
   float c = 0.0F;
   float s = 0.0F;
   float X[] = { -0.314F };
   int incX = 1;
   float Y[] = { -0.406F };
   int incY = -1;
   float x_expected[] = { 0.0F };
   float y_expected[] = { 0.0F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 558)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 559)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.866025403784F;
   float s = 0.5F;
   float X[] = { -0.314F };
   int incX = 1;
   float Y[] = { -0.406F };
   int incY = -1;
   float x_expected[] = { -0.474932F };
   float y_expected[] = { -0.194606F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 560)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 561)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.0F;
   float s = -1.0F;
   float X[] = { -0.314F };
   int incX = 1;
   float Y[] = { -0.406F };
   int incY = -1;
   float x_expected[] = { 0.406F };
   float y_expected[] = { -0.314F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 562)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 563)");
     }
   };
  };


  {
   int N = 1;
   float c = -1.0F;
   float s = 0.0F;
   float X[] = { -0.314F };
   int incX = 1;
   float Y[] = { -0.406F };
   int incY = -1;
   float x_expected[] = { 0.314F };
   float y_expected[] = { 0.406F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 564)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 565)");
     }
   };
  };


  {
   int N = 1;
   double c = 0;
   double s = 0;
   double X[] = { -0.493 };
   int incX = 1;
   double Y[] = { -0.014 };
   int incY = -1;
   double x_expected[] = { 0.0 };
   double y_expected[] = { 0.0 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 566)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 567)");
     }
   };
  };


  {
   int N = 1;
   double c = 0.866025403784;
   double s = 0.5;
   double X[] = { -0.493 };
   int incX = 1;
   double Y[] = { -0.014 };
   int incY = -1;
   double x_expected[] = { -0.433950524066 };
   double y_expected[] = { 0.234375644347 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 568)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 569)");
     }
   };
  };


  {
   int N = 1;
   double c = 0;
   double s = -1;
   double X[] = { -0.493 };
   int incX = 1;
   double Y[] = { -0.014 };
   int incY = -1;
   double x_expected[] = { 0.014 };
   double y_expected[] = { -0.493 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 570)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 571)");
     }
   };
  };


  {
   int N = 1;
   double c = -1;
   double s = 0;
   double X[] = { -0.493 };
   int incX = 1;
   double Y[] = { -0.014 };
   int incY = -1;
   double x_expected[] = { 0.493 };
   double y_expected[] = { 0.014 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 572)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 573)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.0F;
   float s = 0.0F;
   float X[] = { -0.808F };
   int incX = -1;
   float Y[] = { -0.511F };
   int incY = 1;
   float x_expected[] = { 0.0F };
   float y_expected[] = { 0.0F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 574)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 575)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.866025403784F;
   float s = 0.5F;
   float X[] = { -0.808F };
   int incX = -1;
   float Y[] = { -0.511F };
   int incY = 1;
   float x_expected[] = { -0.955249F };
   float y_expected[] = { -0.038539F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 576)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 577)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.0F;
   float s = -1.0F;
   float X[] = { -0.808F };
   int incX = -1;
   float Y[] = { -0.511F };
   int incY = 1;
   float x_expected[] = { 0.511F };
   float y_expected[] = { -0.808F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 578)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 579)");
     }
   };
  };


  {
   int N = 1;
   float c = -1.0F;
   float s = 0.0F;
   float X[] = { -0.808F };
   int incX = -1;
   float Y[] = { -0.511F };
   int incY = 1;
   float x_expected[] = { 0.808F };
   float y_expected[] = { 0.511F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 580)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 581)");
     }
   };
  };


  {
   int N = 1;
   double c = 0;
   double s = 0;
   double X[] = { -0.176 };
   int incX = -1;
   double Y[] = { -0.165 };
   int incY = 1;
   double x_expected[] = { 0.0 };
   double y_expected[] = { 0.0 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 582)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 583)");
     }
   };
  };


  {
   int N = 1;
   double c = 0.866025403784;
   double s = 0.5;
   double X[] = { -0.176 };
   int incX = -1;
   double Y[] = { -0.165 };
   int incY = 1;
   double x_expected[] = { -0.234920471066 };
   double y_expected[] = { -0.0548941916244 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 584)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 585)");
     }
   };
  };


  {
   int N = 1;
   double c = 0;
   double s = -1;
   double X[] = { -0.176 };
   int incX = -1;
   double Y[] = { -0.165 };
   int incY = 1;
   double x_expected[] = { 0.165 };
   double y_expected[] = { -0.176 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 586)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 587)");
     }
   };
  };


  {
   int N = 1;
   double c = -1;
   double s = 0;
   double X[] = { -0.176 };
   int incX = -1;
   double Y[] = { -0.165 };
   int incY = 1;
   double x_expected[] = { 0.176 };
   double y_expected[] = { 0.165 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 588)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 589)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.0F;
   float s = 0.0F;
   float X[] = { -0.201F };
   int incX = -1;
   float Y[] = { 0.087F };
   int incY = -1;
   float x_expected[] = { 0.0F };
   float y_expected[] = { 0.0F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 590)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 591)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.866025403784F;
   float s = 0.5F;
   float X[] = { -0.201F };
   int incX = -1;
   float Y[] = { 0.087F };
   int incY = -1;
   float x_expected[] = { -0.130571F };
   float y_expected[] = { 0.175844F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 592)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 593)");
     }
   };
  };


  {
   int N = 1;
   float c = 0.0F;
   float s = -1.0F;
   float X[] = { -0.201F };
   int incX = -1;
   float Y[] = { 0.087F };
   int incY = -1;
   float x_expected[] = { -0.087F };
   float y_expected[] = { -0.201F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 594)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 595)");
     }
   };
  };


  {
   int N = 1;
   float c = -1.0F;
   float s = 0.0F;
   float X[] = { -0.201F };
   int incX = -1;
   float Y[] = { 0.087F };
   int incY = -1;
   float x_expected[] = { 0.201F };
   float y_expected[] = { -0.087F };
   cblas_srot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srot(case 596)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srot(case 597)");
     }
   };
  };


  {
   int N = 1;
   double c = 0;
   double s = 0;
   double X[] = { -0.464 };
   int incX = -1;
   double Y[] = { 0.7 };
   int incY = -1;
   double x_expected[] = { 0.0 };
   double y_expected[] = { 0.0 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 598)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 599)");
     }
   };
  };


  {
   int N = 1;
   double c = 0.866025403784;
   double s = 0.5;
   double X[] = { -0.464 };
   int incX = -1;
   double Y[] = { 0.7 };
   int incY = -1;
   double x_expected[] = { -0.051835787356 };
   double y_expected[] = { 0.838217782649 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 600)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 601)");
     }
   };
  };


  {
   int N = 1;
   double c = 0;
   double s = -1;
   double X[] = { -0.464 };
   int incX = -1;
   double Y[] = { 0.7 };
   int incY = -1;
   double x_expected[] = { -0.7 };
   double y_expected[] = { -0.464 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 602)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 603)");
     }
   };
  };


  {
   int N = 1;
   double c = -1;
   double s = 0;
   double X[] = { -0.464 };
   int incX = -1;
   double Y[] = { 0.7 };
   int incY = -1;
   double x_expected[] = { 0.464 };
   double y_expected[] = { -0.7 };
   cblas_drot(N, X, incX, Y, incY, c, s);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drot(case 604)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drot(case 605)");
     }
   };
  };


}
