#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {
Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term convertExpressionToSimplestTerm(Expression const& expression);
}  // namespace alba::booleanAlgebra
