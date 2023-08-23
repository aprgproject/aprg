#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {

// Not: ~a
// Not operators are declared in the class

// And: a & b
Term operator&(Term const& term1, Term const& term2);
Term& operator&=(Term& term1, Term const& term2);

// Or: a | b
Term operator|(Term const& term1, Term const& term2);
Term& operator|=(Term& term1, Term const& term2);

}  // namespace alba::booleanAlgebra
