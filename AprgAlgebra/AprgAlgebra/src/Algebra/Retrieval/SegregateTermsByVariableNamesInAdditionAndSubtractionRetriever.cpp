#include "SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp"

#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba::algebra {

SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::
    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever(strings const& variableNames) {
    initializeWithVariableNames(variableNames);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromConstant(Constant const& constant) {
    m_remainingTerm += Term(constant);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromVariable(Variable const& variable) {
    int numberOfTimesFound(0);
    string lastVariableNameFound;
    for (auto const& [variableName, term] : m_variableNameToTermMap) {
        if (variableName == variable.getVariableName()) {
            lastVariableNameFound = variableName;
            ++numberOfTimesFound;
        }
    }
    saveTerm(Term(variable), numberOfTimesFound, lastVariableNameFound);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromMonomial(Monomial const& monomial) {
    int numberOfTimesFound(0);
    string lastVariableNameFound;
    for (auto const& [variableName, term] : m_variableNameToTermMap) {
        if (monomial.getExponentForVariable(variableName) != 0) {
            lastVariableNameFound = variableName;
            ++numberOfTimesFound;
        }
    }
    saveTerm(Term(monomial), numberOfTimesFound, lastVariableNameFound);
}

Term const& SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getTermWithMultipleVariableNames() const {
    return m_termWithMultipleVariableNames;
}

Term const& SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getRemainingTerm() const {
    return m_remainingTerm;
}

SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::VariableNameToTermMap const&
SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getVariableNameToTermMap() const {
    return m_variableNameToTermMap;
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::initializeWithVariableNames(
    strings const& namesInOrder) {
    for (string const& name : namesInOrder) {
        m_variableNameToTermMap.emplace(name, Term());
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::saveTerm(
    Term const& term, int const numberOfTimesFound, string const& variableName) {
    if (numberOfTimesFound == 0) {
        m_remainingTerm += term;
    } else if (numberOfTimesFound == 1) {
        m_variableNameToTermMap[variableName] += term;
    } else {
        m_termWithMultipleVariableNames += term;
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromExpression(
    Expression const& expression) {
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        for (TermWithDetails const& termWithDetails : expression.getTermsWithAssociation().getTermsWithDetails()) {
            if (termWithDetails.hasPositiveAssociation()) {
                retrieveFromTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
            } else {
                retrieveFromTerm(negateTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer)));
            }
        }
    } else {
        int numberOfTimesFound(0);
        string lastVariableNameFound;
        VariableNamesRetriever variableNamesRetriever;
        variableNamesRetriever.retrieveFromExpression(expression);
        VariableNamesSet const& namesInExpression(variableNamesRetriever.getVariableNames());
        for (auto const& [variableName, term] : m_variableNameToTermMap) {
            if (namesInExpression.find(variableName) != namesInExpression.cend()) {
                lastVariableNameFound = variableName;
                ++numberOfTimesFound;
            }
        }
        saveTerm(Term(expression), numberOfTimesFound, lastVariableNameFound);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromFunction(
    Function const& functionObject) {
    int numberOfTimesFound(0);
    string lastVariableNameFound;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromFunction(functionObject);
    VariableNamesSet const& namesInFunction(variableNamesRetriever.getVariableNames());
    for (auto const& [variableName, term] : m_variableNameToTermMap) {
        if (namesInFunction.find(variableName) != namesInFunction.cend()) {
            lastVariableNameFound = variableName;
            ++numberOfTimesFound;
        }
    }
    saveTerm(Term(functionObject), numberOfTimesFound, lastVariableNameFound);
}

}  // namespace alba::algebra
