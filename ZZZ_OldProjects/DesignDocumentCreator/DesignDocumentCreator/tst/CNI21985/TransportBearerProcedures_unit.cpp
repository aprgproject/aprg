#include <Common/Utils/StringHelpers.hpp>
#include <Components/Dsp.hpp>
#include <Components/TcomCchhRlh.hpp>
#include <Components/Trsw.hpp>
#include <Components/TupcCm.hpp>
#include <Components/TupcTbm.hpp>
#include <MessageFactory.hpp>
#include <MessageVerifier.hpp>
#include <ModuleTest.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace DesignDocumentCreator;
using namespace MessageFactory;
using namespace MessageVerifier;
using namespace StringHelpers;

// NOLINTBEGIN(cppcoreguidelines-pro-type-static-cast-downcast)
TEST_F(ModuleTest, OneTransportBearerRegister) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Dsp& dsp(*static_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "DSP")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerRegisterForCell());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerUnregister) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    Dsp& dsp(*static_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "DSP")));

    sendMessage(ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerUnregisterForCell());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationPrepareForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));
    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationPrepareForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationCommitForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));

    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationCommitForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerModificationCancelForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));

    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerModificationCancelForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationPrepareForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    Dsp& dsp(*static_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "New DSP")));

    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationPrepareForUser());
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationCommitForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm, "TUPC/CM")));

    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationCommitForUser());
    tupcTbm.handleOneEvent();
    tupcCm.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationCleanupForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    Dsp& dsp(*static_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "Old DSP")));

    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationCleanupForUser());
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerReallocationCancelForUser) {
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));

    sendMessage(
        ComponentName::TcomCchhRlh, ComponentName::TupcTbm, createOneTransportBearerReallocationCancelForUser());
    tupcTbm.handleOneEvent();
}

TEST_F(ModuleTest, OneTransportBearerUnexpectedRelFromTransport) {
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    TupcTbm& tupcTbm(*static_cast<TupcTbm*>(getComponentAndActivateAsParticipant(ComponentName::TupcTbm, "TUPC/TBM")));
    Dsp& dsp(*static_cast<Dsp*>(getComponentAndActivateAsParticipant(ComponentName::Dsp, "DSP")));

    umlLogger.logNoteOnComponents(
        ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TupcCm receives REL from TRSW/Transport");

    sendMessage(ComponentName::TupcCm, ComponentName::TupcTbm, createOneTransportBearerCmUpdateReleaseFromTransport());
    umlLogger.logNoteOnPreviousMessage(
        "TupcCm sends TUPC_CM_BEARERS_UPDATE_IND_MSG with **ECmBearersUpdateTransactionType_ReleasedFromTransport**");
    tupcTbm.handleOneEvent();
    dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}
// NOLINTEND(cppcoreguidelines-pro-type-static-cast-downcast)

/*TEST_F(ModuleTest, TransportChannelReset)
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    TcomToam& tcomToam(*static_cast<TcomToam*>(getComponentAndActivateAsParticipant(ComponentName::TcomToam,
"TCOM/TOAM"))); TupcCm& tupcCm(*static_cast<TupcCm*>(getComponentAndActivateAsParticipant(ComponentName::TupcCm,
"TUPC/CM")));

    umlLogger.logNoteOnComponents(ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TupcCm receives REL from
TRSW/Transport");

    sendMessage(ComponentName::TupcCm, ComponentName::TupcTbm, createOneTransportBearerCmUpdateReleaseFromTransport());
    umlLogger.logNoteOnPreviousMessage("TupcCm sends TUPC_CM_BEARERS_UPDATE_IND_MSG with
**ECmBearersUpdateTransactionType_ReleasedFromTransport**"); tupcTbm.handleOneEvent(); dsp.handleOneEvent();
    tupcTbm.handleOneEvent();
}*/
