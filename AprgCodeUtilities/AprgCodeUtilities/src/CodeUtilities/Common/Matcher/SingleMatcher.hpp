#pragma once

#include <CodeUtilities/Common/Matcher/BaseMatcher.hpp>
#include <CodeUtilities/Common/Matcher/SpecialMatcherType.hpp>

#include <optional>

namespace alba::CodeUtilities {

class SingleMatcher : public BaseMatcher {
public:
    using TermTypeOptional = std::optional<TermType>;
    using StringOptional = std::optional<std::string>;
    using SpecialMatcherTypeOptional = std::optional<SpecialMatcherType>;
    // constructors
    explicit SingleMatcher(TermType const termType);
    explicit SingleMatcher(std::string const& content);
    explicit SingleMatcher(SpecialMatcherType const matcherType);
    SingleMatcher(TermType const termType, std::string const& content);
    SingleMatcher(bool const m_shouldInverse, TermType const termType);
    SingleMatcher(bool const m_shouldInverse, std::string const& content);
    SingleMatcher(bool const m_shouldInverse, SpecialMatcherType const matcherType);
    SingleMatcher(bool const m_shouldInverse, TermType const termType, std::string const& content);
    // other functions
    [[nodiscard]] BaseMatcherPtr createClone() const override;
    [[nodiscard]] bool isAMatch(Term const& term) const override;
    [[nodiscard]] SpecialMatcherTypeOptional const& getSpecialMatcherTypeOptional() const;
    [[nodiscard]] StringOptional const& getContentOptional() const;
    [[nodiscard]] TermTypeOptional const& getTermTypeOptional() const;
    friend std::ostream& operator<<(std::ostream& out, SingleMatcher const& matcher);

private:
    [[nodiscard]] bool doesContentMatch(Term const& term) const;
    bool m_shouldInverse{false};
    TermTypeOptional m_termTypeOptional;
    StringOptional m_contentOptional;
    SpecialMatcherTypeOptional m_specialMatcherTypeOptional;
};

}  // namespace alba::CodeUtilities
