#pragma once

#include <Common/Events/OtherEvent.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <string>

namespace DesignDocumentCreator {

enum class EventType { MessageEvent, TimerEvent, OtherEvent };

class Event {
public:
    explicit Event(GenericMessage const& message);
    explicit Event(Timer const& timer);
    explicit Event(OtherEvent const& otherEvent);

    [[nodiscard]] EventType getType() const;
    [[nodiscard]] Timer getTimer() const;
    [[nodiscard]] std::string getString() const;
    [[nodiscard]] GenericMessage getMessage() const;
    [[nodiscard]] OtherEvent getOtherEvent() const;

private:
    EventType m_eventType;
    Timer m_timer;
    GenericMessage m_message;
    OtherEvent m_otherEvent;
};

}  // namespace DesignDocumentCreator
