#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba::booleanAlgebra {

template <typename DataType>
class BaseRetriever {
public:
    BaseRetriever() = default;
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseRetriever() = default;
    BaseRetriever(BaseRetriever const&) = default;
    BaseRetriever(BaseRetriever&&) noexcept = default;
    BaseRetriever& operator=(BaseRetriever const&) = default;
    BaseRetriever& operator=(BaseRetriever&&) noexcept = default;

    virtual void retrieveFromTerm(Term const& term) {
        if (term.isConstant()) {
            retrieveFromConstant(term.getConstantConstReference());
        } else if (term.isVariableTerm()) {
            retrieveFromVariableTerm(term.getVariableTermConstReference());
        } else if (term.isExpression()) {
            retrieveFromExpression(term.getExpressionConstReference());
        }
    }

    virtual void retrieveFromConstant(Constant const&) {}
    virtual void retrieveFromVariableTerm(VariableTerm const&) {}

    virtual void retrieveFromExpression(Expression const& expression) {
        for (WrappedTerm const& wrappedTerm : expression.getWrappedTerms()) {
            retrieveFromTerm(getTermConstReferenceFromUniquePointer(wrappedTerm.baseTermPointer));
        }
    }

    [[nodiscard]] DataType const& getSavedData() const { return m_savedData; }
    DataType& getSavedDataReference() { return m_savedData; }

protected:
    DataType m_savedData;
};

}  // namespace alba::booleanAlgebra
