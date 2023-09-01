#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
namespace DesignDocumentCreator {

template <MessageName messageName>
class SpecificStaticMessage : public Message {
public:
    using SpecificStaticMessageWrapper = MessageWrapper<messageName>;
    using SackType = typename SpecificStaticMessageWrapper::MessageStaticSackType;
    SpecificStaticMessage() : Message(SpecificStaticMessageWrapper::getMessageName()) {}
    SpecificStaticMessage(
        alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(SpecificStaticMessageWrapper::getMessageName(), sender, receiver) {
        assert(sizeof(SackType) == payloadBufferReference.getSize());
        m_payload = *reinterpret_cast<SackType const*>(payloadBufferReference.getConstantBufferPointer());
    }
    SackType& getStaticPayloadReference() { return m_payload; }
    [[nodiscard]] alba::AlbaMemoryBuffer createBuffer() const { return createBufferFromStaticPayload(); }

private:
    [[nodiscard]] alba::AlbaMemoryBuffer createBufferFromStaticPayload() const {
        return alba::AlbaMemoryBuffer(&m_payload, sizeof(m_payload));
    }
    SackType m_payload;
};

}  // namespace DesignDocumentCreator

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)