#pragma once

#include <Common/Events/Events.hpp>
#include <Common/Events/OtherEvent.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <deque>
#include <string>

namespace DesignDocumentCreator {

class Component {
public:
    explicit Component(ComponentName const componentName);
    virtual ~Component() = default;  // virtual destructor because of virtual functions (vtable exists)
    Component(Component const& component) = default;
    Component(Component&& component) = default;
    Component& operator=(Component const& component) = default;
    Component& operator=(Component&& component) = default;
    void pushBackEvent(Event const& event);
    void handleOneEvent();
    void handleAllEvents();
    void send(ComponentName const receiver, GenericMessage const& message) const;
    [[nodiscard]] bool isEventQueueEmpty() const;
    [[nodiscard]] GenericMessage peekMessageAtStartOfTheEventQueue() const;
    [[nodiscard]] ComponentName getComponentName() const;
    [[nodiscard]] std::string getComponentNameInString() const;
    [[nodiscard]] std::string getQueueAsString() const;
    static void log(std::string const& line);
    static void logNoteOnPreviousMessage(std::string const& note);
    void logNoteOnComponent(std::string const& note) const;
    static void logNoteOnComponents(ComponentNames const& componentNames, std::string const& note);

protected:
    virtual void handleEvent(Event const& event);
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);

    ComponentName m_componentName;
    std::string m_componentNameInString;
    std::deque<Event> m_eventQueue;
};

}  // namespace DesignDocumentCreator
