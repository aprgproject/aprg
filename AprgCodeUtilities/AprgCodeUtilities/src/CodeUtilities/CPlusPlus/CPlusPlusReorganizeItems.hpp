#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <cstdint>

namespace alba::CodeUtilities {

class CPlusPlusReorganizeItems {
public:
    enum class ItemType {
        AccessControl,
        Data,
        Declaration,
        Function,
        Macro,
        Namespace,
        StaticAssert,
        Template,
        Test,
        Unknown,
        UsingKeyword
    };

    enum class ItemSubType { GenericMacro, IncludeMacro, PragmaMacro, Unknown, UsingNamespace, UsingOther };

    enum class GroupType { CompilerTimeGroup, OtherGroup, UsingGroup };

    struct SortItem {
        int headerIndex;
        uint32_t score;
        int numberOfLines;
        bool isDivider;
        bool shouldSortAlphabetically;
        ItemType itemType;
        ItemSubType itemSubType;
        int itemsIndex;
        std::string functionReturnTypeName;
        std::vector<int> functionIndexesUsed;
    };

    using SortItems = std::vector<SortItem>;

    struct Data {
        CppFileType fileType;
        ScopeType scopeType;
        stringHelper::strings items;
        stringHelper::strings scopeNames;
        stringHelper::strings headerFunctionSignatures;
        Patterns headerFunctionNamePatterns;
    };

    explicit CPlusPlusReorganizeItems(Data const& data);
    explicit CPlusPlusReorganizeItems(Data&& data);
    [[nodiscard]] Terms getReorganizedTerms() const;

private:
    [[nodiscard]] SortItems getSortedItems() const;
    [[nodiscard]] SortItems getSortItems() const;
    [[nodiscard]] Terms getReorganizedTermsInClassDeclaration() const;
    [[nodiscard]] Terms getReorganizedTermsInEnumClass() const;
    [[nodiscard]] Terms getReorganizedTermsInNamespace() const;
    [[nodiscard]] Terms getReorganizedTermsInTopLevelScope() const;
    [[nodiscard]] int getBestHeaderIndex(std::string const& item) const;
    void sortAlphabetically(SortItems& sortItems) const;
    void saveDetailsFromHeaderSignatures(SortItem& sortItem, std::string const& item) const;
    void saveDetailsBasedFromItem(SortItem& sortItem, std::string const& item) const;
    void saveDetailsBasedFromItemTerms(SortItem& sortItem, std::string const& item, Terms const& terms) const;
    void saveDetailsForTest(SortItem& sortItem, Terms const& terms) const;
    void fixItemContents();
    [[nodiscard]] static GroupType getGroupType(ItemType const itemType);
    [[nodiscard]] static Patterns getSearchPatterns();
    [[nodiscard]] static SortItem createSortItem(int const index);
    [[nodiscard]] static std::string getIdentifierBeforeParenthesis(Terms const& terms, int const parenthesisIndex);
    [[nodiscard]] static bool hasMultilineItem(SortItems const& sortItems);
    [[nodiscard]] static bool isMultiLine(int const numberOfLines);
    static void makeIsolatedCommentsStickWithNextLine(Terms& terms, int const startIndex);
    static void sortByComparingItems(SortItems& sortItems);
    static void moveToEndParenthesis(Terms const& terms, int& termIndex, int const parenthesisIndex);
    static void saveDetailsBasedFromFunctionSignature(SortItem& sortItem, std::string const& functionSignature);
    Data m_data;
};

bool operator<(CPlusPlusReorganizeItems::SortItem const& item1, CPlusPlusReorganizeItems::SortItem const& item2);

}  // namespace alba::CodeUtilities
