#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <Common/Container/AlbaConfigurationHolder.hpp>

namespace alba {

namespace booleanAlgebra::Simplification {

class SimplificationOfExpression {
public:
    // is logarithm simplification needed?
    struct ConfigurationDetails {
        bool shouldSimplifyWithOuterOrAndInnerAnd;
        bool shouldSimplifyWithOuterAndAndInnerOr;
        bool shouldSimplifyByQuineMcKluskey;
    };

    class Configuration : public AlbaConfigurationHolder<ConfigurationDetails> {};
    class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails> {};
    explicit SimplificationOfExpression(Expression const& expression);
    explicit SimplificationOfExpression(Expression&& expression);
    SimplificationOfExpression();
    [[nodiscard]] Expression getExpression() const;
    void simplify();
    static bool shouldSimplifyWithOuterOrAndInnerAnd();
    static bool shouldSimplifyWithOuterAndAndInnerOr();
    static bool shouldSimplifyByQuineMcKluskey();

private:
    void simplifyExpressionUntilNoChange();
    static void simplifyExpression(Expression& expression);
    static void processTermsBaseOnOperatorLevel(
        Expression& expression, WrappedTerms const& termsToProcess, OperatorLevel const operatorLevel);
    static void processAndSaveTermsForAndOperation(Expression& expression, WrappedTerms const& termsToProcess);
    static void processAndSaveTermsForOrOperation(Expression& expression, WrappedTerms const& termsToProcess);
    static bool isChangeDetected(Expression const& expression1, Expression const& expression2);
    Expression m_expression;
};

}  // namespace booleanAlgebra::Simplification

template <>
booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<booleanAlgebra::Simplification::SimplificationOfExpression::ConfigurationDetails>();

}  // namespace alba
