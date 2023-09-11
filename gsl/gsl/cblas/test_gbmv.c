#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_gbmv (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha = -1.0F;
   float beta = -1.0F;
   float A[] = { 0.423F, -0.143F, -0.182F, -0.076F, -0.855F, 0.599F, 0.389F, -0.473F, 0.493F, -0.902F, -0.889F, -0.256F, 0.112F, 0.128F, -0.277F, -0.777F };
   float X[] = { 0.488F, 0.029F, -0.633F, 0.84F };
   int incX = -1;
   float Y[] = { 0.874F, 0.322F, -0.477F };
   int incY = -1;
   float y_expected[] = { -0.101941F, 0.764086F, 0.481914F };
   cblas_sgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "sgbmv(case 794)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha = -1.0F;
   float beta = -1.0F;
   float A[] = { 0.423F, -0.143F, -0.182F, -0.076F, -0.855F, 0.599F, 0.389F, -0.473F, 0.493F, -0.902F, -0.889F, -0.256F, 0.112F, 0.128F, -0.277F, -0.777F };
   float X[] = { 0.488F, 0.029F, -0.633F, 0.84F };
   int incX = -1;
   float Y[] = { 0.874F, 0.322F, -0.477F };
   int incY = -1;
   float y_expected[] = { -0.656261F, 0.19575F, 0.055905F };
   cblas_sgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "sgbmv(case 795)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha = 0.0F;
   float beta = 0.1F;
   float A[] = { -0.066F, -0.153F, -0.619F, 0.174F, 0.777F, 0.543F, 0.614F, -0.446F, -0.138F, -0.767F, 0.725F, 0.222F, 0.165F, -0.063F, -0.047F, 0.267F };
   float X[] = { -0.096F, -0.007F, -0.657F };
   int incX = -1;
   float Y[] = { -0.88F, 0.102F, -0.278F, 0.403F };
   int incY = -1;
   float y_expected[] = { -0.088F, 0.0102F, -0.0278F, 0.0403F };
   cblas_sgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "sgbmv(case 796)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha = 0.0F;
   float beta = 0.1F;
   float A[] = { -0.066F, -0.153F, -0.619F, 0.174F, 0.777F, 0.543F, 0.614F, -0.446F, -0.138F, -0.767F, 0.725F, 0.222F, 0.165F, -0.063F, -0.047F, 0.267F };
   float X[] = { -0.096F, -0.007F, -0.657F };
   int incX = -1;
   float Y[] = { -0.88F, 0.102F, -0.278F, 0.403F };
   int incY = -1;
   float y_expected[] = { -0.088F, 0.0102F, -0.0278F, 0.0403F };
   cblas_sgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[i], y_expected[i], flteps, "sgbmv(case 797)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha = 0.1;
   double beta = 0;
   double A[] = { -0.688, 0.29, 0.442, -0.001, 0.313, -0.073, 0.991, -0.654, -0.12, 0.416, 0.571, 0.932, -0.179, -0.724, 0.492, -0.965 };
   double X[] = { 0.187, -0.338, -0.976, -0.052 };
   int incX = -1;
   double Y[] = { -0.101, 0.8, 0.026 };
   int incY = -1;
   double y_expected[] = { 0.0083289, -0.0279986, -0.0446472 };
   cblas_dgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dgbmv(case 798)");
     }
   };
  };


  {
   int order = 102;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha = 0.1;
   double beta = 0;
   double A[] = { -0.688, 0.29, 0.442, -0.001, 0.313, -0.073, 0.991, -0.654, -0.12, 0.416, 0.571, 0.932, -0.179, -0.724, 0.492, -0.965 };
   double X[] = { 0.187, -0.338, -0.976, -0.052 };
   int incX = -1;
   double Y[] = { -0.101, 0.8, 0.026 };
   int incY = -1;
   double y_expected[] = { -0.1141297, 0.0088824, -0.0320568 };
   cblas_dgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dgbmv(case 799)");
     }
   };
  };


  {
   int order = 101;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha = -0.3;
   double beta = -0.3;
   double A[] = { 0.746, 0.262, -0.449, -0.954, -0.093, 0.108, -0.496, 0.927, 0.177, 0.729, -0.92, -0.469, 0.87, -0.877, -0.308, -0.806 };
   double X[] = { 0.662, -0.887, 0.261 };
   int incX = -1;
   double Y[] = { 0.771, 0.637, -0.177, -0.018 };
   int incY = -1;
   double y_expected[] = { -0.048588, -0.467865, 0.0818433, -0.0398619 };
   cblas_dgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dgbmv(case 800)");
     }
   };
  };


  {
   int order = 102;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha = -0.3;
   double beta = -0.3;
   double A[] = { 0.746, 0.262, -0.449, -0.954, -0.093, 0.108, -0.496, 0.927, 0.177, 0.729, -0.92, -0.469, 0.87, -0.877, -0.308, -0.806 };
   double X[] = { 0.662, -0.887, 0.261 };
   int incX = -1;
   double Y[] = { 0.771, 0.637, -0.177, -0.018 };
   int incY = -1;
   double y_expected[] = { -0.404082, -0.2887797, 0.1876263, -0.1345935 };
   cblas_dgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[i], y_expected[i], dbleps, "dgbmv(case 801)");
     }
   };
  };


  {
   int order = 101;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.107F, 0.926F, -0.246F, -0.555F, -0.301F, 0.276F, 0.471F, -0.084F, -0.754F, 0.082F, -0.952F, -0.394F, 0.659F, 0.054F, 0.795F, 0.923F, 0.232F, -0.788F, 0.478F, 0.775F, -0.118F, 0.691F, -0.933F, 0.809F, 0.164F, -0.263F, -0.923F, -0.88F, 0.819F, -0.521F, -0.045F, 0.034F };
   float X[] = { 0.407F, 0.895F, 0.301F, 0.769F, -0.269F, -0.465F, 0.455F, -0.628F };
   int incX = -1;
   float Y[] = { -0.116F, -0.744F, -0.936F, -0.064F, -0.232F, -0.665F };
   int incY = -1;
   float y_expected[] = { -0.806176F, -1.559F, -1.57611F, -0.155463F, 0.098816F, -0.274361F };
   cblas_cgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "cgbmv(case 802) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "cgbmv(case 802) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.107F, 0.926F, -0.246F, -0.555F, -0.301F, 0.276F, 0.471F, -0.084F, -0.754F, 0.082F, -0.952F, -0.394F, 0.659F, 0.054F, 0.795F, 0.923F, 0.232F, -0.788F, 0.478F, 0.775F, -0.118F, 0.691F, -0.933F, 0.809F, 0.164F, -0.263F, -0.923F, -0.88F, 0.819F, -0.521F, -0.045F, 0.034F };
   float X[] = { 0.407F, 0.895F, 0.301F, 0.769F, -0.269F, -0.465F, 0.455F, -0.628F };
   int incX = -1;
   float Y[] = { -0.116F, -0.744F, -0.936F, -0.064F, -0.232F, -0.665F };
   int incY = -1;
   float y_expected[] = { -0.245235F, -0.313725F, -0.798094F, 0.691455F, -0.164015F, -0.242714F };
   cblas_cgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "cgbmv(case 803) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "cgbmv(case 803) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.258F, 0.838F, -0.106F, -0.066F, 0.395F, 0.982F, -0.546F, 0.565F, 0.14F, -0.18F, 0.165F, -0.186F, 0.499F, -0.038F, -0.305F, -0.653F, -0.811F, -0.466F, -0.674F, -0.013F, -0.552F, -0.807F, -0.536F, 0.864F, -0.027F, -0.606F, 0.459F, 0.564F, -0.968F, 0.717F, -0.312F, -0.485F };
   float X[] = { -0.399F, 0.459F, 0.398F, 0.358F, -0.161F, -0.359F };
   int incX = -1;
   float Y[] = { 0.572F, 0.293F, -0.813F, -0.096F, -0.611F, -0.717F, 0.736F, 0.259F };
   int incY = -1;
   float y_expected[] = { -0.619961F, -0.011425F, -0.477499F, 0.059361F, -0.886984F, 0.44008F, -0.139432F, 0.04644F };
   cblas_cgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "cgbmv(case 804) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "cgbmv(case 804) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.258F, 0.838F, -0.106F, -0.066F, 0.395F, 0.982F, -0.546F, 0.565F, 0.14F, -0.18F, 0.165F, -0.186F, 0.499F, -0.038F, -0.305F, -0.653F, -0.811F, -0.466F, -0.674F, -0.013F, -0.552F, -0.807F, -0.536F, 0.864F, -0.027F, -0.606F, 0.459F, 0.564F, -0.968F, 0.717F, -0.312F, -0.485F };
   float X[] = { -0.399F, 0.459F, 0.398F, 0.358F, -0.161F, -0.359F };
   int incX = -1;
   float Y[] = { 0.572F, 0.293F, -0.813F, -0.096F, -0.611F, -0.717F, 0.736F, 0.259F };
   int incY = -1;
   float y_expected[] = { -0.318227F, -0.172201F, -0.109343F, 0.698685F, 0.208261F, -0.269065F, 0.175074F, -0.507326F };
   cblas_cgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "cgbmv(case 805) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "cgbmv(case 805) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.804F, 0.232F, -0.448F, -0.558F, -0.078F, -0.056F, -0.345F, -0.379F, 0.369F, -0.662F, -0.169F, -0.391F, -0.215F, 0.467F, 0.374F, 0.889F, -0.698F, 0.734F, 0.377F, -0.955F, 0.498F, 0.151F, -0.725F, -0.728F, -0.655F, -0.581F, 0.389F, 0.949F, -0.553F, -0.434F, 0.237F, 0.641F };
   float X[] = { -0.262F, -0.823F, -0.357F, -0.994F, -0.347F, -0.375F };
   int incX = -1;
   float Y[] = { -0.683F, -0.87F, -0.708F, 0.071F, 0.575F, -0.575F, 0.845F, 0.032F };
   int incY = -1;
   float y_expected[] = { 0.341749F, 0.301992F, -0.306848F, 0.109252F, -0.018347F, -0.747479F, -0.894201F, 0.713246F };
   cblas_cgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "cgbmv(case 806) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "cgbmv(case 806) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { -0.804F, 0.232F, -0.448F, -0.558F, -0.078F, -0.056F, -0.345F, -0.379F, 0.369F, -0.662F, -0.169F, -0.391F, -0.215F, 0.467F, 0.374F, 0.889F, -0.698F, 0.734F, 0.377F, -0.955F, 0.498F, 0.151F, -0.725F, -0.728F, -0.655F, -0.581F, 0.389F, 0.949F, -0.553F, -0.434F, 0.237F, 0.641F };
   float X[] = { -0.262F, -0.823F, -0.357F, -0.994F, -0.347F, -0.375F };
   int incX = -1;
   float Y[] = { -0.683F, -0.87F, -0.708F, 0.071F, 0.575F, -0.575F, 0.845F, 0.032F };
   int incY = -1;
   float y_expected[] = { -0.562773F, -0.455143F, -0.213881F, -0.466169F, -0.183683F, 0.097891F, -0.451416F, 0.052586F };
   cblas_cgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], flteps, "cgbmv(case 807) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], flteps, "cgbmv(case 807) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {1, 0};
   double A[] = { -0.919, -0.002, 0.105, -0.338, -0.358, -0.715, -0.157, 0.307, 0.334, 0.121, 0.366, 0.029, -0.006, -0.662, -0.314, 0.061, -0.322, -0.865, -0.586, 0.556, 0.507, 0.581, 0.855, -0.09, 0.836, -0.788, -0.209, -0.694, -0.695, 0.11, -0.234, 0.17 };
   double X[] = { 0.356, -0.76, -0.96, 0.437, -0.849, 0.397, -0.382, -0.826 };
   int incX = -1;
   double Y[] = { 0.288, -0.832, 0.889, 0.576, -0.809, 0.4 };
   int incY = -1;
   double y_expected[] = { 0.3241775, -0.6761577, 0.8458527, 0.5705165, -0.8597295, 0.4268499 };
   cblas_zgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zgbmv(case 808) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zgbmv(case 808) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 111;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {1, 0};
   double A[] = { -0.919, -0.002, 0.105, -0.338, -0.358, -0.715, -0.157, 0.307, 0.334, 0.121, 0.366, 0.029, -0.006, -0.662, -0.314, 0.061, -0.322, -0.865, -0.586, 0.556, 0.507, 0.581, 0.855, -0.09, 0.836, -0.788, -0.209, -0.694, -0.695, 0.11, -0.234, 0.17 };
   double X[] = { 0.356, -0.76, -0.96, 0.437, -0.849, 0.397, -0.382, -0.826 };
   int incX = -1;
   double Y[] = { 0.288, -0.832, 0.889, 0.576, -0.809, 0.4 };
   int incY = -1;
   double y_expected[] = { 0.4026074, -0.8033768, 0.7510795, 0.5671044, -0.8162255, 0.3349099 };
   cblas_zgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 3; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zgbmv(case 809) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zgbmv(case 809) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   double A[] = { 0.511, -0.707, -0.906, 0.345, -0.524, -0.933, 0.154, -0.529, -0.651, -0.851, 0.104, 0.532, -0.297, 0.477, 0.511, 0.469, -0.888, -0.789, 0.656, 0.288, -0.749, 0.961, 0.571, 0.539, 0.465, 0.647, 0.653, -0.994, -0.515, 0.297, 0.35, -0.707 };
   double X[] = { -0.991, 0.658, -0.909, -0.99, -0.517, -0.071 };
   int incX = -1;
   double Y[] = { 0.451, 0.351, -0.113, -0.62, 0.983, 0.511, 0.142, -0.186 };
   int incY = -1;
   double y_expected[] = { 0.560921, -1.094193, -0.210397, -0.613323, 3.018979, 0.641612, 0.384166, 1.11801 };
   cblas_zgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zgbmv(case 810) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zgbmv(case 810) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 112;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha[2] = {1, 0};
   double beta[2] = {1, 0};
   double A[] = { 0.511, -0.707, -0.906, 0.345, -0.524, -0.933, 0.154, -0.529, -0.651, -0.851, 0.104, 0.532, -0.297, 0.477, 0.511, 0.469, -0.888, -0.789, 0.656, 0.288, -0.749, 0.961, 0.571, 0.539, 0.465, 0.647, 0.653, -0.994, -0.515, 0.297, 0.35, -0.707 };
   double X[] = { -0.991, 0.658, -0.909, -0.99, -0.517, -0.071 };
   int incX = -1;
   double Y[] = { 0.451, 0.351, -0.113, -0.62, 0.983, 0.511, 0.142, -0.186 };
   int incY = -1;
   double y_expected[] = { -0.435541, 0.015793, -0.926518, 1.122561, 1.671751, -0.257493, 0.187543, 1.066818 };
   cblas_zgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zgbmv(case 811) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zgbmv(case 811) imag");
     };
   };
  };


  {
   int order = 101;
   int trans = 113;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {-0.3, 0.1};
   double A[] = { 0.534, 0.67, -0.621, 0.143, -0.794, 0.073, 0.414, -0.9, 0.155, -0.368, 0.122, -0.583, 0.03, 0.646, -0.768, -0.892, -0.741, -0.397, 0.626, 0.004, -0.515, 0.355, 0.196, -0.989, -0.982, 0.985, 0.445, 0.63, -0.849, -0.528, 0.146, -0.319 };
   double X[] = { -0.199, -0.259, 0.386, -0.131, -0.867, 0.888 };
   int incX = -1;
   double Y[] = { 0.106, 0.874, 0.962, 0.636, -0.759, 0.415, -0.053, 0.315 };
   int incY = -1;
   double y_expected[] = { -0.139603, -0.250546, -0.3107376, -0.1144656, 0.2181809, -0.0877031, 0.0149724, -0.0224571 };
   cblas_zgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zgbmv(case 812) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zgbmv(case 812) imag");
     };
   };
  };


  {
   int order = 102;
   int trans = 113;
   int M = 3;
   int N = 4;
   int KL = 1;
   int KU = 1;
   int lda = 4;
   double alpha[2] = {0, 0.1};
   double beta[2] = {-0.3, 0.1};
   double A[] = { 0.534, 0.67, -0.621, 0.143, -0.794, 0.073, 0.414, -0.9, 0.155, -0.368, 0.122, -0.583, 0.03, 0.646, -0.768, -0.892, -0.741, -0.397, 0.626, 0.004, -0.515, 0.355, 0.196, -0.989, -0.982, 0.985, 0.445, 0.63, -0.849, -0.528, 0.146, -0.319 };
   double X[] = { -0.199, -0.259, 0.386, -0.131, -0.867, 0.888 };
   int incX = -1;
   double Y[] = { 0.106, 0.874, 0.962, 0.636, -0.759, 0.415, -0.053, 0.315 };
   int incY = -1;
   double y_expected[] = { -0.1642353, -0.2575697, -0.3610975, -0.1305629, 0.1713576, -0.2514988, 0.0195631, -0.0648656 };
   cblas_zgbmv(order, trans, M, N, KU, KL, alpha, A,                                  lda, X, incX, beta, Y, incY);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(Y[2*i], y_expected[2*i], dbleps, "zgbmv(case 813) real");
       gsl_test_rel(Y[2*i+1], y_expected[2*i+1], dbleps, "zgbmv(case 813) imag");
     };
   };
  };


}
