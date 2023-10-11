#include "CPlusPlusReorganizeItems.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/CommonUtilities.hpp>
#include <Common/Print/AlbaLogPrints.hpp>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(Data const& data) : m_data(data) {}
CPlusPlusReorganizeItems::CPlusPlusReorganizeItems(Data&& data) : m_data(data) {}

Terms CPlusPlusReorganizeItems::getReorganizedTerms() const {
    switch (m_data.scopeType) {
        case ScopeType::AnonymousNamespace:
        case ScopeType::NamedNamespace:
            return getReorganizedTermsInNamespace();
        case ScopeType::ClassDeclaration:
            return getReorganizedTermsInClassDeclaration();
        case ScopeType::EnumClass:
            return getReorganizedTermsInEnumClass();
        case ScopeType::TopLevel:
            return getReorganizedTermsInTopLevelScope();
        case ScopeType::Unknown:
            return {};
    }
    return {};
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortedItems() const {
    SortItems sortItems(getSortItems());
    if (ScopeType::AnonymousNamespace != m_data.scopeType) {
        // dont sort in anonymous namespace
        sortByComparingItems(sortItems);
        sortAlphabetically(sortItems);
    }
    return sortItems;
}

CPlusPlusReorganizeItems::SortItems CPlusPlusReorganizeItems::getSortItems() const {
    SortItems sortItems;
    sortItems.reserve(m_data.items.size());
    int index = 0;
    for (string const& item : m_data.items) {
        SortItem sortItem(createSortItem(index++));
        saveDetailsFromHeaderSignatures(sortItem, item);
        saveDetailsBasedFromItem(sortItem, item);
        sortItems.emplace_back(sortItem);
    }
    return sortItems;
}

Terms CPlusPlusReorganizeItems::getReorganizedTermsInClassDeclaration() const {
    Terms terms;
    SortItems const sortedItems(getSortedItems());
    bool const isMultilineScope = hasMultilineItem(sortedItems);
    bool isPreviousAMultilineItem(isMultilineScope);
    bool isFirst(true);
    bool isPreviousAnAccessControl(false);
    terms.emplace_back(TermType::WhiteSpace, "\n");  // new line after brace
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_data.items[sortItem.itemsIndex]);
        bool const isAccessControl = sortItem.itemType == ItemType::AccessControl;
        bool const isMultilineItem = isMultiLine(sortItem.numberOfLines) || isAccessControl;
        bool const shouldPreventNewLine = (isFirst && isAccessControl) || isPreviousAnAccessControl;
        bool const placeNewLineBeforeItem = !shouldPreventNewLine && (isMultilineItem || isPreviousAMultilineItem);
        if (placeNewLineBeforeItem) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }
        // stringstream commentStream;
        // auto headerSignature = sortItem.headerIndex < static_cast<int>(m_data.headerFunctionSignatures.size())
        //                            ? m_data.headerFunctionSignatures[sortItem.headerIndex]
        //                            : "NO MAPPING";
        // commentStream << "/*BEGIN ADD (";
        // commentStream << "headerIndex:[" << sortItem.headerIndex << "] ";
        // commentStream << "headerSignature:[" << headerSignature << "] ";
        // commentStream << "score:[" << hex << sortItem.score << dec << "] ";
        // commentStream << "returnType:[" << sortItem.functionReturnTypeName << "] ";
        // ALBA_INF_PRINT(commentStream, sortItem.functionIndexesUsed);
        // commentStream << ")*/";
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

Terms CPlusPlusReorganizeItems::getReorganizedTermsInEnumClass() const {
    Terms terms;
    SortItems const sortedItems(getSortedItems());
    terms.emplace_back(TermType::WhiteSpace, "\n");  // new line after brace
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_data.items[sortItem.itemsIndex]);
        terms.emplace_back(TermType::Aggregate, item);
        terms.emplace_back(TermType::WhiteSpace, "\n");
    }
    return terms;
}

Terms CPlusPlusReorganizeItems::getReorganizedTermsInNamespace() const {
    Terms terms;
    SortItems const sortedItems(getSortedItems());
    bool const isMultilineScope = hasMultilineItem(sortedItems);
    bool isPreviousAMultilineItem(isMultilineScope);
    terms.emplace_back(TermType::WhiteSpace, "\n");  // new line after brace
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_data.items[sortItem.itemsIndex]);
        bool const isMultilineItem = isMultiLine(sortItem.numberOfLines);
        bool const placeNewLineBeforeItem = isMultilineItem || isPreviousAMultilineItem;
        if (placeNewLineBeforeItem) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }
        terms.emplace_back(TermType::Aggregate, item);
        terms.emplace_back(TermType::WhiteSpace, "\n");
        isPreviousAMultilineItem = isMultilineItem;
    }
    if (isMultilineScope) {
        terms.emplace_back(TermType::WhiteSpace, "\n");
    }
    return terms;
}

Terms CPlusPlusReorganizeItems::getReorganizedTermsInTopLevelScope() const {
    Terms terms;
    SortItems const sortedItems(getSortedItems());
    bool isPreviousAMultilineItem(false);
    bool isPreviousAGroupItem(false);
    bool isFirst(true);
    ItemType previousItemType(ItemType::Unknown);
    for (SortItem const& sortItem : sortedItems) {
        string const& item(m_data.items[sortItem.itemsIndex]);
        bool const isMultilineItem =
            isMultiLine(sortItem.numberOfLines) || sortItem.itemSubType == ItemSubType::PragmaMacro;
        bool const isAGroupItem = sortItem.itemType == ItemType::Macro || sortItem.itemType == ItemType::UsingKeyword;
        bool const shouldSeparateGroups =
            sortItem.hasComment || ((isAGroupItem || isPreviousAGroupItem) &&
                                    getGroupType(sortItem.itemType) != getGroupType(previousItemType));
        bool const placeNewLineBeforeItem =
            !isFirst && (isMultilineItem || isPreviousAMultilineItem || shouldSeparateGroups);
        if (placeNewLineBeforeItem) {
            terms.emplace_back(TermType::WhiteSpace, "\n");
        }
        terms.emplace_back(TermType::Aggregate, item);
        terms.emplace_back(TermType::WhiteSpace, "\n");
        isPreviousAMultilineItem = isMultilineItem;
        isPreviousAGroupItem = isAGroupItem;
        previousItemType = sortItem.itemType;
        isFirst = false;
    }
    return terms;
}

int CPlusPlusReorganizeItems::getBestHeaderIndex(string const& item) const {
    if (!m_data.headerFunctionSignatures.empty()) {
        string const itemSignature = getFunctionSignature(item);
        int bestDifference = static_cast<int>(itemSignature.size());
        int bestHeaderIndex = 0;
        bool isFirst(true);
        int headerIndex = 0;
        for (string const& headerSignature : m_data.headerFunctionSignatures) {
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
        return static_cast<int>(m_data.headerFunctionSignatures.size());
    }
    return 0;
}

bool CPlusPlusReorganizeItems::isDefaultConstructor(Terms const& terms) const {
    Patterns const searchPatterns{{M(m_data.scopeName), M("("), M(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

bool CPlusPlusReorganizeItems::isOtherConstructor(Terms const& terms) const {
    Patterns const searchPatterns{{M(m_data.scopeName), M("("), M_NOT(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

bool CPlusPlusReorganizeItems::isDestructor(Terms const& terms) const {
    Patterns const searchPatterns{{M("~"), M(m_data.scopeName), M("("), M(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

bool CPlusPlusReorganizeItems::isCopyConstructor(Terms const& terms) const {
    Patterns const searchPatterns{
        {M(m_data.scopeName), M("("), M(m_data.scopeName), M("const"), M("&"), M(")")},
        {M(m_data.scopeName), M("("), M(m_data.scopeName), M("const"), M("&"), M(TermType::Identifier), M(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

bool CPlusPlusReorganizeItems::isMoveConstructor(Terms const& terms) const {
    Patterns const searchPatterns{
        {M(m_data.scopeName), M("("), M(m_data.scopeName), M("&&"), M(")")},
        {M(m_data.scopeName), M("("), M(m_data.scopeName), M("&&"), M(TermType::Identifier), M(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

bool CPlusPlusReorganizeItems::isCopyAssignment(Terms const& terms) const {
    Patterns const searchPatterns{
        {M(m_data.scopeName), M("&"), M("operator"), M("="), M("("), M(m_data.scopeName), M("const"), M("&"), M(")")},
        {M(m_data.scopeName), M("&"), M("operator"), M("="), M("("), M(m_data.scopeName), M("const"), M("&"),
         M(TermType::Identifier), M(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

bool CPlusPlusReorganizeItems::isMoveAssignment(Terms const& terms) const {
    Patterns const searchPatterns{
        {M(m_data.scopeName), M("&"), M("operator"), M("="), M("("), M(m_data.scopeName), M("&&"), M(")")},
        {M(m_data.scopeName), M("&"), M("operator"), M("="), M("("), M(m_data.scopeName), M("&&"),
         M(TermType::Identifier), M(")")}};
    Indexes const hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    return !hitIndexes.empty();
}

void CPlusPlusReorganizeItems::sortAlphabetically(SortItems& sortItems) const {
    int start = 0;
    int end = 0;
    ItemType itemTypeToSort = ItemType::Unknown;
    for (; end < static_cast<int>(sortItems.size()); ++end) {
        SortItem const& currentSortItem(sortItems[end]);
        if (currentSortItem.shouldSortAlphabetically) {
            if (itemTypeToSort == ItemType::Unknown) {
                start = end;
                itemTypeToSort = currentSortItem.itemType;
            } else if (itemTypeToSort != currentSortItem.itemType) {
                sort(
                    sortItems.begin() + start, sortItems.begin() + end,
                    [&](SortItem const& sortItem1, SortItem const& sortItem2) {
                        return compareAlphabetically(
                            m_data.items[sortItem1.itemsIndex], m_data.items[sortItem2.itemsIndex]);
                    });
                start = end;
                itemTypeToSort = currentSortItem.itemType;
            }
        } else if (itemTypeToSort != ItemType::Unknown) {
            sort(
                sortItems.begin() + start, sortItems.begin() + end,
                [&](SortItem const& sortItem1, SortItem const& sortItem2) {
                    return compareAlphabetically(
                        m_data.items[sortItem1.itemsIndex], m_data.items[sortItem2.itemsIndex]);
                });
            itemTypeToSort = ItemType::Unknown;
        }
    }
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
    Patterns const searchPatterns(getSearchPatternsForAnalysis());
    bool isFound(true);
    bool isConst(false);
    bool isStatic(false);
    bool isAFriend(false);
    sortItem.numberOfLines = stringHelper::getNumberOfNewLines(getTextWithoutCommentsWithNewLine(terms)) + 1;
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, terms, searchPatterns);
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
                sortItem.itemType = ItemType::StaticAssert;
                break;
            }
            if (firstTerm.getTermType() == TermType::Macro) {
                if (firstTerm.getContent() == "#include") {
                    sortItem.itemSubType = ItemSubType::IncludeMacro;
                    sortItem.shouldSortAlphabetically = true;
                } else if (firstTerm.getContent() == "#pragma") {
                    sortItem.itemSubType = ItemSubType::PragmaMacro;
                } else {
                    sortItem.itemSubType = ItemSubType::GenericMacro;
                }
                sortItem.itemType = ItemType::Macro;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "namespace") {
                sortItem.itemType = ItemType::Namespace;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "using") {
                if (lastTerm.getContent() == "namespace") {
                    sortItem.itemSubType = ItemSubType::UsingNamespace;
                    sortItem.shouldSortAlphabetically = true;
                } else {
                    sortItem.itemSubType = ItemSubType::UsingOther;
                }
                sortItem.itemType = ItemType::UsingKeyword;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "template") {
                sortItem.itemType = ItemType::Template;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "public" || firstTerm.getContent() == "protected" ||
                firstTerm.getContent() == "private") {
                sortItem.itemType = ItemType::AccessControl;
                sortItem.isDivider = true;
                break;
            }
            if (firstTerm.getContent() == "TEST_F") {
                sortItem.score += 0x4'0000;  // other:TEST_F
                sortItem.itemType = ItemType::Test;
                saveDetailsForTest(sortItem, terms);
                break;
            }
            if (firstTerm.getContent() == "TEST") {
                sortItem.score += 0x3'0000;  // other:TEST
                sortItem.itemType = ItemType::Test;
                saveDetailsForTest(sortItem, terms);
                break;
            }
            if (firstTerm.getContent() == "BENCHMARK") {
                sortItem.score += 0x2'0000;  // other:BENCHMARK
                sortItem.itemType = ItemType::Test;
                break;
            }
            if (firstTerm.getContent() == "BENCHMARK_MAIN") {
                sortItem.score += 0x1'0000;  // other:BENCHMARK_MAIN
                sortItem.itemType = ItemType::Test;
                break;
            }
            // Score: 0x-TIO'HCQR
            // R - return type
            // Q - qualifiers and attributes (const, volatile)
            // C - class specific (explicit, virtual, override, static, friend)
            // H - header specific (operators, constexpr, inline)
            // O - other (default, delete), TEST, TEST_F, BENCHMARK
            // I - impt functions (constructors/etc, operators)
            // T - type (namespace const data, declarations, namespace data, functions, data, test)
            if (firstTerm.getContent() == "(") {
                moveToEndParenthesis(terms, termIndex, firstHitIndex);
                sortItem.score += 0x200'0000;  // type:function
                sortItem.itemType = ItemType::Function;
            } else {
                if (isComment(firstTerm)) {
                    sortItem.hasComment = true;
                } else if (firstTerm.getContent() == "enum" && lastTerm.getContent() == "class") {
                    sortItem.score += 0x800'0000;  // type:enum
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "enum") {
                    sortItem.score += 0x700'0000;  // type:enum
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "struct") {
                    sortItem.score += 0x600'0000;  // type:struct
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "union") {
                    sortItem.score += 0x500'0000;  // type:union
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "class") {
                    sortItem.score += 0x400'0000;  // type:class
                    sortItem.itemType = ItemType::Declaration;
                } else if (firstTerm.getContent() == "=" && lastTerm.getContent() == "default") {
                    sortItem.score += 0x2'0000;  // other:default
                } else if (firstTerm.getContent() == "=" && lastTerm.getContent() == "delete") {
                    sortItem.score += 0x1'0000;  // other:delete
                } else if (!isAFriend && firstTerm.getContent() == "operator" && lastTerm.getContent() == "=") {
                    sortItem.score += 0x4000;  // header:assignment
                } else if (!isAFriend && firstTerm.getContent() == "operator") {
                    sortItem.score += 0x3000;  // header:operator for items not in class declaration
                    sortItem.isNonFriendOperator = true;
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
                    sortItem.score += 0x50;  // qualifier:nodiscard
                } else if (firstTerm.getTermType() == TermType::Attribute) {
                    sortItem.score += 0x40;  // qualifier:attribute
                } else if (firstTerm.getContent() == "noexcept") {
                    sortItem.score += 0x30;  // qualifier:noexcept
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
        if (sortItem.hasComment && isAllWhiteSpaceOrComment(terms)) {
            sortItem.itemType = ItemType::CommentOnly;
        } else {
            sortItem.itemType = ItemType::Data;
        }
    }
    if (sortItem.itemType == ItemType::Function) {
        saveDetailsBasedFromFunctionSignature(sortItem, getFunctionSignature(item));
        sortItem.score += isAFriend ? 0x100 : isStatic ? 0x200 : 0x300;  // class:friend,static
    } else if (sortItem.itemType == ItemType::Data) {
        if (m_data.scopeType == ScopeType::AnonymousNamespace || m_data.scopeType == ScopeType::NamedNamespace) {
            sortItem.score += isConst ? 0x900'0000 : 0x300'0000;  // type:namespace (const) data
            sortItem.headerIndex = isConst ? 0 : sortItem.headerIndex;
            if (m_data.fileType == CppFileType::CppFile &&
                (m_data.scopeType == ScopeType::NamedNamespace || m_data.scopeType == ScopeType::TopLevel)) {
                cout << "warning: Data not wrapped in anonymous namespace. Item: [" << item << "]\n";
            }
            if (m_data.fileType == CppFileType::HeaderFile && m_data.scopeType == ScopeType::TopLevel) {
                cout << "warning: Data not wrapped in any namespace. Item: [" << item << "]\n";
            }
        } else if (m_data.scopeType == ScopeType::ClassDeclaration) {
            // do not move class member data
            sortItem.score += 0x100'0000;    // type:data
            sortItem.score &= 0xFFFF'FF00U;  // remove qualifiers and return type
        }
    }
}

void CPlusPlusReorganizeItems::saveDetailsBasedFromFunctionSignature(
    SortItem& sortItem, string const& functionSignature) const {
    Terms const functionSignatureTerms(getTermsFromString(functionSignature));
    saveDetailsBasedFromReturnType(sortItem, functionSignatureTerms);
    saveDetailsForSpecialFunctions(sortItem, functionSignatureTerms);
}

void CPlusPlusReorganizeItems::saveDetailsForSpecialFunctions(SortItem& sortItem, Terms const& terms) const {
    if (m_data.scopeType == ScopeType::ClassDeclaration && !m_data.scopeName.empty()) {
        if (isMoveAssignment(terms)) {
            sortItem.score += 0x20'0000;  // impt:
        } else if (isCopyAssignment(terms)) {
            sortItem.score += 0x30'0000;  // impt:
        } else if (isMoveConstructor(terms)) {
            sortItem.score += 0x40'0000;  // impt:
        } else if (isCopyConstructor(terms)) {
            sortItem.score += 0x50'0000;  // impt:
        } else if (isDestructor(terms)) {
            sortItem.score += 0x60'0000;  // impt:
        } else if (isOtherConstructor(terms)) {
            sortItem.score += 0x70'0000;  // impt:
        } else if (isDefaultConstructor(terms)) {
            sortItem.score += 0x80'0000;  // impt:
        } else if (sortItem.isNonFriendOperator) {
            sortItem.score += 0x10'0000;  // impt:
        }
    }
}

void CPlusPlusReorganizeItems::saveDetailsForTest(SortItem& sortItem, Terms const& terms) const {
    set<int> functionIndexes;
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        int const patternIndex =
            getPatternIndexOfAMatchBySearchingForward(termIndex, terms, m_data.headerFunctionNamePatterns);
        isFound = patternIndex >= 0;
        if (isFound) {
            functionIndexes.emplace(patternIndex);
        }
        ++termIndex;
    }
    sortItem.functionIndexesUsed.reserve(functionIndexes.size());
    copy(functionIndexes.cbegin(), functionIndexes.cend(), back_inserter(sortItem.functionIndexesUsed));
    // if (!functionIndexes.empty()) {
    //     ALBA_INF_PRINT(cout, getLocatorString(terms, 0));
    //     ALBA_INF_PRINT(cout, functionIndexes);
    //     strings functionNames;
    //     transform(
    //         functionIndexes.cbegin(), functionIndexes.cend(), back_inserter(functionNames),
    //         [&](int const functionIndex) {
    //             return m_data.headerFunctionNamePatterns[functionIndex].front().getContentOptional().value_or("");
    //         });
    //     ALBA_INF_PRINT(cout, functionNames);
    // }
}

CPlusPlusReorganizeItems::GroupType CPlusPlusReorganizeItems::getGroupType(ItemType const itemType) {
    switch (itemType) {
        case ItemType::Macro:
        case ItemType::StaticAssert:
            return GroupType::CompilerTimeGroup;
        case ItemType::UsingKeyword:
            return GroupType::UsingGroup;
        case ItemType::AccessControl:
        case ItemType::CommentOnly:
        case ItemType::Data:
        case ItemType::Declaration:
        case ItemType::Function:
        case ItemType::Namespace:
        case ItemType::Template:
        case ItemType::Unknown:
        case ItemType::Test:
            return GroupType::OtherGroup;
    }
    return GroupType::OtherGroup;
}

Patterns CPlusPlusReorganizeItems::getSearchPatternsForAnalysis() {
    return Patterns{
        {M(SpecialMatcherType::Comment)},
        {M("(")},
        {M(";")},
        {M("{")},
        {M(":")},
        {M("static_assert")},
        {M("namespace")},
        {M("using"), M("namespace")},
        {M("using")},
        {M("template")},
        {M(TermType::Macro)},
        {M("public"), M(":")},
        {M("protected"), M(":")},
        {M("private"), M(":")},
        {M("TEST"), M("(")},
        {M("TEST_F"), M("(")},
        {M("BENCHMARK"), M("(")},
        {M("BENCHMARK_MAIN"), M("(")},
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

CPlusPlusReorganizeItems::SortItem CPlusPlusReorganizeItems::createSortItem(int const index) {
    return SortItem{0, 0, 0, false, false, false, false, ItemType::Unknown, ItemSubType::Unknown, index, {}, {}};
}

string CPlusPlusReorganizeItems::getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex) {
    int const beforeParenthesis = parenthesisIndex - 1;
    Patterns const searchPatterns{{M(TermType::Identifier)}};
    Indexes hitIndexes = searchPatternsAt(beforeParenthesis, terms, searchPatterns);
    if (!hitIndexes.empty()) {
        return terms[hitIndexes.front()].getContent();
    }
    return {};
}

char CPlusPlusReorganizeItems::getRevisedChar(char const character) {
    return (';' == character) ? ' ' : static_cast<char>(::toupper(character));
}

bool CPlusPlusReorganizeItems::hasMultilineItem(SortItems const& sortItems) {
    return any_of(sortItems.cbegin(), sortItems.cend(), [&](SortItem const& sortItem) {
        return isMultiLine(sortItem.numberOfLines);
    });
}

bool CPlusPlusReorganizeItems::isMultiLine(int const numberOfLines) { return numberOfLines > 1; }

bool CPlusPlusReorganizeItems::compareAlphabetically(string const& string1, string const& string2) {
    for (int i = 0; i < static_cast<int>(string1.length()) && i < static_cast<int>(string2.length()); ++i) {
        auto char1 = string1[i];
        auto char2 = string2[i];
        if (char1 != char2) {
            return getRevisedChar(char1) < getRevisedChar(char2);
        }
    }
    return string1.size() < string2.size();
}

void CPlusPlusReorganizeItems::sortByComparingItems(SortItems& sortItems) {
    int start = 0;
    int end = 0;
    for (; end < static_cast<int>(sortItems.size()); ++end) {
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
    Patterns const searchPatterns{{M_OR(M(")"), M(";"), M("{"), M(":"))}};
    bool isFound(true);
    bool isCloseParenthesisFound(false);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(termIndex, terms, searchPatterns);
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

void CPlusPlusReorganizeItems::saveDetailsBasedFromReturnType(SortItem& sortItem, Terms const& terms) {
    Patterns const searchPatterns{{M_OR(M(TermType::PrimitiveType), M(TermType::Identifier), M(TermType::Keyword))}};
    Indexes hitIndexes = searchForwardsForPatterns(terms, searchPatterns);
    if (!hitIndexes.empty()) {
        int const firstHitIndex = hitIndexes.front();
        Term const& firstTerm(terms[firstHitIndex]);
        if (firstTerm.getTermType() == TermType::PrimitiveType) {
            if (firstTerm.getContent() == "bool") {
                sortItem.score += 0x3;  // returnType: bool
            } else if (firstTerm.getContent() == "void") {
                sortItem.score += 0x6;  // returnType: void
            } else {
                sortItem.score += 0x4;  // returnType: primitive type
            }
        } else if (firstTerm.getTermType() == TermType::Identifier) {
            if (firstTerm.getContent() == "TEST") {
                sortItem.score += 0x1;  // returnType: gtest tests
            } else if (firstTerm.getContent() == "TEST_F") {
                sortItem.score += 0x2;  // returnType: gtest tests
            } else if (firstTerm.getContent() == "size_t") {
                sortItem.score += 0x4;  // returnType: same level as primitive type
            } else {
                sortItem.score += 0x5;  // returnType: user type
            }
        } else if (firstTerm.getTermType() == TermType::Keyword) {
            sortItem.score += 0x7;
        }
        sortItem.functionReturnTypeName = firstTerm.getContent();
    }
}

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2) {
    if (item1.headerIndex == item2.headerIndex) {
        if (item1.score == item2.score) {
            if (item1.functionReturnTypeName == item2.functionReturnTypeName) {
                for (int i = 0; i < static_cast<int>(item1.functionIndexesUsed.size()) &&
                                i < static_cast<int>(item2.functionIndexesUsed.size());
                     ++i) {
                    if (item1.functionIndexesUsed[i] != item2.functionIndexesUsed[i]) {
                        return item1.functionIndexesUsed[i] < item2.functionIndexesUsed[i];
                    }
                }
                if (item1.functionIndexesUsed.size() != item2.functionIndexesUsed.size()) {
                    return item1.functionIndexesUsed.size() < item2.functionIndexesUsed.size();
                }
                return item1.itemsIndex < item2.itemsIndex;
            }
            return item1.functionReturnTypeName < item2.functionReturnTypeName;
        }
        return item1.score > item2.score;
    }
    return item1.headerIndex < item2.headerIndex;
}

}  // namespace alba::CodeUtilities
