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
    bool isSuccessful;
    KeplerNidToLcgMap keplerNidToLcgMap;
};

class AsilBasebandPooling {
public:
    AsilBasebandPooling();
    AsilBasebandPooling(LcgInitializerList const& lcgs, BasebandCardInitializerList const& basebandCards);
    [[nodiscard]] BasebandPoolingResult performBasebandPoolingForAsil() const;
    [[nodiscard]] bool areLcgAndBasebandCardsValid() const;
    static bool canMultipleLcgsBePutOnBasebandCard(BasebandCard const& basebandCard) ;
    [[nodiscard]] unsigned int getNumberBasebandCardsWithMultipleLcgs() const;
    static unsigned int getMaxNumberOfLcgsInBasebandCard(BasebandCard const& basebandCard);
    [[nodiscard]] unsigned int getMaxNumberOfLcgsInAllBasebandCards() const;
    [[nodiscard]] VectorOfLcgs getLcgsInPriorityOrder() const;
    [[nodiscard]] BasebandCardsSplitBasedOnNumberOfLcgs getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(
        unsigned int const numberOfBasebandCardsWithMultipleLcgs) const;
    static void sortAndPrioritizeBasebandCards(VectorOfBasebandCards& basebandCardsWithPrioritization);
    static void sortAndPrioritizeLcgs(VectorOfLcgs& lcgsInPriorityOrder);
    static void assignBasebandCardsWithOneLcg(
        KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
        SetOfBasebandCards const& basebandCardsWithOneLcg) ;
    static void assignBasebandCardsWithMultipleLcgs(
        KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
        SetOfBasebandCards const& basebandCardsWithMultipleLcgs) ;

private:
    SetOfLcgs m_lcgs;
    SetOfBasebandCards m_basebandCards;
};

}  // namespace alba
