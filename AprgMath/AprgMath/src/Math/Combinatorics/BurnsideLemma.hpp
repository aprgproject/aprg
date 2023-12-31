#pragma once

#include <Math/Types.hpp>

namespace alba::math {

UnsignedInteger getNumberOfSymmetricCombinationsUsingBurnsideLemma(
    UnsignedInteger const numberOfWaysToChangePosition,
    UnsignedIntegerBinaryFunction const& getNumberOfCombinationsFunction);

UnsignedInteger getNumberOfCombinationsOfAPearlNecklace(
    UnsignedInteger const numberOfPearls, UnsignedInteger const& numberOfColors);

}  // namespace alba::math
