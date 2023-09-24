#include "AlbaStreamBitWriter.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaStreamBitWriter::AlbaStreamBitWriter(ostream& stream) : m_stream(stream) {}
AlbaStreamBitWriter::~AlbaStreamBitWriter() { transferAllToStream(); }

void AlbaStreamBitWriter::writeBoolData(bool const data) {
    putBoolDataToBuffer(data);
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeCharData(char const data) {
    putCharDataToBuffer(data);
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeStringData(string_view const data) {
    for (char const character : data) {
        putCharDataToBuffer(character);
    }
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::writeHexDigitData(string_view const hexDigitsData) {
    for (char const character : hexDigitsData) {
        bitset<4> hexDigitBitset(convertHexCharacterToNumber<char>(character));
        putBoolDataToBuffer(hexDigitBitset[3]);
        putBoolDataToBuffer(hexDigitBitset[2]);
        putBoolDataToBuffer(hexDigitBitset[1]);
        putBoolDataToBuffer(hexDigitBitset[0]);
    }
    transferBytesAsMuchAsPossibleToStream();
}

void AlbaStreamBitWriter::flush() { transferAllToStream(); }
ostream& AlbaStreamBitWriter::getOutputStream() { return m_stream; }
void AlbaStreamBitWriter::putBoolDataToBuffer(bool const boolValue) { m_bitBuffer.emplace_back(boolValue); }
void AlbaStreamBitWriter::putCharDataToBuffer(char const data) { putBigEndianNumberDataInBuffer<char>(data); }

void AlbaStreamBitWriter::transferBytesAsMuchAsPossibleToStream() {
    auto bitBufferSize = static_cast<int>(m_bitBuffer.size());
    if (bitBufferSize >= 8) {
        int index = 0;
        for (; index + 8 <= bitBufferSize; index += 8) {
            bitset<8> byte;
            byte.set(0, m_bitBuffer[index + 7]);
            byte.set(1, m_bitBuffer[index + 6]);
            byte.set(2, m_bitBuffer[index + 5]);
            byte.set(3, m_bitBuffer[index + 4]);
            byte.set(4, m_bitBuffer[index + 3]);
            byte.set(5, m_bitBuffer[index + 2]);
            byte.set(6, m_bitBuffer[index + 1]);
            byte.set(7, m_bitBuffer[index]);
            m_stream << static_cast<char>(byte.to_ulong());
        }
        m_bitBuffer.erase(begin(m_bitBuffer), begin(m_bitBuffer) + index);
    }
}

void AlbaStreamBitWriter::transferAllToStream() noexcept {
    try {
        bitset<8> byte;
        auto bitBufferSize = static_cast<int>(m_bitBuffer.size());
        int index = 0;
        for (; index < bitBufferSize; ++index) {
            int const remainder(index % 8);
            byte.set(7 - remainder, m_bitBuffer[remainder]);
            if (remainder == 7) {
                m_stream << static_cast<char>(byte.to_ulong());
                byte.reset();
            }
        }
        if (index % 8 != 0) {
            m_stream << static_cast<char>(byte.to_ulong());
        }
        m_bitBuffer.clear();
    } catch (exception const& capturedException) {
        cerr << "Exception happened at transferring all to stream: [" << capturedException.what() << "]\n";
    }
}

}  // namespace alba
