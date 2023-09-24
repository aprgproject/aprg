#include "AlbaFileReader.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <cstdint>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaFileReader::AlbaFileReader(ifstream& stream) : m_stream(stream) { setMaxBufferSize(INITIAL_MAX_BUFFER_SIZE); }
AlbaFileReader::AlbaFileReader(ifstream& stream, size_t const size) : m_stream(stream) { setMaxBufferSize(size); }

char AlbaFileReader::getCharacter() {
    char tempChar(0);
    m_stream.get(tempChar);
    return tempChar;
}

char* AlbaFileReader::getCharacters(size_t& numberOfCharacters) {
    size_t const bufferSize = m_characterBuffer.size();
    if (bufferSize <= numberOfCharacters) {
        numberOfCharacters = bufferSize - 1;
    }
    m_stream.read(getCharacterBufferPointer(), static_cast<streamsize>(numberOfCharacters));
    numberOfCharacters = static_cast<size_t>(m_stream.gcount());
    m_characterBuffer[numberOfCharacters] = '\0';
    return getCharacterBufferPointer();
}

bool AlbaFileReader::isNotFinished() {
    // return !m_stream.eof() && m_stream.peek()!=EOF;
    // return getCurrentLocation() < m_fileSize && !m_stream.eof();
    m_stream.clear();
    return m_stream.peek() != EOF && !m_stream.eof();
}

size_t AlbaFileReader::getCurrentLocation() const {
    auto tellgOutput = m_stream.tellg();
    return tellgOutput > 0 ? static_cast<size_t>(tellgOutput) : 0U;
}

size_t AlbaFileReader::getFileSize() const { return getFileSize(m_stream); }

size_t AlbaFileReader::getMaxBufferSize() const {
    auto bufferSize = static_cast<size_t>(m_characterBuffer.size());
    if (bufferSize > 0) {
        --bufferSize;
    }
    return bufferSize;
}

void AlbaFileReader::moveToTheBeginning() const { m_stream.seekg(0, ifstream::beg); }

void AlbaFileReader::moveLocation(size_t const location) const {
    m_stream.seekg(static_cast<ifstream::off_type>(location), ifstream::beg);
}

void AlbaFileReader::saveDataToMemoryBuffer(AlbaMemoryBuffer& buffer, size_t const numberOfBytesToRead) {
    char* writer =
        static_cast<char*>(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(numberOfBytesToRead));
    m_stream.read(writer, static_cast<streamsize>(numberOfBytesToRead));
}

void AlbaFileReader::skipLine() {
    if (isNotFinished()) {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
    }
}

void AlbaFileReader::setMaxBufferSize(size_t const bufferSize) {
    // This is ensuring that buffer always contains one.
    // 1) This is for "front()".
    // 2) This is for null terminator.
    m_characterBuffer.resize(bufferSize + 1);
}

string AlbaFileReader::getLine() {
    string result;
    if (isNotFinished()) {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
        result = string(getCharacterBufferPointer());
    }
    return result;
}

string AlbaFileReader::getLineAndIgnoreWhiteSpaces() {
    string result;
    while (isNotFinished()) {
        m_stream.clear();
        m_stream.getline(getCharacterBufferPointer(), static_cast<streamsize>(m_characterBuffer.size()));
        string const stringFromBuffer(getCharacterBufferPointer());
        result = getStringWithoutStartingAndTrailingWhiteSpace(stringFromBuffer);
        if (!result.empty()) {
            break;
        }
    }
    return result;
}

char* AlbaFileReader::getCharacterBufferPointer() { return &(m_characterBuffer.front()); }

size_t AlbaFileReader::getFileSize(ifstream& inputStream) {
    inputStream.seekg(0, ifstream::end);
    auto tellgOutput = inputStream.tellg();
    size_t const fileSize = tellgOutput > 0 ? static_cast<size_t>(tellgOutput) : 0U;
    inputStream.seekg(0, ifstream::beg);
    return fileSize;
}

}  // namespace alba
