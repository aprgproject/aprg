#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_hbmv (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { 0.02698F, 0.521724F, -0.379354F, 1.27743F, -0.25427F, -0.043268F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1086) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1086) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { 0.02698F, 0.521724F, -0.379354F, 1.27743F, -0.25427F, -0.043268F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1087) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1087) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { -0.06422F, -0.016288F, 0.734206F, 0.108366F, -0.411982F, 0.347068F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1088) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1088) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { -0.06422F, -0.016288F, 0.734206F, 0.108366F, -0.411982F, 0.347068F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1089) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1089) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { 0.19354F, 0.056192F, 0.72585F, 0.42717F, -0.2047F, 0.405354F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1090) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1090) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { 0.19354F, 0.056192F, 0.72585F, 0.42717F, -0.2047F, 0.405354F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1091) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1091) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { -0.151304F, 0.471592F, -0.507714F, -0.304446F, -1.16395F, -0.299062F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1092) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1092) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {-0.3F, 0.1F};
   int N = 3;
   int k = 1;
   int lda = 3;
   float A[] = { 0.937F, -0.035F, 0.339F, 0.847F, 0.022F, 0.153F, -0.785F, 0.193F, -0.731F, -0.166F, -0.243F, -0.319F, 0.173F, -0.24F, 0.079F, -0.058F, 0.124F, 0.445F };
   float X[] = { -0.093F, -0.103F, -0.537F, -0.151F, 0.094F, 0.954F };
   int incX = -1;
   float Y[] = { 0.029F, -0.391F, -0.256F, 0.031F, -0.478F, 0.098F };
   int incY = -1;
   float y_expected[] = { -0.151304F, 0.471592F, -0.507714F, -0.304446F, -1.16395F, -0.299062F };
   cblas_chbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "chbmv(case 1093) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "chbmv(case 1093) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -0.902712, -0.524419, -0.307439, -2.167713, 1.059385, 1.104445 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1094) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1094) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -0.902712, -0.524419, -0.307439, -2.167713, 1.059385, 1.104445 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1095) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1095) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -0.960834, -0.558818, 1.042598, -1.102864, 0.507945, 0.11149 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1096) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1096) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -0.960834, -0.558818, 1.042598, -1.102864, 0.507945, 0.11149 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1097) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1097) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -1.626828, 0.003954, 0.437012, -2.365106, 0.446715, 0.16323 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1098) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1098) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -1.626828, 0.003954, 0.437012, -2.365106, 0.446715, 0.16323 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1099) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1099) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -0.097302, -1.204999, 1.168771, -0.822543, 0.734395, 1.379065 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1100) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1100) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   int N = 3;
   int k = 1;
   int lda = 3;
   double A[] = { 0.662, 0.24, -0.311, -0.345, -0.782, 0.904, -0.842, 0.065, -0.168, -0.855, -0.692, 0.113, 0.009, -0.707, -0.981, 0.019, -0.687, 0.861 };
   double X[] = { 0.873, -0.509, 0.398, 0.471, 0.214, 0.878 };
   int incX = -1;
   double Y[] = { -0.441, -0.781, 0.979, -0.911, 0.879, 0.807 };
   int incY = -1;
   double y_expected[] = { -0.097302, -1.204999, 1.168771, -0.822543, 0.734395, 1.379065 };
   cblas_zhbmv(order, uplo, N, k, alpha, A, lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zhbmv(case 1101) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zhbmv(case 1101) imag");
     };
   };
  };


}
