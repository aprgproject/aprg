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

    // perfect forwarding
    template <typename ConfigurationType, typename StringType>
    AlbaLargeSorterConfiguration(ConfigurationType&& sorterConfiguration, StringType&& directoryForBlocks)
        : AlbaLargeSorterConfiguration(std::forward<ConfigurationType>(sorterConfiguration)) {
        m_directoryForBlocks = getFixedPath(std::forward<StringType>(directoryForBlocks));
    }

    [[nodiscard]] std::string getFilePathWithBlockNumber(int const blockNumber) const {
        std::stringstream ss;
        ss << m_directoryForBlocks << R"(\BLOCK_)" << blockNumber << ".txt";
        return getFixedPath(ss.str());
    }

    [[nodiscard]] bool isConfigurationValid() const {
        if (m_minimumNumberOfObjectsPerBlock <= 0 ||
            m_maximumNumberOfObjectsPerBlock <= m_minimumNumberOfObjectsPerBlock) {
            return false;
        }
        AlbaLocalPathHandler directoryPath(m_directoryForBlocks);
        directoryPath.createDirectoriesAndIsSuccessful();
        if (!directoryPath.isExistingDirectory()) {
            return false;
        }
        return true;
    }

    static std::string getFixedPath(std::string const& path) { return AlbaLocalPathHandler(path).getPath().string(); }
    std::string m_directoryForBlocks;
    int m_minimumNumberOfObjectsPerBlock;
    int m_maximumNumberOfObjectsPerBlock;
    int m_maximumNumberOfObjectsInMemory;
    int m_maximumFileStreams;
};

}  // namespace alba::algorithm
