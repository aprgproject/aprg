#include "CPlusPlusReorganizeItems.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(Data const& data) : m_data(data) { fixItemContents(); }

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(Data&& data) : m_data(data) { fixItemContents(); }

Terms CPlusPlusReorganizeItems::getSortedAggregateTerms() const {
    Terms terms;
    SortItems const sortedItems(getSortedItems());
    terms.emplace_back(TermType::WhiteSpace, "\n");
    bool const isMultilineScope = hasMultilineItem(sortedItems) && m_data.scopeType != ScopeType::EnumClass;
    bool isPreviousAMultilineItem(isMultilineScope);
    bool isFirst(true);
    bool isPreviousAnAccessControl(false);
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_data.items[sortItem.itemsIndex]);
        bool const isAccessControl = sortItem.itemType == ItemType::AccessControl;
        bool const isMultilineItem = isMultiLine(sortItem.numberOfLines) || isAccessControl;
        bool const shouldPreventNewLine =
            (isFirst && isAccessControl) || isPreviousAnAccessControl || m_data.scopeType == ScopeType::EnumClass;
        if ((isMultilineItem || isPreviousAMultilineItem) && !shouldPreventNewLine) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }

        // stringstream commentStream;
        // commentStream << "/*BEGIN ADD (" << sortItem.headerIndex << ",0x" << hex << sortItem.score << "," << dec
        //               << sortItem.itemsIndex << ")*/";
        // terms.emplace_back(TermType::CommentMultiline, commentStream.str());
        terms.emplace_back(TermType::Aggregate, item);
        // terms.emplace_back(TermType::CommentMultiline, "/*END ADD*/");
        terms.emplace_back(TermType::WhiteSpace, "\n");
        isPreviousAMultilineItem = isMultilineItem;
        isFirst = false;
        isPreviousAnAccessControl = isAccessControl;
    }
    if (isMultilineScope) {
        terms.emplace_back(TermType::WhiteSpace, "\n");
    }
    return terms;
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
        {M("template")},
        {M(TermType::Macro)},
        {M("public"), M(":")},
        {M("protected"), M(":")},
        {M("private"), M(":")},
        {M("enum"), M("class")},
        {M("enum")},
        {M("struct")},
        {M("union")},
        {M("class")},
        {M("="), M("default")},
        {M("="), M("delete")},
        {M("operator"), M("=")},
        {M("operator")},
        {M("constexpr")},
        {M("inline")},
        {M("explicit")},
        {M("virtual")},
        {M("override")},
        {M("static")},
        {M("[[nodiscard]]")},
        {M(TermType::Attribute)},
        {M("volatile")},
        {M("const")},
        {M("friend")}};
}

string CPlusPlusReorganizeItems::getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex) {
    int const beforeParenthesis = parenthesisIndex - 1;
    Patterns const searchPatterns{{M(TermType::Identifier)}};
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

void CPlusPlusReorganizeItems::moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex) {
    termIndex = parenthesisIndex + 1;
    Patterns const searchPatterns{{M(")")}, {M(";")}, {M("{")}, {M(":")}};
    bool isFound(true);
    bool isCloseParenthesisFound(false);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            int const lastHitIndex = hitIndexes.back();
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

void CPlusPlusReorganizeItems::saveDetailsBasedFromFunctionSignature(
    SortItem& sortItem, string const& functionSignature) {
    Terms terms(getTermsFromString(functionSignature));
    Patterns const searchPatterns{{M(TermType::PrimitiveType)}, {M(TermType::Identifier)}, {M(TermType::Keyword)}};
    Indexes hitIndexes = searchForPatternsForwards(terms, 0, searchPatterns);
    if (!hitIndexes.empty()) {
        int const firstHitIndex = hitIndexes.front();
        Term const& firstTerm(terms[firstHitIndex]);
        if (firstTerm.getTermType() == TermType::PrimitiveType) {
            if (firstTerm.getContent() == "bool") {
                sortItem.score += 0x2;  // returnType: bool
            } else if (firstTerm.getContent() == "void") {
                sortItem.score += 0x5;  // returnType: void
            } else {
                sortItem.score += 0x3;  // returnType: primitive type
            }
        } else if (firstTerm.getTermType() == TermType::Identifier) {
            if (firstTerm.getContent() == "TEST" || firstTerm.getContent() == "TEST_F") {
                sortItem.score += 0x1;  // returnType: gtest tests
            } else if (firstTerm.getContent() == "size_t") {
                sortItem.score += 0x3;  // returnType: same level as primitive type
            } else {
                sortItem.score += 0x4;  // returnType: user type
            }
        } else if (firstTerm.getTermType() == TermType::Keyword) {
            sortItem.score += 0x6;
        }
        sortItem.functionReturnTypeName = firstTerm.getContent();
    }
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortedItems() const {
    SortItems sortItems(getSortItems());
    sortByComparingItems(sortItems);
    return sortItems;
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortItems() const {
    SortItems sortItems;
    sortItems.reserve(m_data.items.size());
    int index = 0;
    for (string const& item : m_data.items) {
        SortItem sortItem{0, 0, 0, false, ItemType::Unknown, index++, {}};
        saveDetailsFromHeaderSignatures(sortItem, item);
        saveDetailsBasedFromItem(sortItem, item);
        sortItems.emplace_back(sortItem);
    }
    return sortItems;
}

int CPlusPlusReorganizeItems::getBestHeaderIndex(string const& item) const {
    string const itemSignature = getFunctionSignature(item);
    int bestDifference = static_cast<int>(itemSignature.size());
    int bestHeaderIndex = 0;
    bool isFirst(true);
    int headerIndex = 0;
    for (string const& headerSignature : m_data.headerSignatures) {
        int const difference = static_cast<int>(getLevenshteinDistance(itemSignature, headerSignature));
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
    return static_cast<int>(m_data.headerSignatures.size());
}

void CPlusPlusReorganizeItems::saveDetailsFromHeaderSignatures(SortItem& sortItem, string const& item) const {
    sortItem.headerIndex = getBestHeaderIndex(item);
}

void CPlusPlusReorganizeItems::saveDetailsBasedFromItem(SortItem& sortItem, string const& item) const {
    Terms const terms(getTermsFromString(item));
    saveDetailsBasedFromItemTerms(sortItem, item, terms);
}

void CPlusPlusReorganizeItems::saveDetailsBasedFromItemTerms(
    SortItem& sortItem, string const& item, Terms const& terms) const {
    int termIndex = 0;
    Patterns const searchPatterns(getSearchPatterns());
    bool isFound(true);
    bool isConst(false);
    bool isStatic(false);
    bool isAFriend(false);
    sortItem.numberOfLines = stringHelper::getNumberOfNewLines(getTextWithoutCommentsWithNewLine(terms)) + 1;
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            int const lastHitIndex = hitIndexes.back();
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
            if (firstTerm.getContent() == "template") {
                sortItem.itemType = ItemType::Template;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getTermType() == TermType::Macro) {
                sortItem.itemType = ItemType::Macro;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "public" || firstTerm.getContent() == "protected" ||
                firstTerm.getContent() == "private") {
                sortItem.itemType = ItemType::AccessControl;
                sortItem.isDivider = true;
                break;
            }
            // Score: 0x-TAI'HCQR
            // R - return type
            // Q - qualifiers and attributes (const, volatile)
            // C - class specific (explicit, virtual, override, static, friend)
            // H - header specific (constexpr, inline)
            // I - important functions (constructors/etc, operators)
            // A - automatic (default, delete)
            // T - type (namespace const data, declarations, namespace data, functions, data)
            if (firstTerm.getContent() == "(") {
                if (!m_data.scopeNames.empty() &&
                    m_data.scopeNames.back() == getIdentifierBeforeParenthesis(terms, firstHitIndex)) {
                    sortItem.score += 0x3'0000;  // impt:constructors, etc
                }
                moveToEndParenthesis(terms, termIndex, firstHitIndex);
                sortItem.score += 0x100'0000;  // type:function
                sortItem.itemType = ItemType::Function;
            } else {
                if (firstTerm.getContent() == "enum" && lastTerm.getContent() == "class") {
                    sortItem.score += 0x700'0000;  // type:enum
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "enum") {
                    sortItem.score += 0x600'0000;  // type:enum
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "struct") {
                    sortItem.score += 0x500'0000;  // type:struct
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "union") {
                    sortItem.score += 0x400'0000;  // type:union
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "class") {
                    sortItem.score += 0x300'0000;  // type:class
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "=" && lastTerm.getContent() == "default") {
                    sortItem.score += 0x20'0000;  // auto:default
                } else if (firstTerm.getContent() == "=" && lastTerm.getContent() == "delete") {
                    sortItem.score += 0x10'0000;  // auto:delete
                } else if (!isAFriend && firstTerm.getContent() == "operator" && lastTerm.getContent() == "=") {
                    sortItem.score += 0x2'0000;  // impt:assignment
                } else if (!isAFriend && firstTerm.getContent() == "operator") {
                    sortItem.score += 0x1'0000;  // impt:other operator
                } else if (firstTerm.getContent() == "constexpr") {
                    sortItem.score += 0x2000;  // header:constexpr
                    isConst = true;
                } else if (firstTerm.getContent() == "inline") {
                    sortItem.score += 0x1000;  // header:inline
                } else if (firstTerm.getContent() == "explicit") {
                    sortItem.score += 0x600;  // class:explicit
                } else if (firstTerm.getContent() == "virtual") {
                    sortItem.score += 0x500;  // class:virtual
                } else if (firstTerm.getContent() == "override") {
                    sortItem.score += 0x400;  // class:override
                } else if (firstTerm.getContent() == "static") {
                    isStatic = true;
                } else if (firstTerm.getContent() == "[[nodiscard]]") {
                    sortItem.score += 0x40;  // qualifier:nodiscard
                } else if (firstTerm.getTermType() == TermType::Attribute) {
                    sortItem.score += 0x30;  // qualifier:attribute
                } else if (firstTerm.getContent() == "volatile") {
                    sortItem.score += 0x20;  // qualifier:volatile
                } else if (firstTerm.getContent() == "const") {
                    if (sortItem.itemType == ItemType::Function) {
                        // check the const after parenthesis
                        sortItem.score += 0x10;  // qualifier:const
                    }
                    isConst = true;
                } else if (firstTerm.getContent() == "friend") {
                    isAFriend = true;
                }
                termIndex = lastHitIndex + 1;
            }
        }
    }
    if (sortItem.itemType == ItemType::Unknown) {
        sortItem.itemType = ItemType::Data;
    }
    if (sortItem.itemType == ItemType::Function) {
        saveDetailsBasedFromFunctionSignature(sortItem, getFunctionSignature(item));
        sortItem.score += isAFriend ? 0x100 : isStatic ? 0x200 : 0x300;  // class:friend,static
    } else if (sortItem.itemType == ItemType::Data) {
        if (m_data.scopeType == ScopeType::AnonymousNamespace || m_data.scopeType == ScopeType::NamedNamespace) {
            sortItem.score += isConst ? 0x800'0000 : 0x200'0000;  // type:namespace (const) data
            sortItem.headerIndex = 0;
            if (m_data.scopeType == ScopeType::NamedNamespace) {
                cout << "warning: Data not wrapped in anonymous namespace. Item: [" << item << "]\n";
            }
        } else if (m_data.scopeType == ScopeType::ClassDeclaration) {
            // do not move class member data
            sortItem.score = (isStatic || isConst) ? sortItem.score : 0;
        }
    }
}

void CPlusPlusReorganizeItems::fixItemContents() {
    for (string& item : m_data.items) {
        Terms terms(getTermsFromString(item));
        replaceCommentsWithExtraLine(terms, 0);
        item = getCombinedContents(terms);
    }
}

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2) {
    if (item1.headerIndex == item2.headerIndex) {
        if (item1.score == item2.score) {
            if (item1.functionReturnTypeName == item2.functionReturnTypeName) {
                return item1.itemsIndex < item2.itemsIndex;
            }
            return item1.functionReturnTypeName < item2.functionReturnTypeName;
        }
        return item1.score > item2.score;
    }
    return item1.headerIndex < item2.headerIndex;
}

}  // namespace alba::CodeUtilities
