#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>

namespace alba::algebra {

class DegreeOnlyMutator final : public BaseMutator {
public:
    explicit DegreeOnlyMutator(std::string const& variableName);
    void mutateTerm(Term& term) override;
    void mutateMonomial(Monomial& monomial) override;
    void mutatePolynomial(Polynomial& polynomial) override;
    void mutateExpression(Expression& expression) override;

private:
    AlbaNumber getMaxDegreeForVariable(Polynomial const& polynomial);
    [[nodiscard]] Monomial getMonomialWithDegree(AlbaNumber const& degree) const;
    std::string m_variableName;
};

}  // namespace alba::algebra
