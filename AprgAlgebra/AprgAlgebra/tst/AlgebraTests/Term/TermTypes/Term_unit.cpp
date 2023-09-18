#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

TEST(TermTest, EqualityOperatorWorks) {
    Term const term1;
    Term const term2(Constant(5));
    Term const term3(Constant(10));
    Term const term4(Variable("length"));
    Term const term5(Constant(5));

    EXPECT_TRUE(term1 == term1);
    EXPECT_FALSE(term1 == term2);
    EXPECT_TRUE(term2 == term2);
    EXPECT_FALSE(term2 == term3);
    EXPECT_FALSE(term2 == term4);
    EXPECT_TRUE(term2 == term5);
}

TEST(TermTest, InequalityOperatorWorks) {
    Term const term1;
    Term const term2(Constant(5));
    Term const term3(Constant(10));
    Term const term4(Variable("length"));
    Term const term5(Constant(5));

    EXPECT_FALSE(term1 != term1);
    EXPECT_TRUE(term1 != term2);
    EXPECT_FALSE(term2 != term2);
    EXPECT_TRUE(term2 != term3);
    EXPECT_TRUE(term2 != term4);
    EXPECT_FALSE(term2 != term5);
}

TEST(TermTest, LessThanOperatorWorks) {
    Term const term1;
    Term const term2(Constant(10));
    Term const term3(Constant(9));
    Term const term4(Constant(11));
    Term const term5(Operator("+"));
    Term const term6(Variable("length"));

    EXPECT_FALSE(term1 < term1);
    EXPECT_FALSE(term2 < term2);
    EXPECT_FALSE(term2 < term3);
    EXPECT_TRUE(term2 < term4);
    EXPECT_FALSE(term2 < term5);
    EXPECT_TRUE(term2 < term6);
}

TEST(TermTest, OutputStreamOperatorWorks) {
    stringstream ss;
    Term const term1;
    Term const term2(0);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}}));
    Term const term6(Polynomial{Monomial(3, {}), Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}})});
    Term const term7(createExpressionIfPossible({5, "+", "interest"}));
    Function const function1("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const term8(function1);

    ss << term1 << "," << term2 << "," << term3 << "," << term4 << "," << term5 << "," << term6 << "," << term7 << ","
       << term8;

    EXPECT_EQ(
        "{EmptyTerm},0,length,+,-1.5[distance^-3.75][power^4.5],(3 + "
        "-1.5[distance^-3.75][power^4.5]),(5+interest),functionName(5)",
        ss.str());
}

TEST(TermTest, TermsAsExpressionsWorks) {
    Term const expressionTerm1(Expression{});
    Term const expressionTerm2(createExpressionIfPossible({5, "+", "interest"}));

    // For expression1
    ASSERT_EQ(TermType::Expression, expressionTerm1.getTermType());
    Expression const& expression1(expressionTerm1.getAsExpression());
    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify1(expression1.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());

    // For expression2
    ASSERT_EQ(TermType::Expression, expressionTerm2.getTermType());
    Expression const& expression2(expressionTerm2.getAsExpression());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression2.getCommonOperatorLevel());
    TermsWithDetails const& termsToVerify2(expression2.getTermsWithAssociation().getTermsWithDetails());
    ASSERT_EQ(2U, termsToVerify2.size());
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify2[0].association);
    Term const& termToVerify1(getTermConstReferenceFromUniquePointer(termsToVerify2[0].baseTermPointer));
    EXPECT_EQ(Term(5), termToVerify1);
    EXPECT_EQ(TermAssociationType::Positive, termsToVerify2[1].association);
    Term const& termToVerify2(getTermConstReferenceFromUniquePointer(termsToVerify2[1].baseTermPointer));
    EXPECT_EQ(Term("interest"), termToVerify2);
}

TEST(TermTest, TermsAsFunctionsWorks) {
    Function const function1;
    Function const function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const functionTerm1(function1);
    Term const functionTerm2(function2);
    Term const functionTerm3("abs");

    // For function1
    ASSERT_EQ(TermType::Function, functionTerm1.getTermType());
    Function const& functionToVerify1(functionTerm1.getAsFunction());
    EXPECT_TRUE(functionToVerify1.getFunctionName().empty());
    EXPECT_EQ(Term(), getTermConstReferenceFromBaseTerm(functionToVerify1.getInputTerm()));

    // For function2
    ASSERT_EQ(TermType::Function, functionTerm2.getTermType());
    Function const& functionToVerify2(functionTerm2.getAsFunction());
    EXPECT_EQ("functionName", functionToVerify2.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(functionToVerify2.getInputTerm()));

    // For function3
    ASSERT_EQ(TermType::Function, functionTerm3.getTermType());
    Function const& functionToVerify3(functionTerm3.getAsFunction());
    EXPECT_EQ("abs", functionToVerify3.getFunctionName());
    EXPECT_TRUE(getTermConstReferenceFromBaseTerm(functionToVerify3.getInputTerm()).isEmpty());
}

TEST(TermTest, TermsAsFunctionsCanBeChanged) {
    Term term(Function{});

    getTermReferenceFromBaseTerm(term.getAsFunctionReference().getInputTermReference()) = 7;

    ASSERT_EQ(TermType::Function, term.getTermType());
    EXPECT_EQ(Term(7), getTermConstReferenceFromBaseTerm(term.getAsFunction().getInputTerm()));
}

TEST(TermTest, GetDebugStringWorks) {
    Term const term1;
    Term const term2(0);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}}));
    Term const term6(Polynomial{Monomial(3, {}), Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}})});
    Term const term7(createExpressionIfPossible({5, "+", "interest"}));
    Function const function1("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term const term8(function1);

    EXPECT_EQ("{EmptyTerm}{Empty}", term1.getDebugString());
    EXPECT_EQ("0{Constant}", term2.getDebugString());
    EXPECT_EQ("length{Variable}", term3.getDebugString());
    EXPECT_EQ("+{Operator}", term4.getDebugString());
    EXPECT_EQ("-1.5[distance^-3.75][power^4.5]{Monomial}", term5.getDebugString());
    EXPECT_EQ("(3 + -1.5[distance^-3.75][power^4.5]){Polynomial}", term6.getDebugString());
    EXPECT_EQ("( {+-}||5{Constant}{POS}+interest{Variable}{POS} ){Expression}", term7.getDebugString());
    EXPECT_EQ("functionName(5{Constant}){Function}", term8.getDebugString());
}

TEST(TermTest, ClearWorks) {
    Term constantTerm(1475);
    Term variableTerm("x");
    Term monomialTerm(Monomial(1475, {}));
    Term polynomialTerm(Polynomial{Monomial(1475, {})});
    Term expressionTerm(Expression{createExpressionIfPossible({1475})});
    Function const functionObject(
        "functionName", Term(1475), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term functionTerm(functionObject);

    constantTerm.clear();
    variableTerm.clear();
    monomialTerm.clear();
    polynomialTerm.clear();
    expressionTerm.clear();
    functionTerm.clear();

    EXPECT_EQ(Term(), constantTerm);
    EXPECT_EQ(Term(), variableTerm);
    EXPECT_EQ(Term(), monomialTerm);
    EXPECT_EQ(Term(), polynomialTerm);
    EXPECT_EQ(Term(), expressionTerm);
    EXPECT_EQ(Term(), functionTerm);
}

TEST(TermTest, SimplifyWorks) {
    Term constantTerm(1475);
    Term variableTerm("x");
    Term monomialTerm(Monomial(1475, {}));
    Term polynomialTerm(Polynomial{Monomial(1475, {})});
    Term expressionTerm(Expression{createExpressionIfPossible({1475})});
    Function const functionObject(
        "functionName", Term(1475), [](AlbaNumber const& number) -> AlbaNumber { return number; });
    Term functionTerm(functionObject);

    constantTerm.simplify();
    variableTerm.simplify();
    monomialTerm.simplify();
    polynomialTerm.simplify();
    expressionTerm.simplify();
    functionTerm.simplify();

    EXPECT_EQ(Term(1475), constantTerm);
    EXPECT_EQ(Term("x"), variableTerm);
    EXPECT_EQ(Term(1475), monomialTerm);
    EXPECT_EQ(Term(1475), polynomialTerm);
    EXPECT_EQ(Term(1475), expressionTerm);
    EXPECT_EQ(Term(1475), functionTerm);
}

TEST(TermTest, SimplifyWorksWhenIsSimplifiedIsNotSet) {
    Term term(Monomial(1475, {}));

    term.simplify();

    EXPECT_EQ(Term(1475), term);
}

TEST(TermTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet) {
    Term term(Monomial(1475, {}));
    term.setAsSimplified();

    term.simplify();

    EXPECT_EQ(Term(Monomial(1475, {})), term);
}

TEST(TermTest, CreateBasePointerByMoveWorks) {
    Term termToTest(6415);

    BaseTermUniquePointer const uniquePointerToVerify(termToTest.createBasePointerByMove());

    EXPECT_EQ(Term(6415), getTermConstReferenceFromUniquePointer(uniquePointerToVerify));
}

TEST(TermTest, GetAsNumberWorks) {
    Term const constant1(4353);
    Term const constant2(-3248);
    Term const constant3(AlbaNumber::createFraction(3498, 3459));
    Term const constant4(-34.8767);

    ASSERT_EQ(TermType::Constant, constant1.getTermType());
    EXPECT_DOUBLE_EQ(4353, constant1.getAsNumber().getDouble());

    ASSERT_EQ(TermType::Constant, constant2.getTermType());
    EXPECT_DOUBLE_EQ(-3248, constant2.getAsNumber().getDouble());

    ASSERT_EQ(TermType::Constant, constant3.getTermType());
    EXPECT_DOUBLE_EQ(1.0112749349522983, constant3.getAsNumber().getDouble());

    ASSERT_EQ(TermType::Constant, constant4.getTermType());
    EXPECT_DOUBLE_EQ(-34.8767, constant4.getAsNumber().getDouble());
}

TEST(TermTest, AssignmentOperatorWorks) {
    Term const term1 = 2;
    Term term2(5);
    term2 = 7;
    Term term3(8);
    term3 = term2;

    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_EQ(2, term1.getAsNumber().getInteger());
    ASSERT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_EQ(7, term2.getAsNumber().getInteger());
    ASSERT_EQ(TermType::Constant, term3.getTermType());
    EXPECT_EQ(7, term3.getAsNumber().getInteger());
}

TEST(TermTest, TermsAsConstantsCanBeChanged) {
    Term term(Constant{});

    term.getAsConstantReference().setNumber(7575);

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(7575, term.getAsNumber().getDouble());
}

TEST(TermTest, TermsAsConstructedAsStringWorks) {
    Term const term1("");
    Term const term2("5xxx");
    Term const term3("+");
    Term const term4("power");
    Term const term5("x1");

    ASSERT_EQ(TermType::Empty, term1.getTermType());

    ASSERT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_DOUBLE_EQ(5, term2.getAsConstant().getNumber().getDouble());

    ASSERT_EQ(TermType::Operator, term3.getTermType());
    EXPECT_EQ("+", term3.getAsOperator().getOperatorString());

    ASSERT_EQ(TermType::Variable, term4.getTermType());
    EXPECT_EQ("power", term4.getAsVariable().getVariableName());

    ASSERT_EQ(TermType::Variable, term5.getTermType());
    EXPECT_EQ("x1", term5.getAsVariable().getVariableName());
}

TEST(TermTest, TermsAsConstantsWorks) {
    Term const constantTerm1(4353);
    Term const constantTerm2(-3248);
    Term const constantTerm3(AlbaNumber::createFraction(3498, 3459));
    Term const constantTerm4(-34.8767);

    ASSERT_EQ(TermType::Constant, constantTerm1.getTermType());
    EXPECT_DOUBLE_EQ(4353, constantTerm1.getAsConstant().getNumber().getDouble());

    ASSERT_EQ(TermType::Constant, constantTerm2.getTermType());
    EXPECT_DOUBLE_EQ(-3248, constantTerm2.getAsConstant().getNumber().getDouble());

    ASSERT_EQ(TermType::Constant, constantTerm3.getTermType());
    EXPECT_DOUBLE_EQ(1.0112749349522983, constantTerm3.getAsConstant().getNumber().getDouble());

    ASSERT_EQ(TermType::Constant, constantTerm4.getTermType());
    EXPECT_DOUBLE_EQ(-34.8767, constantTerm4.getAsConstant().getNumber().getDouble());
}

TEST(TermTest, TermsAsExpressionsCanBeChanged) {
    Term term(Expression{});

    term.getAsExpressionReference().setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);

    ASSERT_EQ(TermType::Expression, term.getTermType());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, term.getAsExpression().getCommonOperatorLevel());
}

TEST(TermTest, TermsAsMonomialsWorks) {
    Term const monomialTerm1(Monomial(3, {}));
    Term const monomialTerm2(Monomial(1.5, {{"distance", 3.75}}));
    Term const monomialTerm3(Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}}));

    ASSERT_EQ(TermType::Monomial, monomialTerm1.getTermType());
    EXPECT_DOUBLE_EQ(3, monomialTerm1.getAsMonomial().getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomialTerm1.getAsMonomial().getVariablesToExponentsMap());
    ASSERT_TRUE(variableMap1.empty());

    ASSERT_EQ(TermType::Monomial, monomialTerm2.getTermType());
    EXPECT_DOUBLE_EQ(1.5, monomialTerm2.getAsMonomial().getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomialTerm2.getAsMonomial().getVariablesToExponentsMap());
    ASSERT_EQ(1U, variableMap2.size());
    Monomial::VariableExponentPair const& variable2(*variableMap2.begin());
    EXPECT_EQ("distance", variable2.first);
    EXPECT_DOUBLE_EQ(3.75, variable2.second.getDouble());

    ASSERT_EQ(TermType::Monomial, monomialTerm3.getTermType());
    EXPECT_DOUBLE_EQ(-1.5, monomialTerm3.getAsMonomial().getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomialTerm3.getAsMonomial().getVariablesToExponentsMap());
    ASSERT_EQ(2U, variableMap3.size());
    auto variableMap3It = variableMap3.cbegin();
    Monomial::VariableExponentPair const& variable3_1(*variableMap3It);
    EXPECT_EQ("distance", variable3_1.first);
    EXPECT_DOUBLE_EQ(-3.75, variable3_1.second.getDouble());
    ++variableMap3It;
    Monomial::VariableExponentPair const& variable3_2(*variableMap3It);
    EXPECT_EQ("power", variable3_2.first);
    EXPECT_DOUBLE_EQ(4.5, variable3_2.second.getDouble());
}

TEST(TermTest, TermsAsMonomialsCanBeChanged) {
    Term term(Monomial{});

    term.getAsMonomialReference().setConstant(99);

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    EXPECT_DOUBLE_EQ(99, term.getAsMonomial().getCoefficient().getDouble());
}

TEST(TermTest, ClearAllInnerSimplifiedFlagsWorks) {
    Monomial innerMonomial;
    innerMonomial.setAsSimplified();
    Term term(innerMonomial);
    term.setAsSimplified();
    EXPECT_TRUE(term.isSimplified());
    EXPECT_TRUE(term.getAsMonomial().isSimplified());

    term.clearAllInnerSimplifiedFlags();

    EXPECT_FALSE(term.isSimplified());
    EXPECT_FALSE(term.getAsMonomial().isSimplified());
}

TEST(TermTest, TermsAsOperatorsWorks) {
    Term const operatorTerm1("+");
    Term const operatorTerm2("-");
    Term const operatorTerm3("*");
    Term const operatorTerm4("/");

    ASSERT_EQ(TermType::Operator, operatorTerm1.getTermType());
    EXPECT_EQ("+", operatorTerm1.getAsOperator().getOperatorString());

    ASSERT_EQ(TermType::Operator, operatorTerm2.getTermType());
    EXPECT_EQ("-", operatorTerm2.getAsOperator().getOperatorString());

    ASSERT_EQ(TermType::Operator, operatorTerm3.getTermType());
    EXPECT_EQ("*", operatorTerm3.getAsOperator().getOperatorString());

    ASSERT_EQ(TermType::Operator, operatorTerm4.getTermType());
    EXPECT_EQ("/", operatorTerm4.getAsOperator().getOperatorString());
}

TEST(TermTest, TermsAsOperatorsCanBeChanged) {
    Term term(Operator{});

    term.getAsOperatorReference().setOperatorString("+");

    ASSERT_EQ(TermType::Operator, term.getTermType());
    EXPECT_EQ("+", term.getAsOperator().getOperatorString());
}

TEST(TermTest, TermsAsPolynomialsWorks) {
    Term const polynomialTerm1(Polynomial{});
    Term const polynomialTerm2(Polynomial{Monomial(3, {})});
    Term const polynomialTerm3(Polynomial{Monomial(3, {}), Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}})});

    // For polynomial1
    ASSERT_EQ(TermType::Polynomial, polynomialTerm1.getTermType());
    Monomials const& monomials1(polynomialTerm1.getAsPolynomial().getMonomials());
    ASSERT_TRUE(monomials1.empty());

    // For polynomial2
    ASSERT_EQ(TermType::Polynomial, polynomialTerm2.getTermType());
    Monomials const& monomials2(polynomialTerm2.getAsPolynomial().getMonomials());
    ASSERT_EQ(1U, monomials2.size());
    Monomial const& monomial2(monomials2.front());
    EXPECT_DOUBLE_EQ(3, monomial2.getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMap());
    ASSERT_TRUE(variableMap2.empty());

    // For polynomial3
    ASSERT_EQ(TermType::Polynomial, polynomialTerm3.getTermType());
    Monomials const& monomials3(polynomialTerm3.getAsPolynomial().getMonomials());
    ASSERT_EQ(2U, monomials3.size());

    Monomial const& monomial3_1(monomials3.front());
    EXPECT_DOUBLE_EQ(3, monomial3_1.getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3_1(monomial3_1.getVariablesToExponentsMap());
    ASSERT_TRUE(variableMap3_1.empty());

    Monomial const& monomial3_2(monomials3.back());
    EXPECT_DOUBLE_EQ(-1.5, monomial3_2.getCoefficient().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3_2(monomial3_2.getVariablesToExponentsMap());
    ASSERT_EQ(2U, variableMap3_2.size());
    auto variableMap3It = variableMap3_2.cbegin();
    Monomial::VariableExponentPair const& variable3_1(*variableMap3It);
    EXPECT_EQ("distance", variable3_1.first);
    EXPECT_DOUBLE_EQ(-3.75, variable3_1.second.getDouble());
    ++variableMap3It;
    Monomial::VariableExponentPair const& variable3_2(*variableMap3It);
    EXPECT_EQ("power", variable3_2.first);
    EXPECT_DOUBLE_EQ(4.5, variable3_2.second.getDouble());
}

TEST(TermTest, TermsAsPolynomialsCanBeChanged) {
    Term term(Polynomial{});

    term.getAsPolynomialReference().addMonomial(Monomial(53, {}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Polynomial const expectedPolynomial{Monomial(53, {})};
    EXPECT_EQ(expectedPolynomial, term.getAsPolynomial());
}

TEST(TermTest, GetTermTypeWorks) {
    Term const term1;
    Term const term2(0);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_EQ(TermType::Empty, term1.getTermType());
    EXPECT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ(TermType::Operator, term4.getTermType());
    EXPECT_EQ(TermType::Monomial, term5.getTermType());
    EXPECT_EQ(TermType::Polynomial, term6.getTermType());
    EXPECT_EQ(TermType::Expression, term7.getTermType());
    EXPECT_EQ(TermType::Function, term8.getTermType());
}

TEST(TermTest, TermsAsVariablesWorks) {
    Term const variableTerm1("x");
    Term const variableTerm2("power");

    ASSERT_EQ(TermType::Variable, variableTerm1.getTermType());
    EXPECT_EQ("x", variableTerm1.getAsVariable().getVariableName());

    ASSERT_EQ(TermType::Variable, variableTerm2.getTermType());
    EXPECT_EQ("power", variableTerm2.getAsVariable().getVariableName());
}

TEST(TermTest, TermsAsVariablesCanBeChanged) {
    Term term(Variable{});

    term.getAsVariableReference().setVariableName("time");

    ASSERT_EQ(TermType::Variable, term.getTermType());
    EXPECT_EQ("time", term.getAsVariable().getVariableName());
}

TEST(TermTest, IsEmptyWorks) {
    Term const term1;
    Term const term2(0);
    Term const term3(1);
    Term const term4(Variable("length"));
    Term const term5(Operator("+"));
    Term const term6(Monomial(0, {}));
    Term const term7(Monomial(1, {}));
    Term const term8(Polynomial{});
    Term const term9(Polynomial{Monomial(1, {})});
    Term const term10(Expression{});
    Term const term11(Function{});

    EXPECT_TRUE(term1.isEmpty());
    EXPECT_FALSE(term2.isEmpty());
    EXPECT_FALSE(term3.isEmpty());
    EXPECT_FALSE(term4.isEmpty());
    EXPECT_FALSE(term5.isEmpty());
    EXPECT_FALSE(term6.isEmpty());
    EXPECT_FALSE(term7.isEmpty());
    EXPECT_TRUE(term8.isEmpty());
    EXPECT_FALSE(term9.isEmpty());
    EXPECT_TRUE(term10.isEmpty());
    EXPECT_FALSE(term11.isEmpty());
}

TEST(TermTest, IsConstantWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isConstant());
    EXPECT_TRUE(term2.isConstant());
    EXPECT_FALSE(term3.isConstant());
    EXPECT_FALSE(term4.isConstant());
    EXPECT_FALSE(term5.isConstant());
    EXPECT_FALSE(term6.isConstant());
    EXPECT_FALSE(term7.isConstant());
    EXPECT_FALSE(term8.isConstant());
}

TEST(TermTest, IsVariableWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isVariable());
    EXPECT_FALSE(term2.isVariable());
    EXPECT_TRUE(term3.isVariable());
    EXPECT_FALSE(term4.isVariable());
    EXPECT_FALSE(term5.isVariable());
    EXPECT_FALSE(term6.isVariable());
    EXPECT_FALSE(term7.isVariable());
    EXPECT_FALSE(term8.isVariable());
}

TEST(TermTest, IsOperatorWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isOperator());
    EXPECT_FALSE(term2.isOperator());
    EXPECT_FALSE(term3.isOperator());
    EXPECT_TRUE(term4.isOperator());
    EXPECT_FALSE(term5.isOperator());
    EXPECT_FALSE(term6.isOperator());
    EXPECT_FALSE(term7.isOperator());
    EXPECT_FALSE(term8.isOperator());
}

TEST(TermTest, IsMonomialWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isMonomial());
    EXPECT_FALSE(term2.isMonomial());
    EXPECT_FALSE(term3.isMonomial());
    EXPECT_FALSE(term4.isMonomial());
    EXPECT_TRUE(term5.isMonomial());
    EXPECT_FALSE(term6.isMonomial());
    EXPECT_FALSE(term7.isMonomial());
    EXPECT_FALSE(term8.isMonomial());
}

TEST(TermTest, IsPolynomialWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isPolynomial());
    EXPECT_FALSE(term2.isPolynomial());
    EXPECT_FALSE(term3.isPolynomial());
    EXPECT_FALSE(term4.isPolynomial());
    EXPECT_FALSE(term5.isPolynomial());
    EXPECT_TRUE(term6.isPolynomial());
    EXPECT_FALSE(term7.isPolynomial());
    EXPECT_FALSE(term8.isPolynomial());
}

TEST(TermTest, IsExpressionWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isExpression());
    EXPECT_FALSE(term2.isExpression());
    EXPECT_FALSE(term3.isExpression());
    EXPECT_FALSE(term4.isExpression());
    EXPECT_FALSE(term5.isExpression());
    EXPECT_FALSE(term6.isExpression());
    EXPECT_TRUE(term7.isExpression());
    EXPECT_FALSE(term8.isExpression());
}

TEST(TermTest, IsFunctionWorks) {
    Term const term1;
    Term const term2(1);
    Term const term3(Variable("length"));
    Term const term4(Operator("+"));
    Term const term5(Monomial(1, {}));
    Term const term6(Polynomial{});
    Term const term7(Expression{});
    Term const term8(Function{});

    EXPECT_FALSE(term1.isFunction());
    EXPECT_FALSE(term2.isFunction());
    EXPECT_FALSE(term3.isFunction());
    EXPECT_FALSE(term4.isFunction());
    EXPECT_FALSE(term5.isFunction());
    EXPECT_FALSE(term6.isFunction());
    EXPECT_FALSE(term7.isFunction());
    EXPECT_TRUE(term8.isFunction());
}

TEST(TermTest, TermThatIsDefaultConstructedHasIsSimplifiedFlagNotSet) {
    Term const term;

    EXPECT_FALSE(term.isSimplified());
}

TEST(TermTest, TermThatIsConstructedWithTermTypeHasIsSimplifiedFlagNotSet) {
    Term const constantTerm(4353);
    Term const variableTerm("");
    Term const operatorTerm("+");
    Term const monomialTerm(Monomial{});
    Term const polynomialTerm(Polynomial{});
    Term const expressionTerm(Expression{});
    Term const functionTerm(Function{});

    EXPECT_FALSE(constantTerm.isSimplified());
    EXPECT_FALSE(variableTerm.isSimplified());
    EXPECT_FALSE(operatorTerm.isSimplified());
    EXPECT_FALSE(monomialTerm.isSimplified());
    EXPECT_FALSE(polynomialTerm.isSimplified());
    EXPECT_FALSE(expressionTerm.isSimplified());
    EXPECT_FALSE(functionTerm.isSimplified());
}

TEST(TermTest, TermThatIsCopyConstructedHasIsSimplifiedFlagCopied) {
    Term const termWithSimplifiedNotSet;
    Term termWithSimplifiedSet;
    termWithSimplifiedSet.setAsSimplified();

    EXPECT_FALSE(termWithSimplifiedNotSet.isSimplified());
    EXPECT_TRUE(termWithSimplifiedSet.isSimplified());
}

TEST(TermTest, TermThatIsAssignedHasIsSimplifiedFlagCopied) {
    Term const termWithSimplifiedNotSet;
    Term termWithSimplifiedSet;
    termWithSimplifiedSet.setAsSimplified();
    Term term1(1);
    Term term2(1);

    term1 = termWithSimplifiedNotSet;
    term2 = termWithSimplifiedSet;

    EXPECT_FALSE(term1.isSimplified());
    EXPECT_TRUE(term2.isSimplified());
}

TEST(TermTest, IsSimplifiedWorks) {
    Term const term1;
    Term term2;
    term2.setAsSimplified();

    EXPECT_FALSE(term1.isSimplified());
    EXPECT_TRUE(term2.isSimplified());
}

TEST(TermTest, SetAsSimplifiedWorks) {
    Term term;

    term.setAsSimplified();

    EXPECT_TRUE(term.isSimplified());
}

TEST(TermTest, ClearSimplifiedFlagWorks) {
    Term term;
    term.setAsSimplified();

    term.clearSimplifiedFlag();

    EXPECT_FALSE(term.isSimplified());
}

TEST(TermTest, SortWorks) {
    Term term1;
    Term term2(Polynomial{});
    Term term3(Expression{});
    Term term4(Polynomial{
        Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(10, {})});
    Term term5(createExpressionIfPossible({1, "-", 3, "-", 2, "+", 5, "+", 4}));

    term1.sort();
    term2.sort();
    term3.sort();
    term4.sort();
    term5.sort();

    Term const expectTerm1;
    Term const expectTerm2(Polynomial{});
    Term const expectTerm3(Expression{});
    Term const expectTerm4(Polynomial{
        Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(100, {}), Monomial(10, {})});
    Term const expectTerm5(createExpressionIfPossible({1, "+", 4, "+", 5, "-", 2, "-", 3}));
    EXPECT_EQ(expectTerm1, term1);
    EXPECT_EQ(expectTerm2, term2);
    EXPECT_EQ(expectTerm3, term3);
    EXPECT_EQ(expectTerm4, term4);
    EXPECT_EQ(expectTerm5, term5);
}

}  // namespace alba::algebra
