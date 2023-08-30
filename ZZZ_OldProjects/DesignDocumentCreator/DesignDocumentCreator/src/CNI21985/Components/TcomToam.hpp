#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator {

class TcomToam : public Component {
    class HwConfiguration {
    public:
        // this is fake
        void saveConfiguration(SHwConfigurationMsg const& hwConfigurationMsg);
        static STCWamAddressIndNew generateWamAddressInd();
    };

public:
    explicit TcomToam(ComponentName const componentName);

private:
    void handleHwConfigurationMessage(GenericMessage const& genericMessage);
    void handleHwConfigurationChangeMessage(GenericMessage const& genericMessage) const;
    void handleLinkStatesMessage(GenericMessage const& genericMessage) const;
    void sendHwConfigurationResponseAck() const;
    void sendsLinkStatesResponse() const;
    void sendsTcomDeploymentInd() const;
    void saveConfiguration(SHwConfigurationMsg const& hwConfigurationMsg);

    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    HwConfiguration m_configuration;
};

}  // namespace DesignDocumentCreator
