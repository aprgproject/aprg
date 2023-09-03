#include "Term.hpp"

#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>

using namespace std;
using namespace alba::stringHelper;

namespace alba::CodeUtilities {

Term::Term(TermType termType, string const& content) : m_termType(termType), m_content(content) {}

bool Term::operator==(Term const& term) const { return m_termType == term.m_termType && m_content == term.m_content; }

bool Term::operator!=(Term const& term) const { return !(*this == term); }

ostream& operator<<(ostream& out, Term const& term) {
    out << "[type: {" << term.getTermTypeString() << "} | content:{" << term.m_content << "}]";
    return out;
}

TermType Term::getTermType() const { return m_termType; }

string Term::getContent() const { return m_content; }

string Term::getTermTypeString() const { return convertToString(m_termType); }

void Term::setTermType(TermType termType) { m_termType = termType; }

void Term::setContent(string const& content) { m_content = content; }

}  // namespace alba::CodeUtilities
