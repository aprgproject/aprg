#pragma once

#include <Common/Events/Events.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <deque>
#include <string>

namespace DesignDocumentCreator
{

class Component
{
public:
    Component();
    Component(ComponentName const componentName);
    Component(Component const &) = delete;
    Component& operator=(Component const &) = delete;
    void pushBackEvent(Event const& event);
    void handleOneEvent();
    void handleAllEvents();
    bool isEventQueueEmpty() const;
    GenericMessage peekMessageAtStartOfTheEventQueue() const;
    std::string getComponentNameString() const;
    std::string getQueueAsString() const;

protected:
    virtual void handleEvent(Event const& event);
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
    std::deque<Event> m_eventQueue;
};

}
