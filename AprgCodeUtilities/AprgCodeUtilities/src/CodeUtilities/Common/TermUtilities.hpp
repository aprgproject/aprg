#pragma once

#include <CodeUtilities/Common/TermMatcher.hpp>

#include <optional>
#include <string>
#include <vector>

namespace alba::CodeUtilities {

using Indexes = std::vector<int>;
using IndexesOptional = std::optional<Indexes>;

Indexes searchForPatternsForwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns);
Indexes searchForPatternsBackwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns);
IndexesOptional checkPatternAt(Terms const& terms, int const termIndex, Patterns const& searchPatterns);

void combineTermsInPlace(Terms& terms, TermType const newTermType, int const startIndex, int const endIndex);
void changeTerm(Term& term, TermType const newTermType, std::string const& content);

std::string convertToString(TermType const termType);
std::string convertToString(TermSpecialMatcherType const type);

bool isAMatch(TermSpecialMatcherType const specialMatcherType, Term const& term);
bool isComment(Term const& term);
bool isWhiteSpace(Term const& term);
bool isCommentOrWhiteSpace(Term const& term);

}  // namespace alba::CodeUtilities
