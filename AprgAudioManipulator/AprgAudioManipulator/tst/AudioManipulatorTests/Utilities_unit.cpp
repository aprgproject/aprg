#include <AudioManipulator/AudioManipulator.hpp>
#include <AudioManipulator/NewSamplesBuilder.hpp>
#include <AudioManipulator/Utilities.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

#define SAMPLE_AUDIO_FILES_DIRECTORY APRG_DIR R"(\AprgAudioManipulator\FilesForTests\SampleAudioFiles\)"

namespace alba::AprgAudio {

TEST(UtilitiesTest, DISABLED_RetrieveDeltasWorks) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");
    AudioManipulator const audioManipulator(audioFilePathHandler.getPath());

    AudioInDouble const& audio(audioManipulator.getAudio());
    Samples deltaSamplesInChannel0;
    auto const& samplesInChannel0(audio.getSamplesAtChannel(0));
    retrieveDeltas(deltaSamplesInChannel0, samplesInChannel0, static_cast<int>(samplesInChannel0.size()));
}

TEST(UtilitiesTest, DISABLED_SearchForBestSampleIndexesWorksWithReplacingSamples) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "John Mayer-Neon.wav");
    AlbaLocalPathHandler const audioToSearchFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");  // AChannel_AOpeningSong_001
    AudioManipulator audioToReplicateManipulator(audioToReplicateFilePathHandler.getPath());
    AudioManipulator const audioToSearchManipulator(audioToSearchFilePathHandler.getPath());

    AudioInDouble const& audioToReplicate(audioToReplicateManipulator.getAudio());
    AudioInDouble const& audioToSearch(audioToSearchManipulator.getAudio());

    SearchResultsDetails searchResults;
    Samples const& samplesToReplicate(audioToReplicate.getSamplesAtChannel(0));
    Samples const& samplesToSearch(audioToSearch.getSamplesAtChannel(0));
    searchForBestSampleIndexes(searchResults, 24000, 48000, 100, samplesToReplicate, samplesToSearch);

    AudioInDouble& audioToChange(audioToReplicateManipulator.getAudioReference());
    Samples& samplesToChange(audioToChange.getSamplesReferenceAtChannel(0));

    NewSamplesBuilder newSamplesBuilder(samplesToChange);
    newSamplesBuilder.putSamplesBasedOnSearchResultAndSamples(samplesToChange, searchResults, samplesToSearch, true);

    audioToReplicateManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(UtilitiesTest, DISABLED_SearchAndTryToReplicateSamplesWorks) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "John Mayer-Neon.wav");
    AlbaLocalPathHandler const audioToSearchFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");
    AlbaLocalPathHandler const audioToChangeFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "John Mayer-Neon.wav");
    AudioManipulator const audioToReplicateManipulator(audioToReplicateFilePathHandler.getPath());
    AudioManipulator const audioToSearchManipulator(audioToSearchFilePathHandler.getPath());
    AudioManipulator audioToChangeManipulator(audioToChangeFilePathHandler.getPath());
    AudioInDouble const& audioToReplicate(audioToReplicateManipulator.getAudio());
    AudioInDouble const& audioToSearch(audioToSearchManipulator.getAudio());
    AudioInDouble& audioToChange(audioToChangeManipulator.getAudioReference());

    int const numberOfChannels =
        max(max(audioToReplicate.getNumberOfChannels(), audioToSearch.getNumberOfChannels()),
            audioToChange.getNumberOfChannels());
    for (int i = 0; i < numberOfChannels; ++i) {
        searchAndTryToReplicateSamples(
            audioToChange, audioToReplicate, audioToSearch, clampHigherBound(i, audioToChange.getNumberOfChannels()),
            clampHigherBound(i, audioToReplicate.getNumberOfChannels()),
            clampHigherBound(i, audioToSearch.getNumberOfChannels()), true);
    }
    audioToChangeManipulator.saveAudioIntoFileInTheSameDirectory("output.wav");
}

TEST(UtilitiesTest, DISABLED_SearchAndTryToReplicateWorks) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "John Mayer-Neon.wav");
    AlbaLocalPathHandler const audioToSearchFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");
    AlbaLocalPathHandler const audioToChangeFilePathHandler(audioDirectoryPathHandler.getDirectory() / "output.wav");
    searchAndTryToReplicate(
        audioToChangeFilePathHandler.getPath(), audioToReplicateFilePathHandler.getPath(),
        audioToSearchFilePathHandler.getPath(), true);
}

TEST(UtilitiesTest, DISABLED_SearchAndTryToReplicateTwoFilesWorks) {
    AlbaLocalPathHandler const audioDirectoryPathHandler(SAMPLE_AUDIO_FILES_DIRECTORY);
    AlbaLocalPathHandler const audioToReplicateFilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "John Mayer-Neon.wav");
    AlbaLocalPathHandler const audioToSearch1FilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "AChannel_AOpeningSong_001.wav");
    AlbaLocalPathHandler const audioToSearch2FilePathHandler(
        audioDirectoryPathHandler.getDirectory() / "FullMetalAlchemistBrotherhood_AOpeningSong_003.wav");
    AlbaLocalPathHandler const audioToChangeFilePathHandler(audioDirectoryPathHandler.getDirectory() / "output.wav");

    searchAndTryToReplicate(
        audioToChangeFilePathHandler.getPath(), audioToReplicateFilePathHandler.getPath(),
        audioToSearch1FilePathHandler.getPath(), true);
    searchAndTryToReplicate(
        audioToChangeFilePathHandler.getPath(), audioToReplicateFilePathHandler.getPath(),
        audioToSearch2FilePathHandler.getPath(), false);
}

}  // namespace alba::AprgAudio
