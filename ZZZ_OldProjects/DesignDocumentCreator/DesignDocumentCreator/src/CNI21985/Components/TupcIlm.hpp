#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class TupcIlm : public Component {
public:
    explicit TupcIlm(ComponentName const componentName);

private:
    void handleStartup();
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
};

}  // namespace DesignDocumentCreator
