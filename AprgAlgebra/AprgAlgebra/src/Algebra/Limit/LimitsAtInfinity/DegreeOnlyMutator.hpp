#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>

namespace alba::algebra {

class DegreeOnlyMutator final : public BaseMutator {
public:
    explicit DegreeOnlyMutator(std::string const& variableName);
    explicit DegreeOnlyMutator(std::string&& variableName);
    void mutateTerm(Term& term) override;
    void mutateMonomial(Monomial& monomial) override;
    void mutatePolynomial(Polynomial& polynomial) override;
    void mutateExpression(Expression& expression) override;

private:
    [[nodiscard]] Monomial getMonomialWithDegree(AlbaNumber const& degree) const;
    AlbaNumber getMaxDegreeForVariable(Polynomial const& polynomial);
    std::string m_variableName;
};

}  // namespace alba::algebra
