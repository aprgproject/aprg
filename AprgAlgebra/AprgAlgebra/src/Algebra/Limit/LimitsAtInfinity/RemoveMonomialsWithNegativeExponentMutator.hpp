#pragma once

#include <Algebra/Mutation/BaseMutator.hpp>

namespace alba::algebra {

class RemoveMonomialsWithNegativeExponentMutator final : public BaseMutator {
public:
    explicit RemoveMonomialsWithNegativeExponentMutator(std::string const& variableName);
    explicit RemoveMonomialsWithNegativeExponentMutator(std::string&& variableName);
    void mutateTerm(Term& term) override;
    void mutateMonomial(Monomial& monomial) override;
    void mutatePolynomial(Polynomial& polynomial) override;
    void mutateExpression(Expression& expression) override;
    void mutateFunction(Function& functionObject) override;

private:
    [[nodiscard]] bool isMonomialToBeRemoved(Monomial const& monomial) const;
    std::string m_variableName;
};

}  // namespace alba::algebra
