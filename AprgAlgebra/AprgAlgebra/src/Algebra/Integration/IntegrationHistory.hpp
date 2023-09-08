#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

enum class IntegrationPurpose {

    NotSet,
    IntegrationByParts,
    Trigonometric,
    TrigonometricSubstitution,
    Substitution,
    PartialFraction,
    NoChange

};

using IntegrationPurposes = std::vector<IntegrationPurpose>;

class IntegrationHistory {
public:
    IntegrationHistory();
    static std::string getEnumShortString(IntegrationPurpose const purpose);
    [[nodiscard]] bool didThisIntegrationPurposeAlreadyHappened(IntegrationPurpose const purpose) const;
    [[nodiscard]] int getDepth() const;
    [[nodiscard]] IntegrationPurpose getLastIntegrationPurpose() const;
    void performStepsBeforeIntegration(Term const& input, IntegrationPurpose const purpose);
    void performStepsAfterIntegration(Term const& input, IntegrationPurpose const purpose, Term const& output);
    void clear();

private:
    void addIntegrationPurpose(IntegrationPurpose const purpose);
    void logBefore(Term const& input, IntegrationPurpose const purpose);
    void logAfter(Term const& input, IntegrationPurpose const purpose, Term const& output);
    IntegrationPurposes m_recordOfIntegrationPurposes;
};

}  // namespace alba::algebra
