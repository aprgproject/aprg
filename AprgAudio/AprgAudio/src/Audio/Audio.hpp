#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace alba::AprgAudio {

// The different types of audio file, plus some other types to
// indicate a failure to load a file, or that one hasn't been
// loaded yet

enum class AudioFormat { Error, NotLoaded, Wave, Aiff };

template <class DataType>
class Audio {
public:
    using AudioBuffer = std::vector<std::vector<DataType>>;

    Audio();

    bool load(std::string const& filePath);

    bool save(std::string const& filePath, AudioFormat format = AudioFormat::Wave);

    [[nodiscard]] int getSampleRate() const;

    [[nodiscard]] int getNumberOfChannels() const;

    [[nodiscard]] bool isMono() const;

    [[nodiscard]] bool isStereo() const;

    [[nodiscard]] int getBitDepth() const;

    [[nodiscard]] int getNumberOfSamplesPerChannel() const;

    [[nodiscard]] std::vector<DataType> const& getSamplesAtChannel(int const channelIndex) const;
    std::vector<DataType>& getSamplesReferenceAtChannel(int const channelIndex);

    // @Returns the length in seconds of the audio file based on the number of samples and sample rate
    [[nodiscard]] double getLengthInSeconds() const;

    // Prints a summary of the audio file to the console
    void printSummary() const;

    // Set the audio buffer for this Audio by copying samples from another buffer.
    // @Returns true if the buffer was copied successfully.
    bool setAudioBuffer(AudioBuffer& newBuffer);

    // Sets the audio buffer to a given number of channels and number of samples per channel. This will try to preserve
    // the existing audio, adding zeros to any new channels or new samples in a given channel.
    void setAudioBufferSize(int const numberOfChannels, int const numberOfSamples);

    // Sets the number of samples per channel in the audio buffer. This will try to preserve
    // the existing audio, adding zeros to new samples in a given channel if the number of samples is increased.
    void setNumSamplesPerChannel(int const numberOfSamples);

    // Sets the number of channels. New channels will have the correct number of samples and be initialised to zero
    void setNumberOfChannels(int const numberOfChannels);

    // Sets the bit depth for the audio file. If you use the save() function, this bit depth rate will be used
    void setBitDepth(int const numberOfBitsPerSample);

    // Sets the sample rate for the audio file. If you use the save() function, this sample rate will be used
    void setSampleRate(int const newSampleRate);

    // A vector of vectors holding the audio samples for the Audio. You can
    // access the samples by channel and then by sample index, i.e:
    //      samples[channel][sampleIndex]
    AudioBuffer samples;

private:
    enum class Endianness { LittleEndian, BigEndian };

    AudioFormat determineAudioFormat(std::vector<uint8_t>& dataBuffer);
    bool decodeWaveFile(std::vector<uint8_t>& dataBuffer);
    bool decodeAiffFile(std::vector<uint8_t>& dataBuffer);

    bool saveToWaveFile(std::string const& filePath);
    bool saveToAiffFile(std::string const& filePath);

    void clearAudioBuffer();

    int32_t fourBytesToInt(
        std::vector<uint8_t> const& source, int const startIndex, Endianness endianness = Endianness::LittleEndian);
    int16_t twoBytesToInt(
        std::vector<uint8_t> const& source, int const startIndex, Endianness endianness = Endianness::LittleEndian);
    int getIndexOfString(std::vector<uint8_t> const& source, std::string const& s);

    DataType sixteenBitIntToSample(int16_t const sample);
    int16_t sampleToSixteenBitInt(DataType const sample);

    uint8_t sampleToSingleByte(DataType const sample);
    DataType singleByteToSample(uint8_t const sample);

    int getAiffSampleRate(std::vector<uint8_t>& dataBuffer, int const sampleRateStartIndex);
    bool tenByteMatch(std::vector<uint8_t>& v1, int const startIndex1, std::vector<uint8_t>& v2, int const startIndex2);
    void addSampleRateToAiffData(std::vector<uint8_t>& dataBuffer, int const sampleRate);
    DataType clamp(DataType const value, DataType const minValue, DataType const maxValue);

    void addStringToFileData(std::vector<uint8_t>& dataBuffer, std::string const& stringToCopy);
    void addInt32ToFileData(
        std::vector<uint8_t>& dataBuffer, int32_t const integerToCopy, Endianness endianness = Endianness::LittleEndian);
    void addInt16ToFileData(
        std::vector<uint8_t>& dataBuffer, int16_t const integerToCopy, Endianness endianness = Endianness::LittleEndian);

    bool writeDataToFile(std::vector<uint8_t>& dataBuffer, std::string const& filePath);

    AudioFormat audioFileFormat{AudioFormat::NotLoaded};
    int sampleRate{44100};
    int bitDepth{16};
};

}  // namespace alba::AprgAudio
