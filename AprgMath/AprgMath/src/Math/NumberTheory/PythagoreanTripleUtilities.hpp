#pragma once

#include <Math/Types.hpp>

namespace alba::math {

using PythagoreanTriple = std::tuple<UnsignedInteger, UnsignedInteger, UnsignedInteger>;  //{a,b,c}

PythagoreanTriple getNewPythagoreanTripleUsingMultiplier(
    PythagoreanTriple const& triple, UnsignedInteger const multiplier);

PythagoreanTriple getPrimitivePythagoreanTripleUsingEuclidFormula(
    UnsignedInteger const seedValueM, UnsignedInteger const seedValueN);

bool isPythagoreanTriple(PythagoreanTriple const& triple);
bool isPrimitive(PythagoreanTriple const& triple);

}  // namespace alba::math
