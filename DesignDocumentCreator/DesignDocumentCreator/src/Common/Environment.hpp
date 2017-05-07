#pragma once

#include <Common/Components/Components.hpp>
#include <Common/Uml/UmlLogger.hpp>

namespace DesignDocumentCreator
{

class Environment
{
public:
    Environment();
    Environment(Environment const&) = delete;
    void operator=(Environment const&) = delete;
    void execute();
    Components& getComponentReference();
    UmlLogger& getUmlLogger();
    void send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message);

private:
    Components m_components;
    UmlLogger m_umlLogger;
};

}
