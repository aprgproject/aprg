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
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    Term(bool const boolValue);
    Term(char const* const characterString);
    Term(std::string const& stringAsParameter);
    Term(Constant const& constant);
    Term(VariableTerm const& variableTerm);
    Term(Operator const& operatorTerm);
    Term(Expression const& expression);
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    // rule of five or six
    ~Term() override = default;
    Term(Term const& term);
    Term(Term&& term) noexcept = default;
    Term& operator=(Term const& term);
    Term& operator=(Term&& term) noexcept = default;
    Term operator~() const;
    bool operator==(Term const& second) const;
    bool operator!=(Term const& second) const;
    bool operator<(Term const& second) const;
    [[nodiscard]] Constant const& getConstantConstReference() const;
    [[nodiscard]] Expression const& getExpressionConstReference() const;
    [[nodiscard]] Operator const& getOperatorConstReference() const;
    [[nodiscard]] TermType getTermType() const;
    [[nodiscard]] VariableTerm const& getVariableTermConstReference() const;
    [[nodiscard]] std::string getDebugString() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isConstant() const;
    [[nodiscard]] bool isVariableTerm() const;
    [[nodiscard]] bool isOperator() const;
    [[nodiscard]] bool isExpression() const;
    [[nodiscard]] bool isSimplified() const;
    [[nodiscard]] bool getBooleanValue() const;
    void clear();
    void simplify();
    void sort();
    void negate();
    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();
    BaseTermUniquePointer createBasePointerByMove();
    Constant& getConstantReference();
    Expression& getExpressionReference();
    Operator& getOperatorReference();
    VariableTerm& getVariableTermReference();

private:
    void initializeBasedOnString(std::string const& stringAsParameter);
    static BaseTermDataPointer createANewPointerFrom(Term const& term);
    friend std::ostream& operator<<(std::ostream& out, Term const& term);
    TermType m_type;
    bool m_isSimplified;
    BaseTermDataPointer m_baseTermDataPointer;
};

using Terms = std::vector<Term>;

}  // namespace alba::booleanAlgebra
