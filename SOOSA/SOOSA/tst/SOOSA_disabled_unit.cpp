#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SOOSA.hpp>
#include <SoosaTestUtilities/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::soosa {

TEST(SoosaTest, DISABLED_DistortedWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Distorted.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

TEST(SoosaTest, DISABLED_Noise100PercentWorks) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\SOOSA\FilesForTests\Noise100Percent24Bit.bmp)");
    AlbaLocalPathHandler tempFileToTest(APRG_DIR R"(\SOOSA\FilesForTests\Temp.bmp)");
    inputFile.copyToNewFile(tempFileToTest.getFullPath());
    SoosaConfiguration soosaConfiguration(getSoosaConfiguration());
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(tempFileToTest.getFullPath()));
    SOOSA soosa(soosaConfiguration, inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWardsPattern1(soosa);
}

}  // namespace alba::soosa
