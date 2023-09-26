#pragma once

#include <CodeUtilities/Common/Matcher/LogicalGroupOfMatchers.hpp>
#include <CodeUtilities/Common/Matcher/Matcher.hpp>
#include <CodeUtilities/Common/Matcher/SingleMatcher.hpp>

#define M(argument)               \
    alba::CodeUtilities::Matcher( \
        alba::CodeUtilities::Matcher::Type::Single, std::make_unique<alba::CodeUtilities::SingleMatcher>(argument))
#define M_NOT(argument)                             \
    alba::CodeUtilities::Matcher(                   \
        alba::CodeUtilities::Matcher::Type::Single, \
        std::make_unique<alba::CodeUtilities::SingleMatcher>(true, argument))
#define M_AND(...)                                                           \
    alba::CodeUtilities::Matcher(                                            \
        alba::CodeUtilities::Matcher::Type::Group,                           \
        std::make_unique<alba::CodeUtilities::LogicalGroupOfMatchers>(       \
            alba::CodeUtilities::LogicalGroupOfMatchers::OperationType::And, \
            alba::CodeUtilities::LogicalGroupOfMatchers::Matchers{__VA_ARGS__}))
#define M_OR(...)                                                           \
    alba::CodeUtilities::Matcher(                                           \
        alba::CodeUtilities::Matcher::Type::Group,                          \
        std::make_unique<alba::CodeUtilities::LogicalGroupOfMatchers>(      \
            alba::CodeUtilities::LogicalGroupOfMatchers::OperationType::Or, \
            alba::CodeUtilities::LogicalGroupOfMatchers::Matchers{__VA_ARGS__}))
