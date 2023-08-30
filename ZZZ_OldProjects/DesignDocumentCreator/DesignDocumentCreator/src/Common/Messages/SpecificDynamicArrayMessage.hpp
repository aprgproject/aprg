#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

#include <vector>

namespace DesignDocumentCreator {

template <MessageName messageName>
class SpecificDynamicArrayMessage : public Message {
public:
    using SpecificDynamicArrayMessageWrapper = MessageWrapper<messageName>;
    using SackType = typename SpecificDynamicArrayMessageWrapper::MessageDynamicArraySackType;
    using DynamicPartSackType = typename SpecificDynamicArrayMessageWrapper::DynamicPartSackType;
    SpecificDynamicArrayMessage() : Message(SpecificDynamicArrayMessageWrapper::getMessageName()) {}
    SpecificDynamicArrayMessage(
        alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(SpecificDynamicArrayMessageWrapper::getMessageName(), sender, receiver) {
        saveStaticAndDynamicPartFromBuffer(payloadBufferReference);
    }
    SackType& getStaticPayloadReference() { return m_staticPayload; }
    void addDynamicPart(DynamicPartSackType const& dynamicPart) { m_dynamicArrayPayload.emplace_back(dynamicPart); }
    DynamicPartSackType& getDynamicPayloadReferenceAtAndCreateIfNeeded(unsigned int const position) {
        if (position + 1 > m_dynamicArrayPayload.size()) {
            m_dynamicArrayPayload.resize(position + 1);
        }
        return m_dynamicArrayPayload[position];
    }
    [[nodiscard]] alba::AlbaMemoryBuffer createBuffer() const { return createBufferFromStaticAndDynamicPart(); }

private:
    void saveStaticAndDynamicPartFromBuffer(alba::AlbaMemoryBuffer const& payloadBufferReference) {
        auto const* readingBufferPointer(
            reinterpret_cast<unsigned char const*>(payloadBufferReference.getConstantBufferPointer()));
        m_staticPayload = *reinterpret_cast<SackType const*>(readingBufferPointer);
        auto const* copyPointerStart =
            reinterpret_cast<DynamicPartSackType const*>(readingBufferPointer + calculateOffsetForDynamicPart());
        auto const* const copyPointerEnd =
            reinterpret_cast<DynamicPartSackType const*>(readingBufferPointer + payloadBufferReference.getSize());
        for (DynamicPartSackType const* copyPointer = copyPointerStart; copyPointer < copyPointerEnd; copyPointer++) {
            m_dynamicArrayPayload.emplace_back(*copyPointer);
        }
    }
    [[nodiscard]] alba::AlbaMemoryBuffer createBufferFromStaticAndDynamicPart() const {
        alba::AlbaMemoryBuffer buffer(&m_staticPayload, calculateOffsetForDynamicPart());
        for (DynamicPartSackType const& dynamicArrayContent : m_dynamicArrayPayload) {
            buffer.addData(&dynamicArrayContent, sizeof(DynamicPartSackType));
        }
        return buffer;
    }
    [[nodiscard]] unsigned int calculateOffsetForDynamicPart() const {
        return sizeof(SackType) + (-1 * sizeof(DynamicPartSackType));
    }
    SackType m_staticPayload;
    std::vector<DynamicPartSackType> m_dynamicArrayPayload;
};

}  // namespace DesignDocumentCreator
