#include <SackReader.hpp>

#include <gtest/gtest.h>

#include <Debug/AlbaDebug.hpp>

using namespace alba;
using namespace std;


TEST(SackReaderTest, CheckAllFiles)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.gatherAllFiles();
    EXPECT_EQ(R"(C:\APRG\SackReader\SackReader\SampleFiles\oam_tcom.h)", sackReader.getFileFullPath("oam_tcom.h"));
}

TEST(RealTest, UpdateTrunkFiles)
{
    SackReader sackReader(R"(D:\Branches\trunk\wbts_integration\I_Interface)");

    //sackReader.loadDatabaseFromFile(R"(C:\APRG\SackReader\SackReader\TempFiles\Database_07_11_2018.txt)");

    sackReader.gatherAllFiles();
    sackReader.readFilesNeededForIfs();    sackReader.loadMessagesToGenerate(R"(D:\Specifications\OAM-TCOM-IFS\MessagesToGenerate.txt)");
    sackReader.loadDescriptionToAdd(R"(D:\Specifications\OAM-TCOM-IFS\DescriptionsToAdd.txt)");
    sackReader.performHacks();
    sackReader.readAndMarkFilesNecessaryForIfs();

    sackReader.generateLyxDocument(R"(D:\Specifications\OAM-TCOM-IFS\OAM_CPLANE_IFS.lyx)", R"(D:\Specifications\OAM-TCOM-IFS\OAM_CPLANE_IFS_TEST.lyx)");

    sackReader.saveDatabaseToFile(R"(C:\APRG\SackReader\SackReader\TempFiles\Database_07_11_2018.txt)");
}
