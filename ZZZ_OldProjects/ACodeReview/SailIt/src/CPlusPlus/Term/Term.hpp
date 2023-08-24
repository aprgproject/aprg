#pragma once

#include <CPlusPlus/Database/CPlusPlusType.hpp>
#include <Common/Container/AlbaOptional.hpp>

#include <ostream>
#include <string>

using alba::AlbaOptional;
using std::ostream;
using std::string;

namespace codeReview {

enum class TermType {
    Class,
    Comment,
    Constant_Boolean,
    Constant_Character,
    Constant_Number,
    Constant_String,
    CPlusPlusIgnorableIdentifier,
    Empty,
    FunctionName,
    Identifier,
    Keyword,
    Macro,
    MultiLine_Comment,
    MultiLine_ElseClause,
    MultiLine_ElseIfClause,
    MultiLine_IfElseIfStartChain_Ignorable,
    Namespace,
    NewLine,
    Operator,
    ProcessedTerm,
    SingleLine_Comment,
    Type,
    Unknown,
    Value_LValue,
    Value_RValue,
    Value_RValue_CanBeALine,
    Variable,
    VariableDeclaration,
    WhiteSpace
};

class Term {
public:
    explicit Term(TermType termType, unsigned int const lineNumber = 0);
    explicit Term(TermType termType, string const& content, unsigned int const lineNumber = 0);

    friend ostream& operator<<(ostream& out, Term const& term);
    bool operator==(Term const& termToCompare) const;
    bool operator==(string const& content) const;
    friend bool operator==(string const& content, Term const& term);
    bool operator!=(Term const& termToCompare) const;
    bool operator!=(string const& content) const;
    friend bool operator!=(string const& content, Term const& term);

    [[nodiscard]] string getString() const;
    [[nodiscard]] bool hasValueType() const;
    [[nodiscard]] CPlusPlusType getValueType() const;
    CPlusPlusType& getValueTypeReference();
    [[nodiscard]] string getPrintableString() const;
    [[nodiscard]] string getTermTypeString() const;
    [[nodiscard]] TermType getTermType() const;
    [[nodiscard]] unsigned int getLineNumber() const;

    void clearValueType();
    void setString(string const& string1);
    void setTermType(TermType termType);
    void setValueType(CPlusPlusType const& cPlusPlusType);
    void setLineNumber(unsigned int lineNumber);

private:
    [[nodiscard]] bool hasNoContentString() const;
    bool m_hasContentString;
    TermType m_termType;
    string m_content;
    string m_valueType;
    unsigned int m_lineNumber;
    alba::AlbaOptional<CPlusPlusType> m_ValueTypeOptional;
};

}  // namespace codeReview
