#pragma once

#include <Algebra/Equation/EquationOperator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

class Equation {
public:
    Equation() = default;
    Equation(Term const& leftHandTerm, std::string const& equationOperator, Term const& rightHandTerm);
    // rule of zero
    bool operator==(Equation const& second) const;
    bool operator!=(Equation const& second) const;
    bool operator<(Equation const& second) const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isEquationSatisfied() const;
    [[nodiscard]] EquationOperator const& getEquationOperator() const;
    [[nodiscard]] Term const& getLeftHandTerm() const;
    [[nodiscard]] Term const& getRightHandTerm() const;
    Term& getLeftHandTermReference();
    Term& getRightHandTermReference();
    void simplify();

private:
    friend std::ostream& operator<<(std::ostream& out, Equation const& equation);
    EquationOperator m_equationOperator;
    Term m_leftHandTerm;
    Term m_rightHandTerm;
};

using Equations = std::vector<Equation>;

}  // namespace alba::algebra
