#include "Audio.hpp"

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <array>
#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;
using namespace std::filesystem;

namespace {

// Pre-defined 10-byte representations of common sample rates
unordered_map<int, vector<uint8_t>> const aiffSampleRateTable = {
    {8000, {64, 11, 250, 0, 0, 0, 0, 0, 0, 0}},    {11025, {64, 12, 172, 68, 0, 0, 0, 0, 0, 0}},
    {16000, {64, 12, 250, 0, 0, 0, 0, 0, 0, 0}},   {22050, {64, 13, 172, 68, 0, 0, 0, 0, 0, 0}},
    {32000, {64, 13, 250, 0, 0, 0, 0, 0, 0, 0}},   {37800, {64, 14, 147, 168, 0, 0, 0, 0, 0, 0}},
    {44056, {64, 14, 172, 24, 0, 0, 0, 0, 0, 0}},  {44100, {64, 14, 172, 68, 0, 0, 0, 0, 0, 0}},
    {47250, {64, 14, 184, 146, 0, 0, 0, 0, 0, 0}}, {48000, {64, 14, 187, 128, 0, 0, 0, 0, 0, 0}},
    {50000, {64, 14, 195, 80, 0, 0, 0, 0, 0, 0}},  {50400, {64, 14, 196, 224, 0, 0, 0, 0, 0, 0}},
    {88200, {64, 15, 172, 68, 0, 0, 0, 0, 0, 0}},  {96000, {64, 15, 187, 128, 0, 0, 0, 0, 0, 0}},
    {176400, {64, 16, 172, 68, 0, 0, 0, 0, 0, 0}}, {192000, {64, 16, 187, 128, 0, 0, 0, 0, 0, 0}},
    {352800, {64, 17, 172, 68, 0, 0, 0, 0, 0, 0}}, {2822400, {64, 20, 172, 68, 0, 0, 0, 0, 0, 0}},
    {5644800, {64, 21, 172, 68, 0, 0, 0, 0, 0, 0}}};

}  // namespace

namespace alba::AprgAudio {

template <class DataType>
Audio<DataType>::Audio() {
    samples.resize(1);
    samples[0].resize(0);
}

template <class DataType>
int Audio<DataType>::getSampleRate() const {
    return sampleRate;
}

template <class DataType>
int Audio<DataType>::getNumberOfChannels() const {
    return samples.size();
}

template <class DataType>
bool Audio<DataType>::isMono() const {
    return getNumberOfChannels() == 1;
}

template <class DataType>
bool Audio<DataType>::isStereo() const {
    return getNumberOfChannels() == 2;
}

template <class DataType>
int Audio<DataType>::getBitDepth() const {
    return bitDepth;
}

template <class DataType>
int Audio<DataType>::getNumberOfSamplesPerChannel() const {
    if (!samples.empty()) {
        return samples[0].size();
    }
    return 0;
}

template <class DataType>
std::vector<DataType> const& Audio<DataType>::getSamplesAtChannel(int const channelIndex) const {
    return samples[channelIndex];
}

template <class DataType>
std::vector<DataType>& Audio<DataType>::getSamplesReferenceAtChannel(int const channelIndex) {
    return samples[channelIndex];
}

template <class DataType>
double Audio<DataType>::getLengthInSeconds() const {
    return static_cast<double>(getNumberOfSamplesPerChannel()) / static_cast<double>(sampleRate);
}

template <class DataType>
void Audio<DataType>::printSummary() const {
    cout << "Num Channels: " << getNumberOfChannels() << "\n";
    cout << "Num Samples Per Channel: " << getNumberOfSamplesPerChannel() << "\n";
    cout << "Sample Rate: " << sampleRate << "\n";
    cout << "Bit Depth: " << bitDepth << "\n";
    cout << "Length in Seconds: " << getLengthInSeconds() << "\n";
}

template <class DataType>
bool Audio<DataType>::setAudioBuffer(AudioBuffer& newBuffer) {
    int const numberOfChannels = static_cast<int>(newBuffer.size());

    if (numberOfChannels <= 0) {
        assert(false && "The buffer your are trying to use has no channels");
        return false;
    }

    int const numberOfSamples = newBuffer[0].size();

    // set the number of channels
    samples.resize(newBuffer.size());

    for (int k = 0; k < getNumberOfChannels(); ++k) {
        assert(static_cast<int>(newBuffer[k].size()) == numberOfSamples);

        samples[k].resize(numberOfSamples);

        for (int i = 0; i < numberOfSamples; ++i) {
            samples[k][i] = newBuffer[k][i];
        }
    }

    return true;
}

template <class DataType>
void Audio<DataType>::setAudioBufferSize(int const numberOfChannels, int const numberOfSamples) {
    samples.resize(numberOfChannels);
    setNumSamplesPerChannel(numberOfSamples);
}

template <class DataType>
void Audio<DataType>::setNumSamplesPerChannel(int const numberOfSamples) {
    int const originalSize = getNumberOfSamplesPerChannel();

    for (int i = 0; i < getNumberOfChannels(); ++i) {
        samples[i].resize(numberOfSamples);

        // set any new samples to zero
        if (numberOfSamples > originalSize) {
            fill(samples[i].begin() + originalSize, samples[i].end(), static_cast<DataType>(0));
        }
    }
}

template <class DataType>
void Audio<DataType>::setNumberOfChannels(int const numberOfChannels) {
    int const originalNumberOfChannels = static_cast<int>(getNumberOfChannels());
    int const originalNumSamplesPerChannel = static_cast<int>(getNumberOfSamplesPerChannel());

    samples.resize(numberOfChannels);

    // make sure any new channels are set to the right size
    // and filled with zeros
    if (numberOfChannels > originalNumberOfChannels) {
        for (int i = originalNumberOfChannels; i < numberOfChannels; ++i) {
            samples[i].resize(originalNumSamplesPerChannel);
            fill(samples[i].begin(), samples[i].end(), static_cast<DataType>(0.));
        }
    }
}

template <class DataType>
void Audio<DataType>::setBitDepth(int const numberOfBitsPerSample) {
    bitDepth = numberOfBitsPerSample;
}

template <class DataType>
void Audio<DataType>::setSampleRate(int const newSampleRate) {
    sampleRate = newSampleRate;
}

template <class DataType>
bool Audio<DataType>::load(std::filesystem::path const& filePath) {
    ifstream file(AlbaLocalPathHandler(filePath).getPath(), ios::binary);

    // check the file exists
    if (!file.good()) {
        cout << "ERROR: File doesn't exist or otherwise can't load file\n";
        cout << filePath << "\n";
        return false;
    }

    file.unsetf(ios::skipws);
    istream_iterator<uint8_t> const begin(file);
    istream_iterator<uint8_t> const end;
    vector<uint8_t> dataBuffer(begin, end);

    // get audio file format
    audioFileFormat = determineAudioFormat(dataBuffer);

    if (audioFileFormat == AudioFormat::Wave) {
        return decodeWaveFile(dataBuffer);
    }
    if (audioFileFormat == AudioFormat::Aiff) {
        return decodeAiffFile(dataBuffer);
    }
    cout << "Audio File Type: Error\n";
    return false;
}

template <class DataType>
bool Audio<DataType>::decodeWaveFile(vector<uint8_t>& dataBuffer) {
    // -----------------------------------------------------------
    // HEADER CHUNK
    string const headerChunkID(dataBuffer.begin(), dataBuffer.begin() + 4);
    // int32_t fileSizeInBytes = fourBytesToInt (dataBuffer, 4) + 8;
    string const format(dataBuffer.begin() + 8, dataBuffer.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int const indexOfDataChunk = getIndexOfString(dataBuffer, "data");
    int const indexOfFormatChunk = getIndexOfString(dataBuffer, "fmt");

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfDataChunk == -1 || indexOfFormatChunk == -1 || headerChunkID != "RIFF" || format != "WAVE") {
        cout << "ERROR: this doesn't seem to be a valid .WAV file\n";
        return false;
    }

    // -----------------------------------------------------------
    // FORMAT CHUNK
    int const f = indexOfFormatChunk;
    // string formatChunkID(dataBuffer.begin() + f, dataBuffer.begin() + f + 4);
    //  int32_t formatChunkSize = fourBytesToInt (dataBuffer, f + 4);
    int16_t const audioFormat = twoBytesToInt(dataBuffer, f + 8);
    int16_t const numberOfChannels = twoBytesToInt(dataBuffer, f + 10);
    sampleRate = static_cast<int>(fourBytesToInt(dataBuffer, f + 12));
    int32_t const numberBytesPerSecond = fourBytesToInt(dataBuffer, f + 16);
    int16_t const numberBytesPerBlock = twoBytesToInt(dataBuffer, f + 20);
    bitDepth = static_cast<int>(twoBytesToInt(dataBuffer, f + 22));

    int const numberBytesPerSample = bitDepth / 8;

    // check that the audio format is PCM
    if (audioFormat != 1) {
        cout << "ERROR: this is a compressed .WAV file and this library does not support decoding them at present\n";
        return false;
    }

    // check the number of channels is mono or stereo
    if (numberOfChannels < 1 || numberOfChannels > 2) {
        cout << "ERROR: this WAV file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)\n";
        return false;
    }

    // check header data is consistent
    if (((static_cast<int>(numberBytesPerSecond != numberOfChannels * sampleRate * bitDepth) / 8) != 0) ||
        (numberBytesPerBlock != (numberOfChannels * numberBytesPerSample))) {
        cout << "ERROR: the header data in this WAV file seems to be inconsistent\n";
        return false;
    }

    // check bit depth is either 8, 16 or 24 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24) {
        cout << "ERROR: this file has a bit depth that is not 8, 16 or 24 bits\n";
        return false;
    }

    // -----------------------------------------------------------
    // DATA CHUNK
    int const d = indexOfDataChunk;
    // string dataChunkID(dataBuffer.begin() + d, dataBuffer.begin() + d + 4);
    int32_t const dataChunkSize = fourBytesToInt(dataBuffer, d + 4);

    int const numberOfSamples = dataChunkSize / (numberOfChannels * bitDepth / 8);
    int const samplesStartIndex = indexOfDataChunk + 8;

    clearAudioBuffer();
    samples.resize(numberOfChannels);

    for (int i = 0; i < numberOfSamples; ++i) {
        for (int channel = 0; channel < numberOfChannels; ++channel) {
            int const sampleIndex = samplesStartIndex + (numberBytesPerBlock * i) + channel * numberBytesPerSample;

            if (bitDepth == 8) {
                DataType sample = singleByteToSample(dataBuffer[sampleIndex]);
                samples[channel].push_back(sample);
            } else if (bitDepth == 16) {
                int16_t const sampleAsInt = twoBytesToInt(dataBuffer, sampleIndex);
                DataType sample = sixteenBitIntToSample(sampleAsInt);
                samples[channel].push_back(sample);
            } else if (bitDepth == 24) {
                int32_t sampleAsInt = 0;
                sampleAsInt =
                    (dataBuffer[sampleIndex + 2] << 16) | (dataBuffer[sampleIndex + 1] << 8) | dataBuffer[sampleIndex];

                if ((sampleAsInt & 0x800000) !=
                    0) {  //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF;  // so make sure sign is extended to the 32 bit float
                }

                DataType sample = static_cast<DataType>(sampleAsInt) / static_cast<DataType>(8388608.);
                samples[channel].push_back(sample);
            } else {
                assert(false);
            }
        }
    }

    return true;
}

template <class DataType>
bool Audio<DataType>::decodeAiffFile(vector<uint8_t>& dataBuffer) {
    // -----------------------------------------------------------
    // HEADER CHUNK
    string const headerChunkID(dataBuffer.begin(), dataBuffer.begin() + 4);
    // int32_t fileSizeInBytes = fourBytesToInt (dataBuffer, 4, Endianness::BigEndian) + 8;
    string const format(dataBuffer.begin() + 8, dataBuffer.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int const indexOfCommChunk = getIndexOfString(dataBuffer, "COMM");
    int const indexOfSoundDataChunk = getIndexOfString(dataBuffer, "SSND");

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfSoundDataChunk == -1 || indexOfCommChunk == -1 || headerChunkID != "FORM" || format != "AIFF") {
        cout << "ERROR: this doesn't seem to be a valid AIFF file\n";
        return false;
    }

    // -----------------------------------------------------------
    // COMM CHUNK
    int const p = indexOfCommChunk;
    // string commChunkID(dataBuffer.begin() + p, dataBuffer.begin() + p + 4);
    //  int32_t commChunkSize = fourBytesToInt (dataBuffer, p + 4, Endianness::BigEndian);
    int16_t const numberOfChannels = twoBytesToInt(dataBuffer, p + 8, Endianness::BigEndian);
    int32_t const numberOfSamplesPerChannel = fourBytesToInt(dataBuffer, p + 10, Endianness::BigEndian);
    bitDepth = static_cast<int>(twoBytesToInt(dataBuffer, p + 14, Endianness::BigEndian));
    sampleRate = getAiffSampleRate(dataBuffer, p + 16);

    // check the sample rate was properly decoded
    if (sampleRate == -1) {
        cout << "ERROR: this AIFF file has an unsupported sample rate\n";
        return false;
    }

    // check the number of channels is mono or stereo
    if (numberOfChannels < 1 || numberOfChannels > 2) {
        cout << "ERROR: this AIFF file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)\n";
        return false;
    }

    // check bit depth is either 8, 16 or 24 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24) {
        cout << "ERROR: this file has a bit depth that is not 8, 16 or 24 bits\n";
        return false;
    }

    // -----------------------------------------------------------
    // SSND CHUNK
    int const s = indexOfSoundDataChunk;
    // string soundDataChunkID(dataBuffer.begin() + s, dataBuffer.begin() + s + 4);
    int32_t const soundDataChunkSize = fourBytesToInt(dataBuffer, s + 4, Endianness::BigEndian);
    int32_t const offset = fourBytesToInt(dataBuffer, s + 8, Endianness::BigEndian);
    // int32_t blockSize = fourBytesToInt (dataBuffer, s + 12, Endianness::BigEndian);
    int const numberBytesPerSample = bitDepth / 8;
    int const numberBytesPerFrame = numberBytesPerSample * numberOfChannels;
    int const totalNumAudioSampleBytes = numberOfSamplesPerChannel * numberBytesPerFrame;
    int const samplesStartIndex = s + 16 + static_cast<int>(offset);

    // sanity check the data
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes ||
        totalNumAudioSampleBytes > static_cast<int>(dataBuffer.size() - samplesStartIndex)) {
        cout << "ERROR: the metadatafor this file doesn't seem right\n";
        return false;
    }

    clearAudioBuffer();
    samples.resize(numberOfChannels);

    for (int i = 0; i < numberOfSamplesPerChannel; ++i) {
        for (int channel = 0; channel < numberOfChannels; ++channel) {
            int const sampleIndex = samplesStartIndex + (numberBytesPerFrame * i) + channel * numberBytesPerSample;

            if (bitDepth == 8) {
                auto sampleAsSigned8Bit = static_cast<int8_t>(dataBuffer[sampleIndex]);
                DataType sample = static_cast<DataType>(sampleAsSigned8Bit) / static_cast<DataType>(128);
                samples[channel].push_back(sample);
            } else if (bitDepth == 16) {
                int16_t const sampleAsInt = twoBytesToInt(dataBuffer, sampleIndex, Endianness::BigEndian);
                DataType sample = sixteenBitIntToSample(sampleAsInt);
                samples[channel].push_back(sample);
            } else if (bitDepth == 24) {
                int32_t sampleAsInt = 0;
                sampleAsInt =
                    (dataBuffer[sampleIndex] << 16) | (dataBuffer[sampleIndex + 1] << 8) | dataBuffer[sampleIndex + 2];

                if ((sampleAsInt & 0x800000) !=
                    0) {  //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF;  // so make sure sign is extended to the 32 bit float
                }

                DataType sample = static_cast<DataType>(sampleAsInt) / static_cast<DataType>(8388608.);
                samples[channel].push_back(sample);
            } else {
                assert(false);
            }
        }
    }

    return true;
}

template <class DataType>
int Audio<DataType>::getAiffSampleRate(vector<uint8_t>& dataBuffer, int const sampleRateStartIndex) {
    for (auto it : aiffSampleRateTable) {
        if (tenByteMatch(dataBuffer, sampleRateStartIndex, it.second, 0)) {
            return it.first;
        }
    }

    return -1;
}

template <class DataType>
bool Audio<DataType>::tenByteMatch(
    vector<uint8_t>& v1, int const startIndex1, vector<uint8_t>& v2, int const startIndex2) {
    for (int i = 0; i < 10; ++i) {
        if (v1[startIndex1 + i] != v2[startIndex2 + i]) {
            return false;
        }
    }

    return true;
}

template <class DataType>
void Audio<DataType>::addSampleRateToAiffData(vector<uint8_t>& dataBuffer, int const sampleRate) {
    if (aiffSampleRateTable.contains(sampleRate)) {
        for (int i = 0; i < 10; ++i) {
            dataBuffer.push_back(aiffSampleRateTable.at(sampleRate)[i]);
        }
    }
}

template <class DataType>
bool Audio<DataType>::save(path const& filePath, AudioFormat const format) {
    AlbaLocalPathHandler const filePathHandler(filePath);
    if (format == AudioFormat::Wave) {
        return saveToWaveFile(filePathHandler.getPath());
    }
    if (format == AudioFormat::Aiff) {
        return saveToAiffFile(filePathHandler.getPath());
    }

    return false;
}

template <class DataType>
bool Audio<DataType>::saveToWaveFile(path const& filePath) {
    vector<uint8_t> dataBuffer;

    auto dataChunkSize = static_cast<int32_t>(getNumberOfSamplesPerChannel() * (getNumberOfChannels() * bitDepth / 8));

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData(dataBuffer, "RIFF");

    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size
    int32_t const fileSizeInBytes = 4 + 24 + 8 + dataChunkSize;
    addInt32ToFileData(dataBuffer, fileSizeInBytes);

    addStringToFileData(dataBuffer, "WAVE");

    // -----------------------------------------------------------
    // FORMAT CHUNK
    addStringToFileData(dataBuffer, "fmt ");
    addInt32ToFileData(dataBuffer, 16);                                           // format chunk size (16 for PCM)
    addInt16ToFileData(dataBuffer, 1);                                            // audio format = 1
    addInt16ToFileData(dataBuffer, static_cast<int16_t>(getNumberOfChannels()));  // num channels
    addInt32ToFileData(dataBuffer, static_cast<int32_t>(sampleRate));             // sample rate
    auto numberBytesPerSecond = static_cast<int32_t>((getNumberOfChannels() * sampleRate * bitDepth) / 8);
    addInt32ToFileData(dataBuffer, numberBytesPerSecond);

    auto numberBytesPerBlock = static_cast<int16_t>(getNumberOfChannels() * (bitDepth / 8));
    addInt16ToFileData(dataBuffer, numberBytesPerBlock);

    addInt16ToFileData(dataBuffer, static_cast<int16_t>(bitDepth));

    // -----------------------------------------------------------
    // DATA CHUNK
    addStringToFileData(dataBuffer, "data");
    addInt32ToFileData(dataBuffer, dataChunkSize);

    for (int i = 0; i < getNumberOfSamplesPerChannel(); ++i) {
        for (int channel = 0; channel < getNumberOfChannels(); ++channel) {
            if (bitDepth == 8) {
                uint8_t const byte = sampleToSingleByte(samples[channel][i]);
                dataBuffer.push_back(byte);
            } else if (bitDepth == 16) {
                int16_t const sampleAsInt = sampleToSixteenBitInt(samples[channel][i]);
                addInt16ToFileData(dataBuffer, sampleAsInt);
            } else if (bitDepth == 24) {
                auto sampleAsIntAgain = static_cast<int32_t>(samples[channel][i] * static_cast<DataType>(8388608.));

                dataBuffer.push_back(static_cast<uint8_t>(sampleAsIntAgain >> 16) & 0xFF);
                dataBuffer.push_back(static_cast<uint8_t>(sampleAsIntAgain >> 8) & 0xFF);
                dataBuffer.push_back(static_cast<uint8_t>(sampleAsIntAgain) & 0xFF);
            } else {
                assert(false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(dataBuffer.size() - 8) ||
        dataChunkSize !=
            static_cast<int32_t>(getNumberOfSamplesPerChannel() * getNumberOfChannels() * (bitDepth / 8))) {
        cout << "ERROR: couldn't save file to " << filePath << "\n";
        return false;
    }

    // try to write the file
    return writeDataToFile(dataBuffer, filePath);
}

template <class DataType>
bool Audio<DataType>::saveToAiffFile(path const& filePath) {
    vector<uint8_t> dataBuffer;

    int32_t const numberBytesPerSample = bitDepth / 8;
    auto numberBytesPerFrame = static_cast<int32_t>(numberBytesPerSample * getNumberOfChannels());
    auto totalNumAudioSampleBytes = static_cast<int32_t>(getNumberOfSamplesPerChannel() * numberBytesPerFrame);
    int32_t const soundDataChunkSize = totalNumAudioSampleBytes + 8;

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData(dataBuffer, "FORM");

    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM
    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t const fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
    addInt32ToFileData(dataBuffer, fileSizeInBytes, Endianness::BigEndian);

    addStringToFileData(dataBuffer, "AIFF");

    // -----------------------------------------------------------
    // COMM CHUNK
    addStringToFileData(dataBuffer, "COMM");
    addInt32ToFileData(dataBuffer, 18, Endianness::BigEndian);  // commChunkSize
    addInt16ToFileData(dataBuffer, static_cast<int16_t>(getNumberOfChannels()), Endianness::BigEndian);  // num channels
    addInt32ToFileData(
        dataBuffer, static_cast<int32_t>(getNumberOfSamplesPerChannel()),
        Endianness::BigEndian);                                       // num samples per channel
    addInt16ToFileData(dataBuffer, bitDepth, Endianness::BigEndian);  // bit depth
    addSampleRateToAiffData(dataBuffer, sampleRate);

    // -----------------------------------------------------------
    // SSND CHUNK
    addStringToFileData(dataBuffer, "SSND");
    addInt32ToFileData(dataBuffer, soundDataChunkSize, Endianness::BigEndian);
    addInt32ToFileData(dataBuffer, 0, Endianness::BigEndian);  // offset
    addInt32ToFileData(dataBuffer, 0, Endianness::BigEndian);  // block size
    for (int i = 0; i < getNumberOfSamplesPerChannel(); ++i) {
        for (int channel = 0; channel < getNumberOfChannels(); ++channel) {
            if (bitDepth == 8) {
                uint8_t const byte = sampleToSingleByte(samples[channel][i]);
                dataBuffer.push_back(byte);
            } else if (bitDepth == 16) {
                int16_t const sampleAsInt = sampleToSixteenBitInt(samples[channel][i]);
                addInt16ToFileData(dataBuffer, sampleAsInt, Endianness::BigEndian);
            } else if (bitDepth == 24) {
                auto sampleAsIntAgain = static_cast<int32_t>(samples[channel][i] * static_cast<DataType>(8388608.));

                dataBuffer.push_back((static_cast<uint8_t>(sampleAsIntAgain) >> 16U) & 0xFFU);
                dataBuffer.push_back((static_cast<uint8_t>(sampleAsIntAgain) >> 8U) & 0xFFU);
                dataBuffer.push_back(static_cast<uint8_t>(sampleAsIntAgain) & 0xFFU);
            } else {
                assert(false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(dataBuffer.size() - 8) ||
        soundDataChunkSize != static_cast<int32_t>(getNumberOfSamplesPerChannel() * numberBytesPerFrame + 8)) {
        cout << "ERROR: couldn't save file to " << filePath << "\n";
        return false;
    }

    // try to write the file
    return writeDataToFile(dataBuffer, filePath);
}

template <class DataType>
bool Audio<DataType>::writeDataToFile(vector<uint8_t>& dataBuffer, path const& filePath) {
    ofstream outputFile(filePath, ios::binary);

    if (outputFile.is_open()) {
        for (uint8_t const fileDataBytesByte : dataBuffer) {
            char const value = static_cast<char>(fileDataBytesByte);
            outputFile.write(&value, sizeof(char));
        }
        outputFile.close();
        return true;
    }
    return false;
}

template <class DataType>
void Audio<DataType>::addStringToFileData(vector<uint8_t>& dataBuffer, string const& stringToCopy) {
    dataBuffer.reserve(dataBuffer.size() + stringToCopy.size());
    copy(stringToCopy.cbegin(), stringToCopy.cend(), back_inserter(dataBuffer));
}

template <class DataType>
void Audio<DataType>::addInt32ToFileData(
    vector<uint8_t>& dataBuffer, int32_t const integerToCopy, Endianness const endianness) {
    array<uint8_t, 4> bytes{};

    if (endianness == Endianness::LittleEndian) {
        bytes[3] = (integerToCopy >> 24) & 0xFF;
        bytes[2] = (integerToCopy >> 16) & 0xFF;
        bytes[1] = (integerToCopy >> 8) & 0xFF;
        bytes[0] = integerToCopy & 0xFF;
    } else {
        bytes[0] = (integerToCopy >> 24) & 0xFF;
        bytes[1] = (integerToCopy >> 16) & 0xFF;
        bytes[2] = (integerToCopy >> 8) & 0xFF;
        bytes[3] = integerToCopy & 0xFF;
    }

    dataBuffer.reserve(dataBuffer.size() + 4);
    copy(bytes.cbegin(), bytes.cend(), back_inserter(dataBuffer));
}

template <class DataType>
void Audio<DataType>::addInt16ToFileData(
    vector<uint8_t>& dataBuffer, int16_t const integerToCopy, Endianness const endianness) {
    array<uint8_t, 2> bytes{};

    if (endianness == Endianness::LittleEndian) {
        bytes[1] = (integerToCopy >> 8) & 0xFF;
        bytes[0] = integerToCopy & 0xFF;
    } else {
        bytes[0] = (integerToCopy >> 8) & 0xFF;
        bytes[1] = integerToCopy & 0xFF;
    }

    dataBuffer.push_back(bytes[0]);
    dataBuffer.push_back(bytes[1]);
}

template <class DataType>
void Audio<DataType>::clearAudioBuffer() {
    for (int i = 0; i < static_cast<int>(samples.size()); ++i) {
        samples[i].clear();
    }

    samples.clear();
}

template <class DataType>
AudioFormat Audio<DataType>::determineAudioFormat(vector<uint8_t>& dataBuffer) {
    string const header(dataBuffer.begin(), dataBuffer.begin() + 4);

    if (header == "RIFF") {
        return AudioFormat::Wave;
    }
    if (header == "FORM") {
        return AudioFormat::Aiff;
    }
    return AudioFormat::Error;
}

template <class DataType>
int32_t Audio<DataType>::fourBytesToInt(
    vector<uint8_t> const& source, int const startIndex, Endianness const endianness) {
    int32_t result = 0;

    if (endianness == Endianness::LittleEndian) {
        result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) |
                 source[startIndex];
    } else {
        result = (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) |
                 source[startIndex + 3];
    }

    return result;
}

template <class DataType>
int16_t Audio<DataType>::twoBytesToInt(
    vector<uint8_t> const& source, int const startIndex, Endianness const endianness) {
    int16_t result = 0;

    if (endianness == Endianness::LittleEndian) {
        result = static_cast<int16_t>((source[startIndex + 1] << 8) | source[startIndex]);
    } else {
        result = static_cast<int16_t>((source[startIndex] << 8) | source[startIndex + 1]);
    }

    return result;
}

template <class DataType>
int Audio<DataType>::getIndexOfString(vector<uint8_t> const& source, string const& stringToSearchFor) {
    int index = -1;
    int const stringLength = static_cast<int>(stringToSearchFor.length());

    for (int i = 0; i < static_cast<int>(source.size() - stringLength); ++i) {
        string const section(source.cbegin() + i, source.cbegin() + i + stringLength);

        if (section == stringToSearchFor) {
            index = i;
            break;
        }
    }

    return index;
}

template <class DataType>
DataType Audio<DataType>::sixteenBitIntToSample(int16_t const sample) {
    return static_cast<DataType>(sample) / static_cast<DataType>(32768.);
}

template <class DataType>
int16_t Audio<DataType>::sampleToSixteenBitInt(DataType const sample) {
    return static_cast<int16_t>(clamp(sample, -1., 1.) * 32767.);
}

template <class DataType>
uint8_t Audio<DataType>::sampleToSingleByte(DataType const sample) {
    return static_cast<uint8_t>((clamp(sample, -1., 1.) + 1.) / 2. * 255.);
}

template <class DataType>
DataType Audio<DataType>::singleByteToSample(uint8_t const sample) {
    return static_cast<DataType>(sample - 128) / static_cast<DataType>(128.);
}

template <class DataType>
DataType Audio<DataType>::clamp(DataType const value, DataType const minValue, DataType const maxValue) {
    return max(min(value, maxValue), minValue);
}

//===========================================================
template class Audio<float>;
template class Audio<double>;

}  // namespace alba::AprgAudio
