#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra::Simplification {

void simplifyTermWithOuterOrAndInnerAnd(Term& term);
void simplifyTermWithOuterAndAndInnerOr(Term& term);
void simplifyByQuineMcKluskey(Term& term);

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
    WrappedTerms& newWrappedTerms, OperatorLevel& mainOperatorLevel, WrappedTerms const& oldWrappedTerms);

void combineComplementaryTerms(Terms& termsToCombine, OperatorLevel const operatorLevel);
void combineTermsByCheckingCommonFactor(Terms& termsToCombine, OperatorLevel const operatorLevel);

void distributeTermsIfNeeded(
    Term& outputTerm, Terms const& inputTerms, OperatorLevel const outerOperation, OperatorLevel const innerOperation);

void retrieveTargetOperations(OperatorLevel& targetOuter, OperatorLevel& targetInner);

Term combineTwoTermsByCheckingCommonFactorIfPossible(
    Term const& term1, Term const& term2, OperatorLevel const operatorLevel);

Terms createUniqueTerms(WrappedTerms const& terms);

}  // namespace alba::booleanAlgebra::Simplification
