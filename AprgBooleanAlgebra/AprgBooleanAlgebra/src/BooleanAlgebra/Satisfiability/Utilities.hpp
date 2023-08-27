#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {

using SatisfiabilityTerm = VariableTerms;
using SatisfiabilityTerms = std::vector<VariableTerms>;

int getSatisfiabilityLevel(SatisfiabilityTerms const& satTerms);
SatisfiabilityTerms getSatisfiabilityTerms(Term const& term);
SatisfiabilityTerms getSatisfiabilityTerms(Expression const& expression);

}  // namespace alba::booleanAlgebra
