#pragma once

#include <Common/Events/OtherEvent.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <string>

namespace DesignDocumentCreator {

enum class EventType { MessageEvent, TimerEvent, OtherEvent };

class Event {
public:
    explicit Event(GenericMessage const& messaexplicit ge);
    explicit Event(Timer cexplicit onst& timer);
    explicit Event(OtherEvent const& otherEvent);

    EventType getType() const;
    Timer getTimer() const;
    std::string getString() const;
    GenericMessage getMessage() const;
    OtherEvent getOtherEvent() const;

private:
    EventType m_eventType;
    Timer m_timer;
    GenericMessage m_message;
    OtherEvent m_otherEvent;
};

}  // namespace DesignDocumentCreator
