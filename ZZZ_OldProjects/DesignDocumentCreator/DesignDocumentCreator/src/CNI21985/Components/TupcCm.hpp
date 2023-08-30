#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class TupcCm : public Component {
public:
    explicit TupcCm(ComponentName const componentName);

private:
    void handleTupcExeStartup();
    void handleTupcCmStartup();
    void handleCmBearersSetupReqMsg(GenericMessage const& genericMessage);
    void handleCmBearersReleaseReqMsg(GenericMessage const& genericMessage);
    void handleCmBearersModifyReqMsg(GenericMessage const& genericMessage);
    static void performErqEcfMessagingToTransport();
    static void performRelRlcMessagingToTransport();
    static void performModMoaMessagingToTransport();
    void sendCmBearersSetupRespBasedCmBearersSetupReq(GenericMessage const& genericMessage) const;
    void sendCmBearersReleaseRespBasedCmBearersReleaseReq(GenericMessage const& genericMessage) const;
    void sendCmBearersModifyRespBasedCmBearersModifyReq(GenericMessage const& genericMessage) const;
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
};

}  // namespace DesignDocumentCreator
