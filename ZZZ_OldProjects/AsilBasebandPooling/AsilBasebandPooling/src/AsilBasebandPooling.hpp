#pragma once

#include <BasebandCard.hpp>
#include <Lcg.hpp>

#include <map>

namespace alba {

using KeplerNidToLcgPair = std::pair<unsigned int, unsigned int>;
using KeplerNidToLcgMap = std::map<unsigned int, unsigned int>;

struct BasebandCardsSplitBasedOnNumberOfLcgs {
    SetOfBasebandCards basebandCardsWithOneLcg;
    SetOfBasebandCards basebandCardsWithMultipleLcgs;
};

struct BasebandPoolingResult {
    bool isSuccessful{};
    KeplerNidToLcgMap keplerNidToLcgMap;
};

class AsilBasebandPooling {
public:
    AsilBasebandPooling();
    AsilBasebandPooling(LcgInitializerList const& lcgs, BasebandCardInitializerList const& basebandCards);

    [[nodiscard]] BasebandCardsSplitBasedOnNumberOfLcgs getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(
        unsigned int const numberOfBasebandCardsWithMultipleLcgs) const;

    [[nodiscard]] BasebandPoolingResult performBasebandPoolingForAsil() const;
    [[nodiscard]] VectorOfLcgs getLcgsInPriorityOrder() const;
    [[nodiscard]] unsigned int getNumberBasebandCardsWithMultipleLcgs() const;
    [[nodiscard]] unsigned int getMaxNumberOfLcgsInAllBasebandCards() const;
    [[nodiscard]] bool areLcgAndBasebandCardsValid() const;
    static void sortAndPrioritizeBasebandCards(VectorOfBasebandCards& basebandCardsWithPrioritization);
    static void sortAndPrioritizeLcgs(VectorOfLcgs& lcgsInPriorityOrder);

    static void assignBasebandCardsWithOneLcg(
        KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
        SetOfBasebandCards const& basebandCardsWithOneLcg);

    static void assignBasebandCardsWithMultipleLcgs(
        KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
        SetOfBasebandCards const& basebandCardsWithMultipleLcgs);

    static unsigned int getMaxNumberOfLcgsInBasebandCard(BasebandCard const& basebandCard);
    static bool canMultipleLcgsBePutOnBasebandCard(BasebandCard const& basebandCard);

private:
    SetOfLcgs m_lcgs;
    SetOfBasebandCards m_basebandCards;
};

}  // namespace alba
