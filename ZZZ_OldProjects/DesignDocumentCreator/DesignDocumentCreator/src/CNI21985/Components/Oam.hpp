#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class Oam : public Component {
public:
    explicit Oam(ComponentName const componentName);

private:
    void handleHwConfigurationMessageResponse(GenericMessage const& genericMessage) const;
    void handleLinkStatesResponse(GenericMessage const& genericMessage) const;

    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
};

}  // namespace DesignDocumentCreator
