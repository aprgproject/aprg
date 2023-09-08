#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {
void accumulateTerms(Term& combinedTerm, Terms const& termsToCombine, OperatorLevel const operatorLevel);
void accumulateTermsWithAndOperation(Term& combinedTerm, Terms const& termsToCombine);
void accumulateTermsWithOrOperation(Term& combinedTerm, Terms const& termsToCombine);
}  // namespace alba::booleanAlgebra
