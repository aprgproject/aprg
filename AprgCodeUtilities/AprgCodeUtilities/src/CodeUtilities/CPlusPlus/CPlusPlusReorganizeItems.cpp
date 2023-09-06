#include "CPlusPlusReorganizeItems.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

namespace {

void findEndParenthesis(Terms const& terms, int& termIndex, int parenthesisIndex) {
    termIndex = parenthesisIndex;
    Patterns searchPatterns{{M(")")}, {M(";")}, {M("{")}};
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            if (terms[firstHitIndex].getContent() == ";" || terms[firstHitIndex].getContent() == "{") {
                break;
            }
            if (terms[firstHitIndex].getContent() == ")") {
                termIndex = hitIndexes.back() + 1;
            }
        }
    }
}

}  // namespace

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(Strings&& items) : m_items(items) {}

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(Strings const& items) : m_items(items) {}

Terms CPlusPlusReorganizeItems::getSortedAggregateTerms() const {
    Terms terms;
    SortItems sortedItems(getSortedItems());
    terms.emplace_back(TermType::WhiteSpace, "\n");
    for (SortItem const& sortItem : sortedItems) {
        // terms.emplace_back(
        //     TermType::CommentMultiline, "/*BEGIN ADD " + stringHelper::convertToString(sortItem.score) + "*/");
        terms.emplace_back(TermType::Aggregate, m_items[sortItem.itemsIndex]);
        // terms.emplace_back(TermType::CommentMultiline, "/*END ADD*/");
        terms.emplace_back(TermType::WhiteSpace, "\n");
    }
    return terms;
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortedItems() const {
    SortItems sortItems(getSortItems());
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
    return sortItems;
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortItems() const {
    SortItems sortItems;
    sortItems.reserve(m_items.size());
    int index = 0;
    for (string const& item : m_items) {
        SortItem sortItem{};
        saveDetails(sortItem, item);
        sortItem.itemsIndex = index++;
        sortItems.emplace_back(sortItem);
    }
    return sortItems;
}

void CPlusPlusReorganizeItems::saveDetails(SortItem& sortItem, string const& item) {
    bool isDivider(false);
    int score = 0;
    Terms terms(getTermsFromString(item));
    Patterns searchPatterns{
        {M("(")},
        {M(";")},
        {M("{")},
        {M("static_assert")},
        {M("using")},
        {M("enum")},
        {M("struct")},
        {M("union")},
        {M("class")},
        {M("template")},
        {M("="), M("default")},
        {M("="), M("delete")},
        {M("explicit")},
        {M("operator")},
        {M("static")},
        {M("constexpr")},
        {M("const")},
        {M("[[nodiscard]]")},
        {M("bool")},
        {M("friend")},
        {M(TermType::Macro)},
        {M("public"), M(":")},
        {M("protected"), M(":")},
        {M("private"), M(":")}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            if (terms[firstHitIndex].getContent() == ";" || terms[firstHitIndex].getContent() == "{" ||
                terms[firstHitIndex].getContent() == "static_assert") {
                break;
            }
            if (terms[firstHitIndex].getContent() == "(") {
                findEndParenthesis(terms, termIndex, firstHitIndex);
                score += 1000000;
            } else {
                if (terms[firstHitIndex].getContent() == "using") {
                    score += 60000000;
                } else if (terms[firstHitIndex].getContent() == "enum") {
                    score += 50000000;
                } else if (terms[firstHitIndex].getContent() == "struct") {
                    score += 40000000;
                } else if (terms[firstHitIndex].getContent() == "union") {
                    score += 30000000;
                } else if (terms[firstHitIndex].getContent() == "class") {
                    score += 20000000;
                } else if (terms[firstHitIndex].getContent() == "template") {
                    score += 100000;
                } else if (
                    terms[firstHitIndex].getContent() == "=" && terms[hitIndexes.back()].getContent() == "default") {
                    score += 40000;
                } else if (
                    terms[firstHitIndex].getContent() == "=" && terms[hitIndexes.back()].getContent() == "delete") {
                    score += 30000;
                } else if (terms[firstHitIndex].getContent() == "explicit") {
                    score += 20000;
                } else if (terms[firstHitIndex].getContent() == "operator") {
                    score += 10000;
                } else if (terms[firstHitIndex].getContent() == "static") {
                    score += 1000;
                } else if (terms[firstHitIndex].getContent() == "constexpr") {
                    score += 200;
                } else if (terms[firstHitIndex].getContent() == "const") {
                    score += 100;
                } else if (terms[firstHitIndex].getContent() == "[[nodiscard]]") {
                    score += 10;
                } else if (terms[firstHitIndex].getContent() == "bool") {
                    score += 1;
                } else if (terms[firstHitIndex].getContent() == "friend") {
                    score += -1000000;
                } else if (
                    terms[firstHitIndex].getTermType() == TermType::Macro ||
                    terms[firstHitIndex].getContent() == "public" || terms[firstHitIndex].getContent() == "protected" ||
                    terms[firstHitIndex].getContent() == "private") {
                    isDivider = true;
                }
                termIndex = hitIndexes.back() + 1;
            }
        }
    }
    sortItem.score = score;
    sortItem.isDivider = isDivider;
}

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2) {
    if (item1.score == item2.score) {
        return item1.itemsIndex < item2.itemsIndex;
    }
    return item1.score > item2.score;
}

}  // namespace alba::CodeUtilities
