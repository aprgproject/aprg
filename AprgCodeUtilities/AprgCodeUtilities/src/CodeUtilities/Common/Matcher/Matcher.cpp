#include "Matcher.hpp"

#include <CodeUtilities/Common/CommonUtilities.hpp>

using namespace std;

namespace alba::CodeUtilities {

Matcher::Matcher(TermType const termType) : m_termTypeOptional(termType) {}
Matcher::Matcher(std::string const& content) : m_contentOptional(content) {}
Matcher::Matcher(MatcherType const matcherType) : m_matcherTypeOptional(matcherType) {}

Matcher::Matcher(TermType const termType, string const& content)
    : m_termTypeOptional(termType), m_contentOptional(content) {}

Matcher::MatcherTypeOptional const& Matcher::getMatcherTypeOptional() const { return m_matcherTypeOptional; }
Matcher::StringOptional const& Matcher::getContentOptional() const { return m_contentOptional; }
Matcher::TermTypeOptional const& Matcher::getTermTypeOptional() const { return m_termTypeOptional; }

ostream& operator<<(ostream& out, Matcher const& matcher) {
    out << "[Matcher ";
    if (matcher.m_termTypeOptional) {
        out << "type: (" << convertToString(matcher.m_termTypeOptional.value()) << ") ";
    }
    if (matcher.m_contentOptional) {
        out << "content: (" << matcher.m_contentOptional.value() << ") ";
    }
    if (matcher.m_matcherTypeOptional) {
        out << "special matcher: (" << convertToString(matcher.m_matcherTypeOptional.value()) << ") ";
    }
    out << "]";
    return out;
}

bool operator==(Matcher const& matcher, Term const& term) {
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
    if (matcher.m_matcherTypeOptional) {
        if (!isAMatch(matcher.m_matcherTypeOptional.value(), term)) {
            return false;
        }
    }
    return true;
}

bool operator==(Term const& term, Matcher const& matcher) { return operator==(matcher, term); }
bool operator!=(Matcher const& matcher, Term const& term) { return !operator==(matcher, term); }
bool operator!=(Term const& term, Matcher const& matcher) { return !operator==(matcher, term); }

}  // namespace alba::CodeUtilities
