#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba::CodeUtilities {

class CPlusPlusReorganizeItems {
public:
    enum class ItemType { Unknown, Namespace, Declaration, Template, Macro, AccessControl, Function, Data };
    struct SortItem {
        int headerIndex;
        int score;
        int numberOfLines;
        bool isDivider;
        ItemType itemType;
        int itemsIndex;
        std::string functionSignature;
    };
    using SortItems = std::vector<SortItem>;

    CPlusPlusReorganizeItems(
        ScopeType const scopeType, stringHelper::strings const& items, stringHelper::strings const& scopeNames,
        stringHelper::strings const& headerSignatures);
    CPlusPlusReorganizeItems(
        ScopeType const scopeType, stringHelper::strings&& items, stringHelper::strings&& scopeNames,
        stringHelper::strings&& headerSignatures);
    [[nodiscard]] Terms getSortedAggregateTerms() const;

private:
    [[nodiscard]] SortItems getSortedItems() const;
    [[nodiscard]] SortItems getSortItems() const;
    void fixItemContents();
    static void sortByComparingItems(SortItems& sortItems);
    void saveDetailsBasedFromItem(SortItem& sortItem, std::string const& item) const;
    void saveDetailsFromHeaderSignatures(SortItem& sortItem, std::string const& item) const;
    [[nodiscard]] static Patterns getSearchPatterns();
    void saveDetailsBasedFromItemTerms(SortItem& sortItem, std::string const& item, Terms const& terms) const;
    static void moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex);
    [[nodiscard]] int getBestHeaderIndex(std::string const& item) const;
    static int getScoreAtReturnOfFunctionSignature(std::string const& functionSignature);
    [[nodiscard]] static std::string getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex);
    [[nodiscard]] static int getTotalNumberLines(SortItems const& sortItems);
    [[nodiscard]] static bool hasMultilineItem(SortItems const& sortItems);
    [[nodiscard]] static bool isMultiLine(int const numberOfLines);
    ScopeType m_scopeType;
    stringHelper::strings m_items;
    stringHelper::strings m_scopeNames;
    stringHelper::strings m_headerSignatures;
};

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2);

}  // namespace alba::CodeUtilities
