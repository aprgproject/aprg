#include "Term.hpp"

#include <CodeUtilities/Common/CommonUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

Term::Term(TermType const termType, string&& content) : m_termType(termType), m_content(content) {}
Term::Term(TermType const termType, string const& content) : m_termType(termType), m_content(content) {}
bool Term::operator==(Term const& term) const { return m_termType == term.m_termType && m_content == term.m_content; }
bool Term::operator!=(Term const& term) const { return !(*this == term); }
TermType Term::getTermType() const { return m_termType; }
string Term::getContent() const { return m_content; }
string Term::getTermTypeString() const { return convertToString(m_termType); }

void Term::clear() {
    m_termType = TermType::Empty;
    m_content.clear();
}

void Term::setTermType(TermType const termType) { m_termType = termType; }
void Term::setContent(string const& content) { m_content = content; }

ostream& operator<<(ostream& out, Term const& term) {
    out << "[type: (" << term.getTermTypeString() << ") | content: (" << term.m_content << ")]";
    return out;
}

}  // namespace alba::CodeUtilities
