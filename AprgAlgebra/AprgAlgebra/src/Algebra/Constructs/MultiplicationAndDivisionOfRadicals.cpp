#include "MultiplicationAndDivisionOfRadicals.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMultiplesHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals(TermsWithDetails const& termsWithDetails)
    : m_termsWithDetails(termsWithDetails) {}

MultiplicationAndDivisionOfRadicals::MultiplicationAndDivisionOfRadicals(TermsWithDetails&& termsWithDetails)
    : m_termsWithDetails(termsWithDetails) {}

Term MultiplicationAndDivisionOfRadicals::getCombinedTerm() const {
    SimplificationOfExpression::ConfigurationDetails radicalSimplificationConfigurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    radicalSimplificationConfigurationDetails.shouldNotSimplifyByDistributingConstantExponentToEachBase = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(radicalSimplificationConfigurationDetails);

    Expression combinedExpression;
    combinedExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    combinedExpression.putTermsWithDetails(m_termsWithDetails);
    Term combinedTerm(combinedExpression);
    combinedTerm.simplify();
    return combinedTerm;
}

TermsWithDetails const& MultiplicationAndDivisionOfRadicals::getTermsWithDetails() const { return m_termsWithDetails; }

void MultiplicationAndDivisionOfRadicals::simplify() {
    SimplificationOfExpression::ConfigurationDetails radicalSimplificationConfigurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    radicalSimplificationConfigurationDetails.shouldNotSimplifyByDistributingConstantExponentToEachBase = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(radicalSimplificationConfigurationDetails);

    Monomial combinedMonomial(createMonomialFromNumber(1));
    RadicalDetails radicalDetails;
    TermsWithDetails remainingTerms;
    gatherDetails(radicalDetails, combinedMonomial, remainingTerms);

    AlbaNumber const gcfOfExponents(getGcfOfExponents(radicalDetails));

    if (shouldBeCombined(radicalDetails, combinedMonomial, gcfOfExponents)) {
        m_termsWithDetails.clear();
        combineMonomialAndRadicalsAndSave(radicalDetails, combinedMonomial, gcfOfExponents);
        saveRemainingTerms(remainingTerms);
    }
}

void MultiplicationAndDivisionOfRadicals::gatherDetails(
    RadicalDetails& radicalDetails, Monomial& combinedMonomial, TermsWithDetails& remainingTerms) {
    for (TermWithDetails const& termWithDetails : m_termsWithDetails) {
        Term const& term(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
        TermRaiseToANumber const termRaiseToANumber(createTermRaiseToANumberFromTerm(term));

        if (termRaiseToANumber.isRadical()) {
            radicalDetails.emplace_back(RadicalDetail{termRaiseToANumber, termWithDetails.association});
        } else if (canBeConvertedToMonomial(term)) {
            Monomial const monomial(createMonomialIfPossible(term));
            if (termWithDetails.hasPositiveAssociation()) {
                combinedMonomial.multiplyMonomial(monomial);
            } else {
                combinedMonomial.divideMonomial(monomial);
            }
        } else {
            remainingTerms.emplace_back(termWithDetails);
        }
    }
}

void MultiplicationAndDivisionOfRadicals::combineMonomialAndRadicalsAndSave(
    RadicalDetails const& radicalDetails, Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents) {
    Monomial newMonomial(combinedMonomial);
    newMonomial.raiseToPowerNumber(AlbaNumber(1) / gcfOfExponents);
    TermsWithDetails newRadicalsWithDetails;
    for (RadicalDetail const& radicalDetail : radicalDetails) {
        TermRaiseToANumber newRadicalBaseAndExponent(radicalDetail.radical);
        newRadicalBaseAndExponent.setExponent(newRadicalBaseAndExponent.getExponent() / gcfOfExponents);
        Term const newRadical(newRadicalBaseAndExponent.getCombinedTerm());
        if (canBeConvertedToMonomial(newRadical)) {
            Monomial const newRadicalMonomial(createMonomialIfPossible(newRadical));
            if (radicalDetail.association == TermAssociationType::Positive) {
                newMonomial.multiplyMonomial(newRadicalMonomial);
            } else {
                newMonomial.divideMonomial(newRadicalMonomial);
            }
        } else {
            newRadicalsWithDetails.emplace_back(newRadical, radicalDetail.association);
        }
    }
    Expression combinedExpression;
    combinedExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    if (!isTheValue(newMonomial, 1)) {
        combinedExpression.putTerm(Term(newMonomial), TermAssociationType::Positive);
    }
    combinedExpression.putTermsWithDetails(newRadicalsWithDetails);
    combinedExpression.putTermWithRaiseToPowerIfNeeded(Term(gcfOfExponents));
    m_termsWithDetails.emplace_back(Term(combinedExpression), TermAssociationType::Positive);
}

void MultiplicationAndDivisionOfRadicals::saveRemainingTerms(TermsWithDetails const& remainingTerms) {
    m_termsWithDetails.reserve(m_termsWithDetails.size() + remainingTerms.size());
    copy(remainingTerms.cbegin(), remainingTerms.cend(), back_inserter(m_termsWithDetails));
}

AlbaNumber MultiplicationAndDivisionOfRadicals::getGcfOfExponents(RadicalDetails const& radicalDetails) {
    AlbaNumber gcfOfExponents(1);
    if (!radicalDetails.empty()) {
        gcfOfExponents = radicalDetails.front().radical.getExponent();
        for (auto it = radicalDetails.cbegin() + 1; it != radicalDetails.cend(); ++it) {
            gcfOfExponents = getGreatestCommonFactor(gcfOfExponents, it->radical.getExponent());
        }
    }
    return gcfOfExponents;
}

bool MultiplicationAndDivisionOfRadicals::shouldBeCombined(
    RadicalDetails const& radicalDetails, Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents) {
    return gcfOfExponents != 1 && !radicalDetails.empty() &&
           isNotANegativeTermWithExponentDenominatorEven(combinedMonomial, gcfOfExponents);
}

bool MultiplicationAndDivisionOfRadicals::isNotANegativeTermWithExponentDenominatorEven(
    Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents) {
    bool result(true);
    if (gcfOfExponents.isIntegerOrFractionType()) {
        AlbaNumber::FractionData const fractionData(gcfOfExponents.getFractionData());
        if (isEven(getAbsoluteValue<int>(static_cast<int>(fractionData.denominator)))) {
            result = !isANegativeMonomial(combinedMonomial);
        }
    }
    return result;
}

}  // namespace alba::algebra
