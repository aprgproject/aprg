#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_rotm (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int N = 1;
   float h[] = { -1.0F, -4.44982e+03F, -15.5826F, 7.091334e+04F, 2.95912e+04F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { -3.956017e+04F };
   float y_expected[] = { -1.657054e+04F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 654)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 655)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, 15.9728F, 6.400638e+03F, 1.733082e-05F, 1.524511e-04F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { -0.0340097F };
   float y_expected[] = { -218.182F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 656)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 657)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 1.0F, 5.688411e+04F, 5.914789e+03F, 0.00210473F, 0.0231019F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { -1.93462e+03F };
   float y_expected[] = { 0.0210629F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 658)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 659)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -2.0F, -0.582083F, 0.00103161F, -3.429851e-05F, 7.411469e-05F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { -0.034F };
   float y_expected[] = { -0.56F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 660)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 661)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, 115.163F, -6.715448e+04F, -258.695F, -16.2552F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { 140.954F };
   float y_expected[] = { 2.292355e+03F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 662)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 663)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, -3.314862e+03F, -442.976F, -214.586F, -25.9716F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { 120.134F };
   float y_expected[] = { 14.5012F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 664)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 665)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 1.0F, -1.177304e+03F, -1.236662e-04F, -0.186585F, 1.15841F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { 39.4683F };
   float y_expected[] = { -0.614711F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 666)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 667)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -2.0F, -88.9796F, 0.808226F, 1.106582e-05F, -0.00862288F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { -0.034F };
   float y_expected[] = { -0.56F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 668)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 669)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, -0.00225865F, 8.338551e+04F, -1.98282F, -2.409905e-05F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { 1.11046F };
   float y_expected[] = { -2.835107e+03F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 670)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 671)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, 0.258779F, 74.2802F, 0.923299F, 4.847128e+03F };
   float X[] = { -0.034F };
   int incX = 1;
   float Y[] = { -0.56F };
   int incY = -1;
   float x_expected[] = { -0.551048F };
   float y_expected[] = { -3.08553F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 672)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 673)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, -8.00850735044, 0.0204647351647, 1.898461360078e-04, -4.32701487194 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { -6.72728115497 };
   double y_expected[] = { 3.09369795149 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 674)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 675)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, 1.230610998905e+04, 210.056650134, 9.20757074452, 2.072879691524e+03 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { -5.70658279935 };
   double y_expected[] = { 175.736586112 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 676)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 677)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 1.0, -1.244580625511e+03, 1.11154682624, 2.269384716089e-05, -0.0143785338883 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { -1.046158725429e+03 };
   double y_expected[] = { -0.829776862405 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 678)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 679)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -2.0, 293.927527276, -2.614737743134e+03, 10.3164975867, -7.947030813329e+03 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { 0.84 };
   double y_expected[] = { -0.711 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 680)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 681)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, -0.0178609251786, 0.00983044958941, 105.944529127, 1.687350579234e-05 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { -75.3415633866 };
   double y_expected[] = { 0.00824558059248 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 682)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 683)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, 6.241999071283e-05, 2.495425882445e+03, 304.604891146, 1.604644714854e+04 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { -215.734077605 };
   double y_expected[] = { 2.095446741254e+03 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 684)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 685)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 1.0, -0.058097639487, 8.386083625428e+03, -10.5233229994, 184.653245391 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { -0.759802017169 };
   double y_expected[] = { -132.128457473 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 686)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 687)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -2.0, -92.8754629217, 1.467547244529e-04, -3.197881072301e-04, -1.89874629713 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { 0.84 };
   double y_expected[] = { -0.711 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 688)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 689)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, -0.0961996230646, -2.248344186185e-05, -316.856396787, 1.663969157848e+03 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { 225.204090432 };
   double y_expected[] = { -1.183082090116e+03 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 690)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 691)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, -201.862043128, 4.999906166451e-04, -0.0653365534487, 586.454083328 };
   double X[] = { 0.84 };
   int incX = 1;
   double Y[] = { -0.711 };
   int incY = -1;
   double x_expected[] = { 0.886454289502 };
   double y_expected[] = { -0.710580007882 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 692)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 693)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, 162.86F, 1.379231e-04F, 9.67285F, 0.929218F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 106.173F };
   float y_expected[] = { 0.358765F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 694)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 695)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, 537.387F, -21.6404F, -1.017074e+03F, -1.730546e-05F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { -391.961F };
   float y_expected[] = { -13.2258F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 696)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 697)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 1.0F, -1.339977e-05F, 0.00522784F, 2.020352e-05F, -0.0654088F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 0.385992F };
   float y_expected[] = { -0.654248F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 698)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 699)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -2.0F, -50.922F, 31.5261F, -0.194913F, 0.206417F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 0.629F };
   float y_expected[] = { 0.386F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 700)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 701)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, 1.15659F, 2.599832e+04F, 435.891F, 1.546671e+03F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 168.981F };
   float y_expected[] = { 1.694996e+04F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 702)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 703)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, 3.359889e-04F, -0.00134822F, -12.9136F, -5.655622e+04F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { -4.35566F };
   float y_expected[] = { 0.385152F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 704)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 705)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 1.0F, 2.75119e-05F, 1.70314F, 18.4063F, 185.731F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 0.386017F };
   float y_expected[] = { 71.063F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 706)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 707)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -2.0F, -1.031009e-04F, -3.378602e+04F, 7.869358e-05F, 157.303F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 0.629F };
   float y_expected[] = { 0.386F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 708)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 709)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, 0.00207419F, -89.9374F, -1.40414F, -25.1433F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { -0.540694F };
   float y_expected[] = { -66.276F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 710)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 711)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, -4.972562e+04F, 3.65698e-05F, 632.116F, 0.195207F };
   float X[] = { 0.629F };
   int incX = -1;
   float Y[] = { 0.386F };
   int incY = 1;
   float x_expected[] = { 244.626F };
   float y_expected[] = { 0.386023F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 712)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 713)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, 8.64768339859, -105.906731008, -347.053994991, -1.28802789909 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { 218.021288159 };
   double y_expected[] = { 72.2119146942 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 714)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 715)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, 0.926057152065, 3.315158944851e-04, -1.203638835886e+03, 0.00197484344868 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { 775.673049147 };
   double y_expected[] = { -0.645223441713 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 716)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 717)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 1.0, -9.404298701289e-05, -0.00380843381223, -0.0767212569647, -3.66628238398 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { -0.644936615027 };
   double y_expected[] = { 3.03875213767 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 718)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 719)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -2.0, 0.0900662226146, 0.00250500071094, 6.46624826995, -2.159443948633e-05 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { -0.674 };
   double y_expected[] = { -0.645 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 720)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 721)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, 8.011686652935e+03, -23.8989526115, -1.104879849207e+04, 0.108740065261 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { 1.726598223305e+03 };
   double y_expected[] = { 16.0377567181 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 722)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 723)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, 5.162681717012e-05, 48.059409562, -4.701209666609e+04, -6.80333644488e+04 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { 3.032212834963e+04 };
   double y_expected[] = { -33.0370420448 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 724)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 725)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 1.0, -5.554806445579e-04, 5.101973060197e+04, -5.932040237374e+03, 3.91045757161 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { -0.644625606046 };
   double y_expected[] = { -1.84824513369 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 726)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 727)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -2.0, -1.697234884626e-05, 101.466514367, 5.772202675851e+03, -6.884724590773e-04 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { -0.674 };
   double y_expected[] = { -0.645 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 728)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 729)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, -0.0199779342753, 13.013123509, -17.8393347684, 0.129333249919 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { 11.5198360534 };
   double y_expected[] = { -8.85426519126 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 730)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 731)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, -6.673799053773e+04, 587.759435538, 3.493966594965e+04, 2.098374142331e-05 };
   double X[] = { -0.674 };
   int incX = -1;
   double Y[] = { -0.645 };
   int incY = 1;
   double x_expected[] = { -2.253675853752e+04 };
   double y_expected[] = { -396.794859553 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 732)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 733)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, 0.070033F, 0.034824F, -0.00740144F, -0.153474F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -0.00701131F };
   float y_expected[] = { 0.0119423F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 734)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 735)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, 7.618016e-04F, -0.00396806F, -92.8408F, -0.0018571F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { 9.4516F };
   float y_expected[] = { -0.10256F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 736)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 737)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 1.0F, -5.833806e+03F, 0.00265668F, -587.573F, 0.0972416F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { 647.449F };
   float y_expected[] = { 0.100984F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 738)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 739)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -2.0F, -8.93339e+04F, -5.16022e-05F, 2.589784e-05F, -7.52586F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -0.111F };
   float y_expected[] = { -0.103F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 740)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 741)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, 0.125135F, 0.00586453F, 1.100694e-05F, -0.0137436F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -0.0138912F };
   float y_expected[] = { 7.64631e-04F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 742)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 743)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, -0.0996414F, 0.00505806F, 1.321441e-05F, 1.151406e-04F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -0.111001F };
   float y_expected[] = { -0.103561F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 744)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 745)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 1.0F, 8.18165F, 169.902F, -1.453316e-05F, 1.539957e+03F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -1.01116F };
   float y_expected[] = { -158.505F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 746)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 747)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -2.0F, 1.827623e-04F, -0.0528808F, 24.7305F, 328.39F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -0.111F };
   float y_expected[] = { -0.103F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 748)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 749)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { -1.0F, -0.0876053F, 7.858704e+04F, -4.758389e+03F, -0.0114841F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { 490.124F };
   float y_expected[] = { -8.72316e+03F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 750)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 751)");
     }
   };
  };


  {
   int N = 1;
   float h[] = { 0.0F, 0.00192188F, -1.031412e-05F, -0.00123957F, 0.312197F };
   float X[] = { -0.111F };
   int incX = -1;
   float Y[] = { -0.103F };
   int incY = -1;
   float x_expected[] = { -0.110872F };
   float y_expected[] = { -0.102999F };
   cblas_srotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], flteps, "srotm(case 752)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "srotm(case 753)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, -0.0253351881542, -0.105247702585, -7.18405641016, -5.409804811228e+04 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.21037864911 };
   double y_expected[] = { 1.622920078085e+03 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 754)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 755)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, 8.503080247483e+03, -6.186691885896e-05, -0.201279925805, -5.810746179529e-05 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.209038397774 };
   double y_expected[] = { -0.0300125589845 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 756)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 757)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 1.0, 0.351101212426, 64.9574703355, 3.015315809025e-05, -5.291308403203e-04 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.0412735461225 };
   double y_expected[] = { -0.202984126075 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 758)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 759)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -2.0, 0.0220262018719, -0.00311338149392, -70.6413298654, 31.8952671416 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.203 };
   double y_expected[] = { -0.03 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 760)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 761)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, 1.549812806922e+04, -4.868519165134e+04, -5.230242596804e+04, 1.58043443456e+04 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 4.715192777093e+03 };
   double y_expected[] = { -1.035722423559e+04 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 762)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 763)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, -3.30917942895, -0.0100316602276, -0.0222191220411, -0.0881815578726 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.203666573661 };
   double y_expected[] = { -0.0320364270262 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 764)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 765)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 1.0, 5.68327898035, 1.646867755046e-04, -0.106527931872, -28.2458905362 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 1.12370563301 };
   double y_expected[] = { 0.644376716086 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 766)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 767)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -2.0, 2.20585352008, 1.117638462348e+03, -0.116329468158, 0.00362096329059 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.203 };
   double y_expected[] = { -0.03 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 768)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 769)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { -1.0, -0.00182683798892, -2.288460066516e-05, -37.55844708, -9.54075659826e-05 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 1.12638256429 };
   double y_expected[] = { -1.783346955549e-06 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 770)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 771)");
     }
   };
  };


  {
   int N = 1;
   double h[] = { 0.0, 1.02690456955e-04, -20.1292302013, -1.703870486677e-04, 5.17477399477 };
   double X[] = { 0.203 };
   int incX = -1;
   double Y[] = { -0.03 };
   int incY = -1;
   double x_expected[] = { 0.203005111611 };
   double y_expected[] = { -4.11623373087 };
   cblas_drotm(N, X, incX, Y, incY, h);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], x_expected[i], dbleps, "drotm(case 772)");
     }
   };
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "drotm(case 773)");
     }
   };
  };


}
