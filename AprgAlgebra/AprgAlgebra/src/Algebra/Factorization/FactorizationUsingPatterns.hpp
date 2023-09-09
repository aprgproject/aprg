#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba::algebra::Factorization {
void factorizeUsingPatternsIfPossible(Polynomials& result, Polynomial const& polynomial);
void factorizeDifferenceOfSquaresIfPossible(Polynomials& result, Polynomial const& polynomial);
void factorizeDifferenceOfCubesIfPossible(Polynomials& result, Polynomial const& polynomial);
void factorizeSumOfCubesIfPossible(Polynomials& result, Polynomial const& polynomial);
void addFactorsOfDifferenceOfSquares(Polynomials& result, Polynomial const& polynomial);
void addFactorsOfDifferenceOfCubes(Polynomials& result, Polynomial const& polynomial);
void addFactorsOfSumOfCubes(Polynomials& result, Polynomial const& polynomial);
Polynomials factorizeUsingPatterns(Polynomial const& polynomial);
bool isDifferenceOfSquares(Polynomial const& polynomial);
bool isDifferenceOfCubes(Polynomial const& polynomial);
bool isSumOfCubes(Polynomial const& polynomial);
}  // namespace alba::algebra::Factorization
