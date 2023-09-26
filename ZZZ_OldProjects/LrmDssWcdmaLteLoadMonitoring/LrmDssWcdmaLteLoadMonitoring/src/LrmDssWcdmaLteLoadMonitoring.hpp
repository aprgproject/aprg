#pragma once

namespace alba {

// DssWcdmaLteLoadStateChangeFilteringCounts
inline constexpr unsigned int DSS_WCDMA_LTE_LOAD_STATE_CHANGE_FILTERING_COUNT = 5;

using EDssWcdmaFilterBandwidth = enum EDssWcdmaFilterBandwidth {
    EDssWcdmaFilterBandwidth_0_KHz = 0,
    EDssWcdmaFilterBandwidth_600_KHz = 1,
    EDssWcdmaFilterBandwidth_1200_KHz = 2
};

using EDssWcdmaLoad = enum EDssWcdmaLoad { EDssWcdmaLoad_Low = 0, EDssWcdmaLoad_Medium = 1, EDssWcdmaLoad_High = 2 };

class LrmDssWcdmaLteLoadMonitoring {
public:
    LrmDssWcdmaLteLoadMonitoring();
    [[nodiscard]] EDssWcdmaLoad getLoadStateFromCellLoad(unsigned int const cellLoad) const;
    [[nodiscard]] unsigned int getConsecutiveLowerLoadStateCount() const;
    [[nodiscard]] unsigned int getDchLoadFactor() const;
    [[nodiscard]] unsigned int getHsdpaAndHsfachLoadFactor() const;
    [[nodiscard]] unsigned int getMediumLoadThreshold() const;
    [[nodiscard]] unsigned int getHighLoadThreshold() const;

    [[nodiscard]] unsigned int calculateCellLoad(
        unsigned int const numberOfDchUsers, unsigned int const numberOfHsdpaUsers,
        bool const hasHsfachInTheCell) const;

    void setConsecutiveLowerLoadStateCount(unsigned int const count);

    void setCommissioningLoadFactorValues(
        unsigned int const dchLoadFactor, unsigned int const hsdpaAndHsfachLoadFactor);

    void setCommissioningLoadThresholdValues(
        unsigned int const mediumLoadThreshold, unsigned int const highLoadThreshold);

    EDssWcdmaLoad determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(
        EDssWcdmaLoad const currentLoadState, EDssWcdmaLoad const currentLoadStateOfTheAppliedFilter);

    static EDssWcdmaFilterBandwidth convertLoadStateToFilterBandwidth(EDssWcdmaLoad const loadState);
    static EDssWcdmaLoad getNextLowerLoadState(EDssWcdmaLoad const loadState);
    static EDssWcdmaLoad convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth const filterBandwidth);

private:
    unsigned int m_consecutiveLowerLoadStateCount{0};
    unsigned int m_dchLoadFactor{0};
    unsigned int m_hsdpaAndHsfachLoadFactor{0};
    unsigned int m_mediumLoadThreshold{0};
    unsigned int m_highLoadThreshold{0};
};

}  // namespace alba
