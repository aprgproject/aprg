#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <vector>

namespace alba::algebra {

Terms getLagrangeMultipliers(
    Term const& term, stringHelper::strings const& coordinateNames, Terms const& lagrangeFunctions);
Term getTermWithLagrangeFunctions(
    Term const& term, Terms const& lagrangeFunctions, stringHelper::strings const& lagrangeMultiplierNames);
stringHelper::strings getLagrangeMultiplierNames(int const size);
std::string getLagrangeMultiplierName(int const index);

void calculateLagrangeEquations(
    Equations& lagrangeEquations, Term const& termWithLagrangeFunctions, stringHelper::strings const& coordinateNames,
    stringHelper::strings const& lagrangeMultiplierNames);

}  // namespace alba::algebra
