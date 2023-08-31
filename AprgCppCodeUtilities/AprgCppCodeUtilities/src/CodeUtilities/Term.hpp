#pragma once

#include <CodeUtilities/TermConstants.hpp>

#include <ostream>
#include <string>
#include <vector>

namespace alba::CodeUtilities {

enum class TermType {
    Boolean,
    CharacterLiteral,
    CommentMultiline,
    CommentSingleLine,
    Identifier,
    Keyword,
    Macro,
    Number,
    Operator,
    PrimitiveType,
    StringLiteral,
    Unknown,
    WhiteSpace
};

class Term {
public:
    Term(TermType termType, std::string const& content);

    bool operator==(Term const& term) const;
    bool operator!=(Term const& term) const;

    friend std::ostream& operator<<(std::ostream& out, Term const& term);

    [[nodiscard]] TermType getTermType() const;
    [[nodiscard]] std::string getString() const;
    [[nodiscard]] std::string getTermTypeString() const;

    void clearValueType();
    void setTermType(TermType termType);
    void setContent(std::string const& content);

private:
    TermType m_termType;
    std::string m_content;
};

using Terms = std::vector<Term>;

}  // namespace alba::CodeUtilities
