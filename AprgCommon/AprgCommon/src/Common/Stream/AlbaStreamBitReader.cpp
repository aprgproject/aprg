#include "AlbaStreamBitReader.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

AlbaStreamBitReader::AlbaStreamBitReader(istream& stream)
    : m_stream(stream)
{}

AlbaStreamBitReader::~AlbaStreamBitReader()
{}

bool AlbaStreamBitReader::noRemainingBitsInBuffer() const
{
    return m_bitBuffer.empty();
}

bool AlbaStreamBitReader::readBoolData()
{
    readIfNeeded(1U);
    bool result(m_bitBuffer.front());
    eraseBitsInBitBuffer(1U);
    return result;
}

char AlbaStreamBitReader::readCharData()
{
    return readBigEndianNumberDataInBuffer<char>();
}

std::istream& AlbaStreamBitReader::getInputStream()
{
    return m_stream;
}

void AlbaStreamBitReader::readIfNeeded(unsigned int const numberOfBitsRequired)
{
    if(m_bitBuffer.size() < numberOfBitsRequired)    {
        unsigned int numberOfBytesToRead = static_cast<unsigned int>(
                    ceil(static_cast<double>(numberOfBitsRequired - m_bitBuffer.size())/AlbaBitConstants::BYTE_SIZE_IN_BITS));
        std::vector<char> characterBuffer(numberOfBytesToRead, {});
        m_stream.read(&(characterBuffer.front()), numberOfBytesToRead);
        for(char const c : characterBuffer)
        {
            bitset<8> charByte(c);
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

void AlbaStreamBitReader::eraseBitsInBitBuffer(unsigned int const numberOfBitsToErase)
{
    m_bitBuffer.erase(m_bitBuffer.begin(), m_bitBuffer.begin()+numberOfBitsToErase);
}

}//namespace alba
