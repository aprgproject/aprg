#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class BaseMutator {
public:
    BaseMutator() = default;
    virtual ~BaseMutator() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseMutator(BaseMutator const &) = default;
    BaseMutator(BaseMutator &&) noexcept = default;
    BaseMutator &operator=(BaseMutator const &) = default;
    BaseMutator &operator=(BaseMutator &&) noexcept = default;
    virtual void mutateEquation(Equation &equation);
    virtual void mutateTerm(Term &term);
    virtual void mutateConstant(Constant &);
    virtual void mutateVariable(Variable &);
    virtual void mutateMonomial(Monomial &);
    virtual void mutatePolynomial(Polynomial &polynomial);
    virtual void mutateExpression(Expression &expression);
    virtual void mutateFunction(Function &functionObject);
};

}  // namespace alba::algebra
