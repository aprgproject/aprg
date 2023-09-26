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
    IntegrationHistory() = default;
    [[nodiscard]] IntegrationPurpose getLastIntegrationPurpose() const;
    [[nodiscard]] int getDepth() const;
    [[nodiscard]] bool didThisIntegrationPurposeAlreadyHappened(IntegrationPurpose const purpose) const;
    void performStepsBeforeIntegration(Term const& input, IntegrationPurpose const purpose);
    void performStepsAfterIntegration(Term const& input, IntegrationPurpose const purpose, Term const& output);
    void clear();
    static std::string getEnumShortString(IntegrationPurpose const purpose);

private:
    void addIntegrationPurpose(IntegrationPurpose const purpose);
    void logBefore(Term const& input, IntegrationPurpose const purpose);
    void logAfter(Term const& input, IntegrationPurpose const purpose, Term const& output);
    IntegrationPurposes m_recordOfIntegrationPurposes;
};

}  // namespace alba::algebra
