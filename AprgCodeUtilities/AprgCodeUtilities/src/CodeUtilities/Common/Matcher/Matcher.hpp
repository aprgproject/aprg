#pragma once

#include <CodeUtilities/Common/Matcher/MatcherType.hpp>
#include <CodeUtilities/Common/Term/Term.hpp>

#include <optional>

namespace alba::CodeUtilities {

class Matcher {
public:
    using TermTypeOptional = std::optional<TermType>;
    using StringOptional = std::optional<std::string>;
    using MatcherTypeOptional = std::optional<MatcherType>;
    explicit Matcher(TermType const termType);
    explicit Matcher(std::string const& content);
    explicit Matcher(MatcherType const matcherType);
    Matcher(TermType const termType, std::string const& content);
    [[nodiscard]] MatcherTypeOptional const& getMatcherTypeOptional() const;
    [[nodiscard]] StringOptional const& getContentOptional() const;
    [[nodiscard]] TermTypeOptional const& getTermTypeOptional() const;
    friend std::ostream& operator<<(std::ostream& out, Matcher const& matcher);
    friend bool operator==(Matcher const& matcher, Term const& term);
    friend bool operator==(Term const& term, Matcher const& matcher);
    friend bool operator!=(Matcher const& matcher, Term const& term);
    friend bool operator!=(Term const& term, Matcher const& matcher);

private:
    TermTypeOptional m_termTypeOptional;
    StringOptional m_contentOptional;
    MatcherTypeOptional m_matcherTypeOptional;
};

#define M(argument) alba::CodeUtilities::Matcher(argument)

}  // namespace alba::CodeUtilities
