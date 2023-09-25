#pragma once

#include <CodeUtilities/Common/Term/Term.hpp>

namespace alba::CodeUtilities {

class CPlusPlusTokenizer {
public:
    enum class ScopeType {
        NoScope,
        SingleLineComment,
        MultiLineComment,
        StringLiteral,
        RawStringLiteral,
        CharLiteral,
        Attribute,
        WhiteSpace
    };

    explicit CPlusPlusTokenizer(Terms& terms);
    void processCode(std::string const& code);
    void processLeftoverCode();

private:
    [[nodiscard]] ScopeType getCurrentScope() const;
    [[nodiscard]] std::string getIndentifierAt(int const index) const;
    [[nodiscard]] std::string getNumberAt(int const index) const;
    [[nodiscard]] std::string getAlphaNumericUnderscoreStringAt(int const index) const;
    [[nodiscard]] std::string getContinuousDigitsAt(int const index) const;
    [[nodiscard]] bool isNextString(std::string const& expectedString) const;
    [[nodiscard]] bool isIndentifierStartAt(int const index) const;
    [[nodiscard]] bool isNumberAt(int const index) const;
    [[nodiscard]] bool isOperatorAt(int const index) const;
    [[nodiscard]] bool isThreeCharOperatorAt(int const index) const;
    [[nodiscard]] bool isTwoCharOperatorAt(int const index) const;
    [[nodiscard]] bool isOneCharOperatorAt(int const index) const;
    [[nodiscard]] bool isWhiteSpaceAt(int const index) const;
    void processCode();
    void processScope();
    void processInCodeScope();
    void processInSingleLineCommentScope();
    void processInMultiLineCommentScope();
    void processInStringLiteralScope();
    void processInRawStringLiteralScope();
    void processInCharLiteralScope();
    void processInAttributeScope();
    void processInWhiteSpaceScope();
    void enterScope(ScopeType const scopeType);
    void exitScope();
    bool hasProcessedASingleLineComment();
    bool hasProcessedAMultiLineComment();
    bool hasProcessedAStringLiteral();
    bool hasProcessedARawStringLiteral();
    bool hasProcessedACharLiteral();
    bool hasProcessedAnAttribute();
    bool hasProcessedAWhiteSpace();
    bool hasProcessedAMacro();
    bool hasProcessedANumber();
    bool hasProcessedAnIdentifier();
    bool hasProcessedAnOperator();
    bool isTerminatedWhileCheckingWhiteSpace();
    bool isTerminatedWhileCheckingALiteralWithEscape(char const terminatingCharacter);
    bool isTerminatedWhileCheckingTerminatingString(std::string const& terminatingString);
    Terms& m_terms;
    int m_index{};
    std::string m_code;
    std::string m_scopeContent;
    std::vector<ScopeType> m_scopes;
};

}  // namespace alba::CodeUtilities
