#pragma once

#include <Algorithm/Sort/LargeSorter/DataBlock.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <string>

namespace alba::algorithm {

struct AlbaLargeSorterConfiguration {
    AlbaLargeSorterConfiguration() = default;

    AlbaLargeSorterConfiguration(
        std::string const& directoryForBlocks, int const minimumNumberOfObjectsPerBlock,
        int const maximumNumberOfObjectsPerBlock, int const maximumNumberOfObjectsInMemory,
        int const maximumFileStreams)
        : m_directoryForBlocks(getFixedPath(directoryForBlocks)),
          m_minimumNumberOfObjectsPerBlock(minimumNumberOfObjectsPerBlock),
          m_maximumNumberOfObjectsPerBlock(maximumNumberOfObjectsPerBlock),
          m_maximumNumberOfObjectsInMemory(maximumNumberOfObjectsInMemory),
          m_maximumFileStreams(maximumFileStreams) {}

    [[nodiscard]] AlbaLargeSorterConfiguration getConfigurationWithDifferentDirectory(
        std::string const& directoryForBlocks) const {
        AlbaLargeSorterConfiguration copiedConfiguration(*this);
        copiedConfiguration.m_directoryForBlocks = directoryForBlocks;
        return copiedConfiguration;
    }

    [[nodiscard]] std::string getFilePathWithBlockNumber(int const blockNumber) const {
        std::stringstream ss;
        ss << m_directoryForBlocks << R"(\BLOCK_)" << blockNumber << ".txt";
        return getFixedPath(ss.str());
    }

    [[nodiscard]] bool isConfigurationValid() const {
        bool isValid =
            m_minimumNumberOfObjectsPerBlock > 0 || m_minimumNumberOfObjectsPerBlock < m_maximumNumberOfObjectsPerBlock;
        if (isValid) {
            AlbaLocalPathHandler const directoryPath(m_directoryForBlocks);
            directoryPath.createDirectoriesAndIsSuccessful();
            isValid = directoryPath.isExistingDirectory();
        }
        return isValid;
    }

    static std::string getFixedPath(std::string const& path) { return AlbaLocalPathHandler(path).getPath().string(); }
    std::string m_directoryForBlocks;
    int m_minimumNumberOfObjectsPerBlock{100};
    int m_maximumNumberOfObjectsPerBlock{1000};
    int m_maximumNumberOfObjectsInMemory{2000};
    int m_maximumFileStreams{100};
};

}  // namespace alba::algorithm
