#include "CPlusPlusReorganizeItems.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/Debug/AlbaDebug.hpp>

#include <numeric>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(
    strings const& items, strings const& scopeNames, strings const& headerSignatures)
    : m_items(items), m_scopeNames(scopeNames), m_headerSignatures(headerSignatures) {}

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(strings&& items, strings&& scopeNames, strings&& headerSignatures)
    : m_items(items), m_scopeNames(scopeNames), m_headerSignatures(headerSignatures) {}

Terms CPlusPlusReorganizeItems::getSortedAggregateTerms() const {
    Terms terms;
    SortItems sortedItems(getSortedItems());
    terms.emplace_back(TermType::WhiteSpace, "\n");
    bool hasMultiline = hasMultilineItem(sortedItems) || sortedItems.size() > 10;
    bool isPreviousAMultilineItem(hasMultiline);
    bool isPreviousACommentOrWhiteSpace(false);
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_items[sortItem.itemsIndex]);

        bool isMultilineItem = isMultiLine(sortItem.numberOfLines) || (hasMultiline && sortItem.isAccessControl);
        if ((isMultilineItem || isPreviousAMultilineItem) && !isPreviousACommentOrWhiteSpace) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }

        // terms.emplace_back(
        //     TermType::CommentMultiline, "/*BEGIN ADD (" + stringHelper::convertToString(sortItem.score) + "," +
        //                                     stringHelper::convertToString(sortItem.itemsIndex) + ")*/");
        terms.emplace_back(TermType::Aggregate, item);
        // terms.emplace_back(TermType::CommentMultiline, "/*END ADD*/");

        terms.emplace_back(TermType::WhiteSpace, "\n");
        isPreviousAMultilineItem = isMultilineItem;
        isPreviousACommentOrWhiteSpace = sortItem.isCommentOrWhiteSpace;
    }
    if (hasMultiline) {
        terms.emplace_back(TermType::WhiteSpace, "\n");
    }
    return terms;
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortedItems() const {
    SortItems sortItems(getSortItems());
    sortByComparingItems(sortItems);
    return sortItems;
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortItems() const {
    SortItems sortItems;
    sortItems.reserve(m_items.size());
    int index = 0;
    for (string const& item : m_items) {
        SortItem sortItem{0, 0, 0, false, false, false, index++};
        saveDetailsFromItemContent(sortItem, item);
        saveDetailsFromHeaderSignatures(sortItem, item);
        sortItems.emplace_back(sortItem);
    }
    // putAdditionalDetailsOnCommentsAndWhiteSpace(sortItems);
    return sortItems;
}

void CPlusPlusReorganizeItems::sortByComparingItems(SortItems& sortItems) {
    int start = 0;
    int end = 0;
    for (; end < static_cast<int>(sortItems.size()); end++) {
        if (sortItems[end].isDivider) {
            sort(sortItems.begin() + start, sortItems.begin() + end);
            start = end + 1;
        }
    }
    if (start < end) {
        sort(sortItems.begin() + start, sortItems.begin() + end);
    }
}

void CPlusPlusReorganizeItems::saveDetailsFromItemContent(SortItem& sortItem, string const& item) const {
    sortItem.numberOfLines = stringHelper::getNumberOfNewLines(item) + 1;
    int termIndex = 0;
    Terms terms(getTermsFromString(item));
    if (isAllWhiteSpaceOrComment(terms)) {
        sortItem.isCommentOrWhiteSpace = true;
    } else {
        Patterns searchPatterns(getSearchPatterns());
        bool isFound(true);
        while (isFound) {
            Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
            isFound = !hitIndexes.empty();
            if (isFound) {
                if (processAndShouldStop(terms, termIndex, sortItem, hitIndexes)) {
                    break;
                }
            }
        }
    }
}

void CPlusPlusReorganizeItems::saveDetailsFromHeaderSignatures(SortItem& sortItem, string const& item) const {
    sortItem.headerIndex = getBestHeaderIndex(item);
}

void CPlusPlusReorganizeItems::putAdditionalDetailsOnCommentsAndWhiteSpace(SortItems& sortItems) const {
    // dont use this code, it obscures+ the meaning
    int previousHeaderIndex = 0;
    int previousScore = 0;
    int previousNumberOfLines = 0;
    for (auto itItem = sortItems.rbegin(); itItem != sortItems.rend(); ++itItem) {
        if (itItem->isCommentOrWhiteSpace) {
            itItem->headerIndex = previousHeaderIndex;
            itItem->score = previousScore;
            itItem->numberOfLines = previousNumberOfLines;
        }
        previousScore = itItem->score;
        previousHeaderIndex = itItem->headerIndex;
        previousNumberOfLines = itItem->numberOfLines;
    }
}

Patterns CPlusPlusReorganizeItems::getSearchPatterns() {
    return Patterns{
        {M("(")},
        {M(";")},
        {M("{")},
        {M(":")},
        {M("static_assert")},
        {M("using")},
        {M("enum")},
        {M("struct")},
        {M("union")},
        {M("class")},
        {M("template")},
        {M("="), M("default")},
        {M("="), M("delete")},
        {M("operator"), M("=")},
        {M("operator")},
        {M("explicit")},
        {M("inline")},
        {M("static")},
        {M("constexpr")},
        {M("volatile")},
        {M("const")},
        {M("[[nodiscard]]")},
        {M(TermType::Attribute)},
        {M("bool")},
        {M("void")},
        {M("friend")},
        {M(TermType::Macro)},
        {M("public"), M(":")},
        {M("protected"), M(":")},
        {M("private"), M(":")}};
}

bool CPlusPlusReorganizeItems::processAndShouldStop(
    Terms& terms, int& termIndex, SortItem& sortItem, Indexes const& hitIndexes) const {
    int firstHitIndex = hitIndexes.front();
    if (terms[firstHitIndex].getContent() == ";" || terms[firstHitIndex].getContent() == "{" ||
        terms[firstHitIndex].getContent() == ":" || terms[firstHitIndex].getContent() == "static_assert") {
        return true;
    }
    if (terms[firstHitIndex].getContent() == "(") {
        if (m_scopeNames.back() == getIdentifierBeforeParenthesis(terms, firstHitIndex)) {
            sortItem.score += 100000;
        }
        moveToEndParenthesis(terms, termIndex, firstHitIndex);
        sortItem.score += 10000000;
    } else {
        if (terms[firstHitIndex].getContent() == "using") {
            sortItem.score += 600000000;
        } else if (terms[firstHitIndex].getContent() == "enum") {
            sortItem.score += 500000000;
        } else if (terms[firstHitIndex].getContent() == "struct") {
            sortItem.score += 400000000;
        } else if (terms[firstHitIndex].getContent() == "union") {
            sortItem.score += 300000000;
        } else if (terms[firstHitIndex].getContent() == "class") {
            sortItem.score += 200000000;
        } else if (terms[firstHitIndex].getContent() == "template") {
            sortItem.score += 1000000;
        } else if (terms[firstHitIndex].getContent() == "=" && terms[hitIndexes.back()].getContent() == "default") {
            sortItem.score += 300000;
        } else if (terms[firstHitIndex].getContent() == "=" && terms[hitIndexes.back()].getContent() == "delete") {
            sortItem.score += 200000;
        } else if (terms[firstHitIndex].getContent() == "operator" && terms[hitIndexes.back()].getContent() == "=") {
            sortItem.score += 20000;
        } else if (terms[firstHitIndex].getContent() == "operator") {
            sortItem.score += 10000;
        } else if (terms[firstHitIndex].getContent() == "explicit") {
            sortItem.score += 3000;
        } else if (terms[firstHitIndex].getContent() == "inline") {
            sortItem.score += 2000;
        } else if (terms[firstHitIndex].getContent() == "static") {
            sortItem.score += 1000;
        } else if (terms[firstHitIndex].getContent() == "constexpr") {
            sortItem.score += 300;
        } else if (terms[firstHitIndex].getContent() == "volatile") {
            sortItem.score += 200;
        } else if (terms[firstHitIndex].getContent() == "const") {
            sortItem.score += 100;
        } else if (terms[firstHitIndex].getContent() == "[[nodiscard]]") {
            sortItem.score += 20;
        } else if (terms[firstHitIndex].getTermType() == TermType::Attribute) {
            sortItem.score += 10;
        } else if (terms[firstHitIndex].getContent() == "void") {
            sortItem.score += 2;
        } else if (terms[firstHitIndex].getContent() == "bool") {
            sortItem.score += 1;
        } else if (terms[firstHitIndex].getContent() == "friend") {
            sortItem.score += -10000000;
        } else if (terms[firstHitIndex].getTermType() == TermType::Macro) {
            sortItem.isDivider = true;
        } else if (
            terms[firstHitIndex].getContent() == "public" || terms[firstHitIndex].getContent() == "protected" ||
            terms[firstHitIndex].getContent() == "private") {
            sortItem.isDivider = true;
            sortItem.isAccessControl = true;
        }
        termIndex = hitIndexes.back() + 1;
    }
    return false;
}

void CPlusPlusReorganizeItems::moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex) {
    termIndex = parenthesisIndex + 1;
    Patterns searchPatterns{{M(")")}, {M(";")}, {M("{")}, {M(":")}};
    bool isFound(true);
    bool isCloseParenthesisFound(false);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            if (terms[firstHitIndex].getContent() == ")") {
                termIndex = hitIndexes.back() + 1;
                isCloseParenthesisFound = true;
            }
            if (terms[firstHitIndex].getContent() == ";" || terms[firstHitIndex].getContent() == "{" ||
                terms[firstHitIndex].getContent() == ":") {
                if (!isCloseParenthesisFound) {
                    termIndex = hitIndexes.back();
                }
                break;
            }
        }
    }
}

int CPlusPlusReorganizeItems::getBestHeaderIndex(string const& item) const {
    string itemSignature = getFunctionSignature(item);
    int bestDifference = static_cast<int>(itemSignature.size());
    int bestHeaderIndex = 0;
    bool isFirst(true);
    int headerIndex = 0;
    for (string const& headerSignature : m_headerSignatures) {
        int difference = static_cast<int>(getLevenshteinDistance(itemSignature, headerSignature));
        if (isFirst) {
            bestDifference = difference;
            isFirst = false;
        }
        if (bestDifference > difference) {
            bestDifference = difference;
            bestHeaderIndex = headerIndex;
        }
        ++headerIndex;
    }
    if (bestDifference < 10 &&
        static_cast<double>(bestDifference) / static_cast<double>(itemSignature.length()) < 0.10) {
        return bestHeaderIndex;
    }
    return static_cast<int>(m_headerSignatures.size());
}

string CPlusPlusReorganizeItems::getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex) {
    int beforeParenthesis = parenthesisIndex - 1;
    Patterns searchPatterns{{M(TermType::Identifier)}};
    Indexes hitIndexes = checkPatternAt(terms, beforeParenthesis, searchPatterns);
    if (!hitIndexes.empty()) {
        return terms[hitIndexes.front()].getContent();
    }
    return {};
}

int CPlusPlusReorganizeItems::getTotalNumberLines(SortItems const& sortItems) {
    return accumulate(sortItems.cbegin(), sortItems.cend(), 0, [](int const partialResult, SortItem const& sortItem) {
        return partialResult + sortItem.numberOfLines;
    });
}

bool CPlusPlusReorganizeItems::hasMultilineItem(SortItems const& sortItems) {
    return any_of(sortItems.cbegin(), sortItems.cend(), [&](SortItem const& sortItem) {
        return isMultiLine(sortItem.numberOfLines);
    });
}

bool CPlusPlusReorganizeItems::isMultiLine(int const numberOfLines) { return numberOfLines > 2; }

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2) {
    if (item1.headerIndex == item2.headerIndex) {
        if (item1.score == item2.score) {
            return item1.itemsIndex < item2.itemsIndex;
        }
        return item1.score > item2.score;
    }
    return item1.headerIndex < item2.headerIndex;
}

}  // namespace alba::CodeUtilities
