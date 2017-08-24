#include <gtest/gtest.h>

#include <Common/Components/ComponentName.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Components/Oam.hpp>
#include <Components/TupcCm.hpp>
#include <Components/TupcIlm.hpp>
#include <Components/TupcLom.hpp>
#include <Components/TupcTbm.hpp>
#include <ModuleTest.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

TEST_F(ModuleTest, Startup)
{
    UmlLogger& umlLogger(getUmlLogger());
    Oam& oam(*dynamic_cast<Oam*>(getComponentAndActivateAsParticipant(ComponentName::Oam)));
    TupcIlm& tupcIlm(*dynamic_cast<TupcIlm*>(getComponentAndActivateAsParticipant(ComponentName::TupcIlm)));
    TupcLom& tupcLom(*dynamic_cast<TupcLom*>(getComponentAndActivateAsParticipant(ComponentName::TupcLom)));
    TupcCm& tupcCm(*dynamic_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm)));
    TupcTbm& tupcTbm(*dynamic_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm)));
    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::TupcIlm, ComponentName::TupcTbm}, "TUPCexe starts");
    tupcIlm.pushBackEvent(Event(OtherEvent(OtherEventType::ProcessStartup)));
    tupcIlm.handleOneEvent();

    sendMessage(ComponentName::Oam, ComponentName::TupcLom, createHwConfigurationMessageForRel3BasedFromLogs());
    tupcLom.handleOneEvent();
}
