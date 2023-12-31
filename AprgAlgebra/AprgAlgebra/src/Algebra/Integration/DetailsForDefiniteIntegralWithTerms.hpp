#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

struct DetailsForDefiniteIntegralWithTerms {
    std::string variableName;
    Term lowerEnd;
    Term higherEnd;
};

using DetailsForDefiniteIntegralsWithTerms = std::vector<DetailsForDefiniteIntegralWithTerms>;

}  // namespace alba::algebra
