#pragma once

#include <CodeUtilities/Common/Matcher/BaseMatcher.hpp>

#include <memory>

namespace alba::CodeUtilities {

class Matcher {
public:
    enum class Type { Single, Group };

    Matcher(Type const type, BaseMatcher::BaseMatcherPtr&& baseMatcher);
    ~Matcher() = default;
    Matcher(Matcher const& matcher);
    Matcher(Matcher&&) noexcept = default;
    Matcher& operator=(Matcher const&);
    Matcher& operator=(Matcher&&) noexcept = default;
    [[nodiscard]] bool isAMatch(Term const& term) const;
    friend std::ostream& operator<<(std::ostream& out, Matcher const& matcher);
    friend bool operator==(Matcher const& matcher, Term const& term);
    friend bool operator==(Term const& term, Matcher const& matcher);
    friend bool operator!=(Matcher const& matcher, Term const& term);
    friend bool operator!=(Term const& term, Matcher const& matcher);

private:
    Type m_type;
    BaseMatcher::BaseMatcherPtr m_baseMatcherPtr;
};

}  // namespace alba::CodeUtilities
