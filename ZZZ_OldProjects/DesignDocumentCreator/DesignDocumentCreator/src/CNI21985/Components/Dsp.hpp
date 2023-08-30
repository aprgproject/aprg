#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator {

class Dsp : public Component {
public:
    explicit Dsp(ComponentName const componentName);
    void handleTransportSetupReq(GenericMessage const&);
    void handleTransportReleaseReq(GenericMessage const&);
    void handleTransportTransferReq(GenericMessage const&);
    void sendTransportSetupResp() const;
    void sendTransportReleaseResp() const;
    void sendTransportTransferResp() const;

private:
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
};

}  // namespace DesignDocumentCreator
