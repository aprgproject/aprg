#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_scal (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int N = 1;
   float alpha = 0.0F;
   float X[] = { 0.651F };
   int incX = -1;
   float expected[] = { 0.651F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 112)");
     }
   };
  };


  {
   int N = 1;
   float alpha = 0.1F;
   float X[] = { 0.651F };
   int incX = -1;
   float expected[] = { 0.651F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 113)");
     }
   };
  };


  {
   int N = 1;
   float alpha = 1.0F;
   float X[] = { 0.651F };
   int incX = -1;
   float expected[] = { 0.651F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 114)");
     }
   };
  };


  {
   int N = 1;
   double alpha = 0;
   double X[] = { 0.686 };
   int incX = -1;
   double expected[] = { 0.686 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 115)");
     }
   };
  };


  {
   int N = 1;
   double alpha = 0.1;
   double X[] = { 0.686 };
   int incX = -1;
   double expected[] = { 0.686 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 116)");
     }
   };
  };


  {
   int N = 1;
   double alpha = 1;
   double X[] = { 0.686 };
   int incX = -1;
   double expected[] = { 0.686 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 117)");
     }
   };
  };


  {
   int N = 1;
   float alpha[2] = {0.0F, 0.0F};
   float X[] = { 0.986F, -0.775F };
   int incX = -1;
   float expected[] = { 0.986F, -0.775F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 118) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 118) imag");
     };
   };
  };


  {
   int N = 1;
   float alpha[2] = {0.1F, 0.0F};
   float X[] = { 0.986F, -0.775F };
   int incX = -1;
   float expected[] = { 0.986F, -0.775F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 119) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 119) imag");
     };
   };
  };


  {
   int N = 1;
   float alpha[2] = {1.0F, 0.0F};
   float X[] = { 0.986F, -0.775F };
   int incX = -1;
   float expected[] = { 0.986F, -0.775F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 120) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 120) imag");
     };
   };
  };


  {
   int N = 1;
   float alpha[2] = {0.0F, 0.1F};
   float X[] = { 0.986F, -0.775F };
   int incX = -1;
   float expected[] = { 0.986F, -0.775F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 121) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 121) imag");
     };
   };
  };


  {
   int N = 1;
   float alpha[2] = {0.1F, 0.2F};
   float X[] = { 0.986F, -0.775F };
   int incX = -1;
   float expected[] = { 0.986F, -0.775F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 122) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 122) imag");
     };
   };
  };


  {
   int N = 1;
   float alpha[2] = {1.0F, 0.3F};
   float X[] = { 0.986F, -0.775F };
   int incX = -1;
   float expected[] = { 0.986F, -0.775F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 123) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 123) imag");
     };
   };
  };


  {
   int N = 1;
   double alpha[2] = {0, 0};
   double X[] = { 0.454, -0.478 };
   int incX = -1;
   double expected[] = { 0.454, -0.478 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 124) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 124) imag");
     };
   };
  };


  {
   int N = 1;
   double alpha[2] = {0.1, 0};
   double X[] = { 0.454, -0.478 };
   int incX = -1;
   double expected[] = { 0.454, -0.478 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 125) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 125) imag");
     };
   };
  };


  {
   int N = 1;
   double alpha[2] = {1, 0};
   double X[] = { 0.454, -0.478 };
   int incX = -1;
   double expected[] = { 0.454, -0.478 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 126) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 126) imag");
     };
   };
  };


  {
   int N = 1;
   double alpha[2] = {0, 0.1};
   double X[] = { 0.454, -0.478 };
   int incX = -1;
   double expected[] = { 0.454, -0.478 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 127) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 127) imag");
     };
   };
  };


  {
   int N = 1;
   double alpha[2] = {0.1, 0.2};
   double X[] = { 0.454, -0.478 };
   int incX = -1;
   double expected[] = { 0.454, -0.478 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 128) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 128) imag");
     };
   };
  };


  {
   int N = 1;
   double alpha[2] = {1, 0.3};
   double X[] = { 0.454, -0.478 };
   int incX = -1;
   double expected[] = { 0.454, -0.478 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 1; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 129) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 129) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha = 0.0F;
   float X[] = { 0.389F, -0.236F };
   int incX = 1;
   float expected[] = { 0.0F, -0.0F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 130)");
     }
   };
  };


  {
   int N = 2;
   float alpha = 0.1F;
   float X[] = { 0.389F, -0.236F };
   int incX = 1;
   float expected[] = { 0.0389F, -0.0236F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 131)");
     }
   };
  };


  {
   int N = 2;
   float alpha = 1.0F;
   float X[] = { 0.389F, -0.236F };
   int incX = 1;
   float expected[] = { 0.389F, -0.236F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 132)");
     }
   };
  };


  {
   int N = 2;
   double alpha = 0;
   double X[] = { -0.429, -0.183 };
   int incX = 1;
   double expected[] = { -0.0, -0.0 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 133)");
     }
   };
  };


  {
   int N = 2;
   double alpha = 0.1;
   double X[] = { -0.429, -0.183 };
   int incX = 1;
   double expected[] = { -0.0429, -0.0183 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 134)");
     }
   };
  };


  {
   int N = 2;
   double alpha = 1;
   double X[] = { -0.429, -0.183 };
   int incX = 1;
   double expected[] = { -0.429, -0.183 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 135)");
     }
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.0F, 0.0F};
   float X[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   int incX = 1;
   float expected[] = { -0.0F, 0.0F, 0.0F, 0.0F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 136) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 136) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.1F, 0.0F};
   float X[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   int incX = 1;
   float expected[] = { -0.0603F, 0.0239F, 0.0339F, -0.058F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 137) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 137) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {1.0F, 0.0F};
   float X[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   int incX = 1;
   float expected[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 138) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 138) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.0F, 0.1F};
   float X[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   int incX = 1;
   float expected[] = { -0.0239F, -0.0603F, 0.058F, 0.0339F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 139) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 139) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.1F, 0.2F};
   float X[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   int incX = 1;
   float expected[] = { -0.1081F, -0.0967F, 0.1499F, 0.0098F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 140) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 140) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {1.0F, 0.3F};
   float X[] = { -0.603F, 0.239F, 0.339F, -0.58F };
   int incX = 1;
   float expected[] = { -0.6747F, 0.0581F, 0.513F, -0.4783F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 141) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 141) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0, 0};
   double X[] = { -0.956, 0.613, 0.443, 0.503 };
   int incX = 1;
   double expected[] = { -0.0, 0.0, 0.0, 0.0 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 142) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 142) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0.1, 0};
   double X[] = { -0.956, 0.613, 0.443, 0.503 };
   int incX = 1;
   double expected[] = { -0.0956, 0.0613, 0.0443, 0.0503 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 143) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 143) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {1, 0};
   double X[] = { -0.956, 0.613, 0.443, 0.503 };
   int incX = 1;
   double expected[] = { -0.956, 0.613, 0.443, 0.503 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 144) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 144) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0, 0.1};
   double X[] = { -0.956, 0.613, 0.443, 0.503 };
   int incX = 1;
   double expected[] = { -0.0613, -0.0956, -0.0503, 0.0443 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 145) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 145) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0.1, 0.2};
   double X[] = { -0.956, 0.613, 0.443, 0.503 };
   int incX = 1;
   double expected[] = { -0.2182, -0.1299, -0.0563, 0.1389 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 146) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 146) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {1, 0.3};
   double X[] = { -0.956, 0.613, 0.443, 0.503 };
   int incX = 1;
   double expected[] = { -1.1399, 0.3262, 0.2921, 0.6359 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 147) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 147) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha = 0.0F;
   float X[] = { 0.629F, -0.419F };
   int incX = -1;
   float expected[] = { 0.629F, -0.419F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 148)");
     }
   };
  };


  {
   int N = 2;
   float alpha = 0.1F;
   float X[] = { 0.629F, -0.419F };
   int incX = -1;
   float expected[] = { 0.629F, -0.419F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 149)");
     }
   };
  };


  {
   int N = 2;
   float alpha = 1.0F;
   float X[] = { 0.629F, -0.419F };
   int incX = -1;
   float expected[] = { 0.629F, -0.419F };
   cblas_sscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], flteps, "sscal(case 150)");
     }
   };
  };


  {
   int N = 2;
   double alpha = 0;
   double X[] = { 0.398, -0.656 };
   int incX = -1;
   double expected[] = { 0.398, -0.656 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 151)");
     }
   };
  };


  {
   int N = 2;
   double alpha = 0.1;
   double X[] = { 0.398, -0.656 };
   int incX = -1;
   double expected[] = { 0.398, -0.656 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 152)");
     }
   };
  };


  {
   int N = 2;
   double alpha = 1;
   double X[] = { 0.398, -0.656 };
   int incX = -1;
   double expected[] = { 0.398, -0.656 };
   cblas_dscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[i], expected[i], dbleps, "dscal(case 153)");
     }
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.0F, 0.0F};
   float X[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   int incX = -1;
   float expected[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 154) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 154) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.1F, 0.0F};
   float X[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   int incX = -1;
   float expected[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 155) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 155) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {1.0F, 0.0F};
   float X[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   int incX = -1;
   float expected[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 156) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 156) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.0F, 0.1F};
   float X[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   int incX = -1;
   float expected[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 157) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 157) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {0.1F, 0.2F};
   float X[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   int incX = -1;
   float expected[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 158) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 158) imag");
     };
   };
  };


  {
   int N = 2;
   float alpha[2] = {1.0F, 0.3F};
   float X[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   int incX = -1;
   float expected[] = { 0.736F, 0.331F, -0.318F, 0.622F };
   cblas_cscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], flteps, "cscal(case 159) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], flteps, "cscal(case 159) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0, 0};
   double X[] = { 0.521, -0.811, 0.556, -0.147 };
   int incX = -1;
   double expected[] = { 0.521, -0.811, 0.556, -0.147 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 160) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 160) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0.1, 0};
   double X[] = { 0.521, -0.811, 0.556, -0.147 };
   int incX = -1;
   double expected[] = { 0.521, -0.811, 0.556, -0.147 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 161) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 161) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {1, 0};
   double X[] = { 0.521, -0.811, 0.556, -0.147 };
   int incX = -1;
   double expected[] = { 0.521, -0.811, 0.556, -0.147 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 162) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 162) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0, 0.1};
   double X[] = { 0.521, -0.811, 0.556, -0.147 };
   int incX = -1;
   double expected[] = { 0.521, -0.811, 0.556, -0.147 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 163) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 163) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {0.1, 0.2};
   double X[] = { 0.521, -0.811, 0.556, -0.147 };
   int incX = -1;
   double expected[] = { 0.521, -0.811, 0.556, -0.147 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 164) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 164) imag");
     };
   };
  };


  {
   int N = 2;
   double alpha[2] = {1, 0.3};
   double X[] = { 0.521, -0.811, 0.556, -0.147 };
   int incX = -1;
   double expected[] = { 0.521, -0.811, 0.556, -0.147 };
   cblas_zscal(N, alpha, X, incX);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(X[2*i], expected[2*i], dbleps, "zscal(case 165) real");
       gsl_test_rel(X[2*i+1], expected[2*i+1], dbleps, "zscal(case 165) imag");
     };
   };
  };


}
