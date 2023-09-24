#pragma once

#include <Algorithm/ExpressionEvaluator/ExpressionEvaluator.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>
#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>
#include <GrepStringEvaluator/AlbaGrepStringToken.hpp>

#include <functional>
#include <stack>
#include <string>
#include <vector>

namespace alba {

class AlbaGrepStringEvaluator {
    using VectorOfTokens = std::vector<AlbaGrepStringToken>;

    using InfixEvaluator = algorithm::ExpressionEvaluator::ExpressionInfixEvaluator<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;

    using PostfixEvaluator = algorithm::ExpressionEvaluator::ExpressionPostfixEvaluator<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;

    using EvaluatorTerm = algorithm::ExpressionEvaluator::ExpressionEvaluatorTerm<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;

    using EvaluatorConverter = algorithm::ExpressionEvaluator::ExpressionEvaluatorConverter<
        AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>;

public:
    explicit AlbaGrepStringEvaluator(std::string const& condition);
    [[nodiscard]] std::string getErrorMessage() const;
    [[nodiscard]] bool isInvalid() const;
    bool evaluate(std::string const& stringToEvaluate);

private:
    [[nodiscard]] bool isEvaluationPossible() const;
    void extractTokens(std::string const& condition);
    void extractTokensWhileOnString(bool& isOnString, std::string& stringToBuild, char const& currentCharacter);
    void extractTokensWhileNotOnString(bool& isOnString, char const& currentCharacter, int& parenthesisCount);
    void generateExpressionEvaluatorPostfix();
    void addOperator(char const characterOperator);
    void addParenthesis(char const currentCharacter, int& parenthesisCount);
    void setErrorMessage(std::string const& errorMessage);
    static char convertTildeToExclamationPointIfNeeded(char const character);
    static bool isOperator(char const character);
    static bool isParenthesis(char const character);
    bool m_isEvaluatorInvalid{false};
    std::string m_errorMessage;
    VectorOfTokens m_tokens;
    PostfixEvaluator m_postfixEvaluator;
};

}  // namespace alba
