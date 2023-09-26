#include "Matcher.hpp"

#include <CodeUtilities/Common/Matcher/LogicalGroupOfMatchers.hpp>
#include <CodeUtilities/Common/Matcher/SingleMatcher.hpp>

using namespace std;

namespace alba::CodeUtilities {

Matcher::Matcher(Type const type, BaseMatcher::BaseMatcherPtr&& baseMatcherPtr)
    : m_type(type), m_baseMatcherPtr(std::move(baseMatcherPtr)) {}

Matcher::Matcher(Matcher const& matcher) : m_type(matcher.m_type) {
    if (matcher.m_baseMatcherPtr) {
        m_baseMatcherPtr = matcher.m_baseMatcherPtr->createClone();
    }
}

Matcher& Matcher::operator=(Matcher const& matcher) {
    if (this == &matcher) {
        return *this;
    }
    m_type = matcher.m_type;
    if (matcher.m_baseMatcherPtr) {
        m_baseMatcherPtr = m_baseMatcherPtr->createClone();
    }
    return *this;
}

bool Matcher::isAMatch(Term const& term) const { return m_baseMatcherPtr->isAMatch(term); }

ostream& operator<<(ostream& out, Matcher const& matcher) {
    // NOLINTBEGIN(cppcoreguidelines-pro-type-static-cast-downcast)
    switch (matcher.m_type) {
        case Matcher::Type::Single:
            out << *static_cast<SingleMatcher*>(matcher.m_baseMatcherPtr.get());
            break;
        case Matcher::Type::Group:
            out << *static_cast<LogicalGroupOfMatchers*>(matcher.m_baseMatcherPtr.get());
            break;
    }
    // NOLINTEND(cppcoreguidelines-pro-type-static-cast-downcast)
    out << "[Matcher ";
    return out;
}

bool operator==(Matcher const& matcher, Term const& term) { return matcher.isAMatch(term); }
bool operator==(Term const& term, Matcher const& matcher) { return matcher.isAMatch(term); }
bool operator!=(Matcher const& matcher, Term const& term) { return !matcher.isAMatch(term); }
bool operator!=(Term const& term, Matcher const& matcher) { return !matcher.isAMatch(term); }

}  // namespace alba::CodeUtilities
