#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class TupcLom : public Component {
public:
    explicit TupcLom(ComponentName const componentName);

private:
    void handleStartup();
    void handleHwConfigurationMessage(GenericMessage const& genericMessage);
    void saveAddresses(GenericMessage const& genericMessage);
    void handleTcomDeploymentMessage(GenericMessage const& genericMessage);
    void sendTupcTbmConfigurationMsg(TAaSysComSicad const) const;
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
    TAaSysComSicad m_oamAddress{};
    TAaSysComSicad m_tupcCmAddress{};
    TAaSysComSicad m_tupcIlmAddress{};
};

}  // namespace DesignDocumentCreator
