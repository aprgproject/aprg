#include <BooleanAlgebra/Satisfiability/TwoSatisfiabilityUsingGraphs.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;

namespace alba::booleanAlgebra {

TEST(TwoSatisfiabilityUsingGraphsTest, ExampleWithCompleteSolution) {
    Term const termToTest(buildTermIfPossible("(x2|~x1)&(~x1|~x2)&(x1|x3)&(~x2|~x3)&(x1|x4)"));
    SatisfiabilityTerms const satTermsToTest(getSatisfiabilityTerms(termToTest));
    TwoSatisfiabilityUsingGraphs const twoSat(satTermsToTest);

    EXPECT_TRUE(twoSat.hasSolution());
    EXPECT_EQ("(x1'&x2'&x3&x4)", convertToString(twoSat.getSolution()));
}

TEST(TwoSatisfiabilityUsingGraphsTest, ExampleWithIncompleteSolution) {
    Term const termToTest(buildTermIfPossible("(x1|x2)&(~x1|~x2)"));
    SatisfiabilityTerms const satTermsToTest(getSatisfiabilityTerms(termToTest));
    TwoSatisfiabilityUsingGraphs const twoSat(satTermsToTest);

    EXPECT_TRUE(twoSat.hasSolution());
    EXPECT_EQ("(x1&x2')", convertToString(twoSat.getSolution()));
}

TEST(TwoSatisfiabilityUsingGraphsTest, ExampleWithNoSolution) {
    Term const termToTest(buildTermIfPossible("(x1|x2)^(x1|~x2)^(~x1|x3)^(~x1|~x3)"));
    SatisfiabilityTerms const satTermsToTest(getSatisfiabilityTerms(termToTest));
    TwoSatisfiabilityUsingGraphs const twoSat(satTermsToTest);

    EXPECT_TRUE(twoSat.hasSolution());
    EXPECT_TRUE(twoSat.getSolution().isEmpty());
}

}  // namespace alba::booleanAlgebra
