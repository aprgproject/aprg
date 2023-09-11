/* linalg/bidiag.c
 * 
 * Copyright (C) 2001, 2007 Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/* Factorise a matrix A into
 *
 * A = U B V^T
 *
 * where U and V are orthogonal and B is upper bidiagonal. 
 *
 * On exit, B is stored in the diagonal and first superdiagonal of A.
 *
 * U is stored as a packed set of Householder transformations in the
 * lower triangular part of the input matrix below the diagonal.
 *
 * V is stored as a packed set of Householder transformations in the
 * upper triangular part of the input matrix above the first
 * superdiagonal.
 *
 * The full matrix for U can be obtained as the product
 *
 *       U = U_1 U_2 .. U_N
 *
 * where 
 *
 *       U_i = (I - tau_i * u_i * u_i')
 *
 * and where u_i is a Householder vector
 *
 *       u_i = [0, .. , 0, 1, A(i+1,i), A(i+3,i), .. , A(M,i)]
 *
 * The full matrix for V can be obtained as the product
 *
 *       V = V_1 V_2 .. V_(N-2)
 *
 * where 
 *
 *       V_i = (I - tau_i * v_i * v_i')
 *
 * and where v_i is a Householder vector
 *
 *       v_i = [0, .. , 0, 1, A(i,i+2), A(i,i+3), .. , A(i,N)]
 *
 * See Golub & Van Loan, "Matrix Computations" (3rd ed), Algorithm 5.4.2 
 *
 * Note: this description uses 1-based indices. The code below uses
 * 0-based indices 
 */

#include <config.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#include <gsl/gsl_linalg.h>

int 
gsl_linalg_bidiag_decomp (gsl_matrix * A, gsl_vector * tau_U, gsl_vector * tau_V)  
{
  if (A->size1 < A->size2)
    {
      GSL_ERROR ("bidiagonal decomposition requires M>=N", GSL_EBADLEN);
    }
  else if (tau_U->size  != A->size2)
    {
      GSL_ERROR ("size of tau_U must be N", GSL_EBADLEN);
    }
  else if (tau_V->size + 1 != A->size2)
    {
      GSL_ERROR ("size of tau_V must be (N - 1)", GSL_EBADLEN);
    }
  else
    {
      const size_t M = A->size1;
      const size_t N = A->size2;
      gsl_vector * tmp = gsl_vector_alloc(M);
      size_t j = 0;
  
      for (j = 0 ; j < N; j++)
        {
          /* apply Householder transformation to current column */
          gsl_vector_view v = gsl_matrix_subcolumn(A, j, j, M - j);
          double tau_j = gsl_linalg_householder_transform (&v.vector);

          /* apply the transformation to the remaining columns */
          if (j + 1 < N)
            {
              gsl_matrix_view m = gsl_matrix_submatrix (A, j, j + 1, M - j, N - j - 1);
              gsl_vector_view work = gsl_vector_subvector(tau_U, j, N - j - 1);
              double * ptr = gsl_vector_ptr(&v.vector, 0);
              double tmp = *ptr;

              *ptr = 1.0;
              gsl_linalg_householder_left (tau_j, &v.vector, &m.matrix, &work.vector);
              *ptr = tmp;
            }

          gsl_vector_set (tau_U, j, tau_j);            

          /* apply Householder transformation to current row */
          if (j + 1 < N)
            {
              v = gsl_matrix_subrow (A, j, j + 1, N - j - 1);
              tau_j = gsl_linalg_householder_transform (&v.vector);
              
              /* apply the transformation to the remaining rows */
              if (j + 1 < M)
                {
                  gsl_matrix_view m = gsl_matrix_submatrix (A, j + 1, j + 1, M - j - 1, N - j - 1);
                  gsl_vector_view work = gsl_vector_subvector(tmp, 0, M - j - 1);
                  gsl_linalg_householder_right (tau_j, &v.vector, &m.matrix, &work.vector);
                }

              gsl_vector_set (tau_V, j, tau_j);
            }
        }

      gsl_vector_free(tmp);

      return GSL_SUCCESS;
    }
}

/* Form the orthogonal matrices U, V, diagonal d and superdiagonal sd
   from the packed bidiagonal matrix A */

int
gsl_linalg_bidiag_unpack (const gsl_matrix * A, 
                          const gsl_vector * tau_U, 
                          gsl_matrix * U, 
                          const gsl_vector * tau_V,
                          gsl_matrix * V,
                          gsl_vector * diag, 
                          gsl_vector * superdiag)
{
  const size_t M = A->size1;
  const size_t N = A->size2;

  const size_t K = GSL_MIN(M, N);

  if (M < N)
    {
      GSL_ERROR ("matrix A must have M >= N", GSL_EBADLEN);
    }
  else if (tau_U->size != K)
    {
      GSL_ERROR ("size of tau must be MIN(M,N)", GSL_EBADLEN);
    }
  else if (tau_V->size + 1 != K)
    {
      GSL_ERROR ("size of tau must be MIN(M,N) - 1", GSL_EBADLEN);
    }
  else if (U->size1 != M || U->size2 != N)
    {
      GSL_ERROR ("size of U must be M x N", GSL_EBADLEN);
    }
  else if (V->size1 != N || V->size2 != N)
    {
      GSL_ERROR ("size of V must be N x N", GSL_EBADLEN);
    }
  else if (diag->size != K)
    {
      GSL_ERROR ("size of diagonal must match size of A", GSL_EBADLEN);
    }
  else if (superdiag->size + 1 != K)
    {
      GSL_ERROR ("size of subdiagonal must be (diagonal size - 1)", GSL_EBADLEN);
    }
  else
    {
      size_t i = 0;
      size_t j = 0;

      /* Copy diagonal into diag */

      for (i = 0; i < N; i++)
        {
          double Aii = gsl_matrix_get (A, i, i);
          gsl_vector_set (diag, i, Aii);
        }

      /* Copy superdiagonal into superdiag */

      for (i = 0; i < N - 1; i++)
        {
          double Aij = gsl_matrix_get (A, i, i+1);
          gsl_vector_set (superdiag, i, Aij);
        }

      /* Initialize V to the identity */

      gsl_matrix_set_identity (V);

      for (i = N - 1; i-- > 0;)
        {
          /* Householder row transformation to accumulate V */
          gsl_vector_const_view h = gsl_matrix_const_subrow (A, i, i + 1, N - i - 1);
          double ti = gsl_vector_get (tau_V, i);
          gsl_matrix_view m = gsl_matrix_submatrix (V, i + 1, i + 1, N- i - 1, N - i - 1);
          gsl_vector_view work = gsl_matrix_subrow(U, 0, 0, N - i - 1);
          double * ptr = gsl_vector_ptr((gsl_vector *) &h.vector, 0);
          double tmp = *ptr;

          *ptr = 1.0;
          gsl_linalg_householder_left (ti, &h.vector, &m.matrix, &work.vector);
          *ptr = tmp;
        }

      /* Initialize U to the identity */

      gsl_matrix_set_identity (U);

      for (j = N; j-- > 0;)
        {
          /* Householder column transformation to accumulate U */
          gsl_vector_const_view h = gsl_matrix_const_subcolumn (A, j, j, M - j);
          double tj = gsl_vector_get (tau_U, j);
          gsl_matrix_view m = gsl_matrix_submatrix (U, j, j, M - j, N - j);
          
          gsl_linalg_householder_hm (tj, &h.vector, &m.matrix);
        }

      return GSL_SUCCESS;
    }
}

int
gsl_linalg_bidiag_unpack2 (gsl_matrix * A, 
                           gsl_vector * tau_U, 
                           gsl_vector * tau_V,
                           gsl_matrix * V)
{
  const size_t M = A->size1;
  const size_t N = A->size2;

  const size_t K = GSL_MIN(M, N);

  if (M < N)
    {
      GSL_ERROR ("matrix A must have M >= N", GSL_EBADLEN);
    }
  else if (tau_U->size != K)
    {
      GSL_ERROR ("size of tau must be MIN(M,N)", GSL_EBADLEN);
    }
  else if (tau_V->size + 1 != K)
    {
      GSL_ERROR ("size of tau must be MIN(M,N) - 1", GSL_EBADLEN);
    }
  else if (V->size1 != N || V->size2 != N)
    {
      GSL_ERROR ("size of V must be N x N", GSL_EBADLEN);
    }
  else
    {
      size_t i = 0;
      size_t j = 0;

      /* Initialize V to the identity */

      gsl_matrix_set_identity (V);

      for (i = N - 1; i-- > 0;)
        {
          /* Householder row transformation to accumulate V */
          gsl_vector_const_view r = gsl_matrix_const_row (A, i);
          gsl_vector_const_view h = 
            gsl_vector_const_subvector (&r.vector, i + 1, N - (i+1));
          
          double ti = gsl_vector_get (tau_V, i);
          
          gsl_matrix_view m = 
            gsl_matrix_submatrix (V, i + 1, i + 1, N-(i+1), N-(i+1));
          
          gsl_linalg_householder_hm (ti, &h.vector, &m.matrix);
        }

      /* Copy superdiagonal into tau_v */

      for (i = 0; i < N - 1; i++)
        {
          double Aij = gsl_matrix_get (A, i, i+1);
          gsl_vector_set (tau_V, i, Aij);
        }

      /* Allow U to be unpacked into the same memory as A, copy
         diagonal into tau_U */

      for (j = N; j-- > 0;)
        {
          /* Householder column transformation to accumulate U */
          double tj = gsl_vector_get (tau_U, j);
          double Ajj = gsl_matrix_get (A, j, j);
          gsl_matrix_view m = gsl_matrix_submatrix (A, j, j, M-j, N-j);

          gsl_vector_set (tau_U, j, Ajj);
          gsl_linalg_householder_hm1 (tj, &m.matrix);
        }

      return GSL_SUCCESS;
    }
}


int
gsl_linalg_bidiag_unpack_B (const gsl_matrix * A, 
                            gsl_vector * diag, 
                            gsl_vector * superdiag)
{
  const size_t M = A->size1;
  const size_t N = A->size2;

  const size_t K = GSL_MIN(M, N);

  if (diag->size != K)
    {
      GSL_ERROR ("size of diagonal must match size of A", GSL_EBADLEN);
    }
  else if (superdiag->size + 1 != K)
    {
      GSL_ERROR ("size of subdiagonal must be (matrix size - 1)", GSL_EBADLEN);
    }
  else
    {
      size_t i = 0;

      /* Copy diagonal into diag */

      for (i = 0; i < K; i++)
        {
          double Aii = gsl_matrix_get (A, i, i);
          gsl_vector_set (diag, i, Aii);
        }

      /* Copy superdiagonal into superdiag */

      for (i = 0; i < K - 1; i++)
        {
          double Aij = gsl_matrix_get (A, i, i+1);
          gsl_vector_set (superdiag, i, Aij);
        }

      return GSL_SUCCESS;
    }
}
