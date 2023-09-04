#pragma once

#include <CodeUtilities/Common/TermMatcher.hpp>

#include <string>

namespace alba::CodeUtilities {

using PatternIndexes = std::vector<int>;

PatternIndexes findFirstPatternIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& matchers, int const startIndex = 0);

void combineTermsInPlace(Terms& terms, TermType const newTermType, int const startIndex, int const endIndex);

std::string convertToString(TermType const termType);

bool isComment(Term const& term);
bool isWhiteSpace(Term const& term);
bool isCommentOrWhiteSpace(Term const& term);

}  // namespace alba::CodeUtilities
