#include "CPlusPlusReorganizeItems.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(
    strings const& scopeNames, strings const& items, strings const& headerItems)
    : m_scopeNames(scopeNames), m_items(items), m_headerItems(headerItems) {}

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(strings&& scopeNames, strings&& items, strings&& headerItems)
    : m_scopeNames(scopeNames), m_items(items), m_headerItems(headerItems) {}

Terms CPlusPlusReorganizeItems::getSortedAggregateTerms() const {
    Terms terms;
    SortItems sortedItems(getSortedItems());
    terms.emplace_back(TermType::WhiteSpace, "\n");
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_items[sortItem.itemsIndex]);
        // terms.emplace_back(
        //     TermType::CommentMultiline, "/*BEGIN ADD " + convertToString(sortItem.score) + "*/");
        terms.emplace_back(TermType::Aggregate, item);
        // terms.emplace_back(TermType::CommentMultiline, "/*END ADD*/");
        terms.emplace_back(TermType::WhiteSpace, "\n");
        if (sortItem.addNewLineAtEnd) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }
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
        SortItem sortItem{static_cast<int>(m_headerItems.size()), 0, false, false, index++};
        saveDetailsFromItemContent(sortItem, item);
        saveDetailsFromItemContent(sortItem, item);
        sortItems.emplace_back(sortItem);
    }
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

void CPlusPlusReorganizeItems::saveDetailsFromHeaderItemPosition(SortItem& sortItem, string const& item) const {}

void CPlusPlusReorganizeItems::saveDetailsFromItemContent(SortItem& sortItem, string const& item) const {
    int termIndex = 0;
    Terms terms(getTermsFromString(item));
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
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, Patterns{{M("}")}});
        isFound = !hitIndexes.empty();
        if (isFound) {
            sortItem.addNewLineAtEnd = true;
            break;
        }
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
            sortItem.addNewLineAtEnd = true;
        }
        termIndex = hitIndexes.back() + 1;
    }
    return false;
}

void CPlusPlusReorganizeItems::moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex) {
    termIndex = parenthesisIndex;
    Patterns searchPatterns{{M(")")}, {M(";")}, {M("{")}, {M(":")}};
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            if (terms[firstHitIndex].getContent() == ";" || terms[firstHitIndex].getContent() == "{" ||
                terms[firstHitIndex].getContent() == ":") {
                break;
            }
            if (terms[firstHitIndex].getContent() == ")") {
                termIndex = hitIndexes.back() + 1;
            }
        }
    }
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

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2) {
    if (item1.headerItemPosition == item2.headerItemPosition) {
        if (item1.score == item2.score) {
            return item1.itemsIndex < item2.itemsIndex;
        }
        return item1.score > item2.score;
    }
    return item1.headerItemPosition < item2.headerItemPosition;
}

}  // namespace alba::CodeUtilities
