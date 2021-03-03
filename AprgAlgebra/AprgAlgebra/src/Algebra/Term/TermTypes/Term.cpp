#include "Term.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>

#include <cassert>

using namespace std;

namespace alba
{

namespace algebra
{

Term::Term()
    : m_type(TermType::Empty)
    , m_isSimplified(false)
    , m_baseDataTermPointer(nullptr)
{}

Term::Term(Term const& term)
    : m_type(term.getTermType())
    , m_isSimplified(term.m_isSimplified)
    , m_baseDataTermPointer(nullptr)
{
    resetBaseDataTermPointerBasedFromTerm(term);
}

Term::Term(int const signedValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Constant>(signedValue))
{}

Term::Term(unsigned int const unsignedValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Constant>(unsignedValue))
{}

Term::Term(double const doubleValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Constant>(doubleValue))
{}

Term::Term(AlbaNumber const& number)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Constant>(number))
{}

Term::Term(string const& stringTerm)
    : m_type(TermType::Empty)
    , m_isSimplified(false)    , m_baseDataTermPointer(nullptr)
{
    if(algebra::isOperator(stringTerm))
    {
        m_type=TermType::Operator;
        m_baseDataTermPointer = make_unique<Operator>(stringTerm);
    }
    else if(algebra::isFunction(stringTerm))
    {
        m_type=TermType::Function;
        m_baseDataTermPointer = make_unique<Function>(createFunctionWithEmptyInputExpression(stringTerm));
    }
    else
    {
        m_type=TermType::Variable;
        m_baseDataTermPointer = make_unique<Variable>(stringTerm);
    }
}

Term::Term(Constant const& constant)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Constant>(constant))
{}

Term::Term(Variable const& variable)
    : m_type(TermType::Variable)
    , m_isSimplified(false)
    , m_baseDataTermPointer(nullptr)
{
    m_baseDataTermPointer = make_unique<Variable>(variable);
}

Term::Term(Operator const& operatorTerm)
    : m_type(TermType::Operator)
    , m_isSimplified(false)
    , m_baseDataTermPointer(nullptr)
{
    m_baseDataTermPointer = make_unique<Operator>(operatorTerm);
}

Term::Term(Monomial const& monomial)
    : m_type(TermType::Monomial)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Monomial>(monomial))
{}

Term::Term(Polynomial const& polynomial)
    : m_type(TermType::Polynomial)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Polynomial>(polynomial))
{}

Term::Term(Expression const& expression)
    : m_type(TermType::Expression)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Expression>(expression))
{}

Term::Term(Function const& function)
    : m_type(TermType::Function)
    , m_isSimplified(false)
    , m_baseDataTermPointer(make_unique<Function>(function))
{}

Term& Term::operator=(Term const& term)
{
    m_type = term.m_type;
    m_isSimplified = term.m_isSimplified;
    resetBaseDataTermPointerBasedFromTerm(term);
    return *this;
}

bool Term::operator==(Term const& second) const
{
    bool result(false);
    if(m_type==second.m_type)
    {
        if(m_type==TermType::Empty)
        {
            result=true;
        }
        else if(m_type==TermType::Constant)
        {
            result = getConstantConstReference()==second.getConstantConstReference();
        }
        else if(m_type==TermType::Variable)
        {
            result = getVariableConstReference()==second.getVariableConstReference();
        }
        else if(m_type==TermType::Operator)
        {
            result = getOperatorConstReference()==second.getOperatorConstReference();
        }
        else if(m_type==TermType::Monomial)
        {
            result = getMonomialConstReference()==second.getMonomialConstReference();
        }
        else if(m_type==TermType::Polynomial)
        {
            result = getPolynomialConstReference()==second.getPolynomialConstReference();
        }
        else if(m_type==TermType::Expression)
        {
            result = getExpressionConstReference()==second.getExpressionConstReference();
        }
        else if(m_type==TermType::Function)
        {
            result = getFunctionConstReference()==second.getFunctionConstReference();
        }
    }
    return result;
}

bool Term::operator!=(Term const& second) const
{
    return !(operator==(second));
}

bool Term::operator<(Term const& second) const
{
    bool result(false);
    if(m_type == second.m_type)
    {
        if(m_type==TermType::Empty)
        {
            result=false;
        }
        else if(m_type==TermType::Constant)
        {
            result = getConstantConstReference() < second.getConstantConstReference();
        }
        else if(m_type==TermType::Variable)
        {
            result = getVariableConstReference() < second.getVariableConstReference();
        }
        else if(m_type==TermType::Operator)
        {
            result = getOperatorConstReference() < second.getOperatorConstReference();
        }
        else if(m_type==TermType::Monomial)
        {
            result = getMonomialConstReference() < second.getMonomialConstReference();
        }
        else if(m_type==TermType::Polynomial)
        {
            result = getPolynomialConstReference() < second.getPolynomialConstReference();
        }
        else if(m_type==TermType::Expression)
        {
            result = getExpressionConstReference() < second.getExpressionConstReference();
        }
        else if(m_type==TermType::Function)
        {
            result = getFunctionConstReference() < second.getFunctionConstReference();
        }
    }
    else
    {
        result = getTermTypePriorityValue(m_type) < getTermTypePriorityValue(second.m_type);
    }
    return result;
}

bool Term::isEmpty() const
{
    bool result(false);
    if(m_type==TermType::Empty)
    {
        result = true;
    }
    else if(m_type==TermType::Polynomial)
    {
        result = getPolynomialConstReference().isEmpty();
    }
    else if(m_type==TermType::Expression)
    {
        result = getExpressionConstReference().isEmpty();
    }
    return result;
}

bool Term::isConstant() const
{
    return TermType::Constant == m_type;
}

bool Term::isVariable() const
{
    return TermType::Variable == m_type;
}

bool Term::isOperator() const
{
    return TermType::Operator == m_type;
}

bool Term::isMonomial() const
{
    return TermType::Monomial == m_type;
}

bool Term::isPolynomial() const
{
    return TermType::Polynomial == m_type;
}

bool Term::isExpression() const
{
    return TermType::Expression == m_type;
}

bool Term::isFunction() const
{
    return TermType::Function == m_type;
}

bool Term::isSimplified() const
{
    return m_isSimplified;
}

TermType Term::getTermType() const
{
    return m_type;
}

Constant const& Term::getConstantConstReference() const
{
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant const * const>(m_baseDataTermPointer.get());
}

Variable const& Term::getVariableConstReference() const
{
    assert(m_type==TermType::Variable);
    return *dynamic_cast<Variable const * const>(m_baseDataTermPointer.get());
}

Operator const& Term::getOperatorConstReference() const
{
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator const * const>(m_baseDataTermPointer.get());
}

Monomial const& Term::getMonomialConstReference() const
{
    assert(m_type==TermType::Monomial);
    return *dynamic_cast<Monomial const * const>(m_baseDataTermPointer.get());
}

Polynomial const& Term::getPolynomialConstReference() const
{
    assert(m_type==TermType::Polynomial);
    return *dynamic_cast<Polynomial const * const>(m_baseDataTermPointer.get());
}

Expression const& Term::getExpressionConstReference() const
{
    assert((m_type==TermType::Expression));
    return *dynamic_cast<Expression const * const>(m_baseDataTermPointer.get());
}

Function const& Term::getFunctionConstReference() const
{
    assert((m_type==TermType::Function));
    return *dynamic_cast<Function const * const>(m_baseDataTermPointer.get());
}

AlbaNumber const& Term::getConstantValueConstReference() const
{
    return getConstantConstReference().getNumberConstReference();
}

string Term::getDisplayableString() const
{
    string result;
    if(m_type==TermType::Empty)
    {
        result = "{EmptyTerm}";
    }
    else if(m_type==TermType::Constant)
    {
        result = getConstantConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Variable)
    {
        result = getVariableConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Operator)
    {
        result = getOperatorConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Monomial)
    {
        result = getMonomialConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Polynomial)
    {
        result = getPolynomialConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Expression)
    {
        result = getExpressionConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Function)
    {
        result = getFunctionConstReference().getDisplayableString();
    }
    return result;
}

string Term::getDebugString() const
{
    string result;
    if(m_type==TermType::Constant)
    {
        result = getConstantConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Variable)
    {
        result = getVariableConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Operator)
    {
        result = getOperatorConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Monomial)
    {
        result = getMonomialConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Polynomial)
    {
        result = getPolynomialConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Expression)
    {
        result = getExpressionConstReference().getDebugString();
    }
    else if(m_type==TermType::Function)
    {
        result = getFunctionConstReference().getDebugString();
    }
    result += "{";
    result += getEnumShortString(m_type);
    result += "}";
    return result;
}

Constant & Term::getConstantReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant*>(m_baseDataTermPointer.get());
}

Variable & Term::getVariableReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Variable);
    return *dynamic_cast<Variable*>(m_baseDataTermPointer.get());
}

Operator & Term::getOperatorReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator*>(m_baseDataTermPointer.get());
}

Monomial & Term::getMonomialReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Monomial);
    return *dynamic_cast<Monomial*>(m_baseDataTermPointer.get());
}

Polynomial & Term::getPolynomialReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Polynomial);
    return *dynamic_cast<Polynomial*>(m_baseDataTermPointer.get());
}

Expression & Term::getExpressionReference()
{
    clearSimplifiedFlag();
    assert((m_type==TermType::Expression));
    return *dynamic_cast<Expression*>(m_baseDataTermPointer.get());
}

Function & Term::getFunctionReference()
{
    clearSimplifiedFlag();
    assert((m_type==TermType::Function));
    return *dynamic_cast<Function*>(m_baseDataTermPointer.get());
}

void Term::clear()
{
    m_type=TermType::Empty;
    m_baseDataTermPointer.reset();
    clearSimplifiedFlag();
}

void Term::simplify()
{
    if(!m_isSimplified)
    {
        if(m_type==TermType::Monomial)
        {
            *this = simplifyAndConvertMonomialToSimplestTerm(getMonomialConstReference());
        }
        else if(m_type==TermType::Polynomial)
        {
            *this = simplifyAndConvertPolynomialToSimplestTerm(getPolynomialConstReference());
        }
        else if(m_type==TermType::Expression)
        {
            *this = simplifyAndConvertExpressionToSimplestTerm(getExpressionConstReference());
        }
        else if(m_type==TermType::Function)
        {
            *this = simplifyAndConvertFunctionToSimplestTerm(getFunctionConstReference());
        }
        setAsSimplified();
    }
}

void Term::sort()
{
    if(isPolynomial())
    {
        getPolynomialReference().sortMonomialsWithInversePriority();
    }
    else if(isExpression())
    {
        getExpressionReference().sort();
    }
    clearAllInnerSimplifiedFlags();
}

void Term::setAsSimplified()
{
    m_isSimplified = true;
}

void Term::clearSimplifiedFlag()
{
    m_isSimplified = false;
}

void Term::clearAllInnerSimplifiedFlags()
{
    if(m_type==TermType::Monomial)
    {
        getMonomialReference().clearSimplifiedFlag();
    }
    else if(m_type==TermType::Polynomial)
    {
        getPolynomialReference().clearSimplifiedFlag();
    }
    else if(m_type==TermType::Expression)
    {
        getExpressionReference().clearAllInnerSimplifiedFlags();
    }
    else if(m_type==TermType::Function)
    {
        getFunctionReference().clearAllInnerSimplifiedFlags();
    }
    clearSimplifiedFlag();
}

void Term::resetBaseDataTermPointerBasedFromTerm(Term const& term)
{
    switch(term.getTermType())
    {
    case TermType::Empty:
        break;
    case TermType::Constant:
        m_baseDataTermPointer = make_unique<Constant>(term.getConstantConstReference());
        break;
    case TermType::Variable:
        m_baseDataTermPointer = make_unique<Variable>(term.getVariableConstReference());
        break;
    case TermType::Operator:
        m_baseDataTermPointer = make_unique<Operator>(term.getOperatorConstReference());
        break;
    case TermType::Monomial:
        m_baseDataTermPointer = make_unique<Monomial>(term.getMonomialConstReference());
        break;
    case TermType::Polynomial:
        m_baseDataTermPointer = make_unique<Polynomial>(term.getPolynomialConstReference());
        break;
    case TermType::Expression:
        m_baseDataTermPointer = make_unique<Expression>(term.getExpressionConstReference());
        break;
    case TermType::Function:
        m_baseDataTermPointer = make_unique<Function>(term.getFunctionConstReference());
        break;
    }
}

ostream & operator<<(ostream & out, Term const& term)
{
    out << term.getDisplayableString();
    return out;
}


}

}
