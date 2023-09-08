#pragma once

#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>

#include <string>

namespace alba {

class AlbaGrepStringToken {
public:
    enum class TokenType {

        Dummy,
        Operator,
        StringToFind,
        Result,

    };

    explicit AlbaGrepStringToken(std::string const& stringToFind);
    explicit AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType);
    AlbaGrepStringToken();
    AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType, std::string const& operatorString);
    [[nodiscard]] bool isToBeIgnored() const;
    [[nodiscard]] bool isOperator() const;
    [[nodiscard]] bool isClosingParenthesis() const;
    [[nodiscard]] bool isOpeningParenthesis() const;
    [[nodiscard]] bool isString() const;
    [[nodiscard]] bool isBiDirectionalOperation() const;
    [[nodiscard]] bool isPrefixOperation() const;
    [[nodiscard]] int getOperatorPriority() const;
    [[nodiscard]] TokenType getTokenType() const;
    [[nodiscard]] AlbaGrepStringOperatorType getOperatorType() const;
    [[nodiscard]] std::string getTokenTypeString() const;
    [[nodiscard]] std::string getStringToFind() const;
    void appendToString(char const character);
    void setOperatorType(AlbaGrepStringOperatorType const type);

private:
    TokenType m_type;
    AlbaGrepStringOperatorType m_operatorType;
    std::string m_string;
};

}  // namespace alba
