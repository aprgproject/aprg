#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SOOSA.hpp>
#include <SoosaTestUtilities/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::soosa {

TEST(SoosaTest, DISABLED_InvalidBitmapWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\InvalidBitmap.txt)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_EmptyWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Empty.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_JustABoxWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\JustABox.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_NoAnswersWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\NoAnswers.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_BasicWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Basic.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtInTheSidesWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtInTheSides.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtInTheColumnWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtInTheColumn.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfCanvasSizeWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfCanvasSize.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Scaled3TimesWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Scaled3Times.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Rotated15DegreesWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated15Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Rotated25DegreesWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated25Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Rotated30DegreesWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Rotated30Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Skew15DegreesWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Skew15Degrees.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise20PercentWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise20Percent.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise50PercentWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise50Percent.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Scanned2BitExampleWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Scanned2BitExample.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_ScannedExampleWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\ScannedExample.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM11Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM11.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM12Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM12.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern2(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM13Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM13.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern3(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM14Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM14.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern4(soosa);
}

TEST(SoosaTest, DISABLED_Example1Q20DEM15Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM\1Q20_DEM15.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForDemObasPattern5(soosa);
}

TEST(SoosaTest, DISABLED_ExamplePS2Q21SPECVSWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\CVS_Special Unit_A5 Size\PS2Q21_SPE_CVS.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForSpecialUnits(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForSpecialUnitsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_ExamplePS2Q21SPECVS2Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\CVS_Special Unit_A5 Size\PS2Q21_SPE_CVS(2).bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForSpecialUnits(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForSpecialUnitsPattern2(soosa);
}

TEST(SoosaTest, DISABLED_ExamplePS2Q21SPECVS3Works) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\CVS_Special Unit_A5 Size\PS2Q21_SPE_CVS(3).bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForSpecialUnits(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForSpecialUnitsPattern3(soosa);
}

TEST(SoosaTest, DISABLED_LotsOfDirtAndCannotBeProcessedWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\LotsOfDirtAndCannotBeProcessed.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_RandomWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Witcher.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForEmptyForm(soosa);
}

TEST(SoosaTest, DISABLED_ProcessWorksWithADirectory) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\DEM)");
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForDemObas(inputFile.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();
}

}  // namespace alba::soosa
