#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>
#include <unordered_map>

namespace alba::algebra {

class SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever : public BaseRetriever {
public:
    using VariableNameToTermMap = std::unordered_map<std::string, Term>;
    explicit SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever(stringHelper::strings const& variableNames);
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
    [[nodiscard]] Term const& getTermWithMultipleVariableNames() const;
    [[nodiscard]] Term const& getRemainingTerm() const;
    [[nodiscard]] VariableNameToTermMap const& getVariableNameToTermMap() const;

private:
    void initializeWithVariableNames(stringHelper::strings const& namesInOrder);
    void saveTerm(Term const& term, int const numberOfTimesFound, std::string const& variableName);
    VariableNameToTermMap m_variableNameToTermMap;
    Term m_termWithMultipleVariableNames;
    Term m_remainingTerm;
};

}  // namespace alba::algebra
