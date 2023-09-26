#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SackReader.hpp>

#include <gtest/gtest.h>

#define SAVED_DATABASE_FILE APRG_DIR R"(\ZZZ_OldProjects\SackReader\TempFiles\SavedDatabase.txt)"

using namespace std;

namespace alba {

TEST(SackReaderTest, DISABLED_CheckAllFiles) {
    SackReader sackReader(
        R"(C:\APRG\SackReader\SackReader\SampleFiles)",
        R"(C:\APRG\SackReader\SackReader\SampleFiles\SackReaderExecution.txt)");
    sackReader.gatherAllFiles();
    EXPECT_EQ(R"(C:\APRG\SackReader\SackReader\SampleFiles\oam_tcom.h)", sackReader.getFileFullPath("oam_tcom.h"));
}

TEST(RealTest, DISABLED_UpdateTrunkFiles) {
    SackReader sackReader(
        R"(D:\Branches\trunk\wbts_integration\I_Interface)",
        R"(D:\Specifications\OAM-TCOM-IFS\SackReaderExecution.txt)");
    AlbaLocalPathHandler databasePathHandler(SAVED_DATABASE_FILE);

    // sackReader.loadDatabaseFromFile(databasePathHandler.getPath());

    sackReader.gatherAllFiles();
    sackReader.readFilesNeededForIfs();
    sackReader.loadMessagesToGenerate(R"(D:\Specifications\OAM-TCOM-IFS\MessagesToGenerate.txt)");
    sackReader.performHacks();
    sackReader.readAndMarkFilesNecessaryForIfs();
    sackReader.loadDescriptionToAdd(R"(D:\Specifications\OAM-TCOM-IFS\DescriptionsToAdd.txt)");

    sackReader.generateLyxDocument(
        R"(D:\Specifications\OAM-TCOM-IFS\OAM_CPLANE_IFS_template.lyx)",
        R"(D:\Specifications\OAM-TCOM-IFS\OAM_CPLANE_IFS_TEST.lyx)");

    sackReader.saveDatabaseToFile(databasePathHandler.getPath().string());
}

}  // namespace alba
