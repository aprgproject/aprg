/* cdf/exponential.c
 * 
 * Copyright (C) 2003, 2007 Brian Gough
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

#include <config.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cdf.h>

/* The exponential distribution has the form

   p(x) dx = exp(-x/mu) dx/mu

   for x = 0 ... +infty */

double
gsl_cdf_exponential_P (const double x, const double mu)
{
  if (x < 0)
    {
      return 0;
    }
  
    
      double P = -expm1 (-x / mu);

      return P;
   
}

double
gsl_cdf_exponential_Q (const double x, const double mu)
{
  if (x < 0)
    {
      return 1;
    }
  
    
      double Q = exp (-x / mu);

      return Q;
   
}
