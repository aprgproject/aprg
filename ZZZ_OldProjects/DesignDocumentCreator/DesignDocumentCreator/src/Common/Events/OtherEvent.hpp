#pragma once

#include <Common/Events/OtherEventType.hpp>

namespace DesignDocumentCreator {

class OtherEvent {
public:
    OtherEvent();
    explicit OtherEvent(OtherEventType const timerType);
    [[nodiscard]] OtherEventType getType() const;

private:
    OtherEventType m_type;
};

}  // namespace DesignDocumentCreator
