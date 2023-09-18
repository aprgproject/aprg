#include <AudioManipulator/AudioManipulator.hpp>

#include <gtest/gtest.h>

using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\FilesForTests\SampleAudioFiles\)"

namespace alba::AprgAudio {

TEST(AudioManipulatorTest, DISABLED_AddSamplesWithValueWorks) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");
    AudioManipulator audioManipulator(audioFilePathHandler.getPath());

    audioManipulator.addSamplesWithValue(100);

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(AudioManipulatorTest, DISABLED_MultiplySamplesWithValueWorks) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");
    AudioManipulator audioManipulator(audioFilePathHandler.getPath());

    audioManipulator.multiplySamplesWithValue(0.30);

    audioManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

}  // namespace alba::AprgAudio
