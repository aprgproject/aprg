#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cblas.h>

#include "tests.h"

void
test_trsm (void) {
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
   float A[] = { -0.279F, 0.058F, 0.437F, 0.462F };
   int lda = 2;
   float B[] = { 0.578F, 0.473F, -0.34F, -0.128F, 0.503F, 0.2F };
   int ldb = 3;
   float B_expected[] = { 0.638784F, 0.440702F, -0.392589F, 0.0831169F, -0.326623F, -0.12987F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1822)");
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
   float A[] = { -0.735F, -0.861F, 0.772F, -0.242F };
   int lda = 2;
   float B[] = { -0.793F, -0.162F, -0.844F, 0.143F, -0.379F, -0.46F };
   int ldb = 3;
   float B_expected[] = { 0.200963F, 0.146496F, 0.372018F, -0.0429F, 0.1137F, 0.138F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1823)");
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
   float A[] = { -0.498F, 0.777F, -0.913F, 0.779F };
   int lda = 2;
   float B[] = { -0.831F, -0.663F, -0.098F, -0.894F, -0.059F, 0.468F };
   int ldb = 3;
   float B_expected[] = { -0.500602F, -0.399398F, -0.0590361F, -0.242426F, -0.445379F, -0.249422F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1824)");
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
   float A[] = { -0.543F, 0.095F, -0.933F, -0.669F };
   int lda = 2;
   float B[] = { 0.068F, 0.715F, 0.012F, -0.785F, 0.378F, 0.251F };
   int ldb = 3;
   float B_expected[] = { -0.0204F, -0.2145F, -0.0036F, 0.216467F, -0.313528F, -0.0786588F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1825)");
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
   float A[] = { 0.75F, 0.777F, -0.025F, 0.572F };
   int lda = 2;
   float B[] = { 0.03F, 0.392F, -0.056F, 0.399F, -0.489F, -0.167F };
   int ldb = 2;
   float B_expected[] = { -0.0188531F, -0.205594F, 0.0154245F, -0.209266F, 0.19852F, 0.0875874F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1826)");
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
   float A[] = { 0.899F, -0.447F, 0.338F, -0.74F };
   int lda = 2;
   float B[] = { 0.964F, -0.104F, -0.199F, 0.503F, -0.386F, -0.764F };
   int ldb = 2;
   float B_expected[] = { -0.299746F, 0.0312F, 0.110704F, -0.1509F, 0.0383304F, 0.2292F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1827)");
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
   float A[] = { 0.279F, 0.73F, -0.366F, 0.583F };
   int lda = 2;
   float B[] = { -0.572F, 0.75F, 0.603F, 0.697F, 0.908F, 0.119F };
   int ldb = 2;
   float B_expected[] = { 0.615054F, -1.15607F, -0.648387F, 0.453212F, -0.976344F, 1.16129F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1828)");
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
   float A[] = { 0.581F, -0.911F, 0.438F, 0.731F };
   int lda = 2;
   float B[] = { 0.519F, 0.831F, 0.822F, 0.182F, 0.571F, -0.357F };
   int ldb = 2;
   float B_expected[] = { -0.1557F, -0.391143F, -0.2466F, -0.279253F, -0.1713F, -0.0489543F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1829)");
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
   float A[] = { 0.065F, 0.099F, 0.48F, 0.746F, -0.739F, 0.695F, 0.197F, 0.621F, 0.063F };
   int lda = 3;
   float B[] = { 0.01F, -0.612F, 0.756F, -0.225F, 0.546F, 0.432F };
   int ldb = 3;
   float B_expected[] = { -0.0461538F, -0.254627F, -0.439373F, 1.03846F, 0.360768F, -13.9491F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1830)");
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
   float A[] = { -0.86F, -0.653F, 0.87F, -0.037F, 0.788F, 0.015F, 0.028F, -0.804F, -0.357F };
   int lda = 3;
   float B[] = { -0.546F, 0.892F, -0.085F, -0.541F, -0.207F, 0.765F };
   int ldb = 3;
   float B_expected[] = { 0.1638F, -0.160639F, -0.114596F, 0.1623F, 0.168082F, -0.373222F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1831)");
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
   float A[] = { 0.872F, -0.35F, 0.518F, -0.8F, -0.13F, -0.832F, 0.426F, 0.195F, -0.735F };
   int lda = 3;
   float B[] = { 0.773F, 0.069F, 0.45F, 0.189F, 0.504F, 0.996F };
   int ldb = 3;
   float B_expected[] = { 0.0431742F, 0.434741F, 0.183673F, 1.36286F, 1.77287F, 0.406531F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1832)");
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
   float A[] = { -0.053F, -0.132F, -0.515F, -0.411F, 0.134F, 0.657F, 0.072F, -0.007F, -0.34F };
   int lda = 3;
   float B[] = { 0.494F, 0.072F, -0.882F, -0.112F, 0.904F, 0.755F };
   int ldb = 3;
   float B_expected[] = { -0.175368F, -0.0197478F, 0.2646F, -0.0622068F, -0.272786F, -0.2265F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1833)");
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
   float A[] = { -0.154F, -0.54F, 0.146F, -0.106F, -0.478F, 0.938F, -0.731F, 0.25F, -0.4F };
   int lda = 3;
   float B[] = { -0.88F, -0.555F, 0.642F, 0.751F, -0.859F, -0.409F };
   int ldb = 2;
   float B_expected[] = { -1.71429F, -1.08117F, 0.783084F, 0.711096F, 2.97803F, 2.11352F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1834)");
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
   float A[] = { 0.249F, -0.451F, -0.781F, 0.157F, -0.02F, 0.57F, 0.309F, -0.159F, 0.266F };
   int lda = 3;
   float B[] = { -0.546F, 0.839F, 0.392F, -0.445F, -0.818F, 0.953F };
   int ldb = 2;
   float B_expected[] = { 0.1638F, -0.2517F, -0.143317F, 0.173017F, 0.171998F, -0.180615F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1835)");
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
   float A[] = { 0.299F, 0.626F, -0.471F, 0.208F, -0.842F, 0.674F, 0.03F, 0.628F, 0.534F };
   int lda = 3;
   float B[] = { 0.831F, -0.997F, -0.366F, 0.307F, -0.426F, 0.806F };
   int ldb = 2;
   float B_expected[] = { -0.584851F, 0.816906F, 0.0611706F, -0.25308F, 0.239326F, -0.452809F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1836)");
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
   float A[] = { 0.301F, 0.168F, 0.934F, 0.107F, 0.068F, 0.384F, -0.201F, 0.116F, -0.436F };
   int lda = 3;
   float B[] = { 0.773F, -0.304F, -0.402F, 0.642F, -0.102F, -0.095F };
   int ldb = 2;
   float B_expected[] = { -0.278767F, 0.0987764F, 0.10885F, -0.203544F, 0.0306F, 0.0285F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1837)");
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
   float alpha = 1.0F;
   float A[] = { -0.616F, 0.304F, 0.403F, 0.739F };
   int lda = 2;
   float B[] = { 0.273F, -0.609F, 0.858F, 0.993F, -0.738F, -0.353F };
   int ldb = 3;
   float B_expected[] = { -0.443182F, 0.988636F, -1.39286F, 1.52602F, -1.40534F, 0.0953025F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1838)");
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
   float alpha = 1.0F;
   float A[] = { 0.811F, 0.257F, 0.98F, -0.956F };
   int lda = 2;
   float B[] = { 0.996F, 0.329F, 0.273F, -0.744F, 0.662F, -0.31F };
   int ldb = 3;
   float B_expected[] = { 0.996F, 0.329F, 0.273F, -0.999972F, 0.577447F, -0.380161F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1839)");
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
   float alpha = 1.0F;
   float A[] = { 0.845F, 0.064F, 0.29F, -0.291F };
   int lda = 2;
   float B[] = { 0.878F, 0.156F, 0.217F, 0.082F, -0.869F, 0.595F };
   int ldb = 3;
   float B_expected[] = { 1.13576F, -0.840253F, 0.958527F, -0.281787F, 2.98625F, -2.04467F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1840)");
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
   float alpha = 1.0F;
   float A[] = { 0.836F, 0.359F, -0.415F, 0.154F };
   int lda = 2;
   float B[] = { 0.652F, 0.614F, 0.922F, -0.063F, 0.313F, -0.316F };
   int ldb = 3;
   float B_expected[] = { 0.625855F, 0.743895F, 0.79086F, -0.063F, 0.313F, -0.316F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1841)");
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
   float alpha = 1.0F;
   float A[] = { 0.94F, -0.656F, 0.645F, -0.634F };
   int lda = 2;
   float B[] = { -0.948F, -0.596F, -0.799F, 0.133F, -0.843F, -0.179F };
   int ldb = 2;
   float B_expected[] = { -1.00851F, -0.0859454F, -0.85F, -1.07453F, -0.896809F, -0.630034F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1842)");
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
   float alpha = 1.0F;
   float A[] = { -0.332F, 0.705F, -0.792F, -0.033F };
   int lda = 2;
   float B[] = { 0.561F, 0.883F, -0.136F, 0.203F, -0.531F, 0.733F };
   int ldb = 2;
   float B_expected[] = { 0.561F, 1.32731F, -0.136F, 0.095288F, -0.531F, 0.312448F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1843)");
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
   float alpha = 1.0F;
   float A[] = { 0.991F, 0.614F, 0.108F, -0.125F };
   int lda = 2;
   float B[] = { -0.723F, 0.885F, 0.336F, 0.584F, 0.742F, -0.438F };
   int ldb = 2;
   float B_expected[] = { 3.65703F, -7.08F, 3.23371F, -4.672F, -1.42226F, 3.504F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1844)");
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
   float alpha = 1.0F;
   float A[] = { -0.626F, 0.912F, -0.003F, 0.761F };
   int lda = 2;
   float B[] = { 0.736F, -0.383F, 0.0F, -0.238F, 0.013F, 0.473F };
   int ldb = 2;
   float B_expected[] = { 1.0853F, -0.383F, 0.217056F, -0.238F, -0.418376F, 0.473F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1845)");
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
   float alpha = 1.0F;
   float A[] = { -0.416F, 0.599F, -0.705F, 0.326F, 0.184F, 0.079F, -0.173F, 0.125F, 0.567F };
   int lda = 3;
   float B[] = { 0.466F, 0.907F, -0.85F, -0.342F, -0.058F, -0.379F };
   int ldb = 3;
   float B_expected[] = { 9.44495F, 5.57299F, -1.49912F, 1.91427F, -0.0282283F, -0.66843F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1846)");
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
   float alpha = 1.0F;
   float A[] = { -0.75F, 0.856F, 0.773F, -0.241F, -0.357F, -0.683F, -0.718F, 0.69F, -0.486F };
   int lda = 3;
   float B[] = { -0.532F, -0.817F, 0.85F, -0.135F, 0.797F, 0.981F };
   int ldb = 3;
   float B_expected[] = { -0.986649F, -0.23645F, 0.85F, -2.14908F, 1.46702F, 0.981F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1847)");
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
   float alpha = 1.0F;
   float A[] = { 0.765F, -0.408F, 0.404F, 0.764F, 0.157F, -0.741F, 0.844F, 0.206F, -0.215F };
   int lda = 3;
   float B[] = { -0.859F, 0.563F, -0.61F, 0.2F, 0.816F, -0.692F };
   int ldb = 3;
   float B_expected[] = { -1.12288F, 9.05017F, 7.1006F, 0.261438F, 3.92523F, 8.00582F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1848)");
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
   float alpha = 1.0F;
   float A[] = { 0.354F, -0.931F, 0.18F, 0.391F, 0.01F, 0.429F, 0.685F, 0.332F, -0.643F };
   int lda = 3;
   float B[] = { -0.645F, 0.847F, 0.014F, 0.83F, 0.761F, 0.187F };
   int ldb = 3;
   float B_expected[] = { -0.645F, 1.09919F, 0.0908923F, 0.83F, 0.43647F, -0.526458F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1849)");
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
   float alpha = 1.0F;
   float A[] = { 0.569F, 0.85F, 0.642F, -0.051F, 0.724F, 0.201F, 0.87F, -0.638F, 0.008F };
   int lda = 3;
   float B[] = { -0.923F, 0.27F, -0.319F, -0.856F, -0.533F, 0.183F };
   int ldb = 2;
   float B_expected[] = { 94.9456F, -32.8005F, -59.1516F, 18.9755F, -66.625F, 22.875F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1850)");
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
   float alpha = 1.0F;
   float A[] = { 0.244F, 0.931F, 0.857F, -0.295F, 0.551F, 0.832F, 0.744F, -0.326F, 0.111F };
   int lda = 3;
   float B[] = { -0.478F, -0.252F, -0.155F, 0.419F, -0.192F, 0.291F };
   int ldb = 2;
   float B_expected[] = { -0.399342F, -0.316914F, -0.217592F, 0.513866F, -0.192F, 0.291F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1851)");
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
   float alpha = 1.0F;
   float A[] = { 0.36F, 0.356F, -0.858F, 0.879F, 0.641F, 0.989F, 0.998F, -0.005F, 0.64F };
   int lda = 3;
   float B[] = { -0.634F, -0.529F, -0.344F, 0.375F, -0.168F, 0.465F };
   int ldb = 2;
   float B_expected[] = { -1.76111F, -1.46944F, 0.441428F, 1.40113F, -3.30563F, -3.40859F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1852)");
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
   float alpha = 1.0F;
   float A[] = { 0.389F, 0.997F, 0.909F, -0.598F, -0.43F, -0.345F, -0.897F, 0.119F, -0.285F };
   int lda = 3;
   float B[] = { 0.779F, -0.129F, 0.016F, 0.599F, -0.668F, -0.638F };
   int ldb = 2;
   float B_expected[] = { 0.779F, -0.129F, -0.760663F, 0.727613F, -1.63854F, -0.269713F };
   cblas_strsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], flteps, "strsm(case 1853)");
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
   double alpha = -1;
   double A[] = { -0.876, -0.503, -0.062, -0.987 };
   int lda = 2;
   double B[] = { 0.219, -0.986, -0.0, -0.605, 0.289, 0.641 };
   int ldb = 3;
   double B_expected[] = { 0.601967125138, -1.29370052694, -0.372910623494, -0.612968591692, 0.292806484296, 0.649442755826 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1854)");
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
   double alpha = -1;
   double A[] = { -0.266, -0.505, -0.55, 0.524 };
   int lda = 2;
   double B[] = { 0.1, -0.105, 0.757, 0.522, -0.269, -0.142 };
   int ldb = 3;
   double B_expected[] = { -0.36361, 0.240845, -0.68529, -0.522, 0.269, 0.142 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1855)");
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
   double alpha = -1;
   double A[] = { 0.101, 0.871, 0.202, 0.169 };
   int lda = 2;
   double B[] = { 0.018, 0.292, -0.573, 0.866, 0.749, 0.99 };
   int ldb = 3;
   double B_expected[] = { -0.178217821782, -2.89108910891, 5.67326732673, -4.91124260355, -0.976331360947, -12.6390532544 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1856)");
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
   double alpha = -1;
   double A[] = { -0.387, -0.739, -0.599, 0.114 };
   int lda = 2;
   double B[] = { 0.7, 0.473, 0.86, -0.557, 0.283, 0.62 };
   int ldb = 3;
   double B_expected[] = { -0.7, -0.473, -0.86, 0.1377, -0.566327, -1.13514 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1857)");
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
   double alpha = -1;
   double A[] = { -0.683, -0.009, -0.451, -0.185 };
   int lda = 2;
   double B[] = { 0.552, 0.083, -0.976, 0.22, -0.895, -0.301 };
   int ldb = 2;
   double B_expected[] = { 0.511946499941, 0.448648648649, -2.21423766373, 1.18918918919, -0.236033397966, -1.62702702703 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1858)");
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
   double alpha = -1;
   double A[] = { -0.141, 0.944, 0.529, 0.636 };
   int lda = 2;
   double B[] = { 0.178, -0.22, -0.645, -0.585, -0.342, -0.594 };
   int ldb = 2;
   double B_expected[] = { -0.29438, 0.22, 0.335535, 0.585, 0.027774, 0.594 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1859)");
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
   double alpha = -1;
   double A[] = { 0.541, 0.584, -0.394, 0.371 };
   int lda = 2;
   double B[] = { 0.668, 0.848, -0.816, -0.925, -0.145, 0.746 };
   int ldb = 2;
   double B_expected[] = { -1.23475046211, -0.342063962613, 1.50831792976, 0.118982018923, 0.268022181146, -2.43268181614 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1860)");
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
   double alpha = -1;
   double A[] = { 0.836, -0.024, 0.226, 0.416 };
   int lda = 2;
   double B[] = { -0.172, -0.601, 0.542, 0.25, 0.746, 0.55 };
   int ldb = 2;
   double B_expected[] = { 0.172, 0.605128, -0.542, -0.263008, -0.746, -0.567904 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1861)");
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
   double alpha = -1;
   double A[] = { 0.544, 0.721, 0.623, 0.392, -0.808, -0.022, -0.665, -0.616, -0.735 };
   int lda = 3;
   double B[] = { -0.526, -0.486, -0.716, 0.361, 0.365, -0.492 };
   int ldb = 3;
   double B_expected[] = { 0.966911764706, 0.261316067268, -0.162398536147, -0.663602941176, -0.140417971025, -1.22766726121 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1862)");
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
   double alpha = -1;
   double A[] = { 0.907, 0.558, -0.233, 0.073, -0.734, -0.058, -0.115, 0.513, 0.503 };
   int lda = 3;
   double B[] = { -0.606, -0.124, 0.641, -0.074, -0.053, -0.734 };
   int ldb = 3;
   double B_expected[] = { 0.606, -0.214148, -0.512222584, 0.074, 0.011708, 0.751921064 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1863)");
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
   double alpha = -1;
   double A[] = { 0.9, 0.063, -0.652, -0.841, 0.251, -0.8, 0.365, 0.809, 0.336 };
   int lda = 3;
   double B[] = { -0.584, -0.058, -0.964, -0.214, -0.632, -0.611 };
   int ldb = 3;
   double B_expected[] = { -8.93978245747, -9.01617340163, 2.86904761905, -3.62368367799, -3.34313934737, 1.81845238095 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1864)");
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
   double alpha = -1;
   double A[] = { 0.934, -0.608, 0.49, 0.351, -0.301, 0.602, 0.873, 0.031, -0.2 };
   int lda = 3;
   double B[] = { -0.541, -0.729, -0.382, 0.741, 0.546, -0.833 };
   int ldb = 3;
   double B_expected[] = { -0.044208458, 0.717158, 0.382, -1.267499127, -0.571823, 0.833 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1865)");
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
   double alpha = -1;
   double A[] = { -0.339, 0.049, 0.734, -0.182, 0.427, 0.193, -0.959, -0.679, 0.269 };
   int lda = 3;
   double B[] = { 0.824, 0.907, 0.632, -0.348, -0.646, 0.741 };
   int ldb = 2;
   double B_expected[] = { 2.43067846608, 2.67551622419, -0.444066789635, 1.95537225481, 9.9460940476, 11.7193971004 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1866)");
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
   double alpha = -1;
   double A[] = { 0.766, -0.422, -0.518, 0.517, 0.669, 0.337, -0.579, 0.885, -0.677 };
   int lda = 3;
   double B[] = { 0.211, -0.911, -0.685, -0.777, -0.919, 0.282 };
   int ldb = 2;
   double B_expected[] = { -0.211, 0.911, 0.794087, 0.306013, 0.094064005, -0.025352505 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1867)");
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
   double alpha = -1;
   double A[] = { -0.686, -0.256, 0.028, 0.371, 0.469, 0.115, 0.284, 0.139, 0.677 };
   int lda = 3;
   double B[] = { -0.877, -0.818, 0.191, 0.468, 0.889, -0.002 };
   int ldb = 2;
   double B_expected[] = { -1.30020532939, -0.819646768394, -0.0852626506631, -0.998592183627, -1.31314623338, 0.00295420974889 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1868)");
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
   double alpha = -1;
   double A[] = { -0.819, -0.523, 0.042, 0.545, -0.292, 0.283, 0.224, 0.247, -0.325 };
   int lda = 3;
   double B[] = { 0.153, -0.272, -0.226, 0.987, -0.216, -0.218 };
   int ldb = 2;
   double B_expected[] = { -0.075843944, -0.285622962, 0.164872, -1.048694, 0.216, 0.218 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1869)");
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
   double alpha = -1;
   double A[] = { 0.164, 0.486, 0.891, -0.508 };
   int lda = 2;
   double B[] = { 0.368, 0.761, -0.349, 0.324, 0.241, 0.561 };
   int ldb = 3;
   double B_expected[] = { -2.24390243902, -4.64024390244, 2.12804878049, -1.50893028615, -3.96487900903, 3.14021989629 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1870)");
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
   double alpha = -1;
   double A[] = { -0.019, -0.382, -0.579, 0.76 };
   int lda = 2;
   double B[] = { -0.596, -0.074, 0.576, 0.861, -0.44, 0.842 };
   int ldb = 3;
   double B_expected[] = { 0.596, 0.074, -0.576, -0.633328, 0.468268, -1.062032 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1871)");
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
   double alpha = -1;
   double A[] = { 0.449, -0.367, -0.268, 0.1 };
   int lda = 2;
   double B[] = { 0.58, -0.203, 0.053, 0.792, 0.355, -0.685 };
   int ldb = 3;
   double B_expected[] = { -6.01906458797, -1.66681514477, 3.9706013363, -7.92, -3.55, 6.85 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1872)");
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
   double alpha = -1;
   double A[] = { 0.159, 0.333, 0.515, 0.715 };
   int lda = 2;
   double B[] = { -0.631, 0.472, 0.796, 0.278, 0.802, 0.298 };
   int ldb = 3;
   double B_expected[] = { 0.77417, -0.05897, -0.64253, -0.278, -0.802, -0.298 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1873)");
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
   double alpha = -1;
   double A[] = { 0.056, -0.493, 0.619, -0.028 };
   int lda = 2;
   double B[] = { -0.32, -0.217, 0.301, 0.729, -0.847, -0.577 };
   int ldb = 2;
   double B_expected[] = { 5.71428571429, 118.576530612, -5.375, -92.7901785714, 15.125, 313.763392857 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1874)");
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
   double alpha = -1;
   double A[] = { -0.595, 0.64, 0.109, 0.969 };
   int lda = 2;
   double B[] = { 0.186, -0.435, -0.747, 0.212, 0.257, 0.804 };
   int ldb = 2;
   double B_expected[] = { -0.186, 0.455274, 0.747, -0.293423, -0.257, -0.775987 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1875)");
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
   double alpha = -1;
   double A[] = { 0.484, 0.769, 0.91, 0.817 };
   int lda = 2;
   double B[] = { -0.668, 0.544, 0.753, 0.796, -0.74, -0.091 };
   int ldb = 2;
   double B_expected[] = { 2.4380974539, -0.665850673195, -0.0077814418807, -0.97429620563, 1.35195534965, 0.111383108935 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1876)");
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
   double alpha = -1;
   double A[] = { -0.725, 0.73, -0.095, 0.123 };
   int lda = 2;
   double B[] = { -0.26, 0.579, 0.393, -0.18, 0.358, 0.839 };
   int ldb = 2;
   double B_expected[] = { 0.68267, -0.579, -0.5244, 0.18, 0.25447, -0.839 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1877)");
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
   double alpha = -1;
   double A[] = { -0.009, 0.237, -0.563, 0.993, 0.508, 0.771, 0.745, 0.233, 0.255 };
   int lda = 3;
   double B[] = { -0.328, -0.482, 0.083, -0.125, -0.712, -0.757 };
   int ldb = 3;
   double B_expected[] = { 21.9110553583, 1.44282075035, -0.325490196078, -281.330646047, -3.10396016674, 2.96862745098 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1878)");
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
   double alpha = -1;
   double A[] = { -0.484, -0.131, 0.563, -0.095, 0.012, -0.988, -0.722, 0.738, 0.05 };
   int lda = 3;
   double B[] = { -0.069, -0.137, -0.45, -0.24, 0.221, -0.509 };
   int ldb = 3;
   double B_expected[] = { -0.1081604, 0.5816, 0.45, -0.009639148, 0.281892, 0.509 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1879)");
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
   double alpha = -1;
   double A[] = { 0.521, 0.487, -0.961, 0.903, -0.045, 0.059, -0.61, -0.328, 0.883 };
   int lda = 3;
   double B[] = { -0.772, 0.079, -0.227, 0.998, 0.302, -0.099 };
   int ldb = 3;
   double B_expected[] = { 1.48176583493, 31.4896566432, 12.9778986844, -1.91554702495, -31.7275325229, -12.9967319963 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1880)");
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
   double alpha = -1;
   double A[] = { 0.642, 0.511, 0.762, 0.804, -0.28, -0.318, 0.382, -0.165, -0.007 };
   int lda = 3;
   double B[] = { 0.987, 0.436, -0.783, 0.175, -0.973, -0.319 };
   int ldb = 3;
   double B_expected[] = { -0.987, 0.357548, 1.21902942, -0.175, 1.1137, 0.5696105 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1881)");
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
   double alpha = -1;
   double A[] = { -0.995, 0.625, 0.16, -0.127, -0.722, -0.355, -0.14, -0.146, -0.756 };
   int lda = 3;
   double B[] = { 0.676, 0.038, 0.543, 0.296, -0.44, 0.751 };
   int ldb = 2;
   double B_expected[] = { 0.650272121575, -0.128270318012, 0.869769452872, 0.209093640534, -0.582010582011, 0.993386243386 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1882)");
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
   double alpha = -1;
   double A[] = { -0.619, 0.548, 0.064, -0.483, -0.508, -0.819, 0.237, 0.852, -0.512 };
   int lda = 3;
   double B[] = { -0.169, 0.429, -0.789, 0.79, 0.479, 0.817 };
   int ldb = 2;
   double B_expected[] = { 0.860726164, -0.280732428, 1.197108, -0.093916, -0.479, -0.817 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1883)");
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
   double alpha = -1;
   double A[] = { 0.794, -0.098, 0.442, -0.991, 0.049, 0.079, -0.8, -0.762, 0.395 };
   int lda = 3;
   double B[] = { 0.496, -0.734, -0.679, -0.697, 0.426, 0.094 };
   int ldb = 2;
   double B_expected[] = { -0.624685138539, 0.92443324937, 12.6077725801, 16.0733562947, -2.90102076605, -4.48707504683 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1884)");
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
   double alpha = -1;
   double A[] = { 0.848, -0.765, 0.528, -0.693, 0.252, -0.135, -0.507, 0.954, -0.056 };
   int lda = 3;
   double B[] = { 0.791, -0.787, 0.636, 0.271, -0.905, -0.974 };
   int ldb = 2;
   double B_expected[] = { -0.791, 0.787, -1.241115, 0.331055, 1.155097475, 0.603156425 };
   cblas_dtrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[i], B_expected[i], dbleps, "dtrsm(case 1885)");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.491F, -0.317F, -0.14F, -0.739F, -0.969F, -0.518F, 0.702F, -0.287F };
   int lda = 2;
   float B[] = { -0.962F, -0.38F, 0.656F, 0.587F, -0.195F, -0.862F, -0.679F, 0.598F, 0.919F, 0.714F, -0.513F, 0.726F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1886) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1886) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.6F, 0.338F, -0.048F, -0.926F, 0.236F, 0.362F, 0.605F, 0.562F };
   int lda = 2;
   float B[] = { -0.009F, 0.371F, -0.989F, 0.728F, -0.062F, 0.113F, 0.714F, 0.604F, -0.293F, 0.859F, -0.875F, 0.216F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1887) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1887) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.889F, -0.479F, -0.526F, 0.077F, -0.704F, 0.242F, 0.458F, -0.553F };
   int lda = 2;
   float B[] = { -0.554F, 0.966F, 0.076F, 0.42F, 0.85F, 0.369F, 0.124F, -0.476F, -0.007F, 0.428F, 0.452F, -0.214F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1888) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1888) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.947F, 0.444F, 0.079F, -0.597F, 0.978F, -0.64F, 0.82F, 0.808F };
   int lda = 2;
   float B[] = { -0.899F, -0.964F, -0.714F, 0.422F, -0.084F, -0.78F, -0.609F, -0.595F, 0.748F, -0.926F, 0.242F, -0.474F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1889) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1889) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.547F, -0.763F, -0.805F, 0.498F, 0.786F, -0.082F, 0.922F, 0.538F };
   int lda = 2;
   float B[] = { -0.074F, -0.617F, 0.359F, -0.383F, -0.172F, 0.911F, -0.934F, 0.066F, -0.67F, 0.895F, 0.92F, 0.255F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1890) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1890) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.096F, -0.362F, -0.311F, -0.347F, 0.161F, -0.517F, -0.393F, 0.572F };
   int lda = 2;
   float B[] = { 0.742F, -0.419F, -0.391F, 0.846F, -0.255F, -0.364F, 0.006F, -0.496F, 0.118F, -0.593F, 0.773F, 0.053F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1891) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1891) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.669F, 0.845F, 0.657F, -0.43F, 0.19F, 0.206F, -0.305F, 0.761F };
   int lda = 2;
   float B[] = { -0.457F, 0.857F, -0.203F, 0.942F, 0.462F, 0.52F, 0.521F, -0.609F, 0.069F, 0.005F, -0.419F, 0.806F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1892) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1892) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.269F, -0.87F, -0.592F, 0.813F, 0.977F, -0.848F, 0.282F, -0.311F };
   int lda = 2;
   float B[] = { -0.654F, 0.857F, -0.834F, 0.796F, 0.414F, -0.499F, 0.961F, 0.643F, 0.117F, 0.758F, -0.189F, -0.768F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1893) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1893) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.361F, -0.818F, 0.039F, 0.275F, 0.541F, -0.615F, 0.025F, -0.691F, -0.697F, 0.976F, 0.746F, 0.607F, 0.651F, -0.918F, -0.702F, 0.37F, -0.668F, -0.114F };
   int lda = 3;
   float B[] = { 0.218F, 0.75F, 0.575F, -0.702F, 0.7F, -0.41F, 0.374F, 0.489F, -0.876F, 0.842F, -0.848F, 0.901F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1894) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1894) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.483F, 0.088F, -0.192F, 0.17F, 0.683F, 0.293F, -0.773F, 0.365F, -0.28F, 0.257F, 0.818F, 0.45F, -0.551F, -0.051F, 0.899F, -0.127F, -0.915F, 0.152F };
   int lda = 3;
   float B[] = { 0.732F, -0.394F, 0.073F, -0.082F, 0.918F, -0.53F, 0.67F, 0.149F, -0.344F, -0.65F, -0.62F, -0.632F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1895) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1895) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.508F, -0.251F, 0.655F, -0.315F, -0.26F, 0.229F, 0.05F, -0.276F, -0.993F, 0.647F, -0.547F, -0.34F, 0.781F, -0.819F, 0.865F, 0.361F, -0.028F, 0.178F };
   int lda = 3;
   float B[] = { 0.972F, 0.048F, 0.71F, -0.168F, -0.274F, 0.92F, 0.789F, 0.485F, 0.578F, 0.73F, -0.931F, 0.288F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1896) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1896) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.874F, 0.651F, 0.074F, -0.862F, -0.42F, 0.066F, -0.845F, 0.482F, -0.44F, 0.724F, 0.137F, -0.123F, -0.63F, -0.011F, -0.187F, -0.205F, 0.976F, -0.81F };
   int lda = 3;
   float B[] = { 0.539F, 0.131F, 0.986F, 0.615F, 0.983F, -0.22F, 0.144F, 0.677F, 0.561F, -0.494F, -0.433F, -0.089F };
   int ldb = 3;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1897) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1897) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.284F, 0.871F, -0.835F, 0.926F, 0.459F, -0.889F, 0.387F, 0.319F, -0.366F, 0.884F, 0.236F, 0.921F, 0.619F, -0.41F, -0.709F, -0.372F, 0.06F, 0.551F };
   int lda = 3;
   float B[] = { 0.354F, 0.245F, 0.552F, 0.77F, -0.524F, -0.973F, -0.814F, -0.835F, -0.976F, 0.396F, -0.726F, -0.204F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1898) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1898) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.98F, -0.854F, -0.832F, 0.514F, -0.028F, -0.857F, 0.066F, 0.415F, -0.316F, 0.538F, -0.465F, -0.691F, 0.286F, 0.954F, -0.486F, -0.574F, -0.429F, 0.992F };
   int lda = 3;
   float B[] = { 0.295F, 0.578F, -0.167F, 0.106F, -0.782F, 0.668F, 0.278F, 0.855F, 0.038F, 0.976F, 0.167F, -0.777F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1899) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1899) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { 0.534F, 0.782F, 0.282F, 0.581F, 0.804F, -0.68F, 0.234F, -0.758F, 0.033F, -0.503F, 0.981F, -0.839F, 0.919F, 0.175F, 0.152F, -0.683F, -0.346F, -0.279F };
   int lda = 3;
   float B[] = { 0.135F, -0.969F, -0.314F, -0.026F, -0.284F, 0.529F, 0.781F, -0.413F, -0.018F, -0.859F, -0.817F, -0.849F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1900) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1900) imag");
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
   float alpha[2] = {0.0F, 0.0F};
   float A[] = { -0.426F, 0.148F, 0.889F, 0.217F, 0.779F, -0.963F, -0.516F, -0.366F, 0.721F, 0.4F, -0.976F, -0.365F, 0.532F, 0.188F, 0.176F, 0.082F, -0.691F, -0.833F };
   int lda = 3;
   float B[] = { -0.71F, 0.72F, 0.533F, 0.395F, -0.749F, 0.151F, 0.871F, 0.445F, 0.195F, -0.38F, -0.318F, -0.833F };
   int ldb = 2;
   float B_expected[] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1901) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1901) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { -0.068F, 0.806F, -0.621F, 0.037F, 0.096F, -0.312F, 0.416F, 0.428F };
   int lda = 2;
   float B[] = { 0.481F, 0.192F, -0.954F, -0.958F, -0.015F, -0.203F, -0.352F, 0.08F, -0.662F, 0.681F, -0.571F, 0.146F };
   int ldb = 3;
   float B_expected[] = { 0.612512F, 0.186537F, -1.27483F, -1.08103F, -0.0395775F, -0.248522F, 0.0478574F, -0.671409F, -3.31165F, 0.315466F, -1.07961F, -0.629312F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1902) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1902) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.863F, 0.689F, 0.171F, -0.164F, 0.065F, -0.727F, -0.245F, -0.556F };
   int lda = 2;
   float B[] = { 0.711F, -0.616F, -0.684F, 0.823F, 0.491F, 0.06F, -0.776F, 0.768F, 0.391F, 0.897F, 0.779F, -0.875F };
   int ldb = 3;
   float B_expected[] = { 0.616F, 0.711F, -0.823F, -0.684F, -0.06F, 0.491F, -0.98994F, -0.796557F, -0.644091F, 0.372992F, 0.804736F, 0.685199F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1903) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1903) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.718F, -0.323F, 0.264F, 0.081F, -0.73F, 0.809F, -0.349F, -0.543F };
   int lda = 2;
   float B[] = { 0.862F, 0.676F, -0.085F, 0.204F, 0.063F, -0.124F, 0.162F, 0.754F, -0.978F, -0.097F, 0.986F, 0.943F };
   int ldb = 3;
   float B_expected[] = { -1.32203F, -1.00495F, 1.84655F, 0.329156F, -1.66053F, -2.19061F, 0.420449F, -1.11835F, 1.19333F, 0.945621F, -0.495118F, -2.05487F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1904) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1904) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { -0.515F, -0.166F, -0.364F, 0.24F, 0.056F, 0.023F, 0.05F, 0.853F };
   int lda = 2;
   float B[] = { 0.779F, 0.443F, -0.852F, 0.037F, -0.649F, 0.554F, 0.469F, 0.632F, 0.224F, -0.148F, 0.457F, -0.78F };
   int ldb = 3;
   float B_expected[] = { -0.396821F, 0.767272F, -0.040136F, -0.867948F, -0.587169F, -0.692532F, -0.632F, 0.469F, 0.148F, 0.224F, 0.78F, 0.457F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1905) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1905) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.576F, 0.785F, 0.297F, -0.561F, -0.164F, 0.463F, -0.454F, 0.803F };
   int lda = 2;
   float B[] = { -0.78F, -0.792F, 0.223F, 0.206F, -0.097F, 0.504F, 0.721F, 0.205F, 0.508F, -0.8F, -0.469F, 0.283F };
   int ldb = 2;
   float B_expected[] = { -0.164671F, -1.12975F, 0.510941F, 0.652691F, -0.386549F, 0.358405F, 0.959415F, -0.414847F, 0.906729F, -0.353789F, -0.734462F, 0.786484F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1906) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1906) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { -0.04F, 0.917F, 0.327F, -0.115F, -0.656F, -0.811F, -0.646F, 0.78F };
   int lda = 2;
   float B[] = { 0.131F, 0.677F, -0.431F, -0.652F, -0.415F, 0.094F, -0.253F, 0.496F, 0.797F, 0.166F, 0.737F, -0.685F };
   int ldb = 2;
   float B_expected[] = { -0.677F, 0.131F, 0.101647F, -0.894111F, -0.094F, -0.415F, -0.221099F, -0.601474F, -0.166F, 0.797F, -0.070263F, 1.12521F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1907) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1907) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.769F, -0.384F, -0.522F, -0.086F, -0.129F, -0.574F, 0.56F, -0.809F };
   int lda = 2;
   float B[] = { 0.367F, 0.169F, -0.321F, -0.982F, -0.563F, -0.051F, -0.742F, 0.595F, 0.067F, -0.183F, -0.524F, 0.77F };
   int ldb = 2;
   float B_expected[] = { -0.178752F, 0.912513F, 0.836303F, 0.634945F, 0.817549F, -0.921899F, 0.275884F, -0.926446F, 0.49345F, -0.309856F, -0.00752416F, -0.946584F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1908) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1908) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.758F, 0.228F, 0.263F, 0.731F, 0.171F, 0.051F, 0.968F, 0.731F };
   int lda = 2;
   float B[] = { 0.783F, 0.422F, -0.649F, -0.428F, 0.216F, 0.659F, -0.608F, -0.239F, -0.588F, 0.01F, -0.009F, -0.374F };
   int ldb = 2;
   float B_expected[] = { -1.00898F, 0.640819F, 0.428F, -0.649F, -1.1663F, 0.201195F, 0.239F, -0.608F, -0.114941F, -0.859027F, 0.374F, -0.009F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1909) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1909) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.601F, -0.017F, 0.518F, -0.975F, -0.394F, 0.396F, 0.395F, -0.374F, -0.321F, 0.221F, 0.809F, 0.74F, -0.009F, 0.88F, 0.057F, 0.65F, 0.761F, -0.839F };
   int lda = 3;
   float B[] = { -0.644F, 0.29F, 0.458F, 0.755F, -0.725F, 0.313F, 0.537F, 0.945F, 0.377F, 0.776F, -0.686F, -0.561F };
   int ldb = 3;
   float B_expected[] = { -5.28862F, 4.51343F, 4.18447F, 0.519474F, 0.288441F, -0.634688F, -7.53878F, 2.5597F, 2.79299F, 2.44873F, 0.781327F, -0.0400353F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1910) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1910) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.746F, 0.079F, -0.151F, -0.433F, 0.524F, -0.201F, 0.198F, -0.368F, -0.449F, 0.693F, -0.14F, -0.574F, -0.242F, -0.584F, -0.298F, 0.41F, -0.234F, 0.92F };
   int lda = 3;
   float B[] = { -0.787F, 0.186F, -0.104F, -0.142F, -0.548F, 0.332F, -0.66F, 0.413F, 0.046F, 0.818F, -0.783F, -0.376F };
   int ldb = 3;
   float B_expected[] = { 0.320805F, -0.445083F, 0.410072F, -0.371288F, -0.332F, -0.548F, -0.566249F, -0.287942F, -0.315918F, 0.152204F, 0.376F, -0.783F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1911) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1911) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { -0.623F, -0.229F, 0.653F, -0.19F, 0.42F, -0.181F, -0.061F, 0.963F, 0.422F, 0.989F, 0.919F, -0.352F, -0.849F, 0.052F, 0.02F, -0.771F, -0.38F, -0.566F };
   int lda = 3;
   float B[] = { 0.018F, 0.461F, -0.184F, 0.334F, 0.075F, 0.694F, 0.022F, 0.239F, 0.971F, -0.339F, 0.203F, 0.083F };
   int ldb = 3;
   float B_expected[] = { 0.642534F, -0.265073F, -0.901268F, 0.171623F, 1.29999F, 0.384146F, 0.326529F, -0.155337F, 0.629902F, 0.0571184F, -0.761884F, -0.282697F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1912) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1912) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.35F, 0.154F, 0.397F, -0.709F, 0.587F, -0.895F, -0.848F, 0.933F, -0.887F, -0.393F, 0.824F, 0.182F, 0.159F, 0.303F, -0.011F, -0.363F, 0.875F, 0.991F };
   int lda = 3;
   float B[] = { -0.513F, 0.564F, 0.404F, -0.635F, 0.924F, 0.238F, -0.059F, 0.96F, 0.341F, 0.483F, -0.844F, 0.84F };
   int ldb = 3;
   float B_expected[] = { -0.564F, -0.513F, -0.321901F, 0.495188F, -0.487057F, 1.06506F, -0.96F, -0.059F, -1.35213F, 1.18665F, -1.15086F, -1.02151F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1913) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1913) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.87F, 0.914F, -0.097F, -0.138F, 0.894F, -0.173F, 0.648F, -0.327F, 0.7F, 0.816F, 0.63F, 0.637F, -0.671F, 0.322F, -0.922F, 0.618F, 0.93F, 0.654F };
   int lda = 3;
   float B[] = { -0.347F, -0.273F, -0.384F, 0.02F, 0.392F, -0.206F, 0.347F, 0.269F, 0.016F, 0.797F, 0.699F, -0.966F };
   int ldb = 2;
   float B_expected[] = { -0.443754F, 0.343363F, 0.300599F, -0.548484F, 0.757674F, 0.722159F, 0.224607F, -0.673284F, -0.565323F, 0.414754F, 1.04867F, 0.014162F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1914) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1914) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { 0.965F, -0.191F, 0.489F, 0.84F, 0.011F, -0.951F, 0.067F, -0.21F, -0.911F, 0.767F, -0.162F, 0.274F, -0.502F, -0.445F, 0.492F, 0.023F, -0.818F, 0.859F };
   int lda = 3;
   float B[] = { 0.66F, -0.303F, 0.223F, 0.261F, -0.252F, -0.238F, -0.012F, -0.485F, 0.783F, -0.196F, -0.57F, 0.929F };
   int ldb = 2;
   float B_expected[] = { 0.177032F, 1.21679F, -0.596808F, -0.300881F, 0.159577F, -0.641744F, 0.928958F, 0.289807F, 0.196F, 0.783F, -0.929F, -0.57F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1915) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1915) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { -0.652F, 0.046F, -0.229F, 0.473F, -0.783F, -0.211F, 0.698F, 0.201F, -0.153F, 0.918F, -0.996F, -0.186F, 0.84F, -0.545F, -0.457F, 0.057F, 0.649F, 0.77F };
   int lda = 3;
   float B[] = { -0.227F, 0.14F, 0.165F, -0.945F, -0.212F, -0.522F, 0.908F, 0.722F, -0.208F, 0.969F, 0.721F, -0.816F };
   int ldb = 2;
   float B_expected[] = { 0.189219F, 0.361509F, -1.42444F, -0.353565F, -0.361882F, -0.741783F, 1.80537F, 1.02311F, -1.24128F, 0.407779F, 2.0229F, -0.0912412F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1916) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1916) imag");
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
   float alpha[2] = {0.0F, 1.0F};
   float A[] = { -0.945F, 0.36F, 0.3F, 0.128F, -0.27F, -0.834F, 0.349F, -0.6F, -0.293F, 0.122F, -0.481F, -0.681F, -0.815F, -0.195F, 0.728F, 0.016F, 0.037F, 0.989F };
   int lda = 3;
   float B[] = { -0.97F, 0.784F, 0.488F, 0.39F, -0.482F, -0.518F, -0.797F, 0.271F, 0.257F, 0.637F, 0.118F, -0.993F };
   int ldb = 2;
   float B_expected[] = { -0.784F, -0.97F, -0.39F, 0.488F, 0.62904F, -0.090648F, -0.091536F, -0.89348F, 0.3246F, -0.273981F, 1.04514F, -0.5676F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1917) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1917) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.795F, 0.073F, 0.104F, -0.261F, -0.712F, 0.881F, -0.474F, -0.906F };
   int lda = 2;
   float B[] = { -0.41F, -0.191F, -0.359F, -0.718F, -0.902F, 0.646F, -0.703F, -0.809F, -0.342F, -0.783F, -0.053F, 0.917F };
   int ldb = 3;
   float B_expected[] = { 0.0285203F, -0.0489535F, 0.0936712F, -0.036556F, -0.0702473F, -0.11991F, -0.0924979F, -0.0235243F, -0.0742841F, -0.0262764F, 0.074552F, 0.0886899F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1918) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1918) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { -0.281F, -0.111F, 0.055F, -0.643F, 0.33F, -0.663F, 0.32F, 0.423F };
   int lda = 2;
   float B[] = { 0.103F, 0.357F, -0.591F, 0.833F, -0.906F, -0.192F, -0.391F, -0.622F, -0.345F, -0.58F, -0.132F, -0.874F };
   int ldb = 3;
   float B_expected[] = { -0.0357F, 0.0103F, -0.0833F, -0.0591F, 0.0192F, -0.0906F, 0.0707864F, -0.0167114F, 0.0245802F, 0.0223124F, 0.0280882F, -0.0205626F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1919) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1919) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.311F, -0.648F, -0.732F, 0.825F, 0.152F, -0.529F, -0.353F, 0.568F };
   int lda = 2;
   float B[] = { 0.86F, -0.991F, -0.992F, -0.617F, 0.137F, -0.585F, -0.467F, 0.632F, 0.672F, 0.777F, -0.609F, 0.511F };
   int ldb = 3;
   float B_expected[] = { 0.0795347F, -0.0537122F, -0.0885393F, -0.0194836F, -0.0386006F, -0.0674606F, 0.109194F, -0.0434058F, -0.0240177F, -0.151722F, 0.117678F, -0.0168304F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1920) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1920) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.318F, -0.946F, -0.389F, 0.051F, 0.322F, -0.626F, -0.839F, -0.252F };
   int lda = 2;
   float B[] = { 0.372F, -0.23F, 0.515F, 0.213F, 0.222F, 0.296F, -0.524F, 0.442F, -0.581F, -0.409F, 0.894F, -0.246F };
   int ldb = 3;
   float B_expected[] = { 0.00443F, 0.081742F, -0.0708404F, 0.0446048F, 0.0184432F, -0.0219864F, -0.0442F, -0.0524F, 0.0409F, -0.0581F, 0.0246F, 0.0894F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1921) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1921) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { -0.411F, 0.34F, -0.85F, 0.557F, -0.918F, 0.484F, -0.889F, 0.561F };
   int lda = 2;
   float B[] = { -0.763F, -0.514F, -0.744F, -0.948F, -0.312F, 0.818F, -0.686F, 0.341F, -0.043F, 0.235F, -0.201F, 0.874F };
   int ldb = 2;
   float B_expected[] = { 0.0169288F, 0.17164F, -0.0683166F, -0.0596556F, 0.155447F, -0.0526808F, -0.086698F, 0.101645F, 0.039085F, -0.0218708F, 0.0437248F, -0.0036776F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1922) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1922) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.046F, 0.571F, 0.825F, 0.665F, 0.658F, -0.977F, 0.247F, -0.944F };
   int lda = 2;
   float B[] = { -0.342F, 0.089F, -0.975F, 0.027F, -0.621F, -0.127F, 0.937F, -0.332F, -0.357F, -0.213F, 0.57F, 0.134F };
   int ldb = 2;
   float B_expected[] = { -0.0089F, -0.0342F, -0.0302572F, -0.0663011F, 0.0127F, -0.0621F, -0.0358283F, 0.122154F, 0.0213F, -0.0357F, -0.0622943F, 0.0596805F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1923) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1923) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.655F, 0.051F, -0.864F, 0.04F, -0.45F, 0.276F, -0.365F, 0.766F };
   int lda = 2;
   float B[] = { 0.12F, 0.036F, 0.425F, -0.145F, -0.772F, -0.483F, -0.154F, -0.327F, 0.532F, 0.59F, 0.305F, 0.443F };
   int ldb = 2;
   float B_expected[] = { -0.0745593F, 0.00123365F, -0.0525674F, -0.00611891F, 0.0752311F, -0.0558274F, -0.0001932F, 0.0425972F, -0.0986826F, -0.00963885F, -0.00999124F, -0.0625937F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1924) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1924) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.253F, -0.163F, -0.061F, -0.032F, -0.764F, 0.863F, 0.051F, 0.669F };
   int lda = 2;
   float B[] = { 0.966F, 0.42F, -0.765F, 0.186F, -0.798F, 0.278F, -0.37F, -0.484F, -0.724F, -0.682F, 0.034F, 0.352F };
   int ldb = 2;
   float B_expected[] = { -0.0455826F, 0.0925287F, -0.0186F, -0.0765F, -0.0260316F, -0.0836058F, 0.0484F, -0.037F, 0.0661616F, -0.0710662F, -0.0352F, 0.0034F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1925) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1925) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.017F, -0.631F, -0.052F, 0.296F, -0.486F, -0.279F, -0.378F, 0.997F, 0.533F, 0.87F, 0.808F, 0.007F, 0.185F, -0.263F, -0.757F, -0.856F, 0.575F, -0.81F };
   int lda = 3;
   float B[] = { -0.238F, -0.924F, 0.494F, -0.089F, 0.96F, 0.959F, 0.415F, 0.39F, -0.744F, -0.881F, -0.594F, 0.629F };
   int ldb = 3;
   float B_expected[] = { 0.0798921F, -0.243487F, 0.0441094F, -0.0391653F, 0.0229218F, 0.134667F, 0.192099F, 0.152741F, 0.154557F, 0.0857677F, -0.0854154F, 0.0170199F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1926) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1926) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { -0.977F, -0.949F, 0.192F, 0.803F, -0.964F, -0.162F, 0.799F, -0.081F, -0.055F, 0.014F, 0.99F, 0.804F, 0.913F, -0.898F, -0.057F, 0.51F, 0.453F, 0.622F };
   int lda = 3;
   float B[] = { -0.852F, -0.001F, -0.955F, -0.97F, -0.071F, -0.664F, -0.077F, -0.746F, 0.228F, -0.948F, 0.476F, -0.285F };
   int ldb = 3;
   float B_expected[] = { 0.0840343F, -0.066376F, 0.0369724F, -0.0350854F, 0.0664F, -0.0071F, 0.105481F, 0.0565767F, 0.0283146F, -0.00141F, 0.0285F, 0.0476F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1927) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1927) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.822F, 0.618F, -0.935F, 0.49F, 0.885F, -0.488F, 0.412F, 0.861F, -0.144F, 0.906F, -0.054F, 0.455F, 0.213F, 0.34F, -0.465F, 0.107F, -0.611F, 0.088F };
   int lda = 3;
   float B[] = { 0.476F, -0.297F, -0.966F, -0.038F, -0.346F, -0.81F, -0.749F, -0.065F, -0.225F, -0.663F, 0.073F, -0.379F };
   int ldb = 3;
   float B_expected[] = { -0.00473086F, 0.0543508F, 0.139511F, -0.0231317F, -0.199775F, 0.100154F, 0.0488188F, -0.054416F, -0.0610839F, 0.0929832F, -0.0289368F, -0.113983F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1928) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1928) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { -0.188F, 0.741F, 0.583F, 0.527F, 0.025F, 0.216F, -0.44F, -0.071F, -0.126F, -0.093F, 0.743F, -0.476F, 0.661F, -0.66F, 0.564F, -0.943F, -0.976F, -0.035F };
   int lda = 3;
   float B[] = { -0.648F, -0.367F, -0.402F, -0.309F, 0.412F, 0.531F, -0.248F, 0.181F, 0.507F, 0.502F, -0.593F, 0.404F };
   int ldb = 3;
   float B_expected[] = { 0.0367F, -0.0648F, 0.0424472F, -0.0713177F, -0.21132F, 0.0600063F, -0.0181F, -0.0248F, -0.0599248F, 0.0410731F, 0.0277256F, 0.00238266F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1929) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1929) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.76F, -0.021F, -0.011F, 0.14F, 0.699F, 0.94F, 0.296F, 0.333F, 0.654F, -0.917F, 0.008F, -0.999F, -0.963F, 0.687F, -0.481F, 0.106F, 0.128F, -0.165F };
   int lda = 3;
   float B[] = { -0.742F, 0.774F, -0.335F, -0.99F, 0.799F, 0.901F, 0.753F, -0.085F, -0.042F, -0.591F, 0.202F, 0.515F };
   int ldb = 2;
   float B_expected[] = { 0.313744F, -0.259345F, -0.290807F, 0.212822F, -0.00668591F, -0.0164417F, 0.10903F, 0.137068F, 0.157578F, -0.23594F, -0.0747323F, 0.254147F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1930) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1930) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.582F, -0.175F, -0.48F, 0.567F, -0.571F, 0.062F, 0.038F, -0.625F, 0.737F, 0.799F, -0.569F, -0.932F, 0.522F, -0.763F, 0.156F, -0.524F, 0.138F, 0.007F };
   int lda = 3;
   float B[] = { 0.998F, 0.6F, 0.555F, -0.737F, -0.162F, 0.263F, 0.317F, -0.092F, 0.302F, -0.671F, 0.418F, -0.814F };
   int ldb = 2;
   float B_expected[] = { -0.106233F, 0.0480583F, 0.0514817F, -0.0392668F, -0.0209428F, -0.0560716F, 0.0184048F, -0.0174744F, 0.0671F, 0.0302F, 0.0814F, 0.0418F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1931) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1931) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.964F, 0.509F, 0.48F, -0.833F, 0.867F, 0.51F, -0.643F, 0.115F, -0.594F, -0.409F, -0.174F, 0.527F, 0.676F, 0.431F, 0.261F, -0.239F, 0.816F, -0.231F };
   int lda = 3;
   float B[] = { -0.659F, -0.029F, -0.581F, -0.938F, -0.904F, -0.445F, 0.119F, 0.709F, -0.649F, 0.825F, 0.532F, -0.453F };
   int ldb = 2;
   float B_expected[] = { 0.0305784F, -0.0522153F, 0.100975F, -0.00695419F, -0.055793F, 0.11446F, 0.0887801F, 0.177079F, -0.177262F, 0.0336107F, -0.0717714F, 0.251108F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1932) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1932) imag");
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
   float alpha[2] = {0.0F, 0.1F};
   float A[] = { 0.859F, 0.745F, 0.03F, -0.98F, -0.402F, 0.38F, -0.214F, 0.605F, 0.342F, -0.059F, -0.096F, 0.606F, -0.543F, 0.503F, 0.63F, -0.269F, 0.252F, 0.626F };
   int lda = 3;
   float B[] = { 0.85F, 0.642F, 0.679F, -0.254F, 0.192F, 0.766F, -0.869F, -0.09F, 0.68F, -0.898F, 0.272F, -0.651F };
   int ldb = 2;
   float B_expected[] = { -0.0642F, 0.085F, 0.0254F, 0.0679F, 0.008626F, 0.079566F, 0.07478F, -0.113829F, -0.0156973F, 0.0906397F, 0.125668F, 0.0985369F };
   cblas_ctrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], flteps, "ctrsm(case 1933) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], flteps, "ctrsm(case 1933) imag");
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
   double A[] = { 0.189, 0.519, -0.455, -0.444, -0.21, -0.507, -0.591, 0.859 };
   int lda = 2;
   double B[] = { -0.779, -0.484, 0.249, -0.107, -0.755, -0.047, 0.941, 0.675, -0.757, 0.645, -0.649, 0.242 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1934) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1934) imag");
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
   double A[] = { -0.988, 0.73, 0.279, -0.967, -0.288, -0.095, -0.821, 0.178 };
   int lda = 2;
   double B[] = { 0.702, 0.943, -0.235, -0.565, 0.279, -0.146, 0.816, 0.473, 0.893, 0.877, -0.797, -0.159 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1935) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1935) imag");
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
   double A[] = { 0.716, -0.549, 0.436, -0.822, -0.029, -0.586, 0.791, -0.159 };
   int lda = 2;
   double B[] = { 0.021, 0.391, 0.296, -0.154, -0.513, 0.738, -0.336, 0.317, 0.502, 0.543, 0.027, 0.802 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1936) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1936) imag");
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
   double A[] = { 0.715, -0.875, -0.501, 0.425, -0.928, -0.929, -0.542, 0.915 };
   int lda = 2;
   double B[] = { 0.065, 0.679, -0.545, 0.042, 0.199, -0.86, 0.159, 0.943, 0.19, 0.403, 0.994, 0.76 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1937) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1937) imag");
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
   double A[] = { -0.936, -0.989, -0.57, 0.018, -0.821, 0.516, -0.479, 0.209 };
   int lda = 2;
   double B[] = { 0.722, -0.756, -0.828, -0.191, -0.981, -0.466, 0.347, 0.85, -0.596, -0.826, -0.182, -0.321 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1938) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1938) imag");
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
   double A[] = { 0.693, 0.976, -0.356, -0.313, 0.926, -0.164, -0.337, 0.056 };
   int lda = 2;
   double B[] = { -0.988, -0.633, -0.745, -0.392, -0.362, -0.708, -0.706, -0.093, -0.177, 0.837, 0.391, -0.853 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1939) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1939) imag");
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
   double A[] = { -0.483, -0.383, 0.357, 0.889, 0.523, -0.148, -0.592, 0.481 };
   int lda = 2;
   double B[] = { -0.41, 0.994, -0.779, -0.354, 0.571, 0.51, -0.526, 0.934, 0.469, 0.735, -0.47, -0.164 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1940) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1940) imag");
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
   double A[] = { -0.576, -0.089, 0.953, -0.317, 0.408, 0.618, 0.092, -0.84 };
   int lda = 2;
   double B[] = { 0.141, -0.32, -0.007, -0.682, -0.068, -0.412, 0.675, -0.809, 0.931, -0.257, -0.048, 0.633 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1941) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1941) imag");
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
   double A[] = { 0.269, 0.567, 0.497, -0.969, 0.957, 0.538, -0.921, 0.639, 0.599, -0.436, -0.045, 0.164, 0.827, 0.489, -0.729, 0.723, -0.01, 0.934 };
   int lda = 3;
   double B[] = { -0.391, 0.434, -0.349, -0.456, -0.541, 0.289, 0.31, 0.447, 0.971, -0.626, -0.77, -0.882 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1942) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1942) imag");
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
   double A[] = { -0.523, -0.364, -0.492, 0.294, 0.71, -0.401, 0.947, -0.008, 0.235, -0.47, 0.298, -0.603, -0.193, 0.598, 0.122, -0.733, -0.827, 0.491 };
   int lda = 3;
   double B[] = { 0.872, 0.441, 0.518, 0.607, -0.04, -0.976, 0.201, -0.136, -0.958, -0.501, -0.549, -0.4 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1943) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1943) imag");
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
   double A[] = { -0.177, -0.965, 0.589, -0.236, -0.303, -0.301, 0.982, 0.006, -0.73, 0.241, 0.636, -0.672, 0.886, 0.952, 0.501, -0.803, -0.823, -0.09 };
   int lda = 3;
   double B[] = { -0.475, -0.646, -0.666, -0.886, 0.04, -0.736, -0.592, -0.995, 0.259, 0.701, -0.033, 0.616 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1944) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1944) imag");
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
   double A[] = { -0.76, -0.29, -0.601, 0.327, 0.383, 0.883, 0.589, -0.708, 0.912, -0.982, 0.629, 0.879, -0.578, -0.814, 0.168, 0.91, 0.328, 0.223 };
   int lda = 3;
   double B[] = { 0.381, 0.829, 0.096, 0.382, 0.664, 0.006, -0.376, -0.338, 0.344, -0.889, -0.175, 0.083 };
   int ldb = 3;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1945) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1945) imag");
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
   double A[] = { 0.129, -0.161, 0.102, 0.443, -0.138, 0.677, -0.87, 0.327, 0.917, 0.446, 0.798, -0.91, -0.574, 0.333, -0.626, 0.14, 0.109, 0.161 };
   int lda = 3;
   double B[] = { -0.689, -0.94, -0.814, 0.761, 0.389, 0.03, -0.175, -0.739, -0.904, 0.463, -0.511, 0.615 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1946) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1946) imag");
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
   double A[] = { 0.062, 0.756, 0.179, 0.359, -0.047, -0.197, 0.678, 0.873, 0.003, -0.996, 0.507, -0.491, -0.726, -0.833, -0.118, -0.71, 0.714, 0.638 };
   int lda = 3;
   double B[] = { -0.614, 0.193, 0.881, 0.538, 0.183, -0.034, 0.099, -0.154, -0.121, 0.842, -0.182, -0.229 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1947) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1947) imag");
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
   double A[] = { -0.874, 0.171, 0.637, 0.554, 0.852, -0.203, 0.455, 0.619, -0.128, 0.759, 0.342, 0.372, 0.669, -0.537, -0.76, -0.348, -0.714, 0.573 };
   int lda = 3;
   double B[] = { -0.434, 0.921, -0.949, 0.282, -0.665, 0.223, -0.633, 0.921, -0.73, 0.457, -0.021, -0.844 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1948) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1948) imag");
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
   double A[] = { -0.189, -0.931, 0.414, 0.288, -0.245, 0.252, -0.465, -0.073, 0.327, 0.176, -0.067, 0.1, 0.124, 0.885, -0.731, -0.303, 0.954, -0.763 };
   int lda = 3;
   double B[] = { 0.818, 0.948, -0.749, 0.808, -0.959, -0.797, 0.727, 0.701, 0.244, -0.801, 0.354, -0.781 };
   int ldb = 2;
   double B_expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1949) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1949) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.65, -0.279, -0.543, -0.097, -0.641, 0.984, 0.507, -0.809 };
   int lda = 2;
   double B[] = { -0.176, 0.87, -0.681, 0.409, -0.878, 0.522, 0.348, 0.679, -0.975, -0.815, -0.608, 0.86 };
   int ldb = 3;
   double B_expected[] = { 0.256485077177, 1.22837025149, -0.656630178218, 0.911076645728, -0.849544610576, 1.16772760977, -0.193804546743, -0.283833884163, -0.811035478317, 1.16349859839, 0.292241175557, -0.141827660937 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1950) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1950) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.23, -0.597, 0.068, 0.945, 0.045, -0.436, 0.113, 0.035 };
   int lda = 2;
   double B[] = { -0.744, -0.465, -0.742, 0.996, -0.835, 0.712, -0.968, 0.053, -0.813, 0.36, 0.572, -0.489 };
   int ldb = 3;
   double B_expected[] = { 0.744, 0.465, 0.742, -0.996, 0.835, -0.712, 1.356833, -0.7877, -0.178676, -0.993462, -1.30162, -0.251659 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1951) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1951) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.689, -0.396, 0.415, -0.567, 0.001, 0.513, 0.837, 0.045 };
   int lda = 2;
   double B[] = { -0.012, 0.2, 0.22, 0.81, -0.586, -0.198, 0.16, -0.958, -0.125, 0.833, 0.344, 0.213 };
   int ldb = 3;
   double B_expected[] = { -0.573154258944, 0.525131422048, 1.33801555643, 0.47629585874, -0.770607912552, -0.160087833623, -0.129249609305, 1.15151282248, 0.0955601670381, -1.00035867087, -0.423449388979, -0.231714190557 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1952) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1952) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.102, 0.86, -0.067, 0.12, 0.92, 0.441, 0.367, -0.104 };
   int lda = 2;
   double B[] = { 0.386, 0.59, 0.222, 0.824, 0.091, 0.486, 0.43, 0.766, 0.576, 0.042, 0.013, -0.008 };
   int ldb = 3;
   double B_expected[] = { -0.328206, 0.30435, 0.289398, -0.531344, -0.075512, -0.487627, -0.43, -0.766, -0.576, -0.042, -0.013, 0.008 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1953) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1953) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.087, 0.925, -0.315, 0.251, 0.7, -0.223, 0.448, 0.373 };
   int lda = 2;
   double B[] = { -0.333, -0.495, 0.995, -0.229, 0.425, -0.269, -0.756, -0.783, -0.214, 0.582, -0.351, -0.095 };
   int ldb = 2;
   double B_expected[] = { 0.496880191475, -0.406733596387, -0.965186357327, 2.19761676664, 0.331095906598, 0.428318547163, 1.17655095681, 0.263745306399, -0.645240814927, -0.170663836866, 1.18578937767, -0.829739852214 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1954) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1954) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.717, 0.572, -0.304, 0.878, 0.625, -0.615, -0.565, -0.643 };
   int lda = 2;
   double B[] = { -0.383, -0.669, -0.043, -0.09, -0.999, -0.427, 0.834, 0.539, -0.973, -0.481, 0.071, -0.71 };
   int ldb = 2;
   double B_expected[] = { 0.383, 0.669, -0.60781, -0.09258, 0.999, 0.427, -1.72098, -0.19149, 0.973, 0.481, -0.97494, 1.00777 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1955) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1955) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.143, -0.022, 0.487, 0.444, 0.138, -0.871, 0.572, -0.093 };
   int lda = 2;
   double B[] = { -0.073, -0.9, -0.688, 0.436, -0.213, -0.733, 0.809, -0.618, 0.696, 0.259, 0.494, 0.162 };
   int ldb = 2;
   double B_expected[] = { -6.10129128737, 3.22195959384, 1.29255909931, -0.552083922664, 8.05253150033, 8.35261031753, -1.54904967648, 0.828563601552, -3.66721033067, 1.50334288416, -0.796532800529, -0.412722990296 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1956) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1956) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.544, 0.918, -0.524, 0.547, -0.839, 0.4, -0.548, 0.49 };
   int lda = 2;
   double B[] = { 0.475, -0.594, 0.252, -0.717, 0.867, 0.07, 0.264, 0.538, 0.028, 0.482, -0.59, -0.533 };
   int ldb = 2;
   double B_expected[] = { -0.214849, 1.107552, -0.252, 0.717, -1.299622, -0.207504, -0.264, -0.538, 0.572711, -0.525438, 0.59, 0.533 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1957) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1957) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.038, -0.116, -0.476, -0.818, 0.961, 0.271, -0.593, 0.548, -0.86, 0.429, -0.396, -0.559, 0.766, -0.326, -0.335, 0.633, -0.532, 0.317 };
   int lda = 3;
   double B[] = { -0.459, 0.904, 0.887, 0.07, -0.497, -0.48, -0.313, 0.864, -0.029, -0.754, -0.566, -0.108 };
   int ldb = 3;
   double B_expected[] = { -4.58258258525, -3.00717937382, 0.0668903493808, 0.800759804641, -0.292673260098, -1.0766492922, -0.911020412982, 7.68812066826, -0.0359723342287, -0.157963939743, -0.695872108638, -0.617653117365 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1958) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1958) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.886, 0.945, 0.065, 0.882, -0.46, -0.095, 0.823, -0.245, -0.825, 0.904, -0.214, -0.268, -0.935, -0.017, 0.902, 0.561, 0.954, -0.665 };
   int lda = 3;
   double B[] = { 0.076, -0.043, 0.873, -0.831, -0.329, -0.896, -0.174, 0.653, 0.489, 0.25, -0.896, 0.609 };
   int ldb = 3;
   double B_expected[] = { 1.037824842, 1.333886264, -1.042722, 1.110916, 0.329, 0.896, 0.529073224, -0.720680322, -0.134044, -0.140198, 0.896, -0.609 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1959) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1959) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.691, -0.056, -0.339, -0.483, -0.975, -0.052, -0.198, 0.576, -0.075, 0.718, -0.321, 0.728, -0.124, 0.774, 0.685, -0.112, 0.178, 0.275 };
   int lda = 3;
   double B[] = { -0.062, -0.391, 0.326, 0.42, -0.203, 0.45, 0.338, 0.991, -0.47, -0.363, 0.766, -0.961 };
   int ldb = 3;
   double B_expected[] = { -0.134697690677, -0.554930433172, -0.526377715671, 0.991348747823, -2.94323584375, -1.92805449726, 0.601422754501, 1.38541291715, 0.201151053335, -1.95287726277, 5.96201044303, 2.1797020274 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1960) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1960) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.318, 0.067, -0.097, 0.359, -0.688, 0.307, -0.63, -0.616, 0.193, 0.817, -0.792, -0.117, -0.501, -0.929, -0.595, -0.144, 0.453, 0.658 };
   int lda = 3;
   double B[] = { -0.249, -0.206, 0.424, -0.681, -0.464, 0.21, 0.541, 0.082, 0.803, -0.461, -0.638, 0.358 };
   int ldb = 3;
   double B_expected[] = { 0.249, 0.206, -0.394026, 0.964164, 0.024089914, 0.641464836, -0.541, -0.082, -1.093318, 0.076084, -0.218343306, -1.013838812 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1961) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1961) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.691, 0.808, -0.178, 0.489, 0.159, -0.646, -0.692, -0.968, -0.146, -0.281, -0.385, 0.773, 0.704, 0.782, 0.551, -0.727, 0.669, 0.858 };
   int lda = 3;
   double B[] = { -0.657, -0.69, -0.051, 0.28, -0.846, 0.304, 0.052, 0.543, 0.613, -0.98, 0.983, -0.484 };
   int ldb = 2;
   double B_expected[] = { 2.42007211075, -0.148130095453, 4.93683906416, -0.804178199722, 1.76852672271, 0.633536755193, 4.41638755104, -0.0400468884046, 0.363887727302, 0.998182854971, -0.204739276437, 0.986048279795 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1962) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1962) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.244, -0.925, -0.539, 0.422, 0.285, -0.954, -0.347, -0.255, -0.616, -0.979, 0.631, -0.864, -0.053, -0.715, -0.749, -0.973, -0.409, -0.247 };
   int lda = 3;
   double B[] = { 0.922, -0.728, 0.588, -0.715, -0.92, -0.065, -0.583, 0.178, 0.996, 0.215, -0.614, -0.443 };
   int ldb = 2;
   double B_expected[] = { -0.416484258, -0.267425916, -0.851455486, 1.594186448, 0.383191, -1.065143, 0.611847, 0.751229, -0.996, -0.215, 0.614, 0.443 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1963) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1963) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { 0.992, 0.172, -0.646, 0.067, -0.823, -0.013, -0.55, -0.438, -0.44, -0.302, 0.99, -0.373, 0.513, -0.106, -0.591, -0.504, 0.929, -0.318 };
   int lda = 3;
   double B[] = { 0.467, 0.227, 0.988, -0.709, -0.272, -0.601, 0.719, -0.133, 0.203, 0.937, -0.382, -0.334 };
   int ldb = 2;
   double B_expected[] = { -0.495544804508, -0.142909570186, -0.846593689328, 0.861506163875, -0.485462670276, -0.898345893497, 1.07522946065, -2.43403194583, 0.315527055267, -0.271726799352, -1.73234815305, 3.5434654009 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1964) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1964) imag");
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
   double alpha[2] = {-1, 0};
   double A[] = { -0.692, -0.245, -0.874, 0.77, 0.07, 0.01, 0.018, -0.42, -0.405, -0.387, 0.888, -0.912, -0.81, 0.314, 0.66, -0.895, -0.556, 0.157 };
   int lda = 3;
   double B[] = { -0.801, 0.542, 0.699, 0.574, -0.56, 0.043, 0.742, -0.331, -0.614, 0.776, -0.335, 0.131 };
   int ldb = 2;
   double B_expected[] = { 0.801, -0.542, -0.699, -0.574, 0.842734, -1.133478, -1.794906, 0.367554, 0.837894144, 1.029031872, 1.63685728, -2.047172224 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1965) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1965) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.035, -0.456, 0.152, 0.976, 0.687, -0.527, -0.571, 0.832 };
   int lda = 2;
   double B[] = { -0.868, 0.033, -0.131, -0.936, 0.993, 0.104, -0.684, 0.851, 0.523, 0.836, -0.205, 0.319 };
   int ldb = 3;
   double B_expected[] = { -0.188683836853, 0.0217191541444, -0.044222393276, -0.201868895253, 0.218228063549, 0.00605705652583, 0.252579293874, 0.0800538768738, -0.099911150161, 0.0758372341381, -0.116723296822, -0.16542230206 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1966) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1966) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.481, -0.442, 0.69, 0.415, 0.983, -0.466, 0.503, -0.147 };
   int lda = 2;
   double B[] = { -0.287, -0.777, -0.187, 0.061, 0.631, 0.797, 0.833, -0.49, -0.188, 0.386, -0.904, -0.793 };
   int ldb = 3;
   double B_expected[] = { 0.0777, -0.0287, -0.0061, -0.0187, -0.0797, 0.0631, 0.0072975, 0.1353485, -0.0266305, -0.0084285, 0.1081065, -0.1670145 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1967) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1967) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.286, 0.025, -0.111, 0.724, -0.973, -0.071, 0.527, -0.334 };
   int lda = 2;
   double B[] = { -0.381, -0.131, 0.33, 0.09, 0.35, 0.062, -0.874, 0.252, 0.924, 0.251, 0.559, -0.619 };
   int ldb = 3;
   double B_expected[] = { 0.38447496828, 0.401499279514, -0.210140860451, -0.584596680596, -0.443343106286, -0.127686958741, -0.109102585509, -0.096697792106, 0.045298174859, 0.146623168116, 0.131759250934, 0.0225662432408 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1968) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1968) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.862, -0.003, 0.975, 0.364, -0.996, 0.909, -0.316, -0.816 };
   int lda = 2;
   double B[] = { 0.167, 0.961, 0.116, 0.675, 0.086, 0.259, -0.483, 0.898, 0.434, 0.723, 0.505, 0.042 };
   int ldb = 3;
   double B_expected[] = { -0.1416361, -0.113035, -0.1789614, -0.0108943, -0.0759877, 0.0550802, -0.0898, -0.0483, -0.0723, 0.0434, -0.0042, 0.0505 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1969) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1969) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.826, -0.025, 0.638, -0.183, -0.184, 0.806, 0.131, 0.764 };
   int lda = 2;
   double B[] = { -0.038, 0.14, -0.31, -0.494, -0.974, -0.396, -0.217, 0.519, -0.656, -0.737, 0.383, -0.03 };
   int ldb = 2;
   double B_expected[] = { 0.0167945280502, 0.00510879322186, 0.0315562985639, 0.0579039669012, -0.0514636821443, 0.116360058046, 0.0192833017545, -0.206389577002, -0.0915450409357, 0.0766481525141, 0.0107002286761, -0.100817314679 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1970) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1970) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { 0.282, -0.433, -0.793, -0.008, -0.999, 0.377, -0.979, 0.421 };
   int lda = 2;
   double B[] = { 0.622, -0.722, 0.605, -0.877, 0.935, -0.906, 0.719, -0.607, 0.022, -0.326, -0.905, 0.323 };
   int ldb = 2;
   double B_expected[] = { 0.0722, 0.0622, 0.1363784, 0.1498572, 0.0906, 0.0935, 0.1159599, 0.1994627, 0.0326, 0.0022, -0.000562, -0.076012 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1971) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1971) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { 0.934, 0.007, -0.958, 0.434, 0.263, 0.776, 0.097, 0.83 };
   int lda = 2;
   double B[] = { -0.405, 0.251, 0.13, 0.388, -0.664, -0.732, -0.779, -0.5, 0.775, -0.299, -0.45, 0.923 };
   int ldb = 2;
   double B_expected[] = { -0.026920633021, -0.0986978374343, -0.020841203536, -0.0443113292253, 0.157683298836, 0.0261984465224, 0.099536165222, 0.0486084240644, 0.127725373746, -0.0161073528761, 0.0406652355905, -0.115957262473 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1972) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1972) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.169, -0.768, -0.529, 0.236, -0.506, 0.691, -0.786, -0.36 };
   int lda = 2;
   double B[] = { 0.289, -0.985, 0.931, 0.652, -0.861, -0.51, -0.753, -0.542, -0.822, 0.174, 0.799, 0.8 };
   int ldb = 2;
   double B_expected[] = { 0.0420376, 0.0627627, -0.0652, 0.0931, 0.0974426, -0.1131425, 0.0542, -0.0753, -0.0785764, -0.0588129, -0.08, 0.0799 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1973) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1973) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { 0.834, 0.53, 0.278, 0.293, 0.66, 0.497, -0.664, 0.429, -0.294, -0.661, 0.52, -0.247, 0.392, -0.227, 0.209, -0.902, 0.843, 0.37 };
   int lda = 3;
   double B[] = { -0.738, 0.166, 0.721, -0.541, -0.963, -0.832, -0.376, -0.718, 0.765, -0.547, 0.451, -0.581 };
   int ldb = 3;
   double B_expected[] = { -0.115188282202, -0.000411685478887, 0.105497263516, -0.0083759187965, 0.124793492766, -0.0594619308146, 0.0499107469, -0.0152598288542, 0.00927285309719, -0.0831454824908, 0.0380996260983, 0.0702216627003 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1974) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1974) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { 0.531, -0.691, 0.801, 0.437, 0.402, 0.788, 0.824, 0.599, -0.362, 0.076, 0.192, 0.229, -0.259, -0.279, 0.79, -0.797, 0.728, 0.397 };
   int lda = 3;
   double B[] = { -0.049, 0.642, 0.36, 0.428, 0.523, -0.612, 0.459, -0.664, 0.328, 0.513, -0.225, 0.273 };
   int ldb = 3;
   double B_expected[] = { -0.0941948813, -0.0387898759, -0.0665271, 0.0399732, 0.0612, 0.0523, 0.1143807788, -0.0091687866, -0.0409059, 0.0308683, -0.0273, -0.0225 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1975) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1975) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { 0.169, -0.092, -0.13, 0.001, 0.573, 0.256, 0.632, -0.09, -0.942, 0.948, 0.595, -0.337, 0.01, -0.786, 0.944, 0.906, -0.832, -0.566 };
   int lda = 3;
   double B[] = { -0.461, -0.112, 0.674, -0.268, -0.286, -0.657, 0.329, 0.91, 0.73, 0.488, -0.363, -0.01 };
   int ldb = 3;
   double B_expected[] = { -0.0634274139095, -0.238252532073, -0.142693434208, -0.0938542376785, -0.0907100858097, -0.0412217911039, -0.333617825793, 0.376288993923, -0.0317846476268, 0.175075250306, -0.125200687799, -0.118937960805 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1976) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1976) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.53, 0.141, 0.235, 0.474, -0.964, -0.441, 0.197, -0.703, 0.942, 0.98, 0.741, 0.499, -0.738, 0.234, -0.27, -0.158, 0.804, -0.878 };
   int lda = 3;
   double B[] = { 0.46, -0.508, 0.918, -0.516, 0.012, -0.451, -0.676, 0.551, -0.38, 0.053, 0.645, 0.785 };
   int ldb = 3;
   double B_expected[] = { 0.0508, 0.046, 0.0739304, 0.0470256, 0.0992176528, 0.0480511088, -0.0551, -0.0676, -0.0419681, 0.0140525, -0.112456492, 0.0121429348 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1977) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1977) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { 0.286, 0.548, 0.637, -0.856, -0.739, 0.307, -0.049, -0.342, -0.39, 0.618, -0.757, -0.453, -0.533, 0.131, 0.431, 0.087, -0.776, -0.439 };
   int lda = 3;
   double B[] = { 0.968, 0.032, 0.013, 0.684, -0.485, 0.613, 0.316, 0.812, -0.459, 0.34, -0.268, -0.565 };
   int ldb = 2;
   double B_expected[] = { -0.126374952238, 0.0484874156039, -0.0755178690743, -0.200973083054, 0.138328459491, -0.0263170966956, 0.00492064241274, -0.0787874374991, 0.00784239970713, 0.0635860998343, -0.0699577429529, -0.00504052726328 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1978) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1978) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.911, 0.645, -0.525, 0.045, -0.654, -0.896, -0.39, 0.419, 0.867, 0.561, -0.842, -0.835, -0.249, -0.384, 0.575, -0.41, 0.105, -0.282 };
   int lda = 3;
   double B[] = { 0.777, 0.361, 0.535, 0.441, 0.508, 0.439, -0.347, 0.131, -0.874, 0.646, 0.917, 0.746 };
   int ldb = 2;
   double B_expected[] = { -0.155796389, 0.112639999, 0.0226368685, 0.111048763, -0.042589, 0.127541, 0.067392, -0.0568415, -0.0646, -0.0874, -0.0746, 0.0917 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1979) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1979) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.519, 0.318, -0.318, 0.73, 0.721, 0.302, -0.604, 0.721, 0.387, 0.673, -0.549, -0.136, 0.101, 0.676, -0.064, -0.659, -0.141, 0.991 };
   int lda = 3;
   double B[] = { -0.856, -0.128, 0.721, -0.511, 0.175, -0.341, 0.832, -0.662, 0.652, -0.939, -0.775, -0.899 };
   int ldb = 2;
   double B_expected[] = { 0.055542329649, 0.130900846188, -0.133470180979, -0.0571415846795, -0.13942012508, 0.0150972236507, 0.0782230770838, 0.0522994181773, -0.00621452256957, -0.0615971232698, 0.0222285648871, 0.258910370231 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1980) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1980) imag");
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
   double alpha[2] = {0, 0.1};
   double A[] = { -0.092, -0.392, 0.108, -0.918, 0.505, -0.974, 0.213, 0.97, -0.465, 0.604, -0.737, -0.578, -0.051, -0.43, 0.066, -0.934, -0.347, 0.157 };
   int lda = 3;
   double B[] = { -0.489, 0.673, -0.232, 0.668, -0.396, -0.569, 0.763, 0.581, 0.117, -0.249, 0.272, -0.832 };
   int ldb = 2;
   double B_expected[] = { -0.0673, -0.0489, -0.0668, -0.0232, 0.0192782, 0.0274626, -0.0721832, 0.140128, 0.0413393162, 0.1110418366, 0.1221321656, 0.2489754256 };
   cblas_ztrsm(order, side, uplo, trans, diag, M, N, alpha, A, lda, B, ldb);
   {
     int i = 0;
     for (i = 0; i < 6; i++) {
       gsl_test_rel(B[2*i], B_expected[2*i], dbleps, "ztrsm(case 1981) real");
       gsl_test_rel(B[2*i+1], B_expected[2*i+1], dbleps, "ztrsm(case 1981) imag");
     };
   };
  };


}
