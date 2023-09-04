#pragma once

#include <CodeUtilities/Common/Term.hpp>

#include <optional>

namespace alba::CodeUtilities {

class TermMatcher {
public:
    explicit TermMatcher(TermType const termType);
    explicit TermMatcher(std::string const& content);
    TermMatcher(TermType const termType, std::string const& content);

    friend bool operator==(TermMatcher const& matcher, Term const& term);
    friend bool operator==(Term const& term, TermMatcher const& matcher);
    friend bool operator!=(TermMatcher const& matcher, Term const& term);
    friend bool operator!=(Term const& term, TermMatcher const& matcher);
    friend std::ostream& operator<<(std::ostream& out, TermMatcher const& matcher);

private:
    std::optional<TermType> m_termTypeOptional;
    std::optional<std::string> m_contentOptional;
};

using TermMatchers = std::vector<TermMatcher>;

}  // namespace alba::CodeUtilities
