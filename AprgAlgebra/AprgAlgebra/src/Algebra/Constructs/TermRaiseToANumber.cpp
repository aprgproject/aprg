#include "TermRaiseToANumber.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

namespace alba::algebra {

TermRaiseToANumber::TermRaiseToANumber(Term const& base, AlbaNumber const& exponent)
    : m_base(base), m_exponent(exponent) {}

TermRaiseToANumber::TermRaiseToANumber(Term&& base, AlbaNumber&& exponent) : m_base(base), m_exponent(exponent) {}
AlbaNumber const& TermRaiseToANumber::getExponent() const { return m_exponent; }

Term TermRaiseToANumber::getCombinedTerm() const {
    Term combinedTerm(1);
    if (m_exponent == 1) {
        combinedTerm = m_base;
    } else if (canBeConvertedToMonomial(m_base)) {
        combinedTerm = m_base ^ m_exponent;
    } else {
        combinedTerm = createExpressionIfPossible({m_base, "^", m_exponent});
    }
    return combinedTerm;
}

Term const& TermRaiseToANumber::getBase() const { return m_base; }
bool TermRaiseToANumber::isEmpty() const { return m_base.isEmpty(); }
bool TermRaiseToANumber::isRadical() const { return m_exponent.isDoubleType() || m_exponent.isFractionType(); }
void TermRaiseToANumber::setBase(Term const& base) { m_base = base; }
void TermRaiseToANumber::setExponent(AlbaNumber const& exponent) { m_exponent = exponent; }
Term& TermRaiseToANumber::getBaseReference() { return m_base; }

}  // namespace alba::algebra
