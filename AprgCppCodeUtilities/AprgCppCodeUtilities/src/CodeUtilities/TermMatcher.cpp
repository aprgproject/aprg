#include "TermMatcher.hpp"

#include <CodeUtilities/TermUtilities.hpp>

using namespace std;

namespace alba::CodeUtilities {

TermMatcher::TermMatcher(TermType termType) : m_termTypeOptional(termType) {}

TermMatcher::TermMatcher(std::string const& content) : m_contentOptional(content) {}

TermMatcher::TermMatcher(TermType termType, string const& content)
    : m_termTypeOptional(termType), m_contentOptional(content) {}

ostream& operator<<(ostream& out, TermMatcher const& termMatcher) {
    out << "[Matcher ";
    if (termMatcher.m_termTypeOptional) {
        out << "type: {" << convertToString(termMatcher.m_termTypeOptional.value()) << "}";
    }
    if (termMatcher.m_termTypeOptional || termMatcher.m_contentOptional) {
        out << " | ";
    }
    if (termMatcher.m_contentOptional) {
        out << "content:{" << termMatcher.m_contentOptional.value() << "}";
    }
    out << "]";
    return out;
}

bool operator==(TermMatcher const& termMatcher, Term const& term) {
    if (termMatcher.m_termTypeOptional) {
        if (termMatcher.m_termTypeOptional.value() != term.getTermType()) {
            return false;
        }
    }
    if (termMatcher.m_contentOptional) {
        if (termMatcher.m_contentOptional.value() != term.getContent()) {
            return false;
        }
    }
    return true;
}

bool operator==(Term const& term, TermMatcher const& termMatcher) { return operator==(termMatcher, term); }

bool operator!=(TermMatcher const& termMatcher, Term const& term) { return !operator==(termMatcher, term); }

bool operator!=(Term const& term, TermMatcher const& termMatcher) { return !operator==(termMatcher, term); }

}  // namespace alba::CodeUtilities
