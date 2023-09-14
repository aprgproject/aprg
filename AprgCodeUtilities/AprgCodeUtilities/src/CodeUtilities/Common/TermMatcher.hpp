#pragma once

#include <CodeUtilities/Common/MatcherType.hpp>
#include <CodeUtilities/Common/Term.hpp>

#include <optional>

namespace alba::CodeUtilities {

class TermMatcher {
public:
    using TermTypeOptional = std::optional<TermType>;
    using StringOptional = std::optional<std::string>;
    using MatcherTypeOptional = std::optional<MatcherType>;
    explicit TermMatcher(TermType const termType);
    explicit TermMatcher(std::string const& content);
    explicit TermMatcher(MatcherType const matcherType);
    TermMatcher(TermType const termType, std::string const& content);
    friend std::ostream& operator<<(std::ostream& out, TermMatcher const& matcher);
    friend bool operator==(TermMatcher const& matcher, Term const& term);
    friend bool operator==(Term const& term, TermMatcher const& matcher);
    friend bool operator!=(TermMatcher const& matcher, Term const& term);
    friend bool operator!=(Term const& term, TermMatcher const& matcher);
    [[nodiscard]] TermTypeOptional const& getTermTypeOptional() const;
    [[nodiscard]] StringOptional const& getContentOptional() const;
    [[nodiscard]] MatcherTypeOptional const& getMatcherTypeOptional() const;

private:
    TermTypeOptional m_termTypeOptional;
    StringOptional m_contentOptional;
    MatcherTypeOptional m_matcherTypeOptional;
};

#define M(argument) alba::CodeUtilities::TermMatcher(argument)

}  // namespace alba::CodeUtilities
