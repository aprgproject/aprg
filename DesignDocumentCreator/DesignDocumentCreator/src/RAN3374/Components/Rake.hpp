#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Components/Component.hpp>

namespace DesignDocumentCreator
{

class Rake : public Component
{
public:
    Rake();
    Rake(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}
