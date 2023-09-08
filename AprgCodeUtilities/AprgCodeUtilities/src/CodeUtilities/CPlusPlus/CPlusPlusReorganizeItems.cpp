#include "CPlusPlusReorganizeItems.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>

#include <algorithm>
#include <numeric>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(
    ScopeType const scopeType, strings const& items, strings const& scopeNames, strings const& headerSignatures)
    : m_scopeType(scopeType), m_items(items), m_scopeNames(scopeNames), m_headerSignatures(headerSignatures) {
    fixItemContents();
}

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(
    ScopeType const scopeType, strings&& items, strings&& scopeNames, strings&& headerSignatures)
    : m_scopeType(scopeType), m_items(items), m_scopeNames(scopeNames), m_headerSignatures(headerSignatures) {
    fixItemContents();
}

Terms CPlusPlusReorganizeItems::getSortedAggregateTerms() const {
    Terms terms;
    SortItems sortedItems(getSortedItems());
    terms.emplace_back(TermType::WhiteSpace, "\n");
    bool hasMultiline = hasMultilineItem(sortedItems) || sortedItems.size() > 10;
    bool isPreviousAMultilineItem(hasMultiline);
    bool isFirst(true);
    bool isPreviousAnAccessControl(false);
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_items[sortItem.itemsIndex]);
        bool isAccessControl = sortItem.itemType == ItemType::AccessControl;
        bool isMultilineItem = isMultiLine(sortItem.numberOfLines) || isAccessControl;
        bool shouldPreventNewLine = (isFirst && isAccessControl) || isPreviousAnAccessControl;
        if ((isMultilineItem || isPreviousAMultilineItem) && !shouldPreventNewLine) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }

        // terms.emplace_back(
        //     TermType::CommentMultiline, "/*BEGIN ADD (" + stringHelper::convertToString(sortItem.score) + "," +
        //                                     stringHelper::convertToString(sortItem.itemsIndex) + ")*/");
        terms.emplace_back(TermType::Aggregate, item);
        // terms.emplace_back(TermType::CommentMultiline, "/*END ADD*/");

        terms.emplace_back(TermType::WhiteSpace, "\n");
        isPreviousAMultilineItem = isMultilineItem;
        isFirst = false;
        isPreviousAnAccessControl = isAccessControl;
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
        SortItem sortItem{0, 0, 0, false, ItemType::Unknown, index++, {}};
        saveDetailsBasedFromItem(sortItem, item);
        saveDetailsFromHeaderSignatures(sortItem, item);
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

void CPlusPlusReorganizeItems::fixItemContents() {
    for (string& item : m_items) {
        Terms terms(getTermsFromString(item));
        replaceCommentsWithExtraLine(terms, 0);
        item = getCombinedContents(terms);
    }
}

void CPlusPlusReorganizeItems::saveDetailsBasedFromItem(SortItem& sortItem, string const& item) const {
    Terms terms(getTermsFromString(item));
    saveDetailsBasedFromItemTerms(sortItem, item, terms);
}

void CPlusPlusReorganizeItems::saveDetailsFromHeaderSignatures(SortItem& sortItem, string const& item) const {
    sortItem.headerIndex = getBestHeaderIndex(item);
}

Patterns CPlusPlusReorganizeItems::getSearchPatterns() {
    return Patterns{
        {M("(")},
        {M(";")},
        {M("{")},
        {M(":")},
        {M("static_assert")},
        {M("namespace")},
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
        {M("virtual")},
        {M("constexpr")},
        {M("static")},
        {M("volatile")},
        {M("const")},
        {M("[[nodiscard]]")},
        {M(TermType::Attribute)},
        {M("friend")},
        {M(TermType::Macro)},
        {M("public"), M(":")},
        {M("protected"), M(":")},
        {M("private"), M(":")}};
}

void CPlusPlusReorganizeItems::saveDetailsBasedFromItemTerms(
    SortItem& sortItem, string const& item, Terms const& terms) const {
    int termIndex = 0;
    Patterns searchPatterns(getSearchPatterns());
    bool isFound(true);
    bool isConst(false);
    sortItem.numberOfLines = stringHelper::getNumberOfNewLines(getTextWithoutCommentsWithNewLine(terms)) + 1;
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int firstHitIndex = hitIndexes.front();
            int lastHitIndex = hitIndexes.back();
            Term const& firstTerm(terms[firstHitIndex]);
            Term const& lastTerm(terms[lastHitIndex]);
            if (firstTerm.getContent() == ";" || firstTerm.getContent() == "{" || firstTerm.getContent() == ":") {
                break;
            }
            if (firstTerm.getContent() == "static_assert") {
                sortItem.itemType = ItemType::Declaration;
                break;
            }
            if (firstTerm.getContent() == "namespace") {
                sortItem.itemType = ItemType::Namespace;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "using") {
                sortItem.itemType = ItemType::Declaration;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "(") {
                if (m_scopeNames.back() == getIdentifierBeforeParenthesis(terms, firstHitIndex)) {
                    sortItem.score += 100000;
                }
                moveToEndParenthesis(terms, termIndex, firstHitIndex);
                sortItem.score += 10000000;
                sortItem.itemType = ItemType::Function;
            } else {
                if (firstTerm.getContent() == "enum") {
                    sortItem.score += 500000000;
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "struct") {
                    sortItem.score += 400000000;
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "union") {
                    sortItem.score += 300000000;
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "class") {
                    sortItem.score += 200000000;
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "template") {
                    sortItem.itemType = ItemType::Template;
                    sortItem.isDivider = true;
                    break;
                } else if (firstTerm.getContent() == "=" && lastTerm.getContent() == "default") {
                    sortItem.score += 300000;
                } else if (firstTerm.getContent() == "=" && lastTerm.getContent() == "delete") {
                    sortItem.score += 200000;
                } else if (firstTerm.getContent() == "operator" && lastTerm.getContent() == "=") {
                    sortItem.score += 30000;
                } else if (firstTerm.getContent() == "operator") {
                    sortItem.score += 20000;
                } else if (firstTerm.getContent() == "explicit") {
                    sortItem.score += 5000;
                } else if (firstTerm.getContent() == "inline") {
                    sortItem.score += 4000;
                } else if (firstTerm.getContent() == "virtual") {
                    sortItem.score += 3000;
                } else if (firstTerm.getContent() == "constexpr") {
                    sortItem.score += 2000;
                    isConst = true;
                } else if (firstTerm.getContent() == "static") {
                    sortItem.score += 1000;
                } else if (firstTerm.getContent() == "volatile") {
                    sortItem.score += 200;
                } else if (firstTerm.getContent() == "const") {
                    if (sortItem.itemType == ItemType::Function) {
                        // check the last const
                        sortItem.score += 100;
                    }
                    isConst = true;
                } else if (firstTerm.getContent() == "[[nodiscard]]") {
                    sortItem.score += 20;
                } else if (firstTerm.getTermType() == TermType::Attribute) {
                    sortItem.score += 10;
                } else if (firstTerm.getContent() == "friend") {
                    sortItem.score += -10000000;
                } else if (firstTerm.getTermType() == TermType::Macro) {
                    sortItem.itemType = ItemType::Macro;
                    sortItem.isDivider = true;
                    break;
                } else if (
                    firstTerm.getContent() == "public" || firstTerm.getContent() == "protected" ||
                    firstTerm.getContent() == "private") {
                    sortItem.itemType = ItemType::AccessControl;
                    sortItem.isDivider = true;
                    break;
                }
                termIndex = lastHitIndex + 1;
            }
        }
    }
    if (sortItem.itemType == ItemType::Function) {
        sortItem.functionSignature = getFunctionSignature(item);
        sortItem.score += getScoreAtReturnOfFunctionSignature(sortItem.functionSignature);
    }
    if (sortItem.itemType == ItemType::Unknown) {
        sortItem.itemType = ItemType::Data;
        if (m_scopeType == ScopeType::Namespace) {
            if (isConst) {
                sortItem.score += 700000000;
            } else {
                sortItem.score += 100000000;
            }
        } else {
            sortItem.score = 0;
        }
    }
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
            int lastHitIndex = hitIndexes.back();
            Term const& firstTerm(terms[firstHitIndex]);
            if (firstTerm.getContent() == ")") {
                termIndex = lastHitIndex + 1;
                isCloseParenthesisFound = true;
            }
            if (firstTerm.getContent() == ";" || firstTerm.getContent() == "{" || firstTerm.getContent() == ":") {
                if (!isCloseParenthesisFound) {
                    termIndex = lastHitIndex;
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
        static_cast<double>(bestDifference) / static_cast<double>(itemSignature.length()) < 0.20) {
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

int CPlusPlusReorganizeItems::getScoreAtReturnOfFunctionSignature(string const& functionSignature) {
    int score = 0;
    Terms terms(getTermsFromString(functionSignature));
    Patterns searchPatterns{{M(TermType::PrimitiveType)}, {M(TermType::Identifier)}, {M(TermType::Keyword)}};
    Indexes hitIndexes = searchForPatternsForwards(terms, 0, searchPatterns);
    if (!hitIndexes.empty()) {
        int firstHitIndex = hitIndexes.front();
        Term const& firstTerm(terms[firstHitIndex]);
        if (firstTerm.getTermType() == TermType::PrimitiveType) {
            if (firstTerm.getContent() == "bool") {
                score = 6;
            } else if (firstTerm.getContent() == "void") {
                score = 3;
            } else {
                score = 5;
            }
        } else if (firstTerm.getTermType() == TermType::Identifier) {
            if (firstTerm.getContent() == "TEST" || firstTerm.getContent() == "TEST_F") {
                score = 2;
            } else {
                score = 4;
            }
        } else if (firstTerm.getTermType() == TermType::Keyword) {
            score = 1;
        }
    }
    return score;
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
