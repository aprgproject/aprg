#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

void accumulateAndDoOperationOnTermDetails(
    Term& combinedTerm, OperatorLevel const operatorLevel, TermWithDetails const& termWithDetails);

void accumulateTermsForAdditionAndSubtraction(Term& combinedTerm, TermsWithDetails const& termsToCombine);
void accumulateTermsForMultiplicationAndDivision(Term& combinedTerm, TermsWithDetails const& termsToCombine);
void accumulateTermsForRaiseToPower(Term& combinedTerm, TermsWithDetails const& termsToCombine);

}  // namespace alba::algebra
