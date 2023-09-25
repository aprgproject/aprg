#include "ExponentsRetriever.hpp"

namespace alba::algebra {

void ExponentsRetriever::retrieveFromMonomial(Monomial const& monomial) {
    // cppcheck-suppress unusedVariable
    for (auto const& [_, exponent] : monomial.getVariablesToExponentsMap()) {
        m_exponents.emplace(exponent);
    }
}

AlbaNumbersSet const& ExponentsRetriever::getExponents() const { return m_exponents; }

}  // namespace alba::algebra
