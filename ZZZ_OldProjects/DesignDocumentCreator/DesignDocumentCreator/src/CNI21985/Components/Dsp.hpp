#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator {

class Dsp : public Component {
public:
    explicit Dsp(ComponentName const componentName);
    void handleTransportSetupReq(GenericMessage const&) const;
    void handleTransportReleaseReq(GenericMessage const&) const;
    void handleTransportTransferReq(GenericMessage const&) const;
    void sendTransportSetupResp() const;
    void sendTransportReleaseResp() const;
    void sendTransportTransferResp() const;

private:
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
};

}  // namespace DesignDocumentCreator
