#include "TermMatcher.hpp"

#include <CodeUtilities/Common/TermUtilities.hpp>

using namespace std;

namespace alba::CodeUtilities {

TermMatcher::TermMatcher(TermType const termType) : m_termTypeOptional(termType) {}

TermMatcher::TermMatcher(std::string const& content) : m_contentOptional(content) {}

TermMatcher::TermMatcher(TermType const termType, string const& content)
    : m_termTypeOptional(termType), m_contentOptional(content) {}

ostream& operator<<(ostream& out, TermMatcher const& matcher) {
    out << "[Matcher ";
    if (matcher.m_termTypeOptional) {
        out << "type: {" << convertToString(matcher.m_termTypeOptional.value()) << "}";
    }
    if (matcher.m_termTypeOptional || matcher.m_contentOptional) {
        out << " | ";
    }
    if (matcher.m_contentOptional) {
        out << "content:{" << matcher.m_contentOptional.value() << "}";
    }
    out << "]";
    return out;
}

bool operator==(TermMatcher const& matcher, Term const& term) {
    if (matcher.m_termTypeOptional) {
        if (matcher.m_termTypeOptional.value() != term.getTermType()) {
            return false;
        }
    }
    if (matcher.m_contentOptional) {
        if (matcher.m_contentOptional.value() != term.getContent()) {
            return false;
        }
    }
    return true;
}

bool operator==(Term const& term, TermMatcher const& matcher) { return operator==(matcher, term); }

bool operator!=(TermMatcher const& matcher, Term const& term) { return !operator==(matcher, term); }

bool operator!=(Term const& term, TermMatcher const& matcher) { return !operator==(matcher, term); }

}  // namespace alba::CodeUtilities
