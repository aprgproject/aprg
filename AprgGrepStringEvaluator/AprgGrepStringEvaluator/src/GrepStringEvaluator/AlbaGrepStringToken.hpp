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

    AlbaGrepStringToken();
    explicit AlbaGrepStringToken(std::string const& stringToFind);
    explicit AlbaGrepStringToken(std::string&& stringToFind);
    explicit AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType);
    AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType, std::string const& operatorString);
    AlbaGrepStringToken(AlbaGrepStringOperatorType const operatorType, std::string&& operatorString);
    [[nodiscard]] AlbaGrepStringOperatorType getOperatorType() const;
    [[nodiscard]] TokenType getTokenType() const;
    [[nodiscard]] std::string getTokenTypeString() const;
    [[nodiscard]] std::string getStringToFind() const;
    [[nodiscard]] int getOperatorPriority() const;
    [[nodiscard]] bool isToBeIgnored() const;
    [[nodiscard]] bool isOperator() const;
    [[nodiscard]] bool isClosingParenthesis() const;
    [[nodiscard]] bool isOpeningParenthesis() const;
    [[nodiscard]] bool isString() const;
    [[nodiscard]] bool isBiDirectionalOperation() const;
    [[nodiscard]] bool isPrefixOperation() const;
    void appendToString(char const character);
    void setOperatorType(AlbaGrepStringOperatorType const type);

private:
    TokenType m_type;
    AlbaGrepStringOperatorType m_operatorType;
    std::string m_string;
};

}  // namespace alba
