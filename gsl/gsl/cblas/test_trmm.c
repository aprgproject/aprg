#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_trmm (void) {
const double flteps = 1e-4;
const double dbleps = 1e-6;
  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.18F, 0.199F, 0.122F, -0.547F };
   int lda = 2;
   float B[] = { -0.874F, -0.383F, 0.458F, 0.124F, -0.221F, -0.107F };
   int ldb = 3;
   float B_expected[] = { 0.0397932F, 0.0338757F, -0.0183441F, 0.0203484F, -0.0362661F, -0.0175587F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1662)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.195F, -0.453F, -0.579F, 0.697F };
   int lda = 2;
   float B[] = { 0.736F, 0.131F, 0.533F, 0.692F, -0.672F, -0.435F };
   int ldb = 3;
   float B_expected[] = { -0.126757F, -0.130625F, -0.219017F, -0.2076F, 0.2016F, 0.1305F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1663)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.53F, 0.787F, 0.889F, -0.379F };
   int lda = 2;
   float B[] = { -0.355F, 0.002F, 0.266F, 0.972F, 0.712F, -0.353F };
   int ldb = 3;
   float B_expected[] = { -0.056445F, 3.18e-04F, 0.042294F, 0.205195F, 0.080421F, -0.111078F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1664)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.198F, -0.673F, 0.792F, 0.781F };
   int lda = 2;
   float B[] = { 0.901F, 0.719F, -0.339F, -0.36F, 0.539F, 0.192F };
   int ldb = 3;
   float B_expected[] = { -0.2703F, -0.2157F, 0.1017F, -0.106078F, -0.332534F, 0.0229464F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1665)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.522F, 0.851F, 0.586F, 0.196F };
   int lda = 2;
   float B[] = { 0.335F, 0.617F, 0.118F, -0.143F, 0.677F, 0.456F };
   int ldb = 2;
   float B_expected[] = { -0.0560076F, -0.0362796F, 0.0436182F, 0.0084084F, 0.0258534F, -0.0268128F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1666)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.006F, -0.613F, -0.966F, -0.758F };
   int lda = 2;
   float B[] = { 0.64F, -0.723F, -0.765F, 0.801F, 0.376F, 0.91F };
   int ldb = 2;
   float B_expected[] = { -0.401525F, 0.2169F, 0.46163F, -0.2403F, 0.150918F, -0.273F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1667)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.738F, 0.913F, -0.227F, 0.787F };
   int lda = 2;
   float B[] = { 0.194F, 0.988F, -0.274F, -0.652F, -0.281F, -0.359F };
   int ldb = 2;
   float B_expected[] = { -0.0429516F, -0.286403F, 0.0606636F, 0.228986F, 0.0622134F, 0.161726F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1668)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.952F, 0.598F, 0.25F, -0.508F };
   int lda = 2;
   float B[] = { 0.036F, 0.745F, -0.606F, 0.215F, 0.943F, -0.933F };
   int ldb = 2;
   float B_expected[] = { -0.0108F, -0.229958F, 0.1818F, 0.0442164F, -0.2829F, 0.110726F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1669)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.251F, 0.372F, -0.168F, 0.217F, -0.179F, 0.863F, -0.057F, 0.256F, 0.093F };
   int lda = 3;
   float B[] = { -0.727F, -0.461F, 0.162F, 0.579F, -0.305F, -0.735F };
   int ldb = 3;
   float B_expected[] = { -0.0547431F, 0.0563775F, 0.0781923F, 0.0435987F, -0.0809949F, 0.128653F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1670)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.014F, 0.204F, 0.163F, 0.842F, -0.918F, -0.748F, -0.859F, -0.463F, 0.292F };
   int lda = 3;
   float B[] = { -0.587F, -0.625F, -0.994F, 0.681F, -0.577F, -0.434F };
   int ldb = 3;
   float B_expected[] = { 0.1761F, 0.223424F, 0.186654F, -0.2043F, 0.131423F, -0.0325797F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1671)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.682F, -0.71F, 0.475F, -0.59F, -0.748F, 0.548F, 0.245F, 0.761F, -0.4F };
   int lda = 3;
   float B[] = { 0.565F, 0.967F, -0.969F, 0.184F, 0.349F, -0.552F };
   int ldb = 3;
   float B_expected[] = { 0.357979F, 0.438217F, -0.11628F, 0.139991F, 0.204337F, -0.06624F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1672)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.617F, -0.998F, -0.97F, 0.364F, 0.09F, 0.588F, -0.263F, 0.584F, 0.463F };
   int lda = 3;
   float B[] = { 0.773F, 0.074F, -0.388F, 0.825F, -0.608F, 0.788F };
   int ldb = 3;
   float B_expected[] = { -0.270594F, 0.0457776F, 0.1164F, -0.118933F, 0.0443424F, -0.2364F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1673)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.217F, -0.672F, -0.378F, -0.005F, -0.586F, -0.426F, 0.765F, -0.239F, -0.145F };
   int lda = 3;
   float B[] = { 0.01F, 0.387F, -0.953F, -0.374F, -0.673F, -0.724F };
   int ldb = 2;
   float B_expected[] = { -6.51e-04F, -0.0251937F, -0.167522F, -0.0651687F, -0.0999006F, -0.147126F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1674)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { 0.962F, 0.515F, 0.292F, 0.354F, -0.366F, 0.455F, 0.134F, -0.564F, -0.303F };
   int lda = 3;
   float B[] = { -0.337F, 0.718F, -0.866F, -0.454F, -0.439F, -0.668F };
   int ldb = 2;
   float B_expected[] = { 0.1011F, -0.2154F, 0.295589F, 0.0599484F, -0.0012798F, 0.0947196F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1675)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.228F, -0.097F, 0.205F, 0.875F, -0.162F, 0.542F, -0.839F, -0.935F, 0.2F };
   int lda = 3;
   float B[] = { -0.125F, -0.676F, 0.181F, 0.741F, 0.216F, 0.766F };
   int ldb = 2;
   float B_expected[] = { -0.0165669F, -0.0717843F, -0.026325F, -0.088539F, -0.01296F, -0.04596F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1676)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = -0.3F;
   float A[] = { -0.854F, -0.502F, 0.591F, -0.934F, -0.729F, 0.063F, 0.352F, 0.126F, -0.905F };
   int lda = 3;
   float B[] = { -0.626F, -0.694F, -0.889F, -0.251F, -0.42F, -0.353F };
   int ldb = 2;
   float B_expected[] = { 0.128383F, 0.232986F, 0.274638F, 0.0819717F, 0.126F, 0.1059F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1677)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.755F, 0.12F, 0.525F, 0.917F };
   int lda = 2;
   float B[] = { -0.927F, -0.813F, 0.624F, -0.366F, -0.864F, -0.046F };
   int ldb = 3;
   float B_expected[] = { 0.0699885F, 0.0613815F, -0.047112F, -0.0446862F, -0.0889848F, 0.0032698F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1678)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.444F, 0.515F, 0.081F, -0.69F };
   int lda = 2;
   float B[] = { 0.571F, -0.098F, -0.226F, -0.587F, 0.788F, -0.629F };
   int ldb = 3;
   float B_expected[] = { 0.0571F, -0.0098F, -0.0226F, -0.0292935F, 0.073753F, -0.074539F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1679)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.954F, 0.651F, -0.982F, 0.388F };
   int lda = 2;
   float B[] = { -0.927F, -0.281F, -0.918F, -0.527F, -0.652F, -0.393F };
   int ldb = 3;
   float B_expected[] = { 0.140187F, 0.0908338F, 0.12617F, -0.0204476F, -0.0252976F, -0.0152484F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1680)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { 0.811F, 0.852F, 0.224F, 0.443F };
   int lda = 2;
   float B[] = { -0.493F, -0.497F, -0.605F, 0.433F, -0.082F, -0.077F };
   int ldb = 3;
   float B_expected[] = { -0.0396008F, -0.0515368F, -0.0622248F, 0.0433F, -0.0082F, -0.0077F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1681)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.777F, 0.812F, 0.254F, 0.97F };
   int lda = 2;
   float B[] = { -0.509F, 0.171F, 0.986F, -0.644F, -0.97F, 0.814F };
   int ldb = 2;
   float B_expected[] = { 0.0395493F, 0.0036584F, -0.0766122F, -0.0374236F, 0.075369F, 0.05432F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1682)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { 0.962F, 0.912F, -0.238F, -0.336F };
   int lda = 2;
   float B[] = { -0.666F, 0.066F, -0.176F, 0.402F, 0.286F, -0.703F };
   int ldb = 2;
   float B_expected[] = { -0.0666F, 0.0224508F, -0.0176F, 0.0443888F, 0.0286F, -0.0771068F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1683)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { 0.859F, -0.547F, 0.076F, 0.542F };
   int lda = 2;
   float B[] = { 0.402F, 0.945F, -0.242F, -0.062F, 0.714F, 0.468F };
   int ldb = 2;
   float B_expected[] = { -0.0171597F, 0.051219F, -0.0173964F, -0.0033604F, 0.035733F, 0.0253656F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1684)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.779F, 0.435F, 0.612F, -0.723F };
   int lda = 2;
   float B[] = { 0.512F, -0.987F, -0.167F, 0.047F, -0.701F, -0.25F };
   int ldb = 2;
   float B_expected[] = { 0.0082655F, -0.0987F, -0.0146555F, 0.0047F, -0.080975F, -0.025F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1685)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.757F, 0.396F, -0.927F, -0.558F, -0.289F, -0.66F, 0.83F, 0.363F, -0.13F };
   int lda = 3;
   float B[] = { 0.041F, 0.333F, -0.682F, 0.193F, 0.581F, 0.963F };
   int ldb = 3;
   float B_expected[] = { 0.0733045F, 0.0353883F, 0.008866F, -0.0808726F, -0.0803489F, -0.012519F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1686)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.75F, 0.674F, -0.576F, 0.376F, -0.46F, -0.813F, 0.419F, 0.792F, 0.226F };
   int lda = 3;
   float B[] = { 0.511F, -0.544F, 0.938F, -0.126F, -0.873F, 0.118F };
   int ldb = 3;
   float B_expected[] = { -0.0395944F, -0.130659F, 0.0938F, -0.078237F, -0.0968934F, 0.0118F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1687)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.045F, -0.809F, 0.654F, 0.611F, -0.038F, -0.105F, -0.946F, 0.474F, -0.097F };
   int lda = 3;
   float B[] = { -0.625F, -0.123F, -0.48F, -0.088F, -0.757F, 0.974F };
   int ldb = 3;
   float B_expected[] = { 0.0028125F, -0.0377201F, 0.0579508F, 3.96e-04F, -0.0025002F, -0.0370048F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1688)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { 0.713F, 0.781F, 0.084F, -0.498F, 0.692F, 0.125F, 0.706F, -0.118F, -0.907F };
   int lda = 3;
   float B[] = { 0.442F, -0.563F, 0.065F, -0.18F, 0.63F, -0.328F };
   int ldb = 3;
   float B_expected[] = { 0.0442F, -0.0783116F, 0.0443486F, -0.018F, 0.071964F, -0.052942F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1689)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.442F, 0.566F, 0.064F, 0.962F, -0.669F, 0.416F, 0.761F, -0.359F, 0.863F };
   int lda = 3;
   float B[] = { 0.261F, -0.659F, -0.536F, 0.694F, -0.305F, -0.675F };
   int ldb = 2;
   float B_expected[] = { -0.0863099F, 0.0445231F, 0.0468079F, -0.0221961F, -0.0263215F, -0.0582525F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1690)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { 0.386F, 0.643F, -0.028F, -0.758F, -0.63F, -0.043F, 0.666F, -0.088F, 0.382F };
   int lda = 3;
   float B[] = { -0.241F, 0.766F, 0.656F, -0.977F, 0.274F, 0.565F };
   int ldb = 2;
   float B_expected[] = { -0.0555764F, 0.188286F, 0.0631888F, -0.102672F, 0.0274F, 0.0565F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1691)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.855F, -0.587F, 0.062F, 0.372F, 0.48F, -0.63F, -0.786F, -0.437F, -0.431F };
   int lda = 3;
   float B[] = { 0.116F, 0.534F, 0.043F, 0.73F, 0.945F, 0.528F };
   int ldb = 2;
   float B_expected[] = { -0.009918F, -0.045657F, -0.0047452F, 0.0036942F, -0.0427193F, -0.065436F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1692)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha = 0.1F;
   float A[] = { -0.068F, 0.119F, -0.244F, -0.05F, 0.685F, 0.752F, -0.059F, -0.935F, -0.571F };
   int lda = 3;
   float B[] = { -0.753F, -0.319F, 0.164F, 0.979F, 0.885F, -0.822F };
   int ldb = 2;
   float B_expected[] = { -0.0753F, -0.0319F, 0.0074393F, 0.0941039F, 0.119206F, -7.956e-04F };
   cblas_strmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strmm(case 1693)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.174, -0.308, 0.997, -0.484 };
   int lda = 2;
   double B[] = { -0.256, -0.178, 0.098, 0.004, 0.97, -0.408 };
   int ldb = 3;
   double B_expected[] = { 0.0137328, 0.0989196, -0.0428148, 5.808e-04, 0.140844, -0.0592416 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1694)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.722, -0.372, 0.466, -0.831 };
   int lda = 2;
   double B[] = { 0.322, -0.183, 0.849, -0.051, -0.343, -0.98 };
   int ldb = 3;
   double B_expected[] = { -0.1022916, 0.0166212, -0.364068, 0.0153, 0.1029, 0.294 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1695)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.656, -0.066, 0.582, 0.141 };
   int lda = 2;
   double B[] = { 0.73, 0.407, 0.721, 0.086, -0.294, 0.941 };
   int ldb = 3;
   double B_expected[] = { 0.143664, 0.0800976, 0.1418928, -0.1310958, -0.058626, -0.1656909 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1696)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.341, 0.386, -0.578, 0.863 };
   int lda = 2;
   double B[] = { -0.306, -0.047, -0.162, -0.784, 0.472, 0.137 };
   int ldb = 3;
   double B_expected[] = { 0.0918, 0.0141, 0.0486, 0.1821396, -0.1497498, -0.0691908 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1697)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.844, -0.832, 0.179, -0.775 };
   int lda = 2;
   double B[] = { -0.415, -0.547, -0.023, 0.42, 0.917, 0.485 };
   int ldb = 2;
   double B_expected[] = { 0.1344519, -0.1271775, -0.0167304, 0.09765, -0.2582289, 0.1127625 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1698)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.239, 0.34, 0.964, -0.575 };
   int lda = 2;
   double B[] = { 0.762, -0.038, -0.8, 0.626, -0.701, 0.639 };
   int ldb = 2;
   double B_expected[] = { -0.2176104, 0.0114, 0.0589608, -0.1878, 0.0255012, -0.1917 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1699)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.785, -0.0, -0.592, -0.661 };
   int lda = 2;
   double B[] = { -0.215, 0.953, 0.527, -0.418, -0.675, 0.283 };
   int ldb = 2;
   double B_expected[] = { 0.0506325, 0.1889799, -0.1241085, -0.0828894, 0.1589625, 0.0561189 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1700)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.423, -0.807, -0.683, -0.225 };
   int lda = 2;
   double B[] = { 0.149, -0.129, 0.149, -0.234, 0.275, 0.658 };
   int ldb = 2;
   double B_expected[] = { -0.0447, 0.0747729, -0.0447, 0.1062729, -0.0825, -0.1308225 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1701)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.276, 0.434, 0.917, 0.682, -0.32, 0.557, -0.302, 0.989, -0.043 };
   int lda = 3;
   double B[] = { -0.943, 0.839, 0.759, 0.752, 0.807, 0.288 };
   int ldb = 3;
   double B_expected[] = { -0.0780804, 0.2033226, 0.1290135, 0.0622656, -0.0204384, -0.3380097 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1702)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.731, -0.953, -0.666, 0.684, 0.38, 0.419, -0.361, 0.378, -0.423 };
   int lda = 3;
   double B[] = { -0.983, 0.479, -0.136, 0.048, 0.745, -0.408 };
   int ldb = 3;
   double B_expected[] = { 0.2949, -0.4247397, -0.2158137, -0.0144, -0.2097768, 0.0383439 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1703)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.953, -0.983, 0.237, 0.128, -0.378, 0.607, 0.41, 0.418, -0.221 };
   int lda = 3;
   double B[] = { -0.561, -0.114, -0.148, 0.488, 0.146, -0.688 };
   int ldb = 3;
   double B_expected[] = { -0.1378083, 0.0056316, -0.0098124, 0.2185368, 0.1028316, -0.0456144 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1704)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.277, -0.587, 0.885, -0.933, -0.582, 0.528, 0.268, -0.804, 0.62 };
   int lda = 3;
   double B[] = { -0.831, -0.319, -0.547, -0.577, 0.295, -0.31 };
   int ldb = 3;
   double B_expected[] = { 0.2039907, -0.0362364, 0.1641, 0.2805945, -0.163272, 0.093 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1705)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.256, 0.554, 0.342, 0.318, -0.824, -0.119, -0.399, -0.653, -0.83 };
   int lda = 3;
   double B[] = { -0.577, 0.861, -0.439, -0.916, 0.452, -0.168 };
   int ldb = 2;
   double B_expected[] = { 0.0443136, -0.0661248, -0.053475, -0.3085746, -0.042519, -0.1182147 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1706)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.837, -0.03, 0.552, -0.43, 0.841, 0.035, 0.7, 0.637, 0.095 };
   int lda = 3;
   double B[] = { -0.82, -0.362, -0.252, -0.062, -0.942, -0.299 };
   int ldb = 2;
   double B_expected[] = { 0.246, 0.1086, -0.03018, -0.028098, 0.5029572, 0.1775682 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1707)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { -0.074, 0.49, 0.802, -0.454, 0.626, 0.123, -0.959, 0.971, 0.75 };
   int lda = 3;
   double B[] = { -0.545, -0.107, 0.096, 0.183, 0.185, -0.218 };
   int ldb = 2;
   double B_expected[] = { -0.070722, 0.0231744, -0.0248553, -0.0263232, -0.041625, 0.04905 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1708)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = -0.3;
   double A[] = { 0.048, 0.148, 0.834, -0.98, -0.009, -0.727, 0.241, 0.276, 0.518 };
   int lda = 3;
   double B[] = { -0.664, -0.136, -0.793, -0.742, 0.126, -0.131 };
   int ldb = 2;
   double B_expected[] = { 0.202884, 0.106521, 0.2653806, 0.1940289, -0.0378, 0.0393 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1709)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.427, 0.495, 0.282, 0.158 };
   int lda = 2;
   double B[] = { 0.899, -0.375, 0.376, -0.831, 0.431, -0.387 };
   int ldb = 3;
   double B_expected[] = { 0.0383873, -0.0160125, 0.0160552, 0.0313707, -0.0117527, 0.0124974 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1710)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.632, -0.174, 0.608, -0.669 };
   int lda = 2;
   double B[] = { -0.335, 0.535, -0.978, 0.31, 0.023, -0.853 };
   int ldb = 3;
   double B_expected[] = { -0.0335, 0.0535, -0.0978, 0.036829, -0.007009, -0.0682828 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1711)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.779, -0.73, 0.343, -0.665 };
   int lda = 2;
   double B[] = { -0.976, -0.2, 0.661, -0.975, -0.965, -0.861 };
   int ldb = 3;
   double B_expected[] = { 0.0425879, -0.0175195, -0.0810242, 0.0648375, 0.0641725, 0.0572565 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1712)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.127, -0.634, -0.384, -0.815 };
   int lda = 2;
   double B[] = { -0.348, 0.748, 0.893, 0.91, 0.153, -0.408 };
   int ldb = 3;
   double B_expected[] = { -0.069744, 0.0689248, 0.1049672, 0.091, 0.0153, -0.0408 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1713)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.603, -0.617, 0.402, -0.918 };
   int lda = 2;
   double B[] = { 0.051, -0.096, 0.476, 0.377, 0.931, 0.291 };
   int ldb = 2;
   double B_expected[] = { -0.0030753, 0.010863, -0.0287028, -0.0154734, -0.0561393, 0.0107124 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1714)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.67, -0.475, 0.032, -0.036 };
   int lda = 2;
   double B[] = { -0.19, 0.829, 0.942, 0.885, 0.087, 0.321 };
   int ldb = 2;
   double B_expected[] = { -0.019, 0.082292, 0.0942, 0.0915144, 0.0087, 0.0323784 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1715)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.64, 0.595, 0.642, -0.921 };
   int lda = 2;
   double B[] = { -0.278, -0.83, 0.922, -0.701, -0.598, -0.232 };
   int ldb = 2;
   double B_expected[] = { -0.031593, 0.076443, -0.1007175, 0.0645621, 0.024468, 0.0213672 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1716)");
     }
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.842, 0.625, 0.967, 0.341 };
   int lda = 2;
   double B[] = { -0.679, -0.846, -0.921, 0.672, 0.292, 0.752 };
   int ldb = 2;
   double B_expected[] = { -0.120775, -0.0846, -0.0501, 0.0672, 0.0762, 0.0752 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1717)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.612, 0.593, 0.113, -0.658, 0.703, -0.023, -0.384, 0.439, 0.958 };
   int lda = 3;
   double B[] = { -0.858, -0.559, 0.499, -0.114, 0.57, 0.847 };
   int ldb = 3;
   double B_expected[] = { 0.0249996, -0.0404454, 0.0478042, 0.0503489, 0.0381229, 0.0811426 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1718)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.844, 0.205, -0.692, -0.401, -0.823, 0.342, -0.384, 0.344, 0.18 };
   int lda = 3;
   double B[] = { 0.823, -0.181, 0.141, 0.932, 0.097, -0.636 };
   int ldb = 3;
   double B_expected[] = { 0.0688323, -0.0132778, 0.0141, 0.1391997, -0.0120512, -0.0636 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1719)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.065, 0.678, 0.044, -0.472, 0.932, -0.388, 0.432, -0.167, -0.277 };
   int lda = 3;
   double B[] = { 0.675, -0.468, -0.564, 0.71, -0.624, 0.023 };
   int ldb = 3;
   double B_expected[] = { 0.0043875, -0.0754776, 0.0525984, 0.004615, -0.0916688, 0.0404557 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1720)");
     }
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.649, -0.171, -0.462, 0.593, 0.131, -0.317, -0.254, -0.948, 0.002 };
   int lda = 3;
   double B[] = { -0.519, -0.501, -0.024, -0.767, -0.591, -0.738 };
   int ldb = 3;
   double B_expected[] = { -0.0519, -0.0808767, 0.0582774, -0.0767, -0.1045831, 0.0017086 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1721)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.023, -0.872, -0.313, -0.698, 0.06, -0.838, -0.455, -0.715, -0.257 };
   int lda = 3;
   double B[] = { -0.17, -0.184, -0.243, 0.907, -0.423, 0.665 };
   int ldb = 2;
   double B_expected[] = { 0.0365989, -0.0931429, 0.0287865, -0.0421055, 0.0108711, -0.0170905 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1722)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.792, 0.338, -0.155, 0.009, 0.485, -0.633, -0.08, -0.579, 0.223 };
   int lda = 3;
   double B[] = { -0.19, 0.201, 0.685, 0.663, 0.302, -0.506 };
   int ldb = 2;
   double B_expected[] = { -0.0207995, 0.0247447, 0.0510142, 0.0955974, 0.0302, -0.0506 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1723)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { -0.076, 0.103, -0.021, -0.866, 0.777, 0.723, 0.378, 0.98, -0.32 };
   int lda = 3;
   double B[] = { 0.739, -0.996, 0.182, 0.626, 0.291, -0.267 };
   int ldb = 2;
   double B_expected[] = { -0.0056164, 0.0075696, 0.0217531, 0.0383814, 0.0022947, 0.0558954 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1724)");
     }
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha = 0.1;
   double A[] = { 0.469, 0.822, -0.619, 0.953, -0.706, 0.318, 0.559, -0.68, -0.208 };
   int lda = 3;
   double B[] = { 0.362, 0.719, -0.661, -0.504, 0.595, -0.771 };
   int ldb = 2;
   double B_expected[] = { 0.0362, 0.0719, -0.0363436, 0.0087018, 0.0160724, -0.1376333 };
   cblas_dtrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrmm(case 1725)");
     }
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.023F, 0.762F, -0.687F, -0.039F, -0.459F, 0.047F, 0.189F, 0.33F };
   int lda = 2;
   float B[] = { 0.827F, -0.561F, 0.641F, -0.229F, -0.884F, -0.533F, -0.624F, -0.138F, 0.073F, 0.924F, -0.501F, -0.164F };
   int ldb = 3;
   float B_expected[] = { -0.831767F, -0.762219F, -0.14564F, 0.143926F, -0.764269F, 0.529142F, 0.072396F, 0.232002F, 0.291123F, -0.198726F, 0.040569F, 0.196326F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1726) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1726) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.24F, 0.581F, 0.06F, 0.064F, 0.981F, 0.792F, 0.242F, -0.529F };
   int lda = 2;
   float B[] = { -0.649F, -0.774F, -0.43F, -0.447F, -0.266F, 0.285F, 0.787F, 0.274F, 0.449F, -0.912F, 0.435F, 0.601F };
   int ldb = 3;
   float B_expected[] = { 0.619316F, 0.707192F, 0.344692F, 0.472984F, 0.278364F, -0.3489F, -0.787F, -0.274F, -0.449F, 0.912F, -0.435F, -0.601F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1727) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1727) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.68F, -0.728F, -0.59F, -0.434F, -0.936F, 0.915F, 0.236F, -0.118F };
   int lda = 2;
   float B[] = { 0.461F, 0.48F, 0.224F, 0.215F, -0.419F, -0.525F, 0.113F, -0.582F, 0.468F, 0.269F, 0.943F, -0.587F };
   int ldb = 3;
   float B_expected[] = { -0.66292F, 0.009208F, -0.30884F, 0.016872F, 0.66712F, 0.051968F, 0.912704F, 0.178151F, 0.264199F, -0.01198F, -1.02584F, 0.141791F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1728) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1728) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.699F, -0.709F, -0.775F, 0.779F, 0.5F, 0.774F, -0.399F, -0.843F };
   int lda = 2;
   float B[] = { 0.538F, 0.556F, -0.186F, -0.678F, -0.413F, -0.612F, -0.216F, -0.519F, -0.344F, -0.578F, -0.938F, -0.848F };
   int ldb = 3;
   float B_expected[] = { -0.538F, -0.556F, 0.186F, 0.678F, 0.413F, 0.612F, 0.377344F, -0.175412F, -0.087772F, 1.06096F, 0.670812F, 1.47366F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1729) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1729) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.527F, 0.318F, -0.224F, 0.547F, -0.765F, -0.469F, 0.233F, 0.023F };
   int lda = 2;
   float B[] = { 0.54F, -0.418F, -0.892F, -0.118F, -0.296F, 0.019F, 0.786F, -0.145F, 0.136F, 0.472F, 0.731F, 0.333F };
   int ldb = 2;
   float B_expected[] = { -1.04454F, -0.460052F, 0.205122F, 0.04801F, 0.831329F, 0.341824F, -0.186473F, 0.015707F, 0.481462F, 0.305592F, -0.162664F, -0.094402F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1730) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1730) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.109F, -0.852F, 0.395F, 0.871F, 0.378F, -0.493F, 0.51F, 0.973F };
   int lda = 2;
   float B[] = { -0.867F, -0.758F, 0.687F, -0.596F, -0.912F, -0.561F, -0.389F, 0.21F, -0.561F, 0.132F, 0.689F, 0.653F };
   int ldb = 2;
   float B_expected[] = { 0.901142F, 1.32198F, -0.687F, 0.596F, 0.955512F, 0.289843F, 0.389F, -0.21F, -0.021371F, -0.039157F, -0.689F, -0.653F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1731) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1731) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.686F, 0.349F, 0.299F, -0.462F, 0.009F, -0.693F, -0.478F, -0.617F };
   int lda = 2;
   float B[] = { -0.409F, 0.986F, -0.854F, 0.346F, 0.444F, -0.659F, 0.027F, 0.007F, 0.842F, -0.473F, 0.825F, 0.866F };
   int ldb = 2;
   float B_expected[] = { 0.624688F, -0.533655F, -0.954935F, -0.845302F, -0.534575F, 0.297118F, 0.180289F, 0.422174F, -0.742689F, 0.03062F, -0.173204F, 1.4534F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1732) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1732) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.286F, 0.661F, 0.372F, 0.28F, 0.482F, 0.267F, -0.436F, 0.844F };
   int lda = 2;
   float B[] = { 0.0F, -0.513F, 0.91F, 0.109F, 0.587F, -0.183F, 0.112F, 0.362F, -0.256F, -0.518F, -0.933F, 0.066F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.513F, -1.05364F, 0.081836F, -0.587F, 0.183F, -0.381604F, -0.458284F, 0.256F, 0.518F, 0.883192F, 0.198376F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1733) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1733) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.678F, 0.717F, 0.228F, 0.001F, -0.16F, -0.387F, -0.281F, -0.002F, 0.623F, 0.162F, -0.594F, 0.632F, 0.566F, 0.352F, -0.411F, 0.574F, 0.314F, -0.139F };
   int lda = 3;
   float B[] = { -0.823F, -0.042F, 0.171F, -0.928F, 0.66F, 0.965F, 0.472F, 0.006F, -0.083F, 0.937F, -0.814F, 0.9F };
   int ldb = 3;
   float B_expected[] = { 0.52788F, 0.618567F, -0.069267F, 0.560841F, -0.941723F, -1.19579F, -0.315714F, -0.342492F, 0.095893F, -0.572145F, 0.746576F, 0.396912F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1734) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1734) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.346F, 0.915F, -0.227F, -0.066F, -0.166F, -0.921F, -0.373F, 0.312F, -0.824F, 0.699F, -0.114F, -0.152F, 0.862F, -0.077F, 0.221F, -0.757F, -0.413F, -0.494F };
   int lda = 3;
   float B[] = { -0.02F, -0.247F, -0.62F, 0.651F, -0.07F, -0.491F, 0.042F, 0.936F, 0.272F, -0.582F, 0.012F, -0.534F };
   int ldb = 3;
   float B_expected[] = { 0.02F, 0.247F, 0.631762F, -0.708389F, 0.124535F, 0.411552F, -0.042F, -0.936F, -0.324242F, 0.797244F, -0.747612F, 0.703054F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1735) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1735) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.493F, -0.882F, -0.82F, 0.627F, 0.301F, -0.903F, -0.092F, 0.787F, -0.426F, -0.854F, -0.993F, 0.118F, 0.615F, 0.362F, -0.238F, -0.076F, 0.817F, -0.286F };
   int lda = 3;
   float B[] = { 0.395F, 0.074F, -0.191F, -0.548F, 0.858F, 0.323F, -0.734F, 0.612F, 0.895F, 0.849F, 0.811F, 0.402F };
   int ldb = 3;
   float B_expected[] = { -0.730125F, -0.024468F, 0.566282F, -0.25448F, -0.793364F, -0.018503F, -0.504384F, -1.51274F, -0.18131F, 1.28332F, -0.777559F, -0.096488F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1736) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1736) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.033F, -0.383F, 0.116F, 0.797F, -0.99F, 0.765F, 0.915F, 0.002F, 0.228F, 0.077F, 0.597F, -0.454F, -0.629F, 0.424F, -0.89F, 0.339F, -0.484F, 0.169F };
   int lda = 3;
   float B[] = { -0.377F, -0.451F, -0.464F, -0.673F, 0.231F, -0.712F, -0.457F, -0.588F, 0.373F, -0.754F, -0.468F, 0.433F };
   int ldb = 3;
   float B_expected[] = { 0.643625F, 0.521931F, 0.428222F, -0.038989F, -0.231F, 0.712F, 0.003417F, 1.74795F, -0.642733F, 1.29802F, 0.468F, -0.433F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1737) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1737) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.946F, -0.007F, 0.677F, -0.923F, 0.651F, -0.685F, 0.591F, 0.135F, 0.171F, 0.979F, -0.029F, -0.008F, -0.049F, 0.174F, 0.578F, 0.388F, 0.187F, -0.479F };
   int lda = 3;
   float B[] = { -0.607F, -0.907F, -0.156F, -0.141F, -0.254F, 0.364F, 0.209F, 0.955F, 0.93F, 0.962F, 0.494F, 0.079F };
   int ldb = 2;
   float B_expected[] = { 0.580571F, 0.853773F, 0.148563F, 0.132294F, 0.636082F, 0.804404F, 0.972367F, -0.263525F, -0.534225F, 0.214911F, 0.087341F, -0.390994F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1738) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1738) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.203F, -0.791F, -0.415F, -0.56F, 0.782F, -0.691F, -0.441F, 0.545F, -0.09F, 0.595F, -0.438F, 0.952F, 0.88F, 0.944F, -0.55F, -0.762F, -0.035F, -0.949F };
   int lda = 3;
   float B[] = { -0.035F, 0.448F, 0.487F, -0.108F, -0.482F, -0.708F, -0.317F, 0.816F, -0.547F, 0.22F, -0.654F, 0.57F };
   int ldb = 2;
   float B_expected[] = { 0.035F, -0.448F, -0.487F, 0.108F, 0.710725F, 0.924643F, 0.472907F, -1.12904F, 1.27511F, -1.33788F, -0.672654F, -0.727442F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1739) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1739) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { -0.09F, 0.742F, 0.081F, 0.459F, -0.54F, 0.04F, 0.574F, -0.858F, 0.704F, 0.686F, -0.9F, -0.519F, 0.538F, -0.934F, 0.467F, 0.376F, 0.149F, 0.322F };
   int lda = 3;
   float B[] = { 0.307F, 0.294F, -0.428F, -0.7F, 0.496F, 0.167F, -0.611F, 0.904F, -0.846F, -0.411F, 0.29F, 0.004F };
   int ldb = 2;
   float B_expected[] = { -0.191025F, -0.630625F, 0.063267F, 0.452361F, -0.782713F, -1.2668F, 1.30921F, -0.06316F, -0.006288F, 0.333651F, -0.041922F, -0.093976F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1740) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1740) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-1.0F, 0.0F};
   float A[] = { 0.434F, 0.691F, 0.983F, -0.481F, -0.156F, -0.117F, -0.231F, 0.526F, 0.935F, 0.417F, -0.142F, -0.541F, 0.529F, 0.014F, 0.266F, 0.086F, 0.666F, 0.033F };
   int lda = 3;
   float B[] = { 0.972F, -0.219F, -0.735F, -0.967F, 0.084F, -0.355F, -0.152F, -0.156F, 0.267F, 0.928F, 0.708F, -0.267F };
   int ldb = 2;
   float B_expected[] = { -0.950741F, 0.784376F, 1.10114F, 1.08842F, -0.548134F, 0.631223F, 0.396983F, 0.501114F, -0.267F, -0.928F, -0.708F, 0.267F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1741) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1741) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.25F, -0.779F, -0.138F, -0.017F, -0.319F, -0.555F, 0.674F, -0.256F };
   int lda = 2;
   float B[] = { -0.651F, -0.525F, 0.409F, -0.932F, 0.359F, 0.321F, 0.419F, 0.027F, 0.67F, 0.328F, 0.446F, -0.615F };
   int ldb = 3;
   float B_expected[] = { 0.0100296F, -0.216136F, 0.257045F, -0.0571445F, -0.0121016F, 0.124004F, -0.110514F, 0.0386878F, -0.1561F, -0.0050383F, 0.028185F, 0.183634F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1742) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1742) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.012F, 0.978F, 0.617F, -0.361F, -0.349F, 0.712F, 0.008F, 0.305F };
   int lda = 2;
   float B[] = { -0.771F, -0.335F, -0.565F, 0.866F, -0.516F, -0.869F, -0.097F, -0.711F, 0.308F, 0.207F, -0.459F, 0.766F };
   int ldb = 3;
   float B_expected[] = { 0.2648F, 0.0234F, 0.0829F, -0.3163F, 0.2417F, 0.2091F, 0.272029F, 0.122445F, -0.176135F, -0.256384F, 0.285714F, -0.233939F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1743) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1743) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.063F, -0.605F, 0.473F, 0.763F, 0.548F, -0.167F, -0.825F, 0.011F };
   int lda = 2;
   float B[] = { -0.262F, 0.135F, -0.333F, -0.671F, 0.91F, 0.874F, 0.305F, -0.255F, 0.882F, 0.883F, 0.088F, -0.473F };
   int ldb = 3;
   float B_expected[] = { -0.0627538F, 0.0344746F, -0.131779F, -0.149516F, -0.0442507F, 0.307921F, 0.053273F, -0.089001F, 0.293086F, 0.141896F, -0.0189002F, -0.124098F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1744) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1744) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.493F, -0.852F, -0.567F, 0.21F, 0.168F, 0.666F, -0.328F, 0.803F };
   int lda = 2;
   float B[] = { 0.24F, -0.578F, 0.293F, -0.233F, -0.348F, -0.853F, -0.145F, 0.192F, -0.785F, -0.72F, -0.508F, 0.023F };
   int ldb = 3;
   float B_expected[] = { 0.037901F, 0.201471F, -0.104515F, 0.327095F, 0.253345F, 0.311373F, 0.0243F, -0.0721F, 0.3075F, 0.1375F, 0.1501F, -0.0577F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1745) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1745) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.089F, -0.135F, 0.987F, 0.936F, 0.353F, 0.638F, 0.845F, 0.343F };
   int lda = 2;
   float B[] = { 0.744F, 0.445F, 0.835F, 0.273F, 0.702F, 0.03F, -0.618F, 0.141F, -0.303F, -0.399F, 0.63F, -0.037F };
   int ldb = 2;
   float B_expected[] = { 0.0158468F, 0.0413994F, -0.292082F, -0.285588F, 0.0272724F, 0.0233892F, 0.0660084F, -0.143882F, 0.0004278F, -0.0256146F, -0.19286F, 0.114065F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1746) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1746) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.187F, -0.741F, 0.287F, -0.599F, -0.293F, -0.297F, 0.778F, -0.056F };
   int lda = 2;
   float B[] = { -0.335F, -0.713F, 0.081F, -0.589F, -0.256F, -0.809F, -0.473F, 0.418F, 0.646F, -0.447F, -0.147F, 0.314F };
   int ldb = 2;
   float B_expected[] = { 0.1718F, 0.1804F, 0.0378414F, 0.0809182F, 0.1577F, 0.2171F, 0.118373F, -0.283147F, -0.1491F, 0.1987F, 0.1154F, -0.122836F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1747) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1747) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.259F, -0.645F, -0.09F, 0.709F, 0.729F, -0.023F, -0.792F, 0.03F };
   int lda = 2;
   float B[] = { 0.904F, -0.402F, 0.753F, 0.104F, 0.38F, 0.944F, -0.715F, -0.378F, -0.16F, 0.254F, -0.68F, 0.183F };
   int ldb = 2;
   float B_expected[] = { 0.185924F, -0.0771597F, 0.185827F, -0.0420162F, -0.156592F, 0.373034F, -0.201079F, -0.0256158F, 0.0051007F, 0.152025F, -0.143387F, 0.102908F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1748) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1748) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.938F, 0.25F, -0.509F, 0.377F, -0.063F, 0.166F, 0.227F, -0.24F };
   int lda = 2;
   float B[] = { 0.756F, -0.08F, -0.657F, -0.837F, -0.714F, 0.781F, 0.239F, -0.953F, 0.26F, 0.696F, -0.183F, 0.668F };
   int ldb = 2;
   float B_expected[] = { -0.431623F, 0.111093F, 0.2808F, 0.1854F, 0.007293F, -0.454491F, 0.0236F, 0.3098F, -0.059093F, -0.075968F, -0.0119F, -0.2187F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1749) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1749) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.055F, -0.682F, 0.361F, 0.521F, -0.192F, -0.664F, -0.167F, 0.731F, -0.668F, 0.983F, 0.608F, 0.533F, -0.513F, -0.781F, 0.878F, 0.875F, 0.804F, -0.179F };
   int lda = 3;
   float B[] = { -0.038F, -0.787F, -0.209F, -0.686F, -0.073F, -0.662F, 0.938F, -0.301F, -0.871F, 0.699F, 0.561F, 0.823F };
   int ldb = 3;
   float B_expected[] = { 0.224558F, -0.0087435F, -0.317863F, 0.168822F, 0.105075F, 0.138035F, 0.256887F, 0.377119F, 0.113231F, 0.136832F, -0.235636F, -0.108546F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1750) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1750) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.397F, -0.154F, -0.944F, -0.137F, 0.65F, -0.49F, -0.883F, 0.273F, -0.137F, 0.655F, 0.531F, 0.676F, 0.052F, 0.03F, -0.602F, 0.002F, 0.005F, 0.984F };
   int lda = 3;
   float B[] = { -0.446F, 0.091F, 0.793F, -0.221F, 0.386F, 0.354F, -0.063F, 0.105F, -0.128F, 0.189F, -0.079F, 0.749F };
   int ldb = 3;
   float B_expected[] = { 0.216958F, -0.149634F, -0.25039F, 0.0074932F, -0.1512F, -0.0676F, -0.166784F, -0.100965F, 0.14955F, -0.227622F, -0.0512F, -0.2326F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1751) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1751) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.976F, -0.488F, -0.762F, -0.057F, 0.812F, 0.006F, 0.06F, -0.271F, 0.832F, -0.232F, 0.188F, -0.466F, -0.051F, -0.745F, 0.909F, -0.091F, -0.559F, 0.595F };
   int lda = 3;
   float B[] = { 0.644F, -0.584F, 0.456F, 0.443F, -0.909F, 0.43F, 0.771F, -0.075F, -0.408F, 0.303F, 0.03F, 0.529F };
   int ldb = 3;
   float B_expected[] = { 0.24849F, -0.168067F, -0.114085F, 0.0202884F, 0.0152508F, 0.284926F, 0.267034F, 0.0120048F, 0.0596364F, -0.0643158F, 0.284594F, 0.0837608F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1752) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1752) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.924F, -0.247F, -0.131F, 0.932F, -0.415F, 0.454F, -0.539F, 0.693F, -0.725F, -0.601F, 0.565F, 0.002F, -0.118F, 0.626F, -0.968F, 0.874F, 0.156F, -0.227F };
   int lda = 3;
   float B[] = { 0.793F, -0.15F, -0.967F, 0.821F, 0.37F, -0.572F, -0.156F, 0.106F, -0.877F, -0.297F, 0.448F, -0.576F };
   int ldb = 3;
   float B_expected[] = { -0.2229F, 0.1243F, 0.242003F, -0.564467F, -0.0068716F, 0.568213F, 0.0362F, -0.0474F, 0.306136F, 0.0520352F, -0.336053F, 0.500406F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1753) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1753) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.671F, 0.477F, 0.227F, 0.685F, -0.648F, 0.277F, -0.295F, -0.632F, 0.509F, -0.798F, 0.875F, 0.89F, -0.34F, -0.786F, -0.453F, 0.511F, -0.189F, 0.385F };
   int lda = 3;
   float B[] = { -0.895F, -0.148F, 0.934F, 0.229F, 0.958F, -0.55F, 0.49F, 0.586F, -0.871F, 0.618F, -0.0F, -0.543F };
   int ldb = 2;
   float B_expected[] = { 0.162976F, 0.110656F, -0.12507F, -0.0587256F, 0.138701F, 0.543589F, -0.313677F, 0.0534812F, 0.067207F, 0.12831F, -0.0729792F, -0.0098826F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1754) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1754) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.438F, -0.618F, 0.524F, 0.525F, -0.268F, -0.502F, -0.685F, 0.28F, 0.508F, 0.664F, -0.492F, 0.772F, -0.997F, 0.693F, 0.63F, -0.328F, -0.521F, -0.869F };
   int lda = 3;
   float B[] = { 0.527F, 0.999F, -0.078F, 0.599F, 0.004F, -0.615F, -0.281F, -0.328F, 0.456F, -0.666F, 0.309F, -0.69F };
   int ldb = 2;
   float B_expected[] = { -0.45115F, -0.650085F, -0.277633F, -0.456478F, 0.0965652F, 0.362528F, 0.1802F, 0.227951F, -0.0702F, 0.2454F, -0.0237F, 0.2379F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1755) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1755) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.454F, 0.517F, -0.794F, -0.181F, 0.292F, 0.954F, -0.93F, -0.128F, 0.123F, -0.997F, 0.325F, -0.317F, -0.988F, 0.732F, 0.637F, 0.457F, -0.665F, 0.529F };
   int lda = 3;
   float B[] = { -0.055F, 0.803F, -0.981F, -0.627F, 0.147F, -0.656F, -0.824F, -0.366F, -0.445F, -0.151F, 0.686F, -0.368F };
   int ldb = 2;
   float B_expected[] = { 0.156354F, 0.078881F, -0.208608F, 0.143709F, 0.219569F, 0.211768F, -0.204943F, -0.415655F, 0.191227F, 0.0071854F, 0.136999F, 0.0773624F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1756) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1756) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.623F, -0.129F, -0.419F, -0.006F, 0.21F, -0.165F, 0.218F, 0.915F, 0.736F, 0.07F, 0.502F, -0.809F, 0.242F, -0.015F, 0.67F, -0.956F, 0.153F, 0.365F };
   int lda = 3;
   float B[] = { -0.927F, 0.383F, -0.471F, 0.443F, -0.731F, -0.949F, -0.142F, -0.65F, 0.159F, -0.624F, -0.822F, 0.107F };
   int ldb = 2;
   float B_expected[] = { 0.2398F, -0.2076F, 0.097F, -0.18F, 0.212478F, 0.297146F, 0.065877F, 0.255638F, 0.359717F, -0.0280276F, 0.426852F, -0.164392F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1757) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1757) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.628F, -0.771F, 0.827F, -0.979F, 0.395F, -0.166F, 0.88F, 0.958F };
   int lda = 2;
   float B[] = { 0.297F, 0.49F, 0.425F, -0.386F, 0.672F, 0.992F, -0.077F, 0.761F, 0.393F, -0.605F, -0.273F, 0.725F };
   int ldb = 3;
   float B_expected[] = { 0.177165F, -0.0328107F, -0.0662201F, -0.167954F, 0.366541F, -0.0872256F, -0.2721F, -0.389113F, -0.0674816F, 0.293174F, -0.249446F, -0.709453F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1758) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1758) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.876F, 0.752F, -0.148F, 0.972F, -0.508F, -0.752F, -0.861F, 0.074F };
   int lda = 2;
   float B[] = { 0.878F, -0.987F, -0.896F, 0.519F, -0.355F, -0.117F, 0.329F, 0.068F, -0.644F, 0.344F, -0.187F, -0.343F };
   int ldb = 3;
   float B_expected[] = { -0.1647F, 0.3839F, 0.2169F, -0.2453F, 0.1182F, -0.0004F, 0.292026F, 0.115771F, -0.111733F, -0.342122F, 0.0725176F, -0.0306312F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1759) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1759) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.072F, -0.966F, 0.648F, 0.43F, -0.623F, -0.221F, -0.622F, 0.977F };
   int lda = 2;
   float B[] = { 0.0F, 0.028F, 0.857F, -0.171F, -0.933F, 0.159F, 0.315F, -0.297F, -0.864F, 0.519F, -0.601F, -0.119F };
   int ldb = 3;
   float B_expected[] = { 0.0216306F, -0.0927642F, -0.225266F, -0.0253344F, 0.0408658F, 0.302549F, 0.158132F, -0.0117036F, -0.365472F, -0.0519459F, -0.143387F, -0.172603F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1760) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1760) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.903F, -0.972F, -0.812F, 0.605F, 0.085F, -0.025F, -0.443F, 0.518F };
   int lda = 2;
   float B[] = { -0.725F, -0.451F, 0.779F, 0.969F, 0.25F, 0.021F, 0.029F, -0.382F, 0.022F, 0.957F, 0.704F, 0.832F };
   int ldb = 3;
   float B_expected[] = { 0.26217F, 0.073525F, -0.332173F, -0.239574F, -0.097644F, -0.003892F, 0.0295F, 0.1175F, -0.1023F, -0.2849F, -0.2944F, -0.1792F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1761) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1761) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.322F, -0.981F, 0.193F, -0.604F, 0.87F, -0.384F, 0.463F, -0.502F };
   int lda = 2;
   float B[] = { -0.447F, 0.21F, 0.928F, -0.496F, 0.889F, -0.354F, -0.258F, -0.149F, 0.98F, -0.958F, 0.106F, -0.579F };
   int ldb = 2;
   float B_expected[] = { 0.0692355F, 0.14563F, -0.0874638F, -0.0532654F, -0.116915F, -0.289728F, -0.242902F, 0.136003F, -0.314257F, -0.318533F, -0.400862F, 0.357622F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1762) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1762) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.924F, -0.553F, 0.985F, -0.793F, 0.406F, 0.741F, -0.956F, 0.945F };
   int lda = 2;
   float B[] = { 0.736F, -0.81F, 0.028F, 0.474F, 0.14F, -0.03F, -0.756F, 0.923F, -0.515F, 0.532F, -0.321F, 0.326F };
   int ldb = 2;
   float B_expected[] = { -0.1398F, 0.3166F, 0.122042F, 0.0927314F, -0.039F, 0.023F, 0.135709F, -0.314263F, 0.1013F, -0.2111F, -0.0515973F, -0.29067F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1763) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1763) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.04F, -0.41F, -0.643F, 0.988F, 0.86F, -0.281F, -0.017F, 0.389F };
   int lda = 2;
   float B[] = { 0.204F, 0.524F, -0.558F, -0.736F, 0.26F, -0.202F, -0.757F, 0.346F, 0.917F, 0.541F, -0.108F, -0.965F };
   int ldb = 2;
   float B_expected[] = { 0.059601F, -0.396251F, 0.060088F, -0.096554F, -0.338942F, -0.0950055F, -0.073098F, -0.071831F, 0.208251F, -0.444353F, 0.106223F, -0.05488F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1764) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1764) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.375F, 0.153F, -0.343F, -0.742F, 0.563F, 0.473F, 0.451F, -0.433F };
   int lda = 2;
   float B[] = { -0.804F, -0.016F, -0.715F, -0.902F, -0.89F, 0.155F, -0.408F, 0.419F, 0.078F, -0.691F, -0.717F, -0.637F };
   int ldb = 2;
   float B_expected[] = { -0.0094443F, 0.0821961F, 0.3047F, 0.1991F, 0.347432F, -0.0186595F, 0.0805F, -0.1665F, -0.138523F, 0.381015F, 0.2788F, 0.1194F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1765) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1765) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.867F, -0.597F, -0.577F, 0.735F, 0.827F, -0.104F, -0.861F, -0.802F, -0.288F, 0.293F, 0.593F, 0.228F, -0.469F, 0.942F, 0.193F, 0.591F, 0.241F, 0.382F };
   int lda = 3;
   float B[] = { -0.812F, -0.874F, -0.18F, -0.81F, 0.023F, 0.352F, 0.559F, 0.237F, -0.835F, 0.037F, -0.762F, 0.782F };
   int ldb = 3;
   float B_expected[] = { -0.331628F, -0.278177F, -0.0214727F, -0.156013F, -0.0496067F, -0.0088131F, 0.119788F, -0.469291F, -0.0804714F, -0.263663F, -0.0824792F, -0.132356F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1766) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1766) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.258F, -0.812F, -0.858F, -0.107F, -0.151F, 0.785F, 0.717F, 0.992F, -0.649F, -0.242F, -0.454F, 0.916F, 0.86F, 0.834F, -0.244F, 0.391F, 0.818F, -0.714F };
   int lda = 3;
   float B[] = { 0.163F, 0.441F, 0.54F, 0.679F, 0.071F, -0.76F, 0.345F, -0.956F, 0.654F, -0.217F, -0.892F, 0.106F };
   int ldb = 3;
   float B_expected[] = { 0.296566F, -0.0905963F, -0.0393822F, -0.306541F, 0.0547F, 0.2351F, -0.0059345F, 0.0071855F, -0.402014F, -0.049978F, 0.257F, -0.121F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1767) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1767) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.525F, 0.182F, 0.851F, -0.348F, -0.046F, 0.839F, -0.045F, -0.149F, -0.992F, 0.588F, -0.01F, -0.409F, 0.527F, 0.263F, -0.509F, -0.026F, 0.284F, 0.507F };
   int lda = 3;
   float B[] = { 0.909F, 0.216F, 0.38F, 0.198F, -0.412F, -0.102F, -0.456F, 0.079F, 0.504F, -0.782F, -0.88F, 0.079F };
   int ldb = 3;
   float B_expected[] = { -0.149757F, 0.0672651F, 0.129501F, 0.054878F, -0.0469462F, 0.0277224F, 0.0550599F, -0.0598423F, 0.244521F, -0.217471F, 0.0955519F, -0.37895F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1768) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1768) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.893F, -0.758F, 0.145F, 0.623F, -0.018F, -0.733F, -0.144F, -0.192F, 0.53F, 0.773F, -0.771F, 0.36F, 0.932F, -0.771F, 0.997F, -0.671F, 0.574F, -0.771F };
   int lda = 3;
   float B[] = { 0.592F, 0.985F, -0.62F, -0.095F, -0.344F, -0.607F, 0.759F, 0.085F, -0.609F, 0.068F, -0.084F, -0.575F };
   int ldb = 3;
   float B_expected[] = { -0.2761F, -0.2363F, 0.280628F, -0.052484F, 0.306154F, -0.187624F, -0.2362F, 0.0504F, 0.200236F, -0.133908F, 0.0536278F, 0.0659354F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1769) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1769) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.503F, -0.057F, -0.581F, -0.77F, -0.907F, -0.843F, 0.56F, -0.554F, 0.054F, 0.988F, 0.868F, -0.627F, 0.645F, -0.246F, -0.958F, 0.66F, 0.956F, 0.99F };
   int lda = 3;
   float B[] = { 0.282F, -0.442F, 0.564F, -0.691F, -0.743F, 0.113F, -0.395F, 0.312F, -0.167F, -0.568F, 0.508F, 0.912F };
   int ldb = 2;
   float B_expected[] = { 0.180092F, 0.260648F, -0.045069F, -0.102868F, -0.0964434F, -0.432702F, -0.0404678F, 0.280779F, 0.254359F, 0.0411062F, -0.453454F, 0.0281672F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1770) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1770) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { -0.851F, 0.296F, -0.683F, -0.53F, 0.38F, -0.837F, 0.977F, 0.189F, -0.624F, -0.664F, 0.73F, -0.882F, 0.105F, -0.868F, 0.362F, -0.006F, -0.435F, 0.757F };
   int lda = 3;
   float B[] = { -0.259F, -0.091F, 0.606F, -0.983F, -0.238F, 0.057F, 0.358F, 0.18F, -0.71F, 0.058F, 0.511F, 0.717F };
   int ldb = 2;
   float B_expected[] = { 0.241746F, 0.119591F, -0.0907286F, 0.148899F, 0.141237F, -0.0716576F, -0.205866F, -0.078918F, 0.2072F, -0.0884F, -0.225F, -0.164F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1771) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1771) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.956F, 0.972F, 0.771F, 0.187F, 0.948F, 0.303F, -0.854F, 0.123F, 0.704F, 0.152F, 0.347F, 0.595F, -0.865F, 0.75F, -0.041F, -0.572F, 0.749F, 0.216F };
   int lda = 3;
   float B[] = { -0.821F, -0.098F, 0.347F, -0.639F, 0.314F, -0.009F, -0.725F, 0.45F, 0.536F, 0.801F, 0.431F, 0.936F };
   int ldb = 2;
   float B_expected[] = { 0.193607F, -0.29931F, 0.18163F, 0.255513F, 0.127098F, -0.0503344F, 0.101243F, 0.0097718F, -0.0060322F, -0.148016F, -0.251411F, -0.0777231F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1772) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1772) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   float alpha[2] = {-0.3F, 0.1F};
   float A[] = { 0.78F, -0.205F, 0.073F, -0.859F, 0.568F, -0.599F, -0.947F, -0.514F, 0.835F, 0.176F, 0.27F, -0.617F, 0.171F, -0.074F, 0.939F, -0.469F, -0.471F, 0.25F };
   int lda = 3;
   float B[] = { -0.279F, 0.16F, -0.495F, 0.658F, 0.071F, 0.557F, -0.116F, 0.095F, -0.104F, 0.503F, -0.775F, -0.03F };
   int ldb = 2;
   float B_expected[] = { 0.0677F, -0.0759F, 0.0827F, -0.2469F, -0.0068598F, -0.107386F, 0.243424F, 0.0129156F, 0.142748F, -0.254568F, 0.461939F, -0.154419F };
   cblas_ctrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrmm(case 1773) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrmm(case 1773) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.463, 0.033, -0.929, 0.949, 0.864, 0.986, 0.393, 0.885 };
   int lda = 2;
   double B[] = { -0.321, -0.852, -0.337, -0.175, 0.607, -0.613, 0.688, 0.973, -0.331, -0.35, 0.719, -0.553 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1774) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1774) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.608, -0.393, 0.921, 0.282, -0.857, -0.286, -0.31, -0.057 };
   int lda = 2;
   double B[] = { -0.548, 0.728, 0.391, -0.506, 0.186, 0.97, -0.435, 0.375, -0.995, -0.496, 0.99, 0.186 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1775) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1775) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.253, 0.969, 0.654, -0.016, -0.774, -0.11, -0.101, -0.287 };
   int lda = 2;
   double B[] = { -0.34, -0.268, -0.52, 0.021, -0.875, 0.98, 0.255, 0.564, -0.478, -0.818, -0.043, 0.224 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1776) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1776) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { -0.64, -0.222, 0.922, 0.417, -0.724, 0.012, 0.418, 0.39 };
   int lda = 2;
   double B[] = { 0.619, -0.024, -0.068, 0.219, 0.374, -0.937, 0.79, 0.166, -0.92, 0.753, -0.017, 0.076 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1777) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1777) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.57, 0.987, 0.116, -0.691, -0.603, -0.778, 0.14, -0.073 };
   int lda = 2;
   double B[] = { 0.421, -0.055, 0.92, 0.664, 0.835, 0.861, -0.392, -0.897, -0.346, 0.516, -0.068, -0.156 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1778) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1778) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { -0.754, 0.904, 0.089, 0.206, 0.974, -0.946, -0.55, -0.675 };
   int lda = 2;
   double B[] = { -0.42, -0.372, 0.628, 0.148, 0.344, -0.924, -0.802, -0.307, 0.427, 0.116, 0.916, -0.384 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1779) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1779) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.152, -0.898, -0.024, 0.719, 0.992, -0.841, 0.901, 0.202 };
   int lda = 2;
   double B[] = { 0.243, -0.811, 0.68, 0.118, 0.946, -0.632, 0.729, -0.942, 0.308, 0.507, -0.838, 0.594 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1780) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1780) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.119, -0.849, 0.425, -0.273, -0.918, 0.196, -0.871, -0.39 };
   int lda = 2;
   double B[] = { 0.709, 0.33, -0.207, 0.012, -0.017, 0.787, -0.385, 0.739, -0.874, 0.188, -0.039, 0.692 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1781) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1781) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.837, -0.603, 0.755, -0.92, 0.892, -0.009, -0.741, 0.271, -0.325, -0.861, 0.902, -0.088, 0.091, 0.256, 0.209, -0.724, 0.28, -0.604 };
   int lda = 3;
   double B[] = { 0.455, -0.215, -0.668, 0.917, -0.985, 0.477, 0.564, -0.524, -0.202, -0.53, -0.88, -0.688 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1782) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1782) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { -0.991, 0.253, 0.813, 0.497, -0.268, 0.623, 0.82, -0.946, -0.883, 0.333, -0.265, -0.371, 0.131, -0.812, -0.365, 0.45, 0.929, -0.704 };
   int lda = 3;
   double B[] = { 0.783, -0.756, 0.635, 0.56, 0.434, -0.831, -0.34, -0.531, -0.277, 0.874, 0.986, 0.157 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1783) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1783) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.265, -0.592, -0.721, -0.838, -0.952, 0.115, -0.34, -0.789, -0.265, -0.779, -0.676, 0.048, 0.78, -0.272, -0.651, 0.272, 0.8, -0.693 };
   int lda = 3;
   double B[] = { -0.609, 0.028, -0.818, 0.289, -0.41, -0.25, -0.917, 0.463, 0.942, 0.692, -0.516, 0.378 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1784) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1784) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.962, 0.945, -0.58, -0.358, -0.769, 0.751, -0.068, -0.321, 0.938, 0.183, -0.17, 0.251, -0.248, -0.092, -0.818, 0.928, -0.059, -0.222 };
   int lda = 3;
   double B[] = { 0.015, -0.852, -0.565, 0.16, -0.095, 0.073, 0.405, 0.509, 0.082, -0.478, -0.365, 0.824 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1785) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1785) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.616, 0.669, 0.323, -0.238, 0.153, 0.891, -0.4, 0.996, 0.689, -0.736, -0.259, -0.707, 0.993, 0.13, -0.829, -0.564, -0.09, 0.118 };
   int lda = 3;
   double B[] = { 0.113, 0.724, 0.148, -0.309, -0.833, -0.791, 0.354, -0.528, 0.313, 0.421, 0.28, 0.371 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1786) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1786) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { 0.957, -0.713, 0.976, 0.183, -0.145, -0.858, -0.497, -0.605, -0.742, 0.686, 0.272, 0.83, -0.606, -0.099, -0.807, 0.767, 0.254, 0.244 };
   int lda = 3;
   double B[] = { -0.124, -0.19, 0.665, -0.74, 0.505, -0.194, 0.588, -0.421, -0.727, 0.308, -0.802, -0.278 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1787) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1787) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { -0.649, 0.856, 0.969, 0.382, 0.963, 0.567, 0.599, 0.018, -0.924, 0.578, -0.531, -0.091, -0.454, -0.834, 0.97, -0.126, -0.859, 0.879 };
   int lda = 3;
   double B[] = { 0.35, 0.824, -0.084, 0.662, -0.752, 0.872, 0.129, 0.969, -0.539, 0.907, 0.316, -0.675 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1788) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1788) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 111;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0};
   double A[] = { -0.315, -0.459, 0.327, -0.132, -0.283, 0.173, -0.356, -0.427, 0.508, 0.347, -0.804, -0.849, 0.779, 0.673, 0.019, -0.869, 0.999, -0.338 };
   int lda = 3;
   double B[] = { 0.678, -0.171, 0.136, -0.268, -0.578, -0.431, 0.978, -0.749, 0.333, -0.757, 0.658, 0.456 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1789) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1789) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.532, -0.877, 0.308, -0.807, 0.013, 0.891, 0.077, -0.004 };
   int lda = 2;
   double B[] = { 0.634, -0.969, 0.228, -0.097, 0.419, 0.903, 0.21, 0.313, -0.819, -0.028, 0.574, -0.762 };
   int ldb = 3;
   double B_expected[] = { 0.004051, -0.1187101, 0.0148352, -0.0206365, 0.0847859, 0.0569023, 0.0786829, -0.0569289, 0.0212752, -0.007123, 0.0120979, 0.0898923 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1790) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1790) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.77, -0.037, -0.021, -0.831, -0.663, -0.241, -0.273, -0.023 };
   int lda = 2;
   double B[] = { 0.354, -0.95, -0.944, -0.497, 0.741, 0.084, -0.3, 0.023, -0.056, 0.063, -0.117, -0.498 };
   int ldb = 3;
   double B_expected[] = { 0.095, 0.0354, 0.0497, -0.0944, -0.0084, 0.0741, 0.0251224, -0.1096884, -0.0857901, -0.0449183, 0.1115535, -0.0062757 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1791) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1791) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.623, 0.379, 0.903, -0.378, -0.088, 0.24, -0.964, 0.558 };
   int lda = 2;
   double B[] = { -0.137, 0.706, 0.457, 0.399, -0.69, -0.7, 0.34, 0.479, 0.539, -0.133, 0.876, -0.347 };
   int ldb = 3;
   double B_expected[] = { 0.0452313, -0.0327103, -0.006569, -0.0451444, -0.0415366, 0.0701362, 0.0272036, -0.0595042, -0.0428974, -0.0445382, -0.0823316, -0.0650838 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1792) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1792) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.253, 0.657, 0.636, 0.827, -0.107, 0.353, 0.425, -0.365 };
   int lda = 2;
   double B[] = { -0.402, -0.409, 0.421, -0.333, -0.771, -0.099, 0.697, -0.812, -0.653, 0.823, 0.994, 0.998 };
   int ldb = 3;
   double B_expected[] = { 0.0076075, -0.0189943, 0.065157, 0.0200352, -0.0145096, -0.1229652, 0.0812, 0.0697, -0.0823, -0.0653, -0.0998, 0.0994 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1793) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1793) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.57, -0.805, -0.66, -0.421, 0.643, -0.534, -0.988, -0.581 };
   int lda = 2;
   double B[] = { -0.279, -0.253, 0.976, -0.051, 0.294, 0.451, 0.187, -0.177, 0.31, -0.714, -0.104, -0.177 };
   int ldb = 2;
   double B_expected[] = { -0.0368805, -0.0044635, 0.0530361, -0.1308418, 0.049374, 0.0195475, -0.0199226, 0.0142283, -0.015743, -0.075147, 0.0389342, -0.0182031 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1794) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1794) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.594, 0.273, 0.457, 0.295, 0.434, -0.227, -0.662, 0.623 };
   int lda = 2;
   double B[] = { -0.582, -0.581, 0.259, -0.833, -0.864, -0.284, 0.965, -0.459, -0.539, -0.551, -0.969, 0.09 };
   int ldb = 2;
   double B_expected[] = { 0.0581, -0.0582, 0.095304, -0.0125475, 0.0284, -0.0864, 0.0386128, 0.0525556, 0.0551, -0.0539, 0.0026781, -0.1328003 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1795) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1795) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.398, 0.323, 0.31, 0.718, 0.181, 0.665, 0.402, 0.317 };
   int lda = 2;
   double B[] = { 0.812, -0.244, -0.415, 0.602, 0.901, -0.017, 0.786, -0.119, 0.448, -0.75, 0.851, 0.172 };
   int ldb = 2;
   double B_expected[] = { -0.0053814, -0.0158898, -0.0110449, -0.0357664, -0.0811715, 0.0693191, -0.0201324, 0.0353695, -0.0510542, 0.0560868, -0.0338911, 0.0287578 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1796) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1796) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.265, -0.578, 0.218, -0.093, -0.172, 0.414, 0.448, 0.696 };
   int lda = 2;
   double B[] = { 0.02, -0.254, 0.152, 0.304, 0.289, 0.247, 0.705, 0.419, -0.735, 0.788, -0.942, -0.71 };
   int ldb = 2;
   double B_expected[] = { 0.0201864, 0.0081408, -0.0304, 0.0152, -0.0272777, 0.0481657, -0.0419, 0.0705, -0.0720826, -0.1006386, 0.071, -0.0942 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1797) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1797) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.971, 0.532, 0.175, 0.455, 0.191, 0.493, 0.882, -0.944, 0.358, 0.142, -0.065, 0.632, -0.319, -0.101, 0.578, 0.476, -0.773, 0.912 };
   int lda = 3;
   double B[] = { 0.018, -0.131, 0.964, -0.467, -0.729, -0.794, 0.874, 0.361, 0.744, -0.958, 0.162, 0.555 };
   int ldb = 3;
   double B_expected[] = { 0.0271781, 0.0720558, 0.0439416, 0.0960619, 0.0051086, 0.1287645, -0.117224, 0.0980019, 0.0171007, 0.0041098, 0.0281271, -0.0631386 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1798) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1798) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.506, -0.263, -0.994, 0.681, 0.889, -0.5, -0.912, 0.741, -0.329, -0.912, 0.332, -0.001, -0.484, 0.942, -0.728, -0.104, -0.216, 0.679 };
   int lda = 3;
   double B[] = { 0.562, -0.354, 0.742, -0.177, -0.627, -0.762, 0.476, 0.758, 0.675, -0.504, -0.33, 0.186 };
   int ldb = 3;
   double B_expected[] = { 0.0036678, -0.0993414, 0.0429357, 0.0533074, 0.0762, -0.0627, -0.2049005, -0.0052096, 0.0441918, 0.0565626, -0.0186, -0.033 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1799) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1799) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.341, -0.27, 0.001, 0.939, 0.714, 0.803, -0.508, -0.331, -0.563, -0.725, -0.902, -0.793, 0.461, 0.127, -0.597, -0.498, 0.394, -0.019 };
   int lda = 3;
   double B[] = { 0.015, 0.803, 0.497, 0.667, 0.803, 0.775, 0.026, 0.908, 0.535, -0.111, 0.379, -0.036 };
   int ldb = 3;
   double B_expected[] = { 0.0277873, 0.0211695, 0.1148735, 0.0461937, -0.0016476, 0.0271498, 0.0316648, 0.0236294, 0.0795252, -0.009434, -0.0200342, -0.0329361 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1800) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1800) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.132, 0.903, -0.235, -0.294, -0.09, 0.74, -0.707, -0.855, 0.632, 0.543, -0.558, -0.416, -0.99, -0.088, -0.189, -0.371, -0.844, -0.737 };
   int lda = 3;
   double B[] = { -0.257, 0.159, 0.689, 0.785, 0.398, -0.128, -0.098, -0.735, -0.307, 0.032, 0.517, 0.049 };
   int ldb = 3;
   double B_expected[] = { -0.0159, -0.0257, -0.0892322, 0.1006644, 0.0666778, 0.0827436, 0.0735, -0.0098, -0.0635435, -0.0866139, -0.0893123, 0.0619235 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1801) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1801) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.993, 0.709, 0.225, -0.704, -0.396, 0.656, -0.588, -0.085, -0.024, 0.264, -0.988, -0.67, 0.665, -0.165, -0.778, -0.43, 0.71, -0.35 };
   int lda = 3;
   double B[] = { 0.321, 0.614, 0.058, 0.983, 0.153, -0.647, 0.342, -0.518, -0.071, -0.533, -0.424, 0.283 };
   int ldb = 2;
   double B_expected[] = { -0.0861992, -0.0396692, -0.155091, -0.1119744, -0.0501124, -0.0006816, -0.0064866, 0.0580106, 0.035358, -0.023696, -0.034933, -0.020199 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1802) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1802) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.034, -0.02, -0.401, -0.892, 0.329, -0.799, -0.018, 0.564, 0.095, 0.965, -0.105, 0.756, -0.583, -0.706, -0.436, -0.145, 0.921, 0.416 };
   int lda = 3;
   double B[] = { 0.972, 0.157, -0.029, 0.674, 0.914, 0.434, 0.132, -0.116, -0.907, 0.316, -0.423, 0.321 };
   int ldb = 2;
   double B_expected[] = { -0.1120798, 0.1462649, -0.0862031, 0.0507283, -0.0427739, 0.1355272, 0.0194621, 0.0362973, -0.0316, -0.0907, -0.0321, -0.0423 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1803) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1803) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { -0.195, -0.36, 0.834, -0.505, -0.87, -0.787, 0.997, 0.965, -0.046, -0.591, 0.082, 0.552, 0.414, -0.013, -0.048, -0.766, 0.728, 0.088 };
   int lda = 3;
   double B[] = { -0.916, -0.162, -0.863, 0.67, -0.079, -0.27, -0.191, 0.995, 0.981, -0.25, -0.149, 0.248 };
   int ldb = 2;
   double B_expected[] = { -0.036135, 0.01203, -0.018003, 0.0409485, -0.0386581, -0.100169, -0.1061706, 0.0215439, -0.0700412, 0.1548156, -0.0239871, 0.0582902 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1804) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1804) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 112;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 0.1};
   double A[] = { 0.553, -0.63, -0.079, 0.351, 0.865, -0.062, 0.165, -0.634, -0.513, 0.216, -0.521, 0.349, 0.54, 0.545, -0.719, -0.306, 0.501, 0.757 };
   int lda = 3;
   double B[] = { -0.311, 0.088, -0.328, 0.977, 0.659, -0.06, -0.276, 0.872, -0.734, -0.01, -0.668, -0.327 };
   int ldb = 2;
   double B_expected[] = { -0.0088, -0.0311, -0.0977, -0.0328, 0.0176113, 0.0652681, -0.0679689, -0.0593015, -0.0346653, -0.1319958, 0.0012195, -0.1051678 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1805) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1805) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.993, -0.018, 0.162, -0.222, 0.188, 0.672, -0.675, -0.345 };
   int lda = 2;
   double B[] = { 0.476, -0.009, 0.725, -0.925, -0.245, 0.308, 0.515, 0.1, -0.072, -0.757, 0.212, 0.571 };
   int ldb = 3;
   double B_expected[] = { 0.000369, 0.47283, 0.905475, 0.736575, -0.301434, -0.248829, -0.214389, -0.303015, -0.497235, 0.632565, 0.316779, -0.448161 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1806) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1806) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.78, 0.346, -0.663, -0.86, -0.496, -0.154, 0.356, 0.228 };
   int lda = 2;
   double B[] = { 0.578, 0.492, 0.775, 0.353, 0.198, -0.519, -0.52, -0.677, -0.438, 0.313, 0.941, -0.56 };
   int ldb = 3;
   double B_expected[] = { -0.492, 0.578, -0.353, 0.775, 0.519, 0.198, 0.506116, -1.326334, -0.745461, -1.255405, 0.045623, 1.256066 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1807) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1807) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.455, 0.442, 0.062, 0.815, 0.03, 0.55, 0.592, -0.487 };
   int lda = 2;
   double B[] = { -0.451, 0.01, 0.174, -0.775, 0.22, -0.644, 0.858, -0.004, 0.59, -0.395, -0.943, 0.824 };
   int ldb = 3;
   double B_expected[] = { 0.268128, -0.177245, 0.765883, -0.46293, -0.15311, 0.240362, -0.415478, 0.509884, -0.05349, 0.541645, -0.028567, -0.959544 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1808) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1808) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.268, -0.886, -0.805, 0.875, 0.481, 0.095, -0.057, 0.605 };
   int lda = 2;
   double B[] = { 0.708, -0.638, 0.408, -0.512, 0.175, 0.181, -0.919, -0.126, 0.708, -0.51, 0.212, 0.114 };
   int ldb = 3;
   double B_expected[] = { 0.611301, 0.253991, 0.82457, 0.700098, -0.215694, 0.287802, 0.126, -0.919, 0.51, 0.708, -0.114, 0.212 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1809) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1809) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.881, 0.555, 0.774, 0.148, -0.915, 0.336, 0.103, 0.381 };
   int lda = 2;
   double B[] = { 0.163, 0.963, -0.017, 0.921, 0.809, 0.846, 0.905, -0.43, 0.894, -0.371, -0.988, -0.487 };
   int ldb = 2;
   double B_expected[] = { -0.757938, 0.678068, 0.834573, 0.523573, -0.296331, 1.182259, 1.435009, -0.526594, 0.823021, 0.581709, -0.365348, -1.229977 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1810) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1810) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.719, -0.513, 0.169, -0.524, 0.352, 0.823, -0.741, -0.355 };
   int lda = 2;
   double B[] = { 0.717, 0.052, -0.777, 0.277, -0.962, 0.894, 0.905, -0.216, -0.707, 0.016, 0.481, 0.935 };
   int ldb = 2;
   double B_expected[] = { -0.052, 0.717, 0.294787, -0.48182, -0.894, -0.962, -0.890414, 1.302138, -0.016, -0.707, -1.522493, 0.245304 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1811) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1811) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.501, -0.136, -0.502, 0.669, -0.498, -0.4, -0.518, 0.833 };
   int lda = 2;
   double B[] = { -0.385, 0.88, 0.726, 0.911, 0.839, 0.573, -0.881, -0.517, -0.861, -0.278, 0.941, 0.822 };
   int ldb = 2;
   double B_expected[] = { 0.554496, -0.067558, 1.076656, 0.382795, -1.2501, 0.4388, -1.001679, 0.025697, 1.298547, -0.316017, 1.209649, 0.197288 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1812) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1812) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 141;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.049, 0.641, -0.9, 0.246, -0.734, -0.686, 0.76, -0.869 };
   int lda = 2;
   double B[] = { -0.37, 0.206, -0.731, -0.573, 0.638, -0.417, -0.29, -0.719, 0.107, -0.333, 0.556, 0.124 };
   int ldb = 2;
   double B_expected[] = { -0.901526, 0.146942, 0.573, -0.731, -0.30144, 0.722126, 0.719, -0.29, 0.581376, -0.362896, -0.124, 0.556 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1813) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1813) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.553, 0.338, 0.229, -0.828, -0.594, -0.036, -0.335, -0.249, 0.083, -0.197, 0.995, 0.85, -0.988, 0.596, -0.254, 0.179, 0.441, -0.859 };
   int lda = 3;
   double B[] = { -0.058, -0.225, 0.884, 0.348, 0.123, -0.151, 0.891, 0.711, -0.792, 0.552, 0.033, -0.178 };
   int ldb = 3;
   double B_expected[] = { -0.800945, -0.261458, 0.051763, -0.001149, -0.039066, 0.183952, 0.330423, 0.081423, 0.315368, -0.292945, 0.050151, 0.167455 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1814) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1814) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.257, -0.565, -0.123, 0.129, 0.817, -0.516, -0.613, -0.42, -0.494, 0.122, -0.593, -0.972, -0.695, -0.968, 0.848, -0.2, -0.17, 0.436 };
   int lda = 3;
   double B[] = { -0.274, 0.105, -0.899, -0.33, -0.318, -0.096, -0.237, 0.327, 0.046, 0.584, -0.459, -0.182 };
   int ldb = 3;
   double B_expected[] = { -0.019041, -0.416263, 0.582168, -0.617114, 0.096, -0.318, 0.136304, -0.448413, -0.245778, 0.495091, 0.182, -0.459 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1815) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1815) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.127, 0.025, 0.036, 0.612, 0.773, 0.953, 0.074, -0.006, 0.373, 0.292, -0.052, -0.319, -0.878, -0.401, 0.486, -0.493, -0.316, 0.003 };
   int lda = 3;
   double B[] = { 0.794, -0.666, -0.406, 0.622, -0.512, -0.761, 0.161, -0.137, -0.626, 0.408, 0.536, 0.66 };
   int ldb = 3;
   double B_expected[] = { -0.064732, -0.117488, -0.306038, 0.092938, -1.247288, -0.774519, -0.013374, -0.023872, -0.325804, -0.101626, 0.135651, -0.759197 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1816) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1816) imag");
     };
   };
  };


  {
   int order = 101;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.724, -0.423, 0.028, 0.043, 0.812, -0.568, 0.294, -0.375, -0.85, -0.119, -0.338, -0.415, 0.976, 0.507, 0.913, 0.697, 0.323, 0.206 };
   int lda = 3;
   double B[] = { 0.427, 0.621, -0.212, -0.942, -0.08, 0.416, 0.465, -0.972, -0.529, -0.252, -0.19, 0.073 };
   int ldb = 3;
   double B_expected[] = { -0.621, 0.427, 0.599301, -0.319337, -0.093325, -0.198531, 0.972, 0.465, 0.363393, -0.02779, 0.97279, -0.887585 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1817) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1817) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.501, -0.632, 0.663, 0.151, -0.523, -0.71, -0.811, 0.8, -0.06, 0.994, -0.962, 0.827, -0.543, 0.719, -0.264, -0.942, 0.365, 0.051 };
   int lda = 3;
   double B[] = { -0.974, 0.094, -0.533, 0.633, -0.982, -0.383, -0.297, 0.734, -0.092, -0.15, 0.215, -0.232 };
   int ldb = 2;
   double B_expected[] = { -0.675337, -0.115274, 0.406006, -0.122575, -0.952024, -0.156194, -0.514956, 0.9092, 0.050058, -0.04123, 0.095645, 0.066643 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1818) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1818) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 121;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { 0.669, 0.332, -0.661, 0.611, 0.279, -0.133, -0.033, 0.06, 0.788, -0.407, -0.644, 0.958, 0.247, -0.161, 0.125, -0.184, 0.041, -0.045 };
   int lda = 3;
   double B[] = { -0.603, 0.88, 0.668, -0.152, 0.082, 0.033, 0.733, -0.557, 0.722, 0.024, -0.754, 0.458 };
   int ldb = 2;
   double B_expected[] = { -0.996161, -0.429256, 0.185867, 0.350415, -0.168848, 0.167834, 0.638486, 0.554478, -0.024, 0.722, -0.458, -0.754 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1819) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1819) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 131;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.91, 0.05, -0.944, 0.748, -0.712, 0.619, -0.28, -0.906, 0.314, 0.943, -0.719, -0.983, 0.474, -0.115, -0.859, 0.837, 0.364, -0.164 };
   int lda = 3;
   double B[] = { -0.278, -0.34, 0.584, 0.43, -0.794, -0.465, -0.65, 0.461, 0.24, 0.003, 0.948, -0.778 };
   int ldb = 2;
   double B_expected[] = { -0.3233, 0.23598, 0.4205, -0.50994, -1.131636, -0.679699, 0.085048, 0.000967, -0.008447, 1.102325, 1.765785, 0.337213 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1820) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1820) imag");
     };
   };
  };


  {
   int order = 102;
   int side = 142;
   int uplo = 122;
   int trans = 113;
   int diag = 132;
   int M = 2;
   int N = 3;
   double alpha[2] = {0, 1};
   double A[] = { -0.39, -0.916, 0.257, -0.082, -0.802, 0.215, -0.155, 0.911, -0.099, 0.41, 0.057, 0.105, 0.94, -0.17, -0.714, -0.861, 0.292, -0.231 };
   int lda = 3;
   double B[] = { -0.453, -0.542, 0.135, 0.518, -0.199, 0.776, 0.784, -0.28, -0.499, -0.377, -0.795, -0.965 };
   int ldb = 2;
   double B_expected[] = { 0.542, -0.453, -0.518, 0.135, -0.59956, -0.270977, 0.135804, 0.776219, -0.220206, -0.182087, 1.507741, -0.776612 };
   cblas_ztrmm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrmm(case 1821) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrmm(case 1821) imag");
     };
   };
  };


}
