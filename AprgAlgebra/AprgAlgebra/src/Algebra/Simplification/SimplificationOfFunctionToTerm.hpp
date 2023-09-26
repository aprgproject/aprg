#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra::Simplification {

class SimplificationOfFunctionToTerm {
public:
    struct ConfigurationDetails {
        bool shouldSimplifyTrigonometricFunctionsToSinAndCos;
        bool shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel;
    };

    class Configuration : public AlbaConfigurationHolder<ConfigurationDetails> {};
    class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails> {};
    SimplificationOfFunctionToTerm() = default;
    static Term simplifyToTerm(Function const& functionObject);
    static bool shouldSimplifyTrigonometricFunctionsToSinAndCos();
    static bool shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel();

private:
    static Term simplifyTrigometricFunctionToExpression(Function const& functionObject);
    static Term simplifyLogarithmicFunctionToExpression(Function const& functionObject);
    static Term getLogarithmicOfTermBasedFromName(Term const& term, std::string const& functionName);
};

}  // namespace algebra::Simplification

template <>
algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails
getDefaultConfigurationDetails<alba::algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails>();

}  // namespace alba
