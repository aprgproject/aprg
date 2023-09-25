#include "NumbersRetriever.hpp"

namespace alba::algebra {

void NumbersRetriever::retrieveFromConstant(Constant const& constant) { m_numbers.emplace(constant.getNumber()); }

void NumbersRetriever::retrieveFromMonomial(Monomial const& monomial) {
    m_numbers.emplace(monomial.getCoefficient());
    // cppcheck-suppress unusedVariable
    for (auto const& [_, exponent] : monomial.getVariablesToExponentsMap()) {
        m_numbers.emplace(exponent);
    }
}

AlbaNumbersSet const& NumbersRetriever::getNumbers() const { return m_numbers; }
void NumbersRetriever::retrieveFromVariable(Variable const&) { m_numbers.emplace(1); }

}  // namespace alba::algebra
