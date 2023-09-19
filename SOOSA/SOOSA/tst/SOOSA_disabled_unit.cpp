#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SOOSA.hpp>
#include <SoosaTestUtilities/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::soosa {

TEST(SoosaTest, DISABLED_DistortedWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Distorted.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise100PercentWorks) {
    AlbaLocalPathHandler const inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise100Percent24Bit.bmp)");
    AlbaLocalPathHandler const tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyFileToAndIsSuccessful(tempFileToTest.getPath());
    SoosaConfiguration const soosaConfiguration(getSoosaConfiguration());
    InputConfiguration const inputConfiguration(
        getInputConfigurationForCharityPayWards(tempFileToTest.getPath().string()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

}  // namespace alba::soosa
