#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTerm.hpp>
#include <BooleanAlgebra/Term/TermTypes/Constant.hpp>
#include <BooleanAlgebra/Term/TermTypes/Expression.hpp>
#include <BooleanAlgebra/Term/TermTypes/Operator.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermType.hpp>
#include <BooleanAlgebra/Term/TermTypes/VariableTerm.hpp>

#include <memory>
#include <string>
#include <vector>

namespace alba::booleanAlgebra {

class Term : public BaseTerm {
public:
    using BaseTermDataPointer = std::unique_ptr<BaseTermData>;

    Term();
    Term(TermType const type, bool const isSimplified, BaseTermDataPointer&& m_baseTermDataPointer);  // for move
    explicit Term(bool const boolValue);
    explicit Term(char const* const characterString);
    explicit Term(std::string const& stringAsParameter);
    explicit Term(Constant const& constant);
    explicit Term(VariableTerm const& variableTerm);
    explicit Term(Operator const& operatorTerm);
    explicit Term(Expression const& expression);

    // rule of five or six
    ~Term() = default;
    Term(Term const& term);
    Term& operator=(Term const& term);
    Term(Term&& term) = default;
    Term& operator=(Term&& term) = default;

    bool operator==(Term const& second) const;
    bool operator!=(Term const& second) const;
    bool operator<(Term const& second) const;

    Term operator~() const;

    bool isEmpty() const;
    bool isConstant() const;
    bool isVariableTerm() const;
    bool isOperator() const;
    bool isExpression() const;
    bool isSimplified() const;

    TermType getTermType() const;
    Constant const& getConstantConstReference() const;
    VariableTerm const& getVariableTermConstReference() const;
    Operator const& getOperatorConstReference() const;
    Expression const& getExpressionConstReference() const;
    bool getBooleanValue() const;
    std::string getDebugString() const;

    Constant& getConstantReference();
    VariableTerm& getVariableTermReference();
    Operator& getOperatorReference();
    Expression& getExpressionReference();

    BaseTermUniquePointer createBasePointerByMove();

    void clear();
    void simplify();
    void sort();
    void negate();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    static BaseTermDataPointer createANewPointerFrom(Term const& term);
    void initializeBasedOnString(std::string const& stringAsParameter);

    friend std::ostream& operator<<(std::ostream& out, Term const& term);

    TermType m_type;
    bool m_isSimplified;
    BaseTermDataPointer m_baseTermDataPointer;
};

using Terms = std::vector<Term>;

}  // namespace alba::booleanAlgebra
