#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator {

class Trsw : public Component {
public:
    explicit Trsw(ComponentName const componentName);

private:
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
};

}  // namespace DesignDocumentCreator
