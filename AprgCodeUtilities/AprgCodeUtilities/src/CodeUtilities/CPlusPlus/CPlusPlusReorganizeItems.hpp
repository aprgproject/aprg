#pragma once

#include <CodeUtilities/Common/Term.hpp>
#include <Common/Debug/AlbaDebug.hpp>

#include <string>
#include <vector>

namespace alba::CodeUtilities {

class CPlusPlusReorganizeItems {
public:
    using Strings = std::vector<std::string>;
    struct SortItem {
        int score;
        int itemsIndex;
        bool isDivider;
        bool isComment;
        friend ALBA_DBG_CLASS_OUTPUT_OPERATOR_DEFINITION(
            SortItem const& object,
            "(score:" << object.score << ",itemsIndex:" << object.itemsIndex << ")");
    };
    using SortItems = std::vector<SortItem>;

    explicit CPlusPlusReorganizeItems(Strings&& items);
    explicit CPlusPlusReorganizeItems(Strings const& items);
    [[nodiscard]] Terms getSortedAggregateTerms() const;

private:
    [[nodiscard]] SortItems getSortedItems() const;
    [[nodiscard]] SortItems getSortItems() const;
    static void saveDetails(SortItem& sortItem, std::string const& item);
    Strings m_items;
};

bool operator<(
    CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2);

}  // namespace alba::CodeUtilities
