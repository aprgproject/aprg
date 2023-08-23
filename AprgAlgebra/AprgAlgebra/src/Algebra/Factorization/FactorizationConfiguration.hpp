#pragma once

#include <Common/Container/AlbaConfigurationHolder.hpp>

namespace alba {

namespace algebra::FactorizationonfigurationDetails {
    bool shouldSimplifyExpressionsToFactors;
    bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
};

class Configuration : public AlbaConfigurationHolder<ConfigurationDetails> {};

class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails> {};

bool shouldSimplifyExpressionsToFactors();
bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue();

}  // namesp}::Factorization::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Factorization::ConfigurationDetails>();

}  // namespace alba
