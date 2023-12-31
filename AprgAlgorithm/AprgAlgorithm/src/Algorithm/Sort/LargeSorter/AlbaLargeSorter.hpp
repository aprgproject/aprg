#pragma once

#include <Algorithm/Sort/LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <Algorithm/Sort/LargeSorter/AlbaLargeSorterTypes.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlockCache.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlocks.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <functional>
#include <numeric>

namespace alba::algorithm {

template <typename ObjectToSort>
class AlbaLargeSorter {
    using BlockType = AlbaLargeSorterBlockType<ObjectToSort>;
    using BlockIterator = AlbaLargeSorterBlockIterator<ObjectToSort>;
    using BlockCache = AlbaLargeSorterBlockCache<BlockIterator>;
    using BlockCacheEntry = AlbaLargeSorterBlockCacheEntry<BlockIterator>;
    using BlockCacheContainer = AlbaLargeSorterBlockCacheContainer<BlockIterator>;

public:
    explicit AlbaLargeSorter(AlbaLargeSorterConfiguration const& configuration)
        : m_configuration(configuration),
          m_memoryCache(),
          m_fileStreamOpenedCache(),
          m_blocks(m_configuration, m_memoryCache, m_fileStreamOpenedCache) {
        createTempDirectories();
    }

    explicit AlbaLargeSorter(AlbaLargeSorterConfiguration&& configuration)
        : m_configuration(configuration),
          m_memoryCache(),
          m_fileStreamOpenedCache(),
          m_blocks(m_configuration, m_memoryCache, m_fileStreamOpenedCache) {
        createTempDirectories();
    }

    ~AlbaLargeSorter() { deleteTempFilesAndDirectories(); }
    AlbaLargeSorter(AlbaLargeSorter const&) = default;
    AlbaLargeSorter(AlbaLargeSorter&&) noexcept = default;
    AlbaLargeSorter& operator=(AlbaLargeSorter const&) = default;
    AlbaLargeSorter& operator=(AlbaLargeSorter&&) noexcept = default;
    [[nodiscard]] AlbaLargeSorterConfiguration getConfiguration() const { return m_configuration; }
    [[nodiscard]] bool isEmpty() const { return 0 == m_size; }

    void add(ObjectToSort const& objectToSort) {
        auto blockIterator(m_blocks.getNearestBlockIterator(objectToSort));
        m_blocks.addObjectToBlock(blockIterator, objectToSort);
        splitToSmallestBlocksIfOverflow(blockIterator);
        limitMemoryConsumption();
        limitFileStreams();
        ++m_size;
    }

    void addAtTheStart(ObjectToSort const& objectToSort) {
        m_blocks.moveMainInteratorToStart();
        BlockIterator blockIterator(m_blocks.getNearestBlockIterator(objectToSort));
        m_blocks.addObjectToBlockAtTheStart(blockIterator, objectToSort);
        splitToSmallestBlocksIfOverflow(blockIterator);
        limitMemoryConsumption();
        limitFileStreams();
        ++m_size;
    }

    void sortThenDoFunctionThenReleaseAllObjects(std::function<void(ObjectToSort const&)> doFunctionForAllObjects) {
        m_blocks.sortThenDoFunctionThenReleaseAllObjects(doFunctionForAllObjects);
        m_size = 0;
    }

    long long getSize() { return m_size; }

private:
    void splitToSmallestBlocksIfOverflow(BlockIterator const& blockIterator) {
        if (blockIterator->getNumberOfObjects() >= m_configuration.m_maximumNumberOfObjectsPerBlock) {
            splitToSmallestBlocks(blockIterator, DataBlockType::Memory);
        }
    }

    // nth element is not stable
    // void splitToSmallestBlocks(BlockIterator const& blockIterator, DataBlockType const blockTypeForNewBlocks) {
    //     BlockIterator iteratorAfterBlockToSplit(blockIterator);
    //     iteratorAfterBlockToSplit++;
    //     int index = 0, indexOfIndexes = 0;
    //     BlockIterator newBlockIterator(iteratorAfterBlockToSplit);
    //
    //     Indexes indexes;
    //     putIndexesWithMultiplesOfNumber(
    //         indexes, m_configuration.m_minimumNumberOfObjectsPerBlock, blockIterator->getNumberOfObjects());
    //
    //     blockIterator->nthElementThenDoFunctionThenRelease(indexes, [&](ObjectToSort const& objectToSort) {
    //         if (indexOfIndexes < indexes.size() && index >= indexes[indexOfIndexes]) {
    //             m_blocks.createNewBlockBeforeThisIterator(iteratorAfterBlockToSplit, blockTypeForNewBlocks);
    //             newBlockIterator = iteratorAfterBlockToSplit;
    //             newBlockIterator--;
    //             indexOfIndexes++;
    //         }
    //         m_blocks.addObjectToBlock(newBlockIterator, objectToSort);
    //         index++;
    //     });
    //     m_blocks.deleteBlock(blockIterator);
    // }
    // sort implementation
    void splitToSmallestBlocks(BlockIterator const& blockIterator, DataBlockType const blockTypeForNewBlocks) {
        BlockIterator iteratorAfterBlockToSplit(blockIterator);
        ++iteratorAfterBlockToSplit;
        int numberOfObjectsInCurrentBlock = 0;
        auto newBlockIterator(iteratorAfterBlockToSplit);
        blockIterator->sortThenDoFunctionThenRelease([&](ObjectToSort const& objectToSort) {
            if (numberOfObjectsInCurrentBlock == 0) {
                limitFileStreams();
                m_blocks.createNewBlockBeforeThisIterator(iteratorAfterBlockToSplit, blockTypeForNewBlocks);
                newBlockIterator = iteratorAfterBlockToSplit;
                --newBlockIterator;
            }
            m_blocks.addObjectToBlock(newBlockIterator, objectToSort);
            ++numberOfObjectsInCurrentBlock;
            if (numberOfObjectsInCurrentBlock >= m_configuration.m_minimumNumberOfObjectsPerBlock) {
                numberOfObjectsInCurrentBlock = 0;
            }
        });
        m_blocks.deleteBlock(blockIterator);
    }

    void limitMemoryConsumption() {
        int const totalMemoryConsumption = calculateTotalMemoryConsumption();
        transferMemoryBlocksToFileIfNeeded(totalMemoryConsumption);
    }

    void transferMemoryBlocksToFileIfNeeded(int const totalMemoryConsumption) {
        int memoryConsumption = totalMemoryConsumption;
        while (memoryConsumption > m_configuration.m_maximumNumberOfObjectsInMemory) {
            auto blockToSwitchToFileMode(m_memoryCache.popTheEarliestAddedBlock());
            memoryConsumption -= blockToSwitchToFileMode->getNumberOfObjectsInMemory();
            if (blockToSwitchToFileMode->getNumberOfObjectsInMemory() >
                m_configuration.m_minimumNumberOfObjectsPerBlock) {
                splitToSmallestBlocks(blockToSwitchToFileMode, DataBlockType::File);
            } else {
                blockToSwitchToFileMode->switchToFileMode();
                blockToSwitchToFileMode->releaseFileStream();
            }
        }
    }

    void limitFileStreams() {
        while (m_configuration.m_maximumFileStreams <
               static_cast<int>(m_fileStreamOpenedCache.getContainerReference().size())) {
            auto iteratorOfBlockToReleaseFile(m_fileStreamOpenedCache.popTheEarliestAddedBlock());
            iteratorOfBlockToReleaseFile->releaseFileStream();
        }
    }

    void createTempDirectories() {
        AlbaLocalPathHandler const blockDirectoryPathHandler(m_configuration.m_directoryForBlocks);
        blockDirectoryPathHandler.createDirectoriesAndIsSuccessful();
    }

    void deleteTempFilesAndDirectories() {
        AlbaLocalPathHandler const temporaryLocalDirectory(m_configuration.m_directoryForBlocks);
        if (temporaryLocalDirectory.doesExist()) {
            temporaryLocalDirectory.deleteAllDirectoryContentsAndIsSuccessful();
        }
    }

    void putIndexesWithMultiplesOfNumber(Indexes& indexes, int const number, int const numberOfObjects) {
        for (int index = 0; index < numberOfObjects; index += number) {
            indexes.emplace_back(index);
        }
    }

    int calculateTotalMemoryConsumption() {
        BlockCacheContainer const& memoryLimitCache(m_memoryCache.getContainerReference());
        int const totalMemoryConsumption = accumulate(
            memoryLimitCache.cbegin(), memoryLimitCache.cend(), 0,
            [](int const memoryConsumption, BlockCacheEntry const& blockCacheEntry) {
                return memoryConsumption + blockCacheEntry.m_blockInformation->getNumberOfObjectsInMemory();
            });
        return totalMemoryConsumption;
    }

    long long m_size{};
    AlbaLargeSorterConfiguration const m_configuration;
    BlockCache m_memoryCache;
    BlockCache m_fileStreamOpenedCache;
    DataBlocks<ObjectToSort> m_blocks;
};

}  // namespace alba::algorithm
