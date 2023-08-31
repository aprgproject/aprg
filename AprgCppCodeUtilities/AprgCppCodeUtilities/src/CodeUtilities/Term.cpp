#include "Term.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <string>

using namespace std;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

Term::Term(TermType termType, string const& content) : m_termType(termType), m_content(content) {}

bool Term::operator==(Term const& term) const { return m_termType == term.m_termType && m_content == term.m_content; }

bool Term::operator!=(Term const& term) const { return !(*this == term); }

ostream& operator<<(ostream& out, Term const& term) {
    out << "[type: " << term.getTermTypeString() << " | content:{" << term.m_content << "}]";
    return out;
}

TermType Term::getTermType() const { return m_termType; }

string Term::getString() const { return m_content; }

string Term::getTermTypeString() const {
#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;

    switch (m_termType) {
        GET_ENUM_STRING(TermType::Boolean)
        GET_ENUM_STRING(TermType::CharacterLiteral)
        GET_ENUM_STRING(TermType::CommentMultiline)
        GET_ENUM_STRING(TermType::CommentSingleLine)
        GET_ENUM_STRING(TermType::Identifier)
        GET_ENUM_STRING(TermType::Keyword)
        GET_ENUM_STRING(TermType::Macro)
        GET_ENUM_STRING(TermType::Number)
        GET_ENUM_STRING(TermType::Operator)
        GET_ENUM_STRING(TermType::PrimitiveType)
        GET_ENUM_STRING(TermType::StringLiteral)
        GET_ENUM_STRING(TermType::Unknown)
        GET_ENUM_STRING(TermType::WhiteSpace)
    }
    return {};
}

void Term::setTermType(TermType termType) { m_termType = termType; }

void Term::setContent(string const& content) { m_content = content; }

}  // namespace alba::CodeUtilities
