#pragma once

#include <Algebra/Limit/LimitsAtInfinity/DegreeOnlyMutator.hpp>
#include <Algebra/Limit/LimitsAtInfinity/RemoveMonomialsWithNegativeExponentMutator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba::algebra {

class LimitsAtInfinity {
public:
    LimitsAtInfinity(Term const& term, std::string const& variableName);
    [[nodiscard]] Term getSimplifiedTermAtInfinity() const;
    [[nodiscard]] Term getValueAtInfinity(AlbaNumber const infinityValue) const;

private:
    static AlbaNumber getDegreeToRemove(AlbaNumber const& numeratorDegree, AlbaNumber const& denominatorDegree);
    AlbaNumber getMaxDegree(Term const& term);
    void simplify();
    void simplifyAsATerm();
    void simplifyAsTermsOverTermsIfPossible();
    void simplifyPolynomialToMaxDegreeMonomialOnly();
    Term m_simplifiedTermAtInfinity;
    std::string m_variableName;
    DegreeOnlyMutator m_degreeOnlyMutator;
    RemoveMonomialsWithNegativeExponentMutator m_removeMonomialsWithNegativeExponentMutator;
};

}  // namespace alba::algebra
