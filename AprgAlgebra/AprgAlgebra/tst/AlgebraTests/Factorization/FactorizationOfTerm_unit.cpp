#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfTerm.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra::Factorization {

TEST(FactorizationOfTermTest, FactorizeTermWorksOnNonPolynomialTerm) {
    Terms factorizedTerms(factorizeTerm(5));

    EXPECT_EQ(1U, factorizedTerms.size());
    EXPECT_EQ(Term(5), factorizedTerms[0]);
}

TEST(FactorizationOfTermTest, FactorizeTermWorksOnPolynomialTerm) {
    Terms factorizedTerms(factorizeTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}));

    EXPECT_EQ(2U, factorizedTerms.size());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}), factorizedTerms[0]);
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}), factorizedTerms[1]);
}

TEST(FactorizationOfTermTest, FactorizeTermWorksOnExpressionTermWhenshouldSimplifyExpressionsToFactorsAsDefault) {
    Expression const expressionToTest(createExpressionIfPossible({cos("x"), "*", sin("x"), "*", tan("x")}));

    Terms factorizedTerms(factorizeTerm(expressionToTest));

    Term const termToExpect1(createExpressionIfPossible({cos("x"), "*", sin("x"), "*", tan("x")}));
    EXPECT_EQ(1U, factorizedTerms.size());
    EXPECT_EQ(termToExpect1, factorizedTerms[0]);
}

TEST(FactorizationOfTermTest, FactorizeTermWorksOnExpressionTermWhenShouldSimplifyExpressionsToFactorsIsTrue) {
    ConfigurationDetails configurationDetails(Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = true;
    ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    Expression const expressionToTest(createExpressionIfPossible({cos("x"), "*", sin("x"), "*", tan("x")}));

    Terms factorizedTerms(factorizeTerm(expressionToTest));
    EXPECT_EQ(3U, factorizedTerms.size());
    EXPECT_EQ(Term(cos("x")), factorizedTerms[0]);
    EXPECT_EQ(Term(sin("x")), factorizedTerms[1]);
    EXPECT_EQ(Term(tan("x")), factorizedTerms[2]);
}

TEST(FactorizationOfTermTest, FactorizeTermsWorks) {
    Terms const terms{5, Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}};

    Terms factorizedTerms(factorizeTerms(terms));

    EXPECT_EQ(3U, factorizedTerms.size());
    EXPECT_EQ(Term(5), factorizedTerms[0]);
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}), factorizedTerms[1]);
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}), factorizedTerms[2]);
}

}  // namespace alba::algebra::Factorization
