#pragma once

#include <Algebra/Limit/LimitsAtInfinity/DegreeOnlyMutator.hpp>
#include <Algebra/Limit/LimitsAtInfinity/RemoveMonomialsWithNegativeExponentMutator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba::algebra {

class LimitsAtInfinity {
public:
    LimitsAtInfinity(Term const& term, std::string const& variableName);
    LimitsAtInfinity(Term&& term, std::string&& variableName);
    [[nodiscard]] Term getSimplifiedTermAtInfinity() const;
    [[nodiscard]] Term getValueAtInfinity(AlbaNumber const infinityValue) const;

private:
    void simplify();
    void simplifyAsATerm();
    void simplifyAsTermsOverTermsIfPossible();
    void simplifyPolynomialToMaxDegreeMonomialOnly();
    AlbaNumber getMaxDegree(Term const& term);
    static AlbaNumber getDegreeToRemove(AlbaNumber const& numeratorDegree, AlbaNumber const& denominatorDegree);
    Term m_simplifiedTermAtInfinity;
    std::string m_variableName;
    DegreeOnlyMutator m_degreeOnlyMutator;
    RemoveMonomialsWithNegativeExponentMutator m_removeMonomialsWithNegativeExponentMutator;
};

}  // namespace alba::algebra
