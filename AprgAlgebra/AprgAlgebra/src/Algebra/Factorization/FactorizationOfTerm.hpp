#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra::Factorization {

Terms factorizeTerm(Term const& term);
Terms factorizeTerms(Terms const& terms);

}  // namespace alba
