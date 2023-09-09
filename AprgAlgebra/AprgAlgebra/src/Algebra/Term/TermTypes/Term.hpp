#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Algebra/Term/TermTypes/Constant.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>
#include <Algebra/Term/TermTypes/Operator.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Algebra/Term/TermTypes/TermType.hpp>
#include <Algebra/Term/TermTypes/Variable.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <memory>
#include <string>
#include <vector>

namespace alba::algebra {

class Term : public BaseTerm {
public:
    using BaseTermDataPointer = std::unique_ptr<BaseTermData>;
    Term();
    Term(TermType const type, bool const isSimplified, BaseTermDataPointer&& m_baseTermDataPointer);  // for move
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    template <typename ArithmeticType, typename = std::enable_if_t<typeHelper::isArithmeticType<ArithmeticType>()>>
    Term(ArithmeticType const value) : Term(AlbaNumber(value)) {}
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    // enabled via a type template parameter
    // rule of five or six
    ~Term() override = default;
    Term(Term&& term) = default;
    Term& operator=(Term&& term) = default;
    Term(AlbaNumber const& number);
    Term(char const* const characterString);
    Term(std::string const& stringAsParameter);
    Term(Constant const& constant);
    Term(Variable const& variable);
    Term(Operator const& operatorTerm);
    Term(Monomial const& monomial);
    Term(Polynomial const& polynomial);
    Term(Expression const& expression);
    Term(Function const& function);
    Term(Term const& term);
    Term& operator=(Term const& term);
    bool operator==(Term const& second) const;
    bool operator!=(Term const& second) const;
    bool operator<(Term const& second) const;
    [[nodiscard]] AlbaNumber const& getAsNumber() const;
    [[nodiscard]] Constant const& getAsConstant() const;
    [[nodiscard]] Expression const& getAsExpression() const;
    [[nodiscard]] Function const& getAsFunction() const;
    [[nodiscard]] Monomial const& getAsMonomial() const;
    [[nodiscard]] Operator const& getAsOperator() const;
    [[nodiscard]] Polynomial const& getAsPolynomial() const;
    [[nodiscard]] TermType getTermType() const;
    [[nodiscard]] Variable const& getAsVariable() const;
    [[nodiscard]] std::string getDebugString() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isConstant() const;
    [[nodiscard]] bool isVariable() const;
    [[nodiscard]] bool isOperator() const;
    [[nodiscard]] bool isMonomial() const;
    [[nodiscard]] bool isPolynomial() const;
    [[nodiscard]] bool isExpression() const;
    [[nodiscard]] bool isFunction() const;
    [[nodiscard]] bool isSimplified() const;
    void clear();
    void simplify();
    void sort();
    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();
    BaseTermUniquePointer createBasePointerByMove();
    Constant& getAsConstantReference();
    Expression& getAsExpressionReference();
    Function& getAsFunctionReference();
    Monomial& getAsMonomialReference();
    Operator& getAsOperatorReference();
    Polynomial& getAsPolynomialReference();
    Variable& getAsVariableReference();

private:
    static BaseTermDataPointer createANewDataPointerFrom(Term const& term);
    void initializeBasedOnString(std::string const& stringAsParameter);
    friend std::ostream& operator<<(std::ostream& out, Term const& term);
    TermType m_type;
    bool m_isSimplified;
    BaseTermDataPointer m_baseTermDataPointer;
};

using Terms = std::vector<Term>;

}  // namespace alba::algebra
