#pragma once

#include <Algorithm/Sort/LargeSorter/DataBlock.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <string>

namespace alba::algorithm {

struct AlbaLargeSorterConfiguration {
    AlbaLargeSorterConfiguration()
        : m_minimumNumberOfObjectsPerBlock(100),
          m_maximumNumberOfObjectsPerBlock(1000),
          m_maximumNumberOfObjectsInMemory(2000),
          m_maximumFileStreams(100) {}

    AlbaLargeSorterConfiguration(
        std::string const& directoryForBlocks, int const minimumNumberOfObjectsPerBlock,
        int const maximumNumberOfObjectsPerBlock, int const maximumNumberOfObjectsInMemory,
        int const maximumFileStreams)
        : m_directoryForBlocks(getFixedPath(directoryForBlocks)),
          m_minimumNumberOfObjectsPerBlock(minimumNumberOfObjectsPerBlock),
          m_maximumNumberOfObjectsPerBlock(maximumNumberOfObjectsPerBlock),
          m_maximumNumberOfObjectsInMemory(maximumNumberOfObjectsInMemory),
          m_maximumFileStreams(maximumFileStreams) {}

    AlbaLargeSorterConfiguration(
        AlbaLargeSorterConfiguration const& sorterConfiguration, std::string const& directoryForBlocks)
        : AlbaLargeSorterConfiguration(sorterConfiguration) {
        m_directoryForBlocks = getFixedPath(directoryForBlocks);
    }

    [[nodiscard]] std::string getFilePathWithBlockNumber(int const blockNumber) const {
        std::stringstream ss;
        ss << m_directoryForBlocks << R"(\BLOCK_)" << blockNumber << ".txt";
        return getFixedPath(ss.str());
    }

    [[nodiscard]] bool isConfigurationValid() const {
        if (m_minimumNumberOfObjectsPerBlock <= 0) {
            return false;
        }
        if (m_maximumNumberOfObjectsPerBlock <= m_minimumNumberOfObjectsPerBlock) {
            return false;
        }
        AlbaLocalPathHandler directoryPath(m_directoryForBlocks);
        directoryPath.createDirectoriesForNonExisitingDirectories();
        directoryPath.reInput();
        if (!directoryPath.doesExist()) {
            return false;
        }
        if (!directoryPath.isDirectory()) {
            return false;
        }
        return true;
    }

    static std::string getFixedPath(std::string const& path) { return AlbaLocalPathHandler(path).getPath(); }
    std::string m_directoryForBlocks;
    int m_minimumNumberOfObjectsPerBlock;
    int m_maximumNumberOfObjectsPerBlock;
    int m_maximumNumberOfObjectsInMemory;
    int m_maximumFileStreams;
};

}  // namespace alba::algorithm
