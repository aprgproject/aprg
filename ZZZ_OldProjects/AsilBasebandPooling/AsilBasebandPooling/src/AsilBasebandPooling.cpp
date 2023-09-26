#include "AsilBasebandPooling.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

namespace alba {

AsilBasebandPooling::AsilBasebandPooling(
    LcgInitializerList const& lcgs, BasebandCardInitializerList const& basebandCards) {
    copy(lcgs.begin(), lcgs.end(), inserter(m_lcgs, m_lcgs.cbegin()));
    copy(basebandCards.begin(), basebandCards.end(), inserter(m_basebandCards, m_basebandCards.cbegin()));
}

BasebandCardsSplitBasedOnNumberOfLcgs AsilBasebandPooling::getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(
    unsigned int const numberOfBasebandCardsWithMultipleLcgs) const {
    unsigned int numberOfBasebandCardRemaining(numberOfBasebandCardsWithMultipleLcgs);
    BasebandCardsSplitBasedOnNumberOfLcgs basebandCards;
    auto reverseTraversal = m_basebandCards.crbegin();
    while (reverseTraversal != m_basebandCards.crend()) {
        if (numberOfBasebandCardRemaining > 0 && canMultipleLcgsBePutOnBasebandCard(*reverseTraversal)) {
            basebandCards.basebandCardsWithMultipleLcgs.emplace(*reverseTraversal);
            --numberOfBasebandCardRemaining;
        } else {
            basebandCards.basebandCardsWithOneLcg.emplace(*reverseTraversal);
        }
        ++reverseTraversal;
    }
    return basebandCards;
}

BasebandPoolingResult AsilBasebandPooling::performBasebandPoolingForAsil() const {
    BasebandPoolingResult poolingResult;
    poolingResult.isSuccessful = areLcgAndBasebandCardsValid();
    if (poolingResult.isSuccessful) {
        VectorOfLcgs lcgsInPriorityOrder(getLcgsInPriorityOrder());
        unsigned int const numberOfBasebandCardsWithMultipleLcgs(getNumberBasebandCardsWithMultipleLcgs());
        BasebandCardsSplitBasedOnNumberOfLcgs const basebandCardsBasedOnNumberOfLcgs(
            getBasebandCardsSplitBetweenOneLcgAndMultipleLcgs(numberOfBasebandCardsWithMultipleLcgs));
        assignBasebandCardsWithOneLcg(
            poolingResult.keplerNidToLcgMap, lcgsInPriorityOrder,
            basebandCardsBasedOnNumberOfLcgs.basebandCardsWithOneLcg);
        assignBasebandCardsWithMultipleLcgs(
            poolingResult.keplerNidToLcgMap, lcgsInPriorityOrder,
            basebandCardsBasedOnNumberOfLcgs.basebandCardsWithMultipleLcgs);
    }
    return poolingResult;
}

VectorOfLcgs AsilBasebandPooling::getLcgsInPriorityOrder() const {
    VectorOfLcgs lcgsInPriorityOrder;
    copy(m_lcgs.cbegin(), m_lcgs.cend(), back_inserter(lcgsInPriorityOrder));
    sortAndPrioritizeLcgs(lcgsInPriorityOrder);
    return lcgsInPriorityOrder;
}

unsigned int AsilBasebandPooling::getNumberBasebandCardsWithMultipleLcgs() const {
    return m_lcgs.size() - m_basebandCards.size();
}

unsigned int AsilBasebandPooling::getMaxNumberOfLcgsInAllBasebandCards() const {
    return accumulate(
        m_basebandCards.cbegin(), m_basebandCards.cend(), 0U,
        [](unsigned int const partialResult, BasebandCard const& basebandCard) {
            return partialResult + getMaxNumberOfLcgsInBasebandCard(basebandCard);
        });
}

bool AsilBasebandPooling::areLcgAndBasebandCardsValid() const {
    return getMaxNumberOfLcgsInAllBasebandCards() >= m_lcgs.size();
}

void AsilBasebandPooling::sortAndPrioritizeBasebandCards(VectorOfBasebandCards& basebandCardsWithPrioritization) {
    stable_sort(
        basebandCardsWithPrioritization.begin(), basebandCardsWithPrioritization.end(),
        [](BasebandCard const& basebandCard1, BasebandCard const& basebandCard2) {
            return basebandCard1.getKeplers().size() > basebandCard2.getKeplers().size();
        });
}

void AsilBasebandPooling::sortAndPrioritizeLcgs(VectorOfLcgs& lcgsInPriorityOrder) {
    stable_sort(lcgsInPriorityOrder.begin(), lcgsInPriorityOrder.end(), [](Lcg const& lcg1, Lcg const& lcg2) {
        return lcg1.getPercentageShare() > lcg2.getPercentageShare();
    });
}

void AsilBasebandPooling::assignBasebandCardsWithOneLcg(
    KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
    SetOfBasebandCards const& basebandCardsWithOneLcg) {
    VectorOfBasebandCards basebandCardsWithPrioritization;
    copy(
        basebandCardsWithOneLcg.cbegin(), basebandCardsWithOneLcg.cend(),
        back_inserter(basebandCardsWithPrioritization));
    sortAndPrioritizeBasebandCards(basebandCardsWithPrioritization);

    auto lcgsIterator = lcgsInPriorityOrder.cbegin();
    for (BasebandCard const& basebandCard : basebandCardsWithPrioritization) {
        if (lcgsIterator != lcgsInPriorityOrder.cend()) {
            unsigned int const lcgId(lcgsIterator->getLcgId());
            SetOfKeplers const keplersInBasebandCard(basebandCard.getKeplers());
            for (Kepler const& kepler : keplersInBasebandCard) {
                poolingMap[kepler.getNid()] = lcgId;
            }
            ++lcgsIterator;
        }
    }
    lcgsInPriorityOrder.erase(lcgsInPriorityOrder.cbegin(), lcgsIterator);
}

void AsilBasebandPooling::assignBasebandCardsWithMultipleLcgs(
    KeplerNidToLcgMap& poolingMap, VectorOfLcgs& lcgsInPriorityOrder,
    SetOfBasebandCards const& basebandCardsWithMultipleLcgs) {
    VectorOfBasebandCards basebandCardsWithPrioritization;
    copy(
        basebandCardsWithMultipleLcgs.cbegin(), basebandCardsWithMultipleLcgs.cend(),
        back_inserter(basebandCardsWithPrioritization));
    sortAndPrioritizeBasebandCards(basebandCardsWithPrioritization);

    auto lcgsIterator = lcgsInPriorityOrder.cbegin();
    for (BasebandCard const& basebandCard : basebandCardsWithPrioritization) {
        SetOfKeplers const keplersInBasebandCard(basebandCard.getKeplers());
        unsigned int keplerCount = 0;
        for (Kepler const& kepler : keplersInBasebandCard) {
            if (keplerCount % 2 == 0 && keplerCount != 0) {
                ++lcgsIterator;
            }
            if (lcgsIterator != lcgsInPriorityOrder.cend()) {
                unsigned int const lcgId(lcgsIterator->getLcgId());
                poolingMap[kepler.getNid()] = lcgId;
            }
            ++keplerCount;
        }
        ++lcgsIterator;
    }
    lcgsInPriorityOrder.erase(lcgsInPriorityOrder.cbegin(), lcgsIterator);
}

unsigned int AsilBasebandPooling::getMaxNumberOfLcgsInBasebandCard(BasebandCard const& basebandCard) {
    return basebandCard.getKeplers().size() / 2;
}

bool AsilBasebandPooling::canMultipleLcgsBePutOnBasebandCard(BasebandCard const& basebandCard) {
    return getMaxNumberOfLcgsInBasebandCard(basebandCard) > 1;
}

AsilBasebandPooling::AsilBasebandPooling() = default;

}  // namespace alba
