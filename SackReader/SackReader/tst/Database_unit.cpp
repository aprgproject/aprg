#include <SackFileReader/SackFileReader.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;


TEST(DatabaseTest, SaveAndLoadFile_EHspaMapping)
{
    Database database;
    EXPECT_TRUE(database.fileToPathMap.empty());
    EXPECT_TRUE(database.constantNameToConstantDetailsMap.empty());
    EXPECT_TRUE(database.messageNameToStructureNameMap.empty());
    EXPECT_TRUE(database.structureNameToStructureDetailsMap.empty());
    EXPECT_TRUE(database.enumNameToEnumDetailsMap.empty());
    EXPECT_TRUE(database.messagesToGenerate.empty());

}

/*
TEST(DatabaseTest, SaveAndLoadFile_EHspaMapping)
{
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\EHspaMapping.h)");

    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFileUsingFileNameOnly("EHspaMapping.h");
    sackReader.saveDatabaseToFile(R"(C:\APRG\SackReader\SackReader\TempFiles\ReadFile_EHspaMapping.txt)");
    SackReader sackReader2(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader2.loadDatabaseFromFile(R"(C:\APRG\SackReader\SackReader\TempFiles\ReadFile_EHspaMapping.txt)");

    EnumParameterDetails details(sackReader2.getEnumParameterDetails("EHspaMapping", "EHspaMapping_EmptyValue"));
    EXPECT_EQ("EHspaMapping_EmptyValue", details.name);
    EXPECT_EQ("0", details.value);
    EXPECT_EQ("mapping not used", details.description);

    details = sackReader2.getEnumParameterDetails("EHspaMapping", "EHspaMapping_SubrackUltra");
    EXPECT_EQ("EHspaMapping_SubrackUltra", details.name);
    EXPECT_EQ("4", details.value);
    EXPECT_EQ("in case of UltraSite", details.description);
}
*/

