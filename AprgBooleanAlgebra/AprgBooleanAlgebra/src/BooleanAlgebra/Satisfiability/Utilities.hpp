#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {
using SatisfiabilityTerm = VariableTerms;
using SatisfiabilityTerms = std::vector<VariableTerms>;
SatisfiabilityTerms getSatisfiabilityTerms(Term const& term);
SatisfiabilityTerms getSatisfiabilityTerms(Expression const& expression);
int getSatisfiabilityLevel(SatisfiabilityTerms const& satTerms);
}  // namespace alba::booleanAlgebra
