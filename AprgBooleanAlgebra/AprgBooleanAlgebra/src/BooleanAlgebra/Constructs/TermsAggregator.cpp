#include "TermsAggregator.hpp"

#include <BooleanAlgebra/Operations/PerformOperations.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/TermUtilities.hpp>

#include <map>

using namespace std;

namespace alba::booleanAlgebra {

TermsAggregator::TermsAggregator(Terms const& terms) : m_terms(terms) {}
TermsAggregator::TermsAggregator(Terms&& terms) : m_terms(terms) {}
Terms const& TermsAggregator::getTermsConstReference() const { return m_terms; }
void TermsAggregator::buildExpressionFromTerms() { traverse(AggregatorTraverseSteps::BuildExpression); }
void TermsAggregator::simplifyTerms() { traverse(AggregatorTraverseSteps::Simplify); }

TermsAggregator::Indexes TermsAggregator::getNextOperatorIndexes(OperatorInputType const operatorInputType) const {
    Indexes operatorIndexes;
    multimap<int, int> operatorLevelToIndexMap;
    for (int i = m_startIndex; i < m_endIndex; ++i) {
        Term const& term(m_terms[i]);
        if (term.isOperator()) {
            Operator const& operatorTerm(term.getOperatorConstReference());
            if (operatorTerm.isSameOperatorInputType(operatorInputType)) {
                operatorLevelToIndexMap.emplace(getOperatorTypeInversePriority(operatorTerm.getOperatorType()), i);
            }
        }
    }
    // cppcheck-suppress unusedVariable
    for (auto const& [_, index] : operatorLevelToIndexMap) {
        operatorIndexes.emplace_back(index);
    }
    return operatorIndexes;
}

bool TermsAggregator::hasNoValueBeforeThisIndex(int const index) const {
    bool result(false);
    if (index == 0) {
        result = true;
    } else if (index - 1 < static_cast<int>(m_terms.size())) {
        result = !isNonEmptyOrNonOperatorType(m_terms[index - 1]);
    }
    return result;
}

void TermsAggregator::updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators() {
    m_startIndex = 0;
    m_endIndex = 0;
    if (!m_terms.empty()) {
        m_endIndex = static_cast<int>(m_terms.size()) - 1;
    }
    for (int i = 0; i < static_cast<int>(m_terms.size()); ++i) {
        Term const& term(m_terms[i]);
        if (term.isOperator()) {
            Operator const& operatorTerm(term.getOperatorConstReference());
            if (operatorTerm.isOpeningGroupOperator()) {
                m_startIndex = i;
                m_endIndex = i;
            } else if (operatorTerm.isClosingGroupOperator()) {
                m_endIndex = i;
                break;
            }
        }
    }
}

void TermsAggregator::traverse(AggregatorTraverseSteps const traverseSteps) {
    bool continueToCombine(true);
    while (continueToCombine) {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
        bool continueToTraverse(true);
        while (continueToTraverse) {
            continueToTraverse =
                traverseOnOperatorIndexesAndReturnIfContinue(traverseSteps, OperatorInputType::UnaryOperation);
            if (!continueToTraverse) {
                continueToTraverse =
                    traverseOnOperatorIndexesAndReturnIfContinue(traverseSteps, OperatorInputType::BinaryOperation);
            }
        }
        continueToCombine = combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined();
    }
}

void TermsAggregator::eraseAndThenInsert(int const firstIndex, int const secondIndex, Term const& term) {
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    Term const newTerm(term);
    eraseTermsInclusive(firstIndex, secondIndex);
    insertTerm(firstIndex, newTerm);
}

void TermsAggregator::eraseTermsInclusive(int const firstIndex, int const secondIndex) {
    bool const isOutsideStartAndEndIndex(m_startIndex > firstIndex || m_endIndex < secondIndex);
    m_terms.erase(m_terms.cbegin() + firstIndex, m_terms.cbegin() + secondIndex + 1);
    if (isOutsideStartAndEndIndex) {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    } else {
        m_endIndex = m_endIndex - (secondIndex - firstIndex + 1);
    }
}

void TermsAggregator::insertTerm(int const index, Term const& term) {
    bool const isOutsideStartAndEndIndex(m_startIndex > index || m_endIndex < index);
    m_terms.emplace(m_terms.cbegin() + index, term);
    if (isOutsideStartAndEndIndex) {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    } else {
        ++m_endIndex;
    }
}

bool TermsAggregator::combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined() {
    bool isCombined(false);
    if (m_startIndex + 2 == m_endIndex && m_endIndex < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[m_startIndex]);
        Term const& term2(m_terms[m_startIndex + 1]);
        Term const& term3(m_terms[m_endIndex]);
        if (term1.isOperator() && term1.getOperatorConstReference().isOpeningGroupOperator() &&
            isNonEmptyOrNonOperatorType(term2) && term3.isOperator() &&
            term3.getOperatorConstReference().isClosingGroupOperator()) {
            eraseAndThenInsert(m_startIndex, m_endIndex, term2);
            isCombined = true;
        }
    }
    return isCombined;
}

bool TermsAggregator::traverseOnOperatorIndexesAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, OperatorInputType const operatorInputType) {
    bool continueToTraverse(false);
    Indexes const nextOperatorIndexes(getNextOperatorIndexes(operatorInputType));
    for (int const nextOperatorIndex : nextOperatorIndexes) {
        continueToTraverse =
            performTraverseStepsAndReturnIfContinue(traverseSteps, nextOperatorIndex, operatorInputType);
        if (continueToTraverse) {
            break;
        }
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex,
    OperatorInputType const operatorInputType) {
    bool continueToTraverse(false);
    if (OperatorInputType::UnaryOperation == operatorInputType) {
        continueToTraverse =
            performTraverseStepsWithUnaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
    } else if (OperatorInputType::BinaryOperation == operatorInputType) {
        continueToTraverse =
            performTraverseStepsWithBinaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsWithBinaryOperationAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex) {
    bool continueToTraverse(true);
    if (AggregatorTraverseSteps::BuildExpression == traverseSteps) {
        continueToTraverse = buildExpressionWithBinaryOperationAndReturnIfBuilt(nextOperatorIndex);
    } else if (AggregatorTraverseSteps::Simplify == traverseSteps) {
        continueToTraverse = simplifyBinaryOperationAndReturnIfSimplified(nextOperatorIndex);
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsWithUnaryOperationAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex) {
    bool continueToTraverse(true);
    if (AggregatorTraverseSteps::BuildExpression == traverseSteps) {
        continueToTraverse = buildExpressionWithUnaryOperationAndReturnIfBuilt(nextOperatorIndex);
    } else if (AggregatorTraverseSteps::Simplify == traverseSteps) {
        continueToTraverse = simplifyUnaryOperationAndReturnIfSimplified(nextOperatorIndex);
    }
    return continueToTraverse;
}

bool TermsAggregator::buildExpressionWithBinaryOperationAndReturnIfBuilt(int const index) {
    bool isBuilt(false);
    if (index > 0 && index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index - 1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index + 1]);
        if (isNonEmptyOrNonOperatorType(term1) && term2.isOperator() && isNonEmptyOrNonOperatorType(term3)) {
            Expression newExpression(createOrCopyExpressionFromATerm(term1));
            Operator const& operatorTerm(term2.getOperatorConstReference());
            if (operatorTerm.isAnd()) {
                newExpression.putTermWithAndOperationIfNeeded(term3);
            } else if (operatorTerm.isOr()) {
                newExpression.putTermWithOrOperationIfNeeded(term3);
            }
            eraseAndThenInsert(index - 1, index + 1, newExpression);
            isBuilt = true;
        }
    }
    return isBuilt;
}

bool TermsAggregator::buildExpressionWithUnaryOperationAndReturnIfBuilt(int const index) {
    bool isBuilt(false);
    if (index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index + 1]);
        if (term1.isOperator() && isNonEmptyOrNonOperatorType(term2)) {
            Term finalTerm(term2);
            Operator const& operatorTerm(term1.getOperatorConstReference());
            if (operatorTerm.isNot()) {
                finalTerm.negate();
            }
            eraseAndThenInsert(index, index + 1, finalTerm);
            isBuilt = true;
        }
    }
    return isBuilt;
}

bool TermsAggregator::simplifyBinaryOperationAndReturnIfSimplified(int const index) {
    bool isSimplified(false);
    if (index > 0 && index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index - 1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index + 1]);
        if (isNonEmptyOrNonOperatorType(term1) && term2.isOperator() && isNonEmptyOrNonOperatorType(term3)) {
            Term const newTerm(performOperation(term2.getOperatorConstReference(), term1, term3));
            eraseAndThenInsert(index - 1, index + 1, newTerm);
            isSimplified = true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::simplifyUnaryOperationAndReturnIfSimplified(int const index) {
    bool isSimplified(false);
    if (index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index + 1]);
        if (term1.isOperator() && isNonEmptyOrNonOperatorType(term2)) {
            Term const newTerm(performOperation(term1.getOperatorConstReference(), term2));
            eraseAndThenInsert(index, index + 1, newTerm);
            isSimplified = true;
        }
    }
    return isSimplified;
}

}  // namespace alba::booleanAlgebra
