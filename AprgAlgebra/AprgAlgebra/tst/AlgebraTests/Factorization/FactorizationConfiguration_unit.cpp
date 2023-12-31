#include <Algebra/Factorization/FactorizationConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra::Factorization {

TEST(FactorizationConfigurationTest, SomeConditionWorksAsDefault) {
    EXPECT_FALSE(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue());
}

TEST(FactorizationConfigurationTest, SomeConditionWorksAndCanBeChangedAndChangedBack) {
    {
        ConfigurationDetails configurationDetails(getDefaultConfigurationDetails<ConfigurationDetails>());
        configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
        ScopeObject const scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        EXPECT_TRUE(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue());
    }
    EXPECT_FALSE(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue());
}

}  // namespace alba::algebra::Factorization
