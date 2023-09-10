#include "AlbaStreamBitReader.hpp"

#include <algorithm>
#include <vector>

using namespace std;

namespace alba {

AlbaStreamBitReader::AlbaStreamBitReader(istream& stream) : m_stream(stream) {}
bool AlbaStreamBitReader::noRemainingBitsInBuffer() const { return m_bitBuffer.empty(); }

string AlbaStreamBitReader::readStringData(size_t const numberOfCharacters) {
    string result;
    for (size_t i = 0; i < numberOfCharacters; ++i) {
        char const character(readCharData());
        if (!m_stream.eof()) {
            result += character;
        } else {
            break;
        }
    }
    return result;
}

string AlbaStreamBitReader::readWholeStreamAsStringData() {
    string result;
    while (true) {
        char const character(readCharData());
        if (!m_stream.eof()) {
            result += character;
        } else {
            break;
        }
    }
    return result;
}

char AlbaStreamBitReader::readCharData() { return AlbaStreamBitReader::readBigEndianNumberData<char>(); }

bool AlbaStreamBitReader::readBoolData() {
    readIfNeeded(1U);
    bool const result(m_bitBuffer.front());
    eraseBitsInBitBuffer(1U);
    return result;
}

istream& AlbaStreamBitReader::getInputStream() { return m_stream; }

void AlbaStreamBitReader::readIfNeeded(size_t const numberOfBitsRequired) {
    if (m_bitBuffer.size() < numberOfBitsRequired) {
        auto numberOfBytesToRead = static_cast<size_t>(
            ceil(static_cast<double>(numberOfBitsRequired - m_bitBuffer.size()) / AlbaBitConstants::BYTE_SIZE_IN_BITS));
        vector<char> characterBuffer(numberOfBytesToRead, {});
        m_stream.read(&(characterBuffer.front()), static_cast<std::streamsize>(numberOfBytesToRead));
        for (char const character : characterBuffer) {
            bitset<8> charByte(character);
            m_bitBuffer.emplace_back(charByte[7]);
            m_bitBuffer.emplace_back(charByte[6]);
            m_bitBuffer.emplace_back(charByte[5]);
            m_bitBuffer.emplace_back(charByte[4]);
            m_bitBuffer.emplace_back(charByte[3]);
            m_bitBuffer.emplace_back(charByte[2]);
            m_bitBuffer.emplace_back(charByte[1]);
            m_bitBuffer.emplace_back(charByte[0]);
        }
    }
}

void AlbaStreamBitReader::eraseBitsInBitBuffer(size_t const numberOfBitsToErase) {
    m_bitBuffer.erase(begin(m_bitBuffer), begin(m_bitBuffer) + static_cast<int>(numberOfBitsToErase));
}

}  // namespace alba
