#include <SackFileReader/SackFileReader.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SackFileReaderTest, ReadFile_Constants)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\DOpenIUBCommonDefs.h)");

    ConstantDetails details(database.getConstantDetails("MAX_NR_OF_CODES"));
    EXPECT_EQ("3GPP 10 Nokia 2.", details.description);
    EXPECT_EQ("2", details.value);

    details = (database.getConstantDetails("MAX_NUM_OF_DELAYED_LINKS_INFO"));
    EXPECT_EQ("Max number of Delayed Links Information", details.description);
    EXPECT_EQ("2", details.value);
}

TEST(SackFileReaderTest, ReadFile_MessageOamAtmSigFile)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\MessageId_OamAtm.sig)");

    EXPECT_EQ("SAtmHwConfigurationMsg", database.getMessageStructure("OAM_ATM_HW_CONFIGURATION_MSG"));
    EXPECT_EQ("STupcAalmanInternalConfigurationResp", database.getMessageStructure("OAM_ATM_TUPC_AALMAN_INTERNAL_CONFIGURATION_RESP_MSG"));
}

TEST(SackFileReaderTest, ReadFile_MessageOamTcomFile)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\MessageId_OamTcom.sig)");

    EXPECT_EQ("SHwConfigurationMsg", database.getMessageStructure("TC_HW_CONFIGURATION_MSG"));
    EXPECT_EQ("SetCellParamResp", database.getMessageStructure("TC_SET_CELL_PARAM_RESP_MSG"));
}

TEST(SackFileReaderTest, ReadFile_OamTupcStructures)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\Oam_Atm.h)");

    ParameterDetails details(database.getParameterDetails("SAtmHwConfigurationMsg", "typeOfConfiguration"));
    EXPECT_EQ("typeOfConfiguration", details.name);
    EXPECT_EQ("EControlUnitType", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = database.getParameterDetails("SAtmOamCpuStateChangeMsg", "cpuAddress");
    EXPECT_EQ("cpuAddress", details.name);
    EXPECT_EQ("SMessageAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = database.getParameterDetails("SAtmHwConfigurationMsg", "dynamicData");
    EXPECT_EQ("dynamicData", details.name);
    EXPECT_EQ("TDynamicData", details.type);
    EXPECT_TRUE(details.isAnArray);
    EXPECT_EQ("1", details.arraySize);
    EXPECT_EQ("", details.description);
}

TEST(SackFileReaderTest, ReadFile_OamTcomStructures)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\oam_tcom.h)");

    ParameterDetails details(database.getParameterDetails("SHwConfigurationMsg", "btsomTelecomServiceAddr"));
    EXPECT_EQ("btsomTelecomServiceAddr", details.name);
    EXPECT_EQ("SMessageAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = database.getParameterDetails("SHwConfigurationMsg", "btsSwVersion");
    EXPECT_EQ("btsSwVersion", details.name);
    EXPECT_EQ("TDynamicData", details.type);
    EXPECT_TRUE(details.isAnArray);
    EXPECT_EQ("1", details.arraySize);
    EXPECT_EQ("", details.description);

    details = database.getParameterDetails("SCellInformationInd", "dssDspAddress");
    EXPECT_EQ("dssDspAddress", details.name);
    EXPECT_EQ("TAaSysComSicad", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);
}

TEST(SackFileReaderTest, ReadFile_SWamUnit)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\SWamUnit.h)");

    ParameterDetails details(database.getParameterDetails("SWamUnit", "logUnitAddr"));
    EXPECT_EQ("logUnitAddr", details.name);
    EXPECT_EQ("TBoard", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("logical unit address (e.g. WAM10)", details.description);

    details = database.getParameterDetails("SWamUnit", "numOfFspUnits");
    EXPECT_EQ("numOfFspUnits", details.name);
    EXPECT_EQ("u8", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("Number of FSP units in System Module. Valid only for EControlUnitType_Fcm2 from Extension System Module in TC_HW_CONFIGURATION_CHANGE_MSG.", details.description);
}

TEST(SackFileReaderTest, EHspaMapping)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\EHspaMapping.h)");

    EnumParameterDetails details(database.getEnumParameterDetails("EHspaMapping", "EHspaMapping_EmptyValue"));
    EXPECT_EQ("EHspaMapping_EmptyValue", details.name);
    EXPECT_EQ("0", details.value);
    EXPECT_EQ("mapping not used", details.description);

    details = database.getEnumParameterDetails("EHspaMapping", "EHspaMapping_SubrackUltra");
    EXPECT_EQ("EHspaMapping_SubrackUltra", details.name);
    EXPECT_EQ("4", details.value);
    EXPECT_EQ("in case of UltraSite", details.description);
}

TEST(SackFileReaderTest, EControlUnitType)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\EControlUnitType.h)");

    EnumParameterDetails details(database.getEnumParameterDetails("EControlUnitType", "EControlUnitType_Fcm"));
    EXPECT_EQ("EControlUnitType_Fcm", details.name);
    EXPECT_EQ("1", details.value);
    EXPECT_EQ("FCM type if Flexi rel 1 platform is used", details.description);

    details = database.getEnumParameterDetails("EControlUnitType", "EControlUnitType_Wspf");
    EXPECT_EQ("EControlUnitType_Wspf", details.name);
    EXPECT_EQ("5", details.value);
    EXPECT_EQ("if EUBB WSPF is control unit", details.description);
}

TEST(SackFileReaderTest, CommentInStructure)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\Oam_Tcom_TestModelService.h)");

    ParameterDetails details(database.getParameterDetails("STestModelSetupReqMsg", "numberOfHsPdsch"));
    EXPECT_EQ("numberOfHsPdsch", details.name);
    EXPECT_EQ("TNumberOfItems", details.type);
    EXPECT_FALSE(details.isAnArray);
    //EXPECT_EQ("indicates how many HS-PDSCH is setup for TM5", details.description); //TooHard

    details = database.getParameterDetails("STestModelSetupReqMsg", "testPattern");
    EXPECT_EQ("testPattern", details.name);
    EXPECT_EQ("ECdmaTestDataPattern", details.type);
    EXPECT_FALSE(details.isAnArray);
    //EXPECT_EQ("indicates what kind of testdata is generated to test channels", details.description); //TooHard
}
