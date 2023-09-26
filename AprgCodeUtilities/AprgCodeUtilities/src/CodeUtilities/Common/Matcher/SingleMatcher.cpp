#include "SingleMatcher.hpp"

#include <CodeUtilities/Common/CommonUtilities.hpp>

using namespace std;

namespace alba::CodeUtilities {

SingleMatcher::SingleMatcher(TermType const termType) : m_termTypeOptional(termType) {}
SingleMatcher::SingleMatcher(string const& content) : m_contentOptional(content) {}
SingleMatcher::SingleMatcher(SpecialMatcherType const matcherType) : m_specialMatcherTypeOptional(matcherType) {}
SingleMatcher::SingleMatcher(TermType const termType, string const& content)
    : m_termTypeOptional(termType), m_contentOptional(content) {}
SingleMatcher::SingleMatcher(bool const shouldInverse, TermType const termType)
    : m_shouldInverse(shouldInverse), m_termTypeOptional(termType) {}
SingleMatcher::SingleMatcher(bool const shouldInverse, string const& content)
    : m_shouldInverse(shouldInverse), m_contentOptional(content) {}
SingleMatcher::SingleMatcher(bool const shouldInverse, SpecialMatcherType const matcherType)
    : m_shouldInverse(shouldInverse), m_specialMatcherTypeOptional(matcherType) {}
SingleMatcher::SingleMatcher(bool const shouldInverse, TermType const termType, string const& content)
    : m_shouldInverse(shouldInverse), m_termTypeOptional(termType), m_contentOptional(content) {}

SingleMatcher::BaseMatcherPtr SingleMatcher::createClone() const { return make_unique<SingleMatcher>(*this); }

bool SingleMatcher::isAMatch(Term const& term) const { return m_shouldInverse ^ doesContentMatch(term); }

SingleMatcher::SpecialMatcherTypeOptional const& SingleMatcher::getSpecialMatcherTypeOptional() const {
    return m_specialMatcherTypeOptional;
}
SingleMatcher::StringOptional const& SingleMatcher::getContentOptional() const { return m_contentOptional; }
SingleMatcher::TermTypeOptional const& SingleMatcher::getTermTypeOptional() const { return m_termTypeOptional; }

ostream& operator<<(ostream& out, SingleMatcher const& matcher) {
    out << "[Match ";
    if (matcher.m_termTypeOptional) {
        out << "type: (" << convertToString(matcher.m_termTypeOptional.value()) << ") ";
    }
    if (matcher.m_contentOptional) {
        out << "content: (" << matcher.m_contentOptional.value() << ") ";
    }
    if (matcher.m_specialMatcherTypeOptional) {
        out << "special: (" << convertToString(matcher.m_specialMatcherTypeOptional.value()) << ") ";
    }
    out << "]";
    return out;
}

bool SingleMatcher::doesContentMatch(Term const& term) const {
    if (m_termTypeOptional) {
        if (m_termTypeOptional.value() != term.getTermType()) {
            return false;
        }
    }
    if (m_contentOptional) {
        if (m_contentOptional.value() != term.getContent()) {
            return false;
        }
    }
    if (m_specialMatcherTypeOptional) {
        if (!CodeUtilities::isAMatch(m_specialMatcherTypeOptional.value(), term)) {
            return false;
        }
    }
    return true;
}

}  // namespace alba::CodeUtilities
