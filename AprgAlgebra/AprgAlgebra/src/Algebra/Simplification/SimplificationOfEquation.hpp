#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba::algebra::Simplification {

class SimplificationOfEquation {
public:
    explicit SimplificationOfEquation(Equation const& equation);
    explicit SimplificationOfEquation(Equation&& equation);
    [[nodiscard]] Equation getEquation() const;
    void simplify();

private:
    static void simplifyLeftHandSideAndRightHandSide(Term& leftHandSide, Term& rightHandSide);
    static void raiseLeftHandSideAndRightHandSideToPowerIfLogarithmic(Term& leftHandSide, Term& rightHandSide);
    static void negateTermIfNeeded(Term& leftHandSide, std::string& equationOperatorString);
    static void removeExponentIfNeeded(Term& leftHandSide);
    static void completeExpressionWithFractionalExponentsIfNeeded(Term& leftHandSide);
    static void removeCommonConstant(Term& leftHandSide);
    static void simplifyLeftHandSide(Term& term);
    static Term getNewCombinedTerm(Term const& leftHandSide, Term const& rightHandSide);
    static bool areTheSignsOfTwoTermsDifferent(TermWithDetails const& firstTerm, TermWithDetails const& secondTerm);
    Equation m_equation;
};

}  // namespace alba::algebra::Simplification
