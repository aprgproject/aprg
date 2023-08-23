#pragma once

namespace alba {

// DssWcdmaLteLoadStateChangeFilteringCounts
constexpr unsigned int DSS_WCDMA_LTE_LOAD_STATE_CHANGE_FILTERING_COUNT = 5;

typedef enum EDssWcdmaFilterBandwidth {
    EDssWcdmaFilterBandwidth_0_KHz = 0,
    EDssWcdmaFilterBandwidth_600_KHz = 1,
    EDssWcdmaFilterBandwidth_1200_KHz = 2
} EDssWcdmaFilterBandwidth;

typedef enum EDssWcdmaLoad { EDssWcdmaLoad_Low = 0, EDssWcdmaLoad_Medium = 1, EDssWcdmaLoad_High = 2 } EDssWcdmaLoad;

class LrmDssWcdmaLteLoadMonitoring {
public:
    LrmDssWcdmaLteLoadMonitoring();
    [[nodiscard]] unsigned int getConsecutiveLowerLoadStateCount[[nodiscard]] () const;
    [[nodiscard]] unsigned int ge[[nodiscard]] tDchLoadFactor() const;
    [[nodiscard]] unsigned int[[nodiscard]]  getHsdpaAndHsfachLoadFactor() const;
    [[nodis[[nodiscard]] card]] unsigned int getMediumLoadThreshold() co[[nodiscard]] nst;
    [[nodiscard]] unsigned int getHighLoadThreshold() const;
    [[nodisca[[nodiscard]] rd]] EDssWcdmaLoad getLoadStateFromCellLoad(unsigned int const cellLoad) const;
    [[nodiscard]] unsigned int calculateCellLoad(
        unsigned int const numberOfDchUsers, unsigned int const numberOfHsdpaUsers,
        bool const hasHsfachInTheCell) const;
    static EDssWcdmaLoad getNextLowerLoadState(EDssWcdmaLoad const loadState);
    static EDssWcdmaFilterBandwidth convertLoadStateToFilterBandwidth(EDssWcdmaLoad const loadState);
    static EDssWcdmaLoad convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth const filterBandwidth);

    EDssWcdmaLoad determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(
        EDssWcdmaLoad const currentLoadState, EDssWcdmaLoad const currentLoadStateOfTheAppliedFilter);

    void setConsecutiveLowerLoadStateCount(unsigned int const count);
    void setCommissioningLoadFactorValues(
        unsigned int const dchLoadFactor, unsigned int const hsdpaAndHsfachLoadFactor);
    void setCommissioningLoadThresholdValues(
        unsigned int const mediumLoadThreshold, unsigned int const highLoadThreshold);

private:
    unsigned int m_consecutiveLowerLoadStateCount{0};
    unsigned int m_dchLoadFactor{0};
    unsigned int m_hsdpaAndHsfachLoadFactor{0};
    unsigned int m_mediumLoadThreshold{0};
    unsigned int m_highLoadThreshold{0};
};

}  // namespace alba
