#include "AlbaMemoryBuffer.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <memory>

using namespace std;

namespace alba {

AlbaMemoryBuffer::AlbaMemoryBuffer(void const* sourcePointer, size_t const size) { addData(sourcePointer, size); }
AlbaMemoryBuffer::operator bool() const { return hasContent(); }
AlbaMemoryBuffer::ByteType AlbaMemoryBuffer::operator[](size_t const index) const { return m_buffer[index]; }
AlbaMemoryBuffer::ByteType& AlbaMemoryBuffer::operator[](size_t const index) { return m_buffer[index]; }
bool AlbaMemoryBuffer::hasContent() const { return !m_buffer.empty(); }
size_t AlbaMemoryBuffer::getSize() const { return m_buffer.size(); }
void const* AlbaMemoryBuffer::getConstantBufferPointer() const { return static_cast<void const*>(m_buffer.data()); }
void* AlbaMemoryBuffer::getBufferPointer() { return static_cast<void*>(m_buffer.data()); }
void AlbaMemoryBuffer::clear() { m_buffer.clear(); }

void AlbaMemoryBuffer::clearAndSetNewData(void* sourcePointer, size_t const size) {
    clear();
    addData(sourcePointer, size);
}

void AlbaMemoryBuffer::resize(size_t const size) { m_buffer.resize(size); }
void AlbaMemoryBuffer::resize(size_t const size, uint8_t const initialValue) { m_buffer.resize(size, initialValue); }

std::ostream& operator<<(std::ostream& out, AlbaMemoryBuffer const& memoryBuffer) {
    containerHelper::saveContentsInDecimalAndHexadecimalFormat<std::vector<uint8_t>, size_t>(
        out, memoryBuffer.m_buffer);
    return out;
}

void* AlbaMemoryBuffer::resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(size_t const additionalSize) {
    int oldSize = static_cast<int>(m_buffer.size());
    m_buffer.resize(oldSize + additionalSize);
    return static_cast<void*>((m_buffer.begin() + oldSize).operator->());
}

void AlbaMemoryBuffer::addData(void const* sourcePointer, size_t const additionalSize) {
    void* destinationVoidPointer = resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(additionalSize);
    memcpy(destinationVoidPointer, sourcePointer, additionalSize);
}

}  // namespace alba
