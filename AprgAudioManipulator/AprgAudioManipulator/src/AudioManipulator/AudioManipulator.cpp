#include "AudioManipulator.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba::AprgAudio {

AudioManipulator::AudioManipulator(path const& audioFilePath) : m_filePathHandler(audioFilePath) {
    m_audio.load(m_filePathHandler.getPath());
}

AudioInDouble const& AudioManipulator::getAudio() const { return m_audio; }

void AudioManipulator::addSamplesWithValue(double const value) {
    for (int i = 0; i < m_audio.getNumberOfChannels(); ++i) {
        addSamplesAtChannelWithValue(i, value);
    }
}

void AudioManipulator::addSamplesAtChannelWithValue(int const channelIndex, double const value) {
    Samples& samplesAtChannel(m_audio.getSamplesReferenceAtChannel(channelIndex));
    for_each(samplesAtChannel.begin(), samplesAtChannel.end(), [value](double& sampleAtChannel) {
        sampleAtChannel += value;
    });
}

void AudioManipulator::multiplySamplesWithValue(double const value) {
    for (int i = 0; i < m_audio.getNumberOfChannels(); ++i) {
        multiplySamplesAtChannelWithValue(i, value);
    }
}

void AudioManipulator::multiplySamplesAtChannelWithValue(int const channelIndex, double const value) {
    Samples& samplesAtChannel(m_audio.getSamplesReferenceAtChannel(channelIndex));
    for_each(samplesAtChannel.begin(), samplesAtChannel.end(), [value](double& sampleAtChannel) {
        sampleAtChannel *= value;
    });
}

void AudioManipulator::saveAudioIntoCurrentFile() { saveAudioIntoFileWithFullFilePath(m_filePathHandler.getPath()); }

void AudioManipulator::saveAudioIntoFileInTheSameDirectory(string const& filename) {
    saveAudioIntoFileWithFullFilePath(m_filePathHandler.getDirectory() / filename);
}

void AudioManipulator::saveAudioIntoFileWithFullFilePath(path const& newFilePath) {
    AlbaLocalPathHandler const newFilePathHandler(newFilePath);
    string const extension(getStringWithCapitalLetters(newFilePathHandler.getExtension().string()));
    if (extension == "WAV") {
        m_audio.save(newFilePathHandler.getPath(), AudioFormat::Wave);
    } else if (extension == "AIFF") {
        m_audio.save(newFilePathHandler.getPath(), AudioFormat::Aiff);
    }
}

AudioInDouble& AudioManipulator::getAudioReference() { return m_audio; }

}  // namespace alba::AprgAudio
