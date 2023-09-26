#include "IntegrationHistory.hpp"

#include <Common/Macros/AlbaMacros.hpp>

#include <algorithm>

using namespace std;

namespace alba::algebra {

IntegrationPurpose IntegrationHistory::getLastIntegrationPurpose() const {
    IntegrationPurpose result(IntegrationPurpose::NotSet);
    if (!m_recordOfIntegrationPurposes.empty()) {
        result = m_recordOfIntegrationPurposes.back();
    }
    return result;
}

int IntegrationHistory::getDepth() const { return static_cast<int>(m_recordOfIntegrationPurposes.size()); }

bool IntegrationHistory::didThisIntegrationPurposeAlreadyHappened(IntegrationPurpose const purpose) const {
    return find(m_recordOfIntegrationPurposes.cbegin(), m_recordOfIntegrationPurposes.cend(), purpose) !=
           m_recordOfIntegrationPurposes.cend();
}

void IntegrationHistory::performStepsBeforeIntegration(Term const& input, IntegrationPurpose const purpose) {
    logBefore(input, purpose);
    addIntegrationPurpose(purpose);
}

void IntegrationHistory::performStepsAfterIntegration(
    Term const& input, IntegrationPurpose const purpose, Term const& output) {
    logAfter(input, purpose, output);
    if (!m_recordOfIntegrationPurposes.empty()) {
        m_recordOfIntegrationPurposes.pop_back();
    }
}

void IntegrationHistory::clear() { m_recordOfIntegrationPurposes.clear(); }

string IntegrationHistory::getEnumShortString(IntegrationPurpose const purpose) {
    switch (purpose) {
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::NotSet, "NotSet")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::IntegrationByParts, "IntegrationByParts")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::Trigonometric, "Trigonometric")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::TrigonometricSubstitution, "TrigonometricSubstitution")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::Substitution, "Substitution")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::PartialFraction, "PartialFraction")
        ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::NoChange, "NoChange")
        default:
            return "default";
    }
}

void IntegrationHistory::addIntegrationPurpose(IntegrationPurpose const purpose) {
    if (IntegrationPurpose::NoChange != purpose) {
        m_recordOfIntegrationPurposes.emplace_back(purpose);
    }
}

void IntegrationHistory::logBefore(
    Term const&,  // input,
    IntegrationPurpose const) {
    // purpose)
}

void IntegrationHistory::logAfter(
    Term const&,               // input,
    IntegrationPurpose const,  // purpose,
    Term const&) {
    // output)
}

}  // namespace alba::algebra
