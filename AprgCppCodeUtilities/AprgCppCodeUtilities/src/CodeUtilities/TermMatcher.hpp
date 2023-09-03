#pragma once

#include <CodeUtilities/Term.hpp>

#include <optional>

namespace alba::CodeUtilities {

class TermMatcher {
public:
    explicit TermMatcher(TermType termType);
    explicit TermMatcher(std::string const& content);
    TermMatcher(TermType termType, std::string const& content);

    friend bool operator==(TermMatcher const& termMatcher, Term const& term);
    friend bool operator==(Term const& term, TermMatcher const& termMatcher);
    friend bool operator!=(TermMatcher const& termMatcher, Term const& term);
    friend bool operator!=(Term const& term, TermMatcher const& termMatcher);
    friend std::ostream& operator<<(std::ostream& out, TermMatcher const& termMatcher);

private:
    std::optional<TermType> m_termTypeOptional;
    std::optional<std::string> m_contentOptional;
};

using TermMatchers = std::vector<TermMatcher>;

}  // namespace alba::CodeUtilities
