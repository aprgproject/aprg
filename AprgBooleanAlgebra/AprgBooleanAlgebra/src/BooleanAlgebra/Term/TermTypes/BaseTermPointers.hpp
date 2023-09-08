#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTerm.hpp>

#include <memory>

namespace alba::booleanAlgebra {
using BaseTermUniquePointer = std::unique_ptr<BaseTerm>;
}  // namespace alba::booleanAlgebra
