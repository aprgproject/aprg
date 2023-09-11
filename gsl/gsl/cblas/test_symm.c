#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_symm (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha = -0.3F;
   float beta = -1.0F;
   float A[] = { -0.581F };
   int lda = 1;
   float B[] = { 0.157F, 0.451F };
   int ldb = 2;
   float C[] = { -0.869F, -0.871F };
   int ldc = 2;
   float C_expected[] = { 0.896365F, 0.949609F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1518)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha = -0.3F;
   float beta = -1.0F;
   float A[] = { 0.874F };
   int lda = 1;
   float B[] = { 0.085F, 0.069F };
   int ldb = 1;
   float C[] = { -0.495F, -0.828F };
   int ldc = 1;
   float C_expected[] = { 0.472713F, 0.809908F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1519)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha = -1.0F;
   float beta = 0.0F;
   float A[] = { -0.671F, -0.343F, 0.6F, 0.177F };
   int lda = 2;
   float B[] = { 0.043F, 0.01F };
   int ldb = 2;
   float C[] = { 0.988F, 0.478F };
   int ldc = 2;
   float C_expected[] = { 0.032283F, 0.012979F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1520)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha = -1.0F;
   float beta = 0.0F;
   float A[] = { 0.069F, 0.096F, 0.139F, -0.044F };
   int lda = 2;
   float B[] = { -0.448F, 0.07F };
   int ldb = 1;
   float C[] = { 0.361F, 0.995F };
   int ldc = 1;
   float C_expected[] = { 0.021182F, 0.065352F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1521)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha = 0.0F;
   float beta = -0.3F;
   float A[] = { 0.745F };
   int lda = 1;
   float B[] = { -0.269F, 0.448F };
   int ldb = 2;
   float C[] = { -0.986F, 0.2F };
   int ldc = 2;
   float C_expected[] = { 0.2958F, -0.06F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1522)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha = 0.0F;
   float beta = -0.3F;
   float A[] = { 0.96F };
   int lda = 1;
   float B[] = { 0.392F, -0.07F };
   int ldb = 1;
   float C[] = { -0.235F, 0.554F };
   int ldc = 1;
   float C_expected[] = { 0.0705F, -0.1662F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1523)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha = -0.3F;
   float beta = 0.1F;
   float A[] = { -0.839F, 0.498F, -0.215F, -0.314F };
   int lda = 2;
   float B[] = { -0.66F, 0.593F };
   int ldb = 2;
   float C[] = { -0.806F, 0.525F };
   int ldc = 2;
   float C_expected[] = { -0.208474F, 0.0657906F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1524)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha = -0.3F;
   float beta = 0.1F;
   float A[] = { 0.994F, -0.117F, -0.639F, 0.925F };
   int lda = 2;
   float B[] = { -0.478F, 0.147F };
   int ldb = 1;
   float C[] = { -0.814F, 0.316F };
   int ldc = 1;
   float C_expected[] = { 0.0662993F, -0.0259703F };
   cblas_ssymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], flteps, "ssymm(case 1525)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { -0.981 };
   int lda = 1;
   double B[] = { -0.823, 0.83 };
   int ldb = 2;
   double C[] = { 0.991, 0.382 };
   int ldc = 2;
   double C_expected[] = { 0.7487911, 0.626269 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1526)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha = -0.3;
   double beta = 1;
   double A[] = { -0.248 };
   int lda = 1;
   double B[] = { 0.74, 0.068 };
   int ldb = 1;
   double C[] = { -0.905, 0.742 };
   int ldc = 1;
   double C_expected[] = { -0.849944, 0.7470592 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1527)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha = -1;
   double beta = 1;
   double A[] = { 0.591, -0.01, -0.192, -0.376 };
   int lda = 2;
   double B[] = { 0.561, 0.946 };
   int ldb = 2;
   double C[] = { 0.763, 0.189 };
   int ldc = 2;
   double C_expected[] = { 0.440909, 0.550306 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1528)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha = -1;
   double beta = 1;
   double A[] = { -0.786, 0.87, 0.222, -0.043 };
   int lda = 2;
   double B[] = { -0.503, -0.526 };
   int ldb = 1;
   double C[] = { -0.027, -0.391 };
   int ldc = 1;
   double C_expected[] = { -0.305586, -0.301952 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1529)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha = 0.1;
   double beta = 0.1;
   double A[] = { -0.468 };
   int lda = 1;
   double B[] = { -0.881, 0.692 };
   int ldb = 2;
   double C[] = { -0.812, -0.395 };
   int ldc = 2;
   double C_expected[] = { -0.0399692, -0.0718856 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1530)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha = 0.1;
   double beta = 0.1;
   double A[] = { 0.849 };
   int lda = 1;
   double B[] = { -0.887, 0.518 };
   int ldb = 1;
   double C[] = { 0.414, -0.251 };
   int ldc = 1;
   double C_expected[] = { -0.0339063, 0.0188782 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1531)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha = -1;
   double beta = 1;
   double A[] = { 0.457, 0.624, 0.807, 0.349 };
   int lda = 2;
   double B[] = { -0.609, 0.03 };
   int ldb = 2;
   double C[] = { 0.719, -0.624 };
   int ldc = 2;
   double C_expected[] = { 0.973103, -0.143007 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1532)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha = -1;
   double beta = 1;
   double A[] = { -0.133, -0.117, -0.163, 0.795 };
   int lda = 2;
   double B[] = { -0.882, 0.549 };
   int ldb = 1;
   double C[] = { 0.715, -0.327 };
   int ldc = 1;
   double C_expected[] = { 0.661927, -0.866649 };
   cblas_dsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[i], C_expected[i], dbleps, "dsymm(case 1533)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {1.0F, 0.0F};
   float A[] = { 0.476F, 0.816F };
   int lda = 1;
   float B[] = { 0.282F, 0.852F, -0.891F, -0.588F };
   int ldb = 2;
   float C[] = { 0.9F, 0.486F, -0.78F, -0.637F };
   int ldc = 2;
   float C_expected[] = { 1.461F, -0.149664F, -0.835692F, 0.369944F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1534) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1534) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {1.0F, 0.0F};
   float A[] = { 0.048F, 0.172F };
   int lda = 1;
   float B[] = { 0.786F, 0.783F, 0.809F, -0.569F };
   int ldb = 1;
   float C[] = { -0.227F, -0.215F, 0.881F, 0.233F };
   int ldc = 1;
   float C_expected[] = { -0.130052F, -0.387776F, 0.7443F, 0.121164F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1535) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1535) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { -0.495F, -0.012F, 0.843F, -0.986F, -0.243F, 0.833F, 0.921F, 0.004F };
   int lda = 2;
   float B[] = { 0.876F, 0.612F, 0.805F, -0.57F };
   int ldb = 2;
   float C[] = { 0.938F, -0.24F, -0.874F, -0.062F };
   int ldc = 2;
   float C_expected[] = { 1.82769F, 0.628319F, 0.93157F, 1.21158F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1536) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1536) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   float alpha[2] = {0.0F, 1.0F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { -0.812F, 0.83F, 0.705F, 0.15F, -0.463F, 0.901F, -0.547F, -0.483F };
   int lda = 2;
   float B[] = { -0.808F, -0.664F, 0.352F, -0.102F };
   int ldb = 1;
   float C[] = { -0.64F, 0.399F, 0.896F, -0.163F };
   int ldc = 1;
   float C_expected[] = { -0.631906F, 0.496142F, 0.697798F, 1.62656F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1537) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1537) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { 0.342F, -0.906F };
   int lda = 1;
   float B[] = { 0.676F, 0.863F, -0.517F, -0.138F };
   int ldb = 2;
   float C[] = { 0.274F, 0.388F, -0.271F, 0.205F };
   int ldc = 2;
   float C_expected[] = { -1.40107F, 0.59131F, 0.096842F, -0.692206F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1538) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1538) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-1.0F, 0.0F};
   float beta[2] = {0.0F, 1.0F};
   float A[] = { 0.418F, 0.354F };
   int lda = 1;
   float B[] = { -0.74F, 0.018F, 0.395F, 0.248F };
   int ldb = 1;
   float C[] = { -0.162F, 0.175F, -0.853F, 0.652F };
   int ldc = 1;
   float C_expected[] = { 0.140692F, 0.092436F, -0.729318F, -1.09649F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1539) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1539) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-0.3F, 0.1F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { 0.12F, 0.496F, 0.313F, -0.136F, 0.987F, 0.532F, 0.58F, -0.687F };
   int lda = 2;
   float B[] = { -0.587F, 0.278F, 0.857F, 0.136F };
   int ldb = 2;
   float C[] = { 0.162F, 0.249F, -0.665F, 0.456F };
   int ldc = 2;
   float C_expected[] = { -0.22769F, -0.0269913F, 0.0502096F, 0.0841558F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1540) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1540) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   float alpha[2] = {-0.3F, 0.1F};
   float beta[2] = {0.0F, 0.1F};
   float A[] = { 0.579F, -0.859F, 0.192F, -0.737F, 0.396F, -0.498F, 0.751F, -0.379F };
   int lda = 2;
   float B[] = { 0.84F, -0.755F, -0.019F, -0.063F };
   int ldb = 1;
   float C[] = { 0.04F, 0.639F, -0.876F, -0.778F };
   int ldc = 1;
   float C_expected[] = { 0.115459F, 0.329813F, 0.288206F, 0.110315F };
   cblas_csymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], flteps, "csymm(case 1541) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], flteps, "csymm(case 1541) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {0, 0};
   double A[] = { 0.511, -0.486 };
   int lda = 1;
   double B[] = { 0.985, -0.923, -0.234, -0.756 };
   int ldb = 2;
   double C[] = { -0.16, 0.049, 0.618, -0.349 };
   int ldc = 2;
   double C_expected[] = { 0.0, 0.0, 0.0, 0.0 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1542) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1542) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {0, 0};
   double beta[2] = {0, 0};
   double A[] = { 0.46, -0.816 };
   int lda = 1;
   double B[] = { 0.404, 0.113, -0.904, -0.627 };
   int ldb = 1;
   double C[] = { 0.114, 0.318, 0.636, -0.839 };
   int ldc = 1;
   double C_expected[] = { 0.0, 0.0, 0.0, 0.0 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1543) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1543) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {-1, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.835, 0.344, 0.975, 0.634, 0.312, -0.659, -0.624, -0.175 };
   int lda = 2;
   double B[] = { -0.707, -0.846, 0.825, -0.661 };
   int ldb = 2;
   double C[] = { 0.352, -0.499, 0.267, 0.548 };
   int ldc = 2;
   double C_expected[] = { -2.160518, -0.156877, 0.648536, 0.867299 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1544) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1544) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int M = 1;
   int N = 2;
   double alpha[2] = {-1, 0};
   double beta[2] = {-0.3, 0.1};
   double A[] = { -0.409, 0.013, -0.308, -0.317, -0.535, -0.697, -0.385, 0.119 };
   int lda = 2;
   double B[] = { 0.299, -0.233, 0.093, 0.664 };
   int ldb = 1;
   double C[] = { 0.699, 0.47, -0.347, -0.182 };
   int ldc = 1;
   double C_expected[] = { -0.550491, 0.249777, 0.559487, 0.348221 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1545) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1545) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {0, 1};
   double A[] = { -0.151, 0.635 };
   int lda = 1;
   double B[] = { 0.711, -0.869, 0.153, 0.647 };
   int ldb = 2;
   double C[] = { -0.299, 0.43, -0.307, 0.133 };
   int ldc = 2;
   double C_expected[] = { 0.014454, 0.283704, -0.566948, -0.307542 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1546) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1546) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {0, 1};
   double A[] = { 0.793, -0.543 };
   int lda = 1;
   double B[] = { 0.054, -0.045, 0.989, 0.453 };
   int ldb = 1;
   double C[] = { 0.443, -0.641, -0.809, -0.83 };
   int ldc = 1;
   double C_expected[] = { 0.659387, 0.377993, 1.860256, -0.986798 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1547) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1547) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {-1, 0};
   double A[] = { -0.432, -0.293, -0.819, 0.44, -0.818, -0.258, -0.836, 0.683 };
   int lda = 2;
   double B[] = { -0.259, -0.878, 0.161, 0.744 };
   int ldb = 2;
   double C[] = { 0.436, -0.655, -0.61, -0.875 };
   int ldc = 2;
   double C_expected[] = { -0.521112, 0.460053, -0.04741, 1.148005 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1548) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1548) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int M = 1;
   int N = 2;
   double alpha[2] = {1, 0};
   double beta[2] = {-1, 0};
   double A[] = { -0.656, 0.378, -0.688, 0.676, 0.967, -0.804, 0.455, -0.425 };
   int lda = 2;
   double B[] = { 0.791, -0.947, -0.945, -0.444 };
   int ldb = 1;
   double C[] = { 0.014, -0.814, -0.091, -0.417 };
   int ldc = 1;
   double C_expected[] = { 0.775374, 1.400882, -0.431711, 1.802857 };
   cblas_zsymm(order, side, uplo, M, N, alpha, A, lda, B, ldb, beta, C, ldc);
   {
     int i = 0;
     for (i = 0; i < 2; i++) {
       gsl_test_rel(C[2*i], C_expected[2*i], dbleps, "zsymm(case 1549) real");
       gsl_test_rel(C[2*i+1], C_expected[2*i+1], dbleps, "zsymm(case 1549) imag");
     };
   };
  };


}
