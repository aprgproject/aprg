#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <vector>

namespace alba::algebra {

void calculateLagrangeEquations(
    Equations& lagrangeEquations, Term const& termWithLagrangeFunctions, stringHelper::strings const& coordinateNames,
    stringHelper::strings const& lagrangeMultiplierNames);

Term getTermWithLagrangeFunctions(
    Term const& term, Terms const& lagrangeFunctions, stringHelper::strings const& lagrangeMultiplierNames);

Terms getLagrangeMultipliers(
    Term const& term, stringHelper::strings const& coordinateNames, Terms const& lagrangeFunctions);

std::string getLagrangeMultiplierName(int const index);
stringHelper::strings getLagrangeMultiplierNames(int const size);

}  // namespace alba::algebra
