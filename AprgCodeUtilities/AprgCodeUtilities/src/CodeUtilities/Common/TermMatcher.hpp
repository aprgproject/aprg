#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <CodeUtilities/Common/TermSpecialMatcherType.hpp>

#include <optional>

namespace alba::CodeUtilities {

class TermMatcher {
public:
    explicit TermMatcher(TermType const termType);
    explicit TermMatcher(std::string const& content);
    explicit TermMatcher(TermSpecialMatcherType const termSpecialMatcherType);
    TermMatcher(TermType const termType, std::string const& content);

    friend bool operator==(TermMatcher const& matcher, Term const& term);
    friend bool operator==(Term const& term, TermMatcher const& matcher);
    friend bool operator!=(TermMatcher const& matcher, Term const& term);
    friend bool operator!=(Term const& term, TermMatcher const& matcher);
    friend std::ostream& operator<<(std::ostream& out, TermMatcher const& matcher);

private:
    std::optional<TermType> m_termTypeOptional;
    std::optional<std::string> m_contentOptional;
    std::optional<TermSpecialMatcherType> m_termSpecialMatcherTypeOptional;
};

using Pattern = std::vector<TermMatcher>;
using Patterns = std::vector<Pattern>;

#define M(argument) alba::CodeUtilities::TermMatcher(argument)

}  // namespace alba::CodeUtilities
