#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
namespace DesignDocumentCreator {

template <MessageName messageName, typename DynamicPartSackType>
class SpecificDynamicPolymorphicMessage : public Message {
public:
    using SpecificDynamicPolymorphicMessageWrapper = MessageWrapper<messageName>;
    using SackType = typename SpecificDynamicPolymorphicMessageWrapper::MessageDynamicPolymorphicSackType;
    using DynamicPlaceHolderSackType = typename SpecificDynamicPolymorphicMessageWrapper::DynamicPlaceHolderSackType;
    SpecificDynamicPolymorphicMessage() : Message(SpecificDynamicPolymorphicMessageWrapper::getMessageName()) {}
    SpecificDynamicPolymorphicMessage(
        alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(SpecificDynamicPolymorphicMessageWrapper::getMessageName(), sender, receiver) {
        saveStaticAndDynamicPartFromBuffer(payloadBufferReference);
    }
    SackType& getStaticPayloadReference() { return m_staticPayload; }
    DynamicPartSackType& getDynamicPayloadReference() { return m_dynamicPayload; }
    [[nodiscard]] alba::AlbaMemoryBuffer createBuffer() const { return createBufferFromStaticAndDynamicPart(); }

private:
    void saveStaticAndDynamicPartFromBuffer(alba::AlbaMemoryBuffer const& payloadBufferReference) {
        auto const* readingBufferPointer(
            reinterpret_cast<unsigned char const*>(payloadBufferReference.getConstantBufferPointer()));
        m_staticPayload = *reinterpret_cast<SackType const*>(readingBufferPointer);
        m_dynamicPayload =
            *reinterpret_cast<DynamicPartSackType const*>(readingBufferPointer + calculateOffsetForDynamicPart());
    }
    [[nodiscard]] alba::AlbaMemoryBuffer createBufferFromStaticAndDynamicPart() const {
        alba::AlbaMemoryBuffer buffer(&m_staticPayload, calculateOffsetForDynamicPart());
        buffer.addData(&m_dynamicPayload, sizeof(DynamicPartSackType));
        return buffer;
    }
    [[nodiscard]] unsigned int calculateOffsetForDynamicPart() const {
        return sizeof(SackType) - sizeof(DynamicPlaceHolderSackType);
    }
    SackType m_staticPayload;
    DynamicPartSackType m_dynamicPayload;
};

}  // namespace DesignDocumentCreator

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)