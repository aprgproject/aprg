#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba::booleanAlgebra {

class TermsAggregator {
public:
    enum class AggregatorTraverseSteps { BuildExpression, Simplify };

    using Indexes = std::vector<int>;
    explicit TermsAggregator(Terms const& terms);
    explicit TermsAggregator(Terms&& terms);
    [[nodiscard]] Terms const& getTermsConstReference() const;
    void buildExpressionFromTerms();
    void simplifyTerms();

private:
    [[nodiscard]] Indexes getNextOperatorIndexes(OperatorInputType const operatorInputType) const;
    [[nodiscard]] bool hasNoValueBeforeThisIndex(int const index) const;
    void updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    void traverse(AggregatorTraverseSteps const traverseSteps);
    void eraseAndThenInsert(int const firstIndex, int const secondIndex, Term const& term);
    void eraseTermsInclusive(int const firstIndex, int const secondIndex);
    void insertTerm(int const index, Term const& term);
    bool combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined();

    bool traverseOnOperatorIndexesAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, OperatorInputType const operatorInputType);

    bool performTraverseStepsAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex,
        OperatorInputType const operatorInputType);

    bool performTraverseStepsWithBinaryOperationAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex);

    bool performTraverseStepsWithUnaryOperationAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex);

    bool buildExpressionWithBinaryOperationAndReturnIfBuilt(int const index);
    bool buildExpressionWithUnaryOperationAndReturnIfBuilt(int const index);
    bool simplifyBinaryOperationAndReturnIfSimplified(int const index);
    bool simplifyUnaryOperationAndReturnIfSimplified(int const index);
    int m_startIndex{0};
    int m_endIndex{0};
    Terms m_terms;
};

}  // namespace alba::booleanAlgebra
