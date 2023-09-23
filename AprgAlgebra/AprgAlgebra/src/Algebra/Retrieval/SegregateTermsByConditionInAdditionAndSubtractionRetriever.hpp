#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>

#include <functional>

namespace alba::algebra {

class SegregateTermsByConditionInAdditionAndSubtractionRetriever : public BaseRetriever {
public:
    using ConditionFunction = std::function<bool(Term const&)>;
    explicit SegregateTermsByConditionInAdditionAndSubtractionRetriever(ConditionFunction const& condition);
    explicit SegregateTermsByConditionInAdditionAndSubtractionRetriever(ConditionFunction&& condition);
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
    [[nodiscard]] Term const& getTermWithCondition() const;
    [[nodiscard]] Term const& getTermWithoutCondition() const;

private:
    void saveTerm(Term const& term);
    ConditionFunction m_condition;
    Term m_termWithCondition;
    Term m_termWithoutCondition;
};

}  // namespace alba::algebra
