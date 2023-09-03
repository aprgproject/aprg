#pragma once

#include <CodeUtilities/Common/Term.hpp>

#include <string>
#include <vector>

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
        WhiteSpace
    };
    explicit CPlusPlusTokenizer(Terms& terms);

    void processCode(std::string const& code);
    void processLeftoverCode();

private:
    void processCode();
    void processScope();
    void processInCodeScope();
    bool hasProcessedASingleLineComment();
    bool hasProcessedAMultiLineComment();
    bool hasProcessedAStringLiteral();
    bool hasProcessedARawStringLiteral();
    bool hasProcessedACharLiteral();
    bool hasProcessedAWhiteSpace();
    bool hasProcessedAMacro();
    bool hasProcessedANumber();
    bool hasProcessedAnIdentifier();
    bool hasProcessedAnOperator();
    void processInSingleLineCommentScope();
    void processInMultiLineCommentScope();
    void processInStringLiteralScope();
    void processInRawStringLiteralScope();
    void processInCharLiteralScope();
    void processInWhiteSpaceScope();
    void enterScope(ScopeType const scopeType);
    void exitScope();
    bool isTerminatedWhileCheckingWhiteSpace();
    bool isTerminatedWhileCheckingALiteralWithEscape(char const terminatingCharacter);
    bool isTerminatedWhileCheckingTerminatingString(std::string const& terminatingString);
    [[nodiscard]] ScopeType getCurrentScope() const;
    [[nodiscard]] bool isNextString(std::string const& expectedString) const;
    [[nodiscard]] bool isIndentifierStartAt(int const index) const;
    [[nodiscard]] bool isNumberAt(int const index) const;
    [[nodiscard]] bool isOperatorAt(int const index) const;
    [[nodiscard]] bool isThreeCharOperatorAt(int const index) const;
    [[nodiscard]] bool isTwoCharOperatorAt(int const index) const;
    [[nodiscard]] bool isOneCharOperatorAt(int const index) const;
    [[nodiscard]] bool isWhiteSpaceAt(int const index) const;
    [[nodiscard]] std::string getIndentifierAt(int const index) const;
    [[nodiscard]] std::string getNumberAt(int const index) const;
    [[nodiscard]] std::string getAlphaNumericUnderscoreStringAt(int const index) const;

    Terms& m_terms;
    int m_index{};
    std::string m_code;
    std::string m_scopeContent;
    std::vector<ScopeType> m_scopes;
};

}  // namespace alba::CodeUtilities
