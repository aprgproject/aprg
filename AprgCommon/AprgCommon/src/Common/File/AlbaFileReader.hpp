#pragma once

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <fstream>
#include <numeric>
#include <string>
#include <vector>

namespace alba {

class AlbaFileReader {
public:
    explicit AlbaFileReader(std::ifstream& stream);
    explicit AlbaFileReader(std::ifstream& stream, size_t const size);
    bool isNotFinished();
    char getCharacter();
    char* getCharacters(size_t& numberOfCharacters);
    template <typename NumberType>
    NumberType getOneByteData();
    template <typename NumberType>
    NumberType getTwoByteData();
    template <typename NumberType>
    NumberType getFourByteData();
    template <typename NumberType>
    NumberType getEightByteData();
    template <typename NumberType>
    NumberType getTwoByteSwappedData();
    template <typename NumberType>
    NumberType getFourByteSwappedData();
    template <typename NumberType>
    NumberType getEightByteSwappedData();
    template <typename NumberType, size_t numberOfBytesToRead>
    NumberType getData();
    template <typename NumberType>
    NumberType getDataForOneByte();
    void saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, size_t const numberOfBytesToRead);
    void skipLine();
    std::string getLine();
    std::string getLineAndIgnoreWhiteSpaces();

    [[nodiscard]] size_t getCurrentLocation() const;
    [[nodiscard]] size_t getFileSize() const;
    void moveToTheBeginning() const;
    void moveLocation(size_t const location) const;
    void setMaxBufferSize(size_t const bufferSize);
    [[nodiscard]] size_t getMaxBufferSize() const;

private:
    char* getCharacterBufferPointer();
    [[nodiscard]] static size_t getFileSize(std::ifstream& inputStream);
    static constexpr size_t INITIAL_MAX_BUFFER_SIZE = 10000;
    size_t m_fileSize{};
    std::vector<char> m_characterBuffer;
    std::ifstream& m_stream;
};

template <typename NumberType>
NumberType AlbaFileReader::getOneByteData() {
    return getDataForOneByte<NumberType>();
}

template <typename NumberType>
NumberType AlbaFileReader::getTwoByteData() {
    return getData<NumberType, 2>();
}

template <typename NumberType>
NumberType AlbaFileReader::getFourByteData() {
    return getData<NumberType, 4>();
}

template <typename NumberType>
NumberType AlbaFileReader::getEightByteData() {
    return getData<NumberType, 8>();
}

template <typename NumberType>
NumberType AlbaFileReader::getTwoByteSwappedData() {
    return AlbaBitManipulation<NumberType>::swapForTwoBytes(getData<NumberType, 2>());
}

template <typename NumberType>
NumberType AlbaFileReader::getFourByteSwappedData() {
    return AlbaBitManipulation<NumberType>::swapForFourBytes(getData<NumberType, 4>());
}

template <typename NumberType>
NumberType AlbaFileReader::getEightByteSwappedData() {
    return AlbaBitManipulation<NumberType>::swapForEightBytes(getData<NumberType, 8>());
}

template <typename NumberType, size_t numberOfBytesToRead>
NumberType AlbaFileReader::getData() {
    m_stream.read(getCharacterBufferPointer(), numberOfBytesToRead);
    auto numberOfCharacters = m_stream.gcount();
    return std::accumulate(
        m_characterBuffer.cbegin(), m_characterBuffer.cbegin() + numberOfCharacters, static_cast<NumberType>(0U),
        [&](NumberType partialSum, char newValue) {
            partialSum <<= 8;
            partialSum |= static_cast<NumberType>(AlbaBitConstants::ALL_ONES_8_BITS & static_cast<uint8_t>(newValue));
            return partialSum;
        });
}

template <typename NumberType>
NumberType AlbaFileReader::getDataForOneByte() {
    m_stream.read(getCharacterBufferPointer(), 1U);
    if (m_stream.gcount() > 0) {
        return static_cast<NumberType>(m_characterBuffer.front());
    }
    return 0;
}

}  // namespace alba
