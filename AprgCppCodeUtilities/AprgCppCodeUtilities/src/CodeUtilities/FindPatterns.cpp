#include "FindPatterns.hpp"

#include <CodeUtilities/TermUtilities.hpp>

#include <algorithm>

using namespace std;

namespace alba::CodeUtilities {

IndexOptional findFirstPatternIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& termMatchers, int const startIndex) {
    for (int termIndex = startIndex; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        Term const& currentTerm(terms[termIndex]);
        if (!isComment(currentTerm) && !isWhiteSpace(currentTerm)) {
            int matchIndex = 0;
            for (; matchIndex < static_cast<int>(termMatchers.size()) && currentTerm == termMatchers[matchIndex];
                 ++matchIndex) {
            }
            if (matchIndex == static_cast<int>(termMatchers.size())) {
                return {termIndex};
            }
        }
    }
    return {};
}

Indexes findPatternsIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& termMatchers, int const startIndex) {
    Indexes result;
    for (int termIndex = startIndex; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        Term const& currentTerm(terms[termIndex]);
        if (!isComment(currentTerm) && !isWhiteSpace(currentTerm)) {
            int matchIndex = 0;
            for (; matchIndex < static_cast<int>(termMatchers.size()) && currentTerm == termMatchers[matchIndex];
                 ++matchIndex) {
            }
            if (matchIndex == static_cast<int>(termMatchers.size())) {
                result.emplace_back(termIndex);
            }
        }
    }
    return result;
}

}  // namespace alba::CodeUtilities
