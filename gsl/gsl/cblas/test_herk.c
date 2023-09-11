#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_herk (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = 0.0F;
   float beta = 0.1F;
   float A[] = { -0.617F, 0.179F, -0.626F, 0.334F };
   int lda = 1;
   float C[] = { 0.346F, -0.903F, 0.022F, -0.839F, -0.715F, 0.049F, -0.338F, 0.149F };
   int ldc = 2;
   float C_expected[] = { 0.0346F, 0.0F, 0.0022F, -0.0839F, -0.715F, 0.049F, -0.0338F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1598) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1598) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = 0.0F;
   float beta = 0.1F;
   float A[] = { -0.356F, -0.308F, 0.493F, -0.351F };
   int lda = 2;
   float C[] = { -0.898F, -0.905F, 0.002F, -0.219F, 0.881F, 0.879F, 0.275F, -0.351F };
   int ldc = 2;
   float C_expected[] = { -0.0898F, 0.0F, 0.002F, -0.219F, 0.0881F, 0.0879F, 0.0275F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1599) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1599) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 113;
   int N = 2;
   int K = 1;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { -0.103F, -0.951F, -0.601F, -0.041F };
   int lda = 2;
   float C[] = { -0.918F, -0.018F, 0.991F, -0.789F, -0.698F, -0.067F, 0.956F, -0.599F };
   int ldc = 2;
   float C_expected[] = { -0.826499F, 0.0F, 1.00109F, -0.845733F, -0.698F, -0.067F, 0.992288F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1600) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1600) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 113;
   int N = 2;
   int K = 1;
   float alpha = 0.1F;
   float beta = 1.0F;
   float A[] = { -0.237F, 0.925F, -0.904F, -0.091F };
   int lda = 1;
   float C[] = { -0.572F, 0.915F, 0.398F, 0.222F, 0.016F, 0.288F, -0.078F, -0.507F };
   int ldc = 2;
   float C_expected[] = { -0.480821F, 0.0F, 0.398F, 0.222F, 0.0290073F, 0.373777F, 0.0045497F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1601) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1601) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = -0.3F;
   float beta = 0.0F;
   float A[] = { 0.963F, -0.23F, -0.435F, 0.289F };
   int lda = 1;
   float C[] = { 0.282F, -0.272F, -0.516F, -0.594F, -0.001F, 0.155F, -0.39F, -0.354F };
   int ldc = 2;
   float C_expected[] = { -0.294081F, 0.0F, -0.516F, -0.594F, 0.145613F, -0.0534771F, -0.0818238F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1602) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1602) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   float alpha = -0.3F;
   float beta = 0.0F;
   float A[] = { 0.674F, 0.1F, -0.098F, 0.552F };
   int lda = 2;
   float C[] = { 0.089F, -0.523F, -0.551F, 0.618F, 0.67F, 0.247F, 0.975F, -0.714F };
   int ldc = 2;
   float C_expected[] = { -0.139283F, 0.0F, 0.0032556F, -0.114554F, 0.67F, 0.247F, -0.0942924F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1603) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1603) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 113;
   int N = 2;
   int K = 1;
   float alpha = 1.0F;
   float beta = 0.1F;
   float A[] = { 0.033F, -0.864F, 0.168F, 0.524F };
   int lda = 2;
   float C[] = { 0.788F, 0.016F, -0.436F, 0.749F, -0.89F, -0.87F, 0.421F, -0.203F };
   int ldc = 2;
   float C_expected[] = { 0.826385F, 0.0F, -0.436F, 0.749F, -0.536192F, -0.249444F, 0.3449F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1604) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1604) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 113;
   int N = 2;
   int K = 1;
   float alpha = 1.0F;
   float beta = 0.1F;
   float A[] = { 0.957F, -0.079F, 0.935F, 0.232F };
   int lda = 1;
   float C[] = { -0.744F, -0.061F, 0.195F, -0.574F, 0.551F, 0.478F, -0.337F, 0.1F };
   int ldc = 2;
   float C_expected[] = { 0.84769F, 0.0F, 0.895967F, -0.353289F, 0.551F, 0.478F, 0.894349F, 0.0F };
   cblas_cherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "cherk(case 1605) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "cherk(case 1605) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 1;
   double beta = 1;
   double A[] = { 0.934, 0.664, 0.426, 0.263 };
   int lda = 1;
   double C[] = { 0.251, -0.97, 0.76, -0.349, 0.152, -0.899, -0.17, 0.707 };
   int ldc = 2;
   double C_expected[] = { 1.564252, 0.0, 1.332516, -0.311778, 0.152, -0.899, 0.080645, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1606) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1606) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 1;
   double beta = 1;
   double A[] = { 0.16, 0.464, -0.623, 0.776 };
   int lda = 2;
   double C[] = { 0.771, -0.449, 0.776, 0.112, -0.134, 0.317, 0.547, -0.551 };
   int ldc = 2;
   double C_expected[] = { 1.011896, 0.0, 0.776, 0.112, 0.126384, -0.096232, 1.537305, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1607) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1607) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 121;
   int trans = 113;
   int N = 2;
   int K = 1;
   double alpha = 0.1;
   double beta = 1;
   double A[] = { 0.787, 0.057, -0.49, 0.47 };
   int lda = 2;
   double C[] = { -0.758, 0.912, 0.992, -0.356, 0.584, 0.806, 0.965, 0.674 };
   int ldc = 2;
   double C_expected[] = { -0.6957382, 0.0, 0.956116, -0.316218, 0.584, 0.806, 1.0111, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1608) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1608) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 121;
   int trans = 113;
   int N = 2;
   int K = 1;
   double alpha = 0.1;
   double beta = 1;
   double A[] = { 0.961, -0.384, 0.165, 0.395 };
   int lda = 1;
   double C[] = { -0.186, 0.404, -0.873, 0.09, -0.451, -0.972, -0.203, -0.304 };
   int ldc = 2;
   double C_expected[] = { -0.0789023, 0.0, -0.873, 0.09, -0.4503115, -0.9277045, -0.184675, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1609) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1609) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 0;
   double beta = -0.3;
   double A[] = { 0.04, 0.608, 0.21, -0.44 };
   int lda = 1;
   double C[] = { 0.285, -0.943, 0.581, -0.56, 0.112, 0.529, 0.16, -0.913 };
   int ldc = 2;
   double C_expected[] = { -0.0855, 0.0, 0.581, -0.56, -0.0336, -0.1587, -0.048, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1610) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1610) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 111;
   int N = 2;
   int K = 1;
   double alpha = 0;
   double beta = -0.3;
   double A[] = { -0.984, -0.398, -0.379, 0.919 };
   int lda = 2;
   double C[] = { -0.44, -0.087, 0.156, -0.945, -0.943, -0.355, 0.577, 0.053 };
   int ldc = 2;
   double C_expected[] = { 0.132, 0.0, -0.0468, 0.2835, -0.943, -0.355, -0.1731, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1611) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1611) imag");
     };
   };
  };


  {
   int order = 101;
   int uplo = 122;
   int trans = 113;
   int N = 2;
   int K = 1;
   double alpha = 1;
   double beta = -1;
   double A[] = { 0.269, -0.428, -0.029, 0.964 };
   int lda = 2;
   double C[] = { 0.473, -0.932, -0.689, -0.072, -0.952, -0.862, 0.001, 0.282 };
   int ldc = 2;
   double C_expected[] = { -0.217455, 0.0, -0.689, -0.072, 0.531607, 0.615096, 0.929137, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1612) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1612) imag");
     };
   };
  };


  {
   int order = 102;
   int uplo = 122;
   int trans = 113;
   int N = 2;
   int K = 1;
   double alpha = 1;
   double beta = -1;
   double A[] = { -0.303, -0.037, -0.411, -0.243 };
   int lda = 1;
   double C[] = { 0.652, -0.227, -0.849, 0.87, -0.051, -0.535, 0.418, -0.681 };
   int ldc = 2;
   double C_expected[] = { -0.558822, 0.0, 0.982524, -0.928422, -0.051, -0.535, -0.19003, 0.0 };
   cblas_zherk(order, uplo, trans, N, K, alpha, A, lda, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 4; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zherk(case 1613) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zherk(case 1613) imag");
     };
   };
  };


}
