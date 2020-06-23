#pragma once

#include <Equation/Term/Constant.hpp>
#include <Equation/Term/Expression.hpp>
#include <Equation/Term/Monomial.hpp>
#include <Equation/Term/Polynomial.hpp>
#include <Equation/Term/Term.hpp>
#include <Equation/Term/Variable.hpp>

namespace alba
{

namespace equation
{

//Unary plus: +a
Term operator+(Constant const& constant);
Term operator+(Variable const& variable);
Term operator+(Monomial const& monomial);
Term operator+(Polynomial const& polynomial);
Term operator+(Expression const& expression);
Term operator+(Function const& functionAsParameter);
Term operator+(Term const& term);

//Unary minus: -a
Term operator-(Constant const& constant);
Term operator-(Variable const& variable);
Term operator-(Monomial const& monomial);
Term operator-(Polynomial const& polynomial);
Term operator-(Expression const& expression);
Term operator-(Function const& functionAsParameter);
Term operator-(Term const& term);

//Addition: a + b
Term operator+(Constant const& constant1, Constant const& constant2);
Term operator+(Constant const& constant, Variable const& variable);
Term operator+(Constant const& constant, Monomial const& monomial);
Term operator+(Constant const& constant, Polynomial const& polynomial);
Term operator+(Constant const& constant, Expression const& expression);
Term operator+(Constant const& constant, Function const& functionAsParameter);
Term operator+(Variable const& variable, Constant const& constant);
Term operator+(Variable const& variable1, Variable const& variable2);
Term operator+(Variable const& variable, Monomial const& monomial);
Term operator+(Variable const& variable, Polynomial const& polynomial);
Term operator+(Variable const& variable, Expression const& expression);
Term operator+(Variable const& variable, Function const& functionAsParameter);
Term operator+(Monomial const& monomial, Constant const& constant);
Term operator+(Monomial const& monomial, Variable const& variable);
Term operator+(Monomial const& monomial1, Monomial const& monomial2);
Term operator+(Monomial const& monomial, Polynomial const& polynomial);
Term operator+(Monomial const& monomial, Expression const& expression);
Term operator+(Monomial const& monomial, Function const& functionAsParameter);
Term operator+(Polynomial const& polynomial, Constant const& constant);
Term operator+(Polynomial const& polynomial, Variable const& variable);
Term operator+(Polynomial const& polynomial, Monomial const& monomial);
Term operator+(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator+(Polynomial const& polynomial, Expression const& expression);
Term operator+(Polynomial const& polynomial, Function const& functionAsParameter);
Term operator+(Expression const& expression, Constant const& constant);
Term operator+(Expression const& expression, Variable const& variable);
Term operator+(Expression const& expression, Monomial const& monomial);
Term operator+(Expression const& expression, Polynomial const& polynomial);
Term operator+(Expression const& expression1, Expression const& expression2);
Term operator+(Expression const& expression, Function const& functionAsParameter);
Term operator+(Function const& functionAsParameter, Constant const& constant);
Term operator+(Function const& functionAsParameter, Variable const& variable);
Term operator+(Function const& functionAsParameter, Monomial const& monomial);
Term operator+(Function const& functionAsParameter, Polynomial const& polynomial);
Term operator+(Function const& functionAsParameter, Expression const& expression);
Term operator+(Function const& function1, Function const& function2);
Term operator+(Term const& term1, Term const& term2);

//Subtraction: a - b
Term operator-(Constant const& constant1, Constant const& constant2);
Term operator-(Constant const& constant, Variable const& variable);
Term operator-(Constant const& constant, Monomial const& monomial);
Term operator-(Constant const& constant, Polynomial const& polynomial);
Term operator-(Constant const& constant, Expression const& expression);
Term operator-(Constant const& constant, Function const& functionAsParameter);
Term operator-(Variable const& variable, Constant const& constant);
Term operator-(Variable const& variable1, Variable const& variable2);
Term operator-(Variable const& variable, Monomial const& monomial);
Term operator-(Variable const& variable, Polynomial const& polynomial);
Term operator-(Variable const& variable, Expression const& expression);
Term operator-(Variable const& variable, Function const& functionAsParameter);
Term operator-(Monomial const& monomial, Constant const& constant);
Term operator-(Monomial const& monomial, Variable const& variable);
Term operator-(Monomial const& monomial1, Monomial const& monomial2);
Term operator-(Monomial const& monomial, Polynomial const& polynomial);
Term operator-(Monomial const& monomial, Expression const& expression);
Term operator-(Monomial const& monomial, Function const& functionAsParameter);
Term operator-(Polynomial const& polynomial, Constant const& constant);
Term operator-(Polynomial const& polynomial, Variable const& variable);
Term operator-(Polynomial const& polynomial, Monomial const& monomial);
Term operator-(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator-(Polynomial const& polynomial, Expression const& expression);
Term operator-(Polynomial const& polynomial, Function const& functionAsParameter);
Term operator-(Expression const& expression, Constant const& constant);
Term operator-(Expression const& expression, Variable const& variable);
Term operator-(Expression const& expression, Monomial const& monomial);
Term operator-(Expression const& expression, Polynomial const& polynomial);
Term operator-(Expression const& expression1, Expression const& expression2);
Term operator-(Expression const& expression, Function const& functionAsParameter);
Term operator-(Function const& functionAsParameter, Constant const& constant);
Term operator-(Function const& functionAsParameter, Variable const& variable);
Term operator-(Function const& functionAsParameter, Monomial const& monomial);
Term operator-(Function const& functionAsParameter, Polynomial const& polynomial);
Term operator-(Function const& functionAsParameter, Expression const& expression);
Term operator-(Function const& function1, Function const& function2);
Term operator-(Term const& term1, Term const& term2);

//Multiplication: a * b
Term operator*(Constant const& constant1, Constant const& constant2);
Term operator*(Constant const& constant, Variable const& variable);
Term operator*(Constant const& constant, Monomial const& monomial);
Term operator*(Constant const& constant, Polynomial const& polynomial);
Term operator*(Constant const& constant, Expression const& expression);
Term operator*(Constant const& constant, Function const& functionAsParameter);
Term operator*(Variable const& variable, Constant const& constant);
Term operator*(Variable const& variable1, Variable const& variable2);
Term operator*(Variable const& variable, Monomial const& monomial);
Term operator*(Variable const& variable, Polynomial const& polynomial);
Term operator*(Variable const& variable, Expression const& expression);
Term operator*(Variable const& variable, Function const& functionAsParameter);
Term operator*(Monomial const& monomial, Constant const& constant);
Term operator*(Monomial const& monomial, Variable const& variable);
Term operator*(Monomial const& monomial1, Monomial const& monomial2);
Term operator*(Monomial const& monomial, Polynomial const& polynomial);
Term operator*(Monomial const& monomial, Expression const& expression);
Term operator*(Monomial const& monomial, Function const& functionAsParameter);
Term operator*(Polynomial const& polynomial, Constant const& constant);
Term operator*(Polynomial const& polynomial, Variable const& variable);
Term operator*(Polynomial const& polynomial, Monomial const& monomial);
Term operator*(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator*(Polynomial const& polynomial, Expression const& expression);
Term operator*(Polynomial const& polynomial, Function const& functionAsParameter);
Term operator*(Expression const& expression, Constant const& constant);
Term operator*(Expression const& expression, Variable const& variable);
Term operator*(Expression const& expression, Monomial const& monomial);
Term operator*(Expression const& expression, Polynomial const& polynomial);
Term operator*(Expression const& expression1, Expression const& expression2);
Term operator*(Expression const& expression, Function const& functionAsParameter);
Term operator*(Function const& functionAsParameter, Constant const& constant);
Term operator*(Function const& functionAsParameter, Variable const& variable);
Term operator*(Function const& functionAsParameter, Monomial const& monomial);
Term operator*(Function const& functionAsParameter, Polynomial const& polynomial);
Term operator*(Function const& functionAsParameter, Expression const& expression);
Term operator*(Function const& function1, Function const& function2);
Term operator*(Term const& term1, Term const& term2);

//Divsion: a / bTerm operator/(Constant const& constant1, Constant const& constant2);
Term operator/(Constant const& constant, Variable const& variable);
Term operator/(Constant const& constant, Monomial const& monomial);
Term operator/(Constant const& constant, Polynomial const& polynomial);
Term operator/(Constant const& constant, Expression const& expression);
Term operator/(Constant const& constant, Function const& functionAsParameter);
Term operator/(Variable const& variable, Constant const& constant);
Term operator/(Variable const& variable1, Variable const& variable2);
Term operator/(Variable const& variable, Monomial const& monomial);
Term operator/(Variable const& variable, Polynomial const& polynomial);
Term operator/(Variable const& variable, Expression const& expression);
Term operator/(Variable const& variable, Function const& functionAsParameter);
Term operator/(Monomial const& monomial, Constant const& constant);
Term operator/(Monomial const& monomial, Variable const& variable);
Term operator/(Monomial const& monomial1, Monomial const& monomial2);
Term operator/(Monomial const& monomial, Polynomial const& polynomial);
Term operator/(Monomial const& monomial, Expression const& expression);
Term operator/(Monomial const& monomial, Function const& functionAsParameter);
Term operator/(Polynomial const& polynomial, Constant const& constant);
Term operator/(Polynomial const& polynomial, Variable const& variable);
Term operator/(Polynomial const& polynomial, Monomial const& monomial);
Term operator/(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator/(Polynomial const& polynomial, Expression const& expression);
Term operator/(Polynomial const& polynomial, Function const& functionAsParameter);
Term operator/(Expression const& expression, Constant const& constant);
Term operator/(Expression const& expression, Variable const& variable);
Term operator/(Expression const& expression, Monomial const& monomial);
Term operator/(Expression const& expression, Polynomial const& polynomial);
Term operator/(Expression const& expression1, Expression const& expression2);
Term operator/(Expression const& expression, Function const& functionAsParameter);
Term operator/(Function const& functionAsParameter, Constant const& constant);
Term operator/(Function const& functionAsParameter, Variable const& variable);
Term operator/(Function const& functionAsParameter, Monomial const& monomial);
Term operator/(Function const& functionAsParameter, Polynomial const& polynomial);
Term operator/(Function const& functionAsParameter, Expression const& expression);
Term operator/(Function const& function1, Function const& function2);
Term operator/(Term const& term1, Term const& term2);

//RaiseToThePower: a ^ bTerm operator^(Constant const& constant1, Constant const& constant2);
Term operator^(Constant const& constant, Variable const& variable);
Term operator^(Constant const& constant, Monomial const& monomial);
Term operator^(Constant const& constant, Polynomial const& polynomial);
Term operator^(Constant const& constant, Expression const& expression);
Term operator^(Constant const& constant, Function const& functionAsParameter);
Term operator^(Variable const& variable, Constant const& constant);
Term operator^(Variable const& variable1, Variable const& variable2);
Term operator^(Variable const& variable, Monomial const& monomial);
Term operator^(Variable const& variable, Polynomial const& polynomial);
Term operator^(Variable const& variable, Expression const& expression);
Term operator^(Variable const& variable, Function const& functionAsParameter);
Term operator^(Monomial const& monomial, Constant const& constant);
Term operator^(Monomial const& monomial, Variable const& variable);
Term operator^(Monomial const& monomial1, Monomial const& monomial2);
Term operator^(Monomial const& monomial, Polynomial const& polynomial);
Term operator^(Monomial const& monomial, Expression const& expression);
Term operator^(Monomial const& monomial, Function const& functionAsParameter);
Term operator^(Polynomial const& polynomial, Constant const& constant);
Term operator^(Polynomial const& polynomial, Variable const& variable);
Term operator^(Polynomial const& polynomial, Monomial const& monomial);
Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2);
Term operator^(Polynomial const& polynomial, Expression const& expression);
Term operator^(Polynomial const& polynomial, Function const& functionAsParameter);
Term operator^(Expression const& expression, Constant const& constant);
Term operator^(Expression const& expression, Variable const& variable);
Term operator^(Expression const& expression, Monomial const& monomial);
Term operator^(Expression const& expression, Polynomial const& polynomial);
Term operator^(Expression const& expression1, Expression const& expression2);
Term operator^(Expression const& expression, Function const& functionAsParameter);
Term operator^(Function const& functionAsParameter, Constant const& constant);
Term operator^(Function const& functionAsParameter, Variable const& variable);
Term operator^(Function const& functionAsParameter, Monomial const& monomial);
Term operator^(Function const& functionAsParameter, Polynomial const& polynomial);
Term operator^(Function const& functionAsParameter, Expression const& expression);
Term operator^(Function const& function1, Function const& function2);
Term operator^(Term const& term1, Term const& term2);

}
}
