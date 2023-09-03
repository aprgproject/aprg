#include "FindPatterns.hpp"

#include <CodeUtilities/Common/TermUtilities.hpp>

#include <algorithm>

using namespace std;

namespace alba::CodeUtilities {

PatternIndexes findFirstPatternIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& matchers, int const startIndex) {
    for (int termIndex = startIndex; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        int matchIndex = 0;
        PatternIndexes patternIndexes;
        for (int termIndexInPattern = termIndex;
             termIndexInPattern < static_cast<int>(terms.size()) && matchIndex < static_cast<int>(matchers.size());
             ++termIndexInPattern) {
            Term const& currentTerm(terms[termIndexInPattern]);
            bool isAMatch = currentTerm == matchers[matchIndex];
            if (isAMatch) {
                patternIndexes.emplace_back(termIndexInPattern);
                ++matchIndex;
            }
            if (!isCommentOrWhiteSpace(currentTerm) && !isAMatch) {
                break;
            }
        }
        if (static_cast<int>(patternIndexes.size()) == static_cast<int>(matchers.size())) {
            return patternIndexes;
        }
    }
    return {};
}

}  // namespace alba::CodeUtilities
