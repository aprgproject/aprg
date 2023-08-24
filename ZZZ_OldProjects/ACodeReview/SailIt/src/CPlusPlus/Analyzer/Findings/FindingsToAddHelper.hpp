#pragma once

#include <CPlusPlus/Analyzer/Findings/FindingsToAdd.hpp>

namespace codeReview::FindingsToAddHelper {
bool isUnexpectedWhiteSpaceIncluded(FindingsToAdd const findingsToAdd);
bool isExpectedNewLineIncluded(FindingsToAdd const findingsToAdd);
bool isUnexpectedNewLineIncluded(FindingsToAdd const findingsToAdd);
}  // namespace codeReview
