#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <string>

namespace alba::algebra {

class SingleVariableNameRetriever final : public BaseRetriever {
public:
    SingleVariableNameRetriever() = default;
    void retrieveFromEquations(Equations const& equations) override;
    void retrieveFromEquation(Equation const& equation) override;
    void retrieveFromTerm(Term const& term) override;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& function) override;
    void retrieveFromPolynomials(Polynomials const& polynomials) override;
    [[nodiscard]] std::string const& getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty() const;
    [[nodiscard]] bool hasNoVariables() const;
    [[nodiscard]] bool hasOnlyASingleVariable() const;
    [[nodiscard]] bool hasMultipleVariables() const;
    // private:
    void putVariableIfPossible(std::string const& variableName);
    bool m_hasEncounteredAVariable{false};
    bool m_hasMultipleVariables{false};
    std::string m_singleVariableName;
};

template <typename DataType>
bool hasOnlyASingleVariable(DataType const& dataType) {
    SingleVariableNameRetriever retriever;
    retriever.retrieve(dataType);
    return retriever.hasOnlyASingleVariable();
}

template <typename DataType>
bool hasNoVariables(DataType const& dataType) {
    SingleVariableNameRetriever retriever;
    retriever.retrieve(dataType);
    return retriever.hasNoVariables();
}

template <typename DataType>
std::string getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty(DataType const& dataType) {
    SingleVariableNameRetriever retriever;
    retriever.retrieve(dataType);
    return retriever.getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty();
}

}  // namespace alba::algebra
