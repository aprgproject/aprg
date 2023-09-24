#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {

class BaseMutator {
public:
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseMutator() = default;
    BaseMutator() = default;
    BaseMutator(BaseMutator const &) = default;
    BaseMutator(BaseMutator &&) = default;
    BaseMutator &operator=(BaseMutator const &) = default;
    BaseMutator &operator=(BaseMutator &&) = default;
    virtual void mutateTerm(Term &term);
    virtual void mutateConstant(Constant &);
    virtual void mutateVariableTerm(VariableTerm &);
    virtual void mutateExpression(Expression &expression);
};

}  // namespace alba::booleanAlgebra
