#pragma once

#include <HardwareConfiguration.hpp>

#include <functional>
#include <map>
#include <set>
#include <vector>

namespace alba {

struct NyquistAndTurboNyquistCount {
    unsigned int numberOfNyquists;
    unsigned int numberOfTurboNyquists;
};

struct SelectionDspResult {
    SelectionDspResult();
    bool isSelectionSuccessful{false};
    bool isNbicAllocated{false};
    unsigned int address{0};
    unsigned int dliPool{0};
};

struct SelectionDspResultForCcdAndMcd {
    SelectionDspResultForCcdAndMcd();
    bool isSelectionSuccessful{false};
    bool isNbicAllocated{false};
    unsigned int ccdAddress{0};
    unsigned int mcdAddress{0};
    unsigned int dliPool{0};
};

struct FspPairDetails {
    FspPairDetails(unsigned int const firstFspTemp, unsigned int const secondFspTemp, unsigned int const priorityTemp);
    unsigned int firstFspAddress;
    unsigned int secondFspAddress;
    unsigned int priority;
};

using FspPairsDetails = std::vector<FspPairDetails>;
using DspBooleanCondition = std::function<bool(Dsp const&)>;
using DspComparisonCondition = std::function<bool(Dsp const&, Dsp const&)>;
using FspBooleanCondition = std::function<bool(Fsp const&)>;
using FspComparisonCondition = std::function<bool(Fsp const&, Fsp const&)>;
using FspPairDetailsComparisonCondition = std::function<bool(FspPairDetails const&, FspPairDetails const&)>;
using FspPairDetailsCondition = std::function<bool(FspPairDetails const&)>;
using DliPools = std::set<unsigned int>;

class Lrm {
public:
    explicit Lrm(HardwareConfiguration& hardwareConfiguration);
    void setHibernationCommissioned(bool const isHibernationCommissioned);
    void setNumberOfUnallocatedPicPoolsPerLcg(unsigned int const lcgId, unsigned int const numberOfPicPools);
    void clearLcgToUnallocatedPicPools(unsigned int const lcgId);
    void setMaxAmountOfNonDcdsPerFsp(unsigned int const maxAmountOfNonDcdsPerFsp);
    SelectionDspResult allocateMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResult allocateNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResult allocatePicForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResultForCcdAndMcd allocateCcdMcdForLcgIdAccordingToMark(unsigned int const lcgId);
    SelectionDspResultForCcdAndMcd allocateCcdNbicMcdForLcgIdAccordingToMark(unsigned int const lcgId);

private:
    // CCD+MCD
    [[nodiscard]] FspAddresses selectFspsForCcdMcd(unsigned int const lcgId) const;
    [[nodiscard]] FspAddresses selectFspsForCcdMcd2(unsigned int const lcgId) const;
    // CCD NBIC MCD
    [[nodiscard]] FspAddresses selectFspsForCcdNbicMcd(unsigned int const lcgId) const;
    [[nodiscard]] FspAddresses selectFspsForCcdNbicMcd2(unsigned int const lcgId) const;

    [[nodiscard]] NyquistAndTurboNyquistCount getNumberOfEmptyNAndTnOfFspAndLcg(
        unsigned int const fspAddress, unsigned int const lcgId) const;

    [[nodiscard]] NyquistAndTurboNyquistCount getNumberOfNAndTnWithoutCfsOfFspAndLcg(
        unsigned int const fspAddress, unsigned int const lcgId) const;

    [[nodiscard]] NyquistAndTurboNyquistCount getNumberOfEmptyNAndTnOfLcg(unsigned int const lcgId) const;
    [[nodiscard]] NyquistAndTurboNyquistCount getNumberOfEmptyNAndTnInMsmOfLcg(unsigned int const lcgId) const;
    // MCD
    [[nodiscard]] SelectionDspResult selectFspForEmptyDspForMcd(unsigned int const lcgId) const;
    [[nodiscard]] SelectionDspResult selectNonEmptyDspToClearForMcd(unsigned int const lcgId) const;
    // NBIC MCD
    [[nodiscard]] SelectionDspResult selectFspForEmptyDspForNbicMcd(unsigned int const lcgId) const;
    [[nodiscard]] SelectionDspResult selectNonEmptyDspToClearForNbicMcd(unsigned int const lcgId) const;
    // PIC
    [[nodiscard]] SelectionDspResult selectFspForPic(unsigned int const lcgId) const;

    [[nodiscard]] SelectionDspResult selectEmptyDspPriotizingNyquistTypeAndAddressInFsp(
        unsigned int const lcgId, unsigned int const fspAddress) const;

    [[nodiscard]] SelectionDspResult selectTnPriotizingLessUsersAndHsupaCfsInFsp(
        unsigned int const lcgId, unsigned int const fspAddress) const;

    [[nodiscard]] unsigned int getPriorityBasedOnNAndTnCountForFspMcdSelection(
        Fsp const& fsp, unsigned int const lcgId) const;

    [[nodiscard]] unsigned int getPriorityBasedSharedLcgFspMcdSelection(Fsp const& fsp, unsigned int const lcgId) const;

    [[nodiscard]] unsigned int getPriorityBasedOnNAndTnCountForFspCcdMcdSelection(
        Fsp const& fsp, unsigned int const lcgId) const;

    [[nodiscard]] unsigned int getPriorityBasedSharedLcgTnInPicSelection(
        Fsp const& fsp, unsigned int const lcgId) const;

    [[nodiscard]] unsigned int getPriorityBasedOnTnWithoutCfsForFspPicSelection(
        Fsp const& fsp, unsigned int const lcgId) const;

    [[nodiscard]] unsigned int getNumberOfNonDcdsInFsp(unsigned int const fspAddress) const;
    [[nodiscard]] unsigned int getNumberOfFreeDliPoolsOfFsp(unsigned int const fspAddress) const;
    [[nodiscard]] unsigned int getFreeDliToAllocateForDsp(unsigned int const dspAddress) const;
    [[nodiscard]] unsigned int getFreeDliBasedOnSameFsp(Dsp const& dsp, DliPools const& freeDliPools) const;
    [[nodiscard]] unsigned int getFreeDliBasedOnOtherFsps(Dsp const& dsp, DliPools const& freeDliPools) const;

    [[nodiscard]] unsigned int getPriorityForFspPair(
        FspPairDetails const& fspPairDetails, unsigned int const lcgId) const;

    [[nodiscard]] unsigned int getNumberOfUnallocatedPicPoolsForLcg(unsigned int const lcgId) const;

    [[nodiscard]] bool isThereSpaceForTnForMcdOrCcdConsideringPic(
        unsigned int const fspAddress, unsigned int const numberOfMcdOrCcd, unsigned int const lcgId) const;

    [[nodiscard]] bool canTnBeAllocatedBasedOnPicAndNumberOfTnToBeAllocated(
        NyquistAndTurboNyquistCount const& nAndTnCountInMsmOfLcg, unsigned int const numberOfTurboNyquistToBeUsed,
        unsigned int const lcgId) const;

    [[nodiscard]] bool isSharedLcg(unsigned int const lcgId) const;
    [[nodiscard]] bool canAFreeDliBeAllocatedInFsp(unsigned int const fspAddress, unsigned int const lcgId) const;
    void sortFspBasedPriorityForMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForMcdSelection2(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForNbicMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForNbicMcdSelection2(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void removeNotNeededFspsForMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForCcdMcdSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void removeNotNeededFspsForCcdMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void removeNotNeededFspsForNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void fixFspsForNbic(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void removeNotNeededFspsForCcdNbicMcd(FspAddresses& fspAddresses, unsigned int const lcgId) const;
    void sortFspBasedPriorityForPicSelection(FspAddresses& fspAddresses, unsigned int const lcgId) const;

    void saveNeededFspsForCcdOrMcdBasedOnNOrTn(
        UniqueFspAddresses& neededUniqueFspAddresses, unsigned int& numberOfDspCcdAndMcd,
        FspAddresses const& fspAddresses, unsigned int const lcgId) const;

    void saveNeededFspsForCcdOrNbicMcdBasedOnNOrTnWithDliRestrictions(
        UniqueFspAddresses& neededUniqueFspAddresses, FspAddresses const& fspAddresses, unsigned int const lcgId,
        unsigned int const numberOfDspCcdAndMcd) const;

    void copyFspWithAtLeastThisNumberOfEmptyNAndTnAndBelowMaxAmountOfNonDcds(
        FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const;

    void copyFspWithAtLeastThisNumberOfEmptyNAndTnWithDliRestrictions(
        FspAddresses& fspAddresses, unsigned int const requiredEmptyCount, unsigned int const lcgId) const;

    void copyFspWithAtLeastThisNumberOfTnDcdsWithoutHsRachCfsWithDliRestrictions(
        FspAddresses& fspAddresses, unsigned int const lcgId) const;

    void copyFspAddressesThatSatisfiesThisCondition(
        FspAddresses& fspAddresses, FspBooleanCondition const& condition) const;

    void sortFspAddressesBasedOnCondition(FspAddresses& fspAddresses, FspComparisonCondition const& condition) const;

    void copyDspAddressesThatSatisfiesThisCondition(
        DspAddresses& dspAddressesForLcgInFsp, DspBooleanCondition const& condition) const;

    void copyDspAddressesInFspThatSatisfiesThisCondition(
        DspAddresses& dspAddressesForLcgInFsp, unsigned int const fspAddress,
        DspBooleanCondition const& condition) const;

    void sortDspAddressesBasedOnCondition(
        DspAddresses& dspAddressesForLcgInFsp, DspComparisonCondition const& condition) const;

    void copyFreeDliPools(DliPools& freeDliPools) const;
    void copyUsedDliPools(DliPools& usedDliPools) const;
    void copyUsedDliPoolsOnFsp(DliPools& usedDliPools, unsigned int const fspAddress) const;

    void copyUsedDliPoolsOnOtherFspsExceptThisFsp(
        DliPools& usedDliPools, unsigned int const fspAddressOfSkippedFsp) const;

    void copyAllFspPairs(FspPairsDetails& fspPairsDetails) const;
    void sortFspPairsForCcdMcdSelection(FspPairsDetails& fspPairsDetails) const;
    void removeFspPairsForCcdMcdSelection(FspPairsDetails& fspPairsDetails, unsigned int const lcgId) const;
    void removeFspPairsForCcdNbicMcdSelection(FspPairsDetails& fspPairsDetails, unsigned int const lcgId) const;
    void updatePriorityForAllFspPairs(FspPairsDetails& fspPairsDetail, unsigned int const lcgId) const;
    void changeModeForCcdAndUpdateDspDetails(SelectionDspResultForCcdAndMcd const& selectionDspResultForCcdAndMcd);
    void changeModeForMcdAndUpdateDspDetails(SelectionDspResultForCcdAndMcd const& selectionDspResultForCcdAndMcd);
    void changeModeAndUpdateDspDetails(SelectionDspResult const& selectionDspResult, DspMode const dspMode);
    static void setSelectionDspResult(SelectionDspResult& selectionDspResultReference, unsigned int const fspAddress);

    static void incrementNAndTnCountBasedOnNyquistType(
        NyquistAndTurboNyquistCount& countReference, NyquistType const nyquistType);

    static void sortFspPairsBasedOnCondition(
        FspPairsDetails& fspPairsDetails, FspPairDetailsComparisonCondition const& condition);

    static void removeFspPairsBasedOnCondition(
        FspPairsDetails& fspPairsDetails, FspPairDetailsCondition const& condition);

    static void changeMode(Dsp& dspToChange, DspMode const dspMode);
    static void setDliIfNeeded(Dsp& dspToChange, DspMode const dspMode, bool const isNbic, unsigned int const dliPool);
    static void setAsNbicIfNeeded(Dsp& dspToChange, DspMode const dspMode, bool const isNbic);
    // Common
    // void saveNeededFspsForCcdOrMcdBasedOnNyquist(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int&
    // numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const; void
    // saveNeededFspsForCcdOrMcdBasedOnTurboNyquist(UniqueFspAddresses & neededUniqueFspAddresses, unsigned int&
    // numberOfDspToAllocate, FspAddresses const& fspAddresses, unsigned int const lcgId) const;
    static unsigned int getPriorityBasedOnLessUsersAndHsupaCfsForDsp(Dsp const& dsp);
    static unsigned int getConflictingDliPoolForThisDli(unsigned int const dliPool);
    static unsigned int getLeastConflictingDliPoolForThisDli(unsigned int const dliPool);
    bool m_isHibernationCommissioned{false};
    unsigned int m_maxAmountOfNonDcdsPerFsp{6};
    std::map<unsigned int, bool> m_lcgToUnallocatedPicPools;
    HardwareConfiguration& m_hardwareConfigurationReference;
    AddressToDspMap& m_addressToDspMap;
    AddressToFspMap& m_addressToFspMap;
};

}  // namespace alba
