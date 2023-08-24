#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

struct DetailsForDefiniteIntegralWithValues {
    std::string variableName;
    AlbaNumber lowerEnd;
    AlbaNumber higherEnd;
};

using DetailsForDefiniteIntegralsWithValues = std::vector<DetailsForDefiniteIntegralWithValues>;

}  // namespace alba::algebra
