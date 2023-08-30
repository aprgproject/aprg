#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class SampleComponent : public Component {
public:
    explicit SampleComponent(ComponentName const componentName);

private:
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    ComponentName m_componentName;
};

}  // namespace DesignDocumentCreator
