#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SOOSA.hpp>
#include <SoosaTestUtilities/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::soosa {

TEST(SoosaTest, DISABLED_InvalidBitmapWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\InvalidBitmap.txt)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_EmptyWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Empty.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_JustABoxWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\JustABox.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_NoAnswersWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\NoAnswers.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_BasicWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Basic.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtInTheSidesWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtInTheSides.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtInTheColumnWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtInTheColumn.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfCanvasSizeWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfCanvasSize.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Scaled3TimesWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Scaled3Times.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Rotated15DegreesWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated15Degrees.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Rotated25DegreesWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated25Degrees.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Rotated30DegreesWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated30Degrees.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Skew15DegreesWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Skew15Degrees.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise20PercentWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise20Percent.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise50PercentWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise50Percent.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Scanned2BitExampleWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Scanned2BitExample.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_ScannedExampleWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\ScannedExample.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM11Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM11.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM12Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM12.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern2(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM13Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM13.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern3(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM14Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM14.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern4(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM15Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM15.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern5(soosa);
}

TEST(SoosaTest, DISABLED_ExamplePS2Q21SPECVSWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\SOOSA\FilesForTests\CVS_Special Unit_A5 Size\PS2Q21_SPE_CVS.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForSpecialUnits(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForSpecialUnitsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_ExamplePS2Q21SPECVS2Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\SOOSA\FilesForTests\CVS_Special Unit_A5 Size\PS2Q21_SPE_CVS(2).bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForSpecialUnits(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForSpecialUnitsPattern2(soosa);
}

TEST(SoosaTest, DISABLED_ExamplePS2Q21SPECVS3Works) {
    AlbaLocalPathHandler const inputFile(APRG_DIR
                                         R"(\SOOSA\FilesForTests\CVS_Special Unit_A5 Size\PS2Q21_SPE_CVS(3).bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForSpecialUnits(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForSpecialUnitsPattern3(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtAndCannotBeProcessedWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtAndCannotBeProcessed.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_RandomWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Witcher.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_ProcessWorksWithADirectory) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM)");
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(getInputConfigurationForDemObas(inputFile.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();
}

}  // namespace alba::soosa
