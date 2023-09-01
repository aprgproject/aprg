#include "Audio.hpp"

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <array>
#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

namespace alba::AprgAudio {

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
int Audio<DataType>::getNumChannels() const {
    return samples.size();
}

template <class DataType>
bool Audio<DataType>::isMono() const {
    return getNumChannels() == 1;
}

template <class DataType>
bool Audio<DataType>::isStereo() const {
    return getNumChannels() == 2;
}

template <class DataType>
int Audio<DataType>::getBitDepth() const {
    return bitDepth;
}

template <class DataType>
int Audio<DataType>::getNumSamplesPerChannel() const {
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
    return static_cast<double>(getNumSamplesPerChannel()) / static_cast<double>(sampleRate);
}

template <class DataType>
void Audio<DataType>::printSummary() const {
    cout << "|======================================|\n";
    cout << "Num Channels: " << getNumChannels() << "\n";
    cout << "Num Samples Per Channel: " << getNumSamplesPerChannel() << "\n";
    cout << "Sample Rate: " << sampleRate << "\n";
    cout << "Bit Depth: " << bitDepth << "\n";
    cout << "Length in Seconds: " << getLengthInSeconds() << "\n";
    cout << "|======================================|\n";
}

template <class DataType>
bool Audio<DataType>::setAudioBuffer(AudioBuffer& newBuffer) {
    int numChannels = static_cast<int>(newBuffer.size());

    if (numChannels <= 0) {
        assert(false && "The buffer your are trying to use has no channels");
        return false;
    }

    int numSamples = newBuffer[0].size();

    // set the number of channels
    samples.resize(newBuffer.size());

    for (int k = 0; k < getNumChannels(); k++) {
        assert(static_cast<int>(newBuffer[k].size()) == numSamples);

        samples[k].resize(numSamples);

        for (int i = 0; i < numSamples; i++) {
            samples[k][i] = newBuffer[k][i];
        }
    }

    return true;
}

template <class DataType>
void Audio<DataType>::setAudioBufferSize(int numChannels, int numSamples) {
    samples.resize(numChannels);
    setNumSamplesPerChannel(numSamples);
}

template <class DataType>
void Audio<DataType>::setNumSamplesPerChannel(int numSamples) {
    int originalSize = getNumSamplesPerChannel();

    for (int i = 0; i < getNumChannels(); i++) {
        samples[i].resize(numSamples);

        // set any new samples to zero
        if (numSamples > originalSize) {
            fill(samples[i].begin() + originalSize, samples[i].end(), static_cast<DataType>(0));
        }
    }
}

template <class DataType>
void Audio<DataType>::setNumChannels(int numChannels) {
    int originalNumChannels = static_cast<int>(getNumChannels());
    int originalNumSamplesPerChannel = static_cast<int>(getNumSamplesPerChannel());

    samples.resize(numChannels);

    // make sure any new channels are set to the right size
    // and filled with zeros
    if (numChannels > originalNumChannels) {
        for (int i = originalNumChannels; i < numChannels; i++) {
            samples[i].resize(originalNumSamplesPerChannel);
            fill(samples[i].begin(), samples[i].end(), static_cast<DataType>(0.));
        }
    }
}

template <class DataType>
void Audio<DataType>::setBitDepth(int numBitsPerSample) {
    bitDepth = numBitsPerSample;
}

template <class DataType>
void Audio<DataType>::setSampleRate(int newSampleRate) {
    sampleRate = newSampleRate;
}

template <class DataType>
bool Audio<DataType>::load(string const& filePath) {
    ifstream file(AlbaLocalPathHandler(filePath).getFullPath(), ios::binary);

    // check the file exists
    if (!file.good()) {
        cout << "ERROR: File doesn't exist or otherwise can't load file\n";
        cout << filePath << "\n";
        return false;
    }

    file.unsetf(ios::skipws);
    istream_iterator<uint8_t> begin(file);
    istream_iterator<uint8_t> end;
    vector<uint8_t> fileDataBytes(begin, end);

    // get audio file format
    audioFileFormat = determineAudioFormat(fileDataBytes);

    if (audioFileFormat == AudioFormat::Wave) {
        return decodeWaveFile(fileDataBytes);
    }
    if (audioFileFormat == AudioFormat::Aiff) {
        return decodeAiffFile(fileDataBytes);
    }
    cout << "Audio File Type: Error\n";
    return false;
}

template <class DataType>
bool Audio<DataType>::decodeWaveFile(vector<uint8_t>& fileDataBytes) {
    // -----------------------------------------------------------
    // HEADER CHUNK
    string headerChunkID(fileDataBytes.begin(), fileDataBytes.begin() + 4);
    // int32_t fileSizeInBytes = fourBytesToInt (fileDataBytes, 4) + 8;
    string format(fileDataBytes.begin() + 8, fileDataBytes.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfDataChunk = getIndexOfString(fileDataBytes, "data");
    int indexOfFormatChunk = getIndexOfString(fileDataBytes, "fmt");

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfDataChunk == -1 || indexOfFormatChunk == -1 || headerChunkID != "RIFF" || format != "WAVE") {
        cout << "ERROR: this doesn't seem to be a valid .WAV file\n";
        return false;
    }

    // -----------------------------------------------------------
    // FORMAT CHUNK
    int f = indexOfFormatChunk;
    string formatChunkID(fileDataBytes.begin() + f, fileDataBytes.begin() + f + 4);
    // int32_t formatChunkSize = fourBytesToInt (fileDataBytes, f + 4);
    int16_t audioFormat = twoBytesToInt(fileDataBytes, f + 8);
    int16_t numChannels = twoBytesToInt(fileDataBytes, f + 10);
    sampleRate = static_cast<int>(fourBytesToInt(fileDataBytes, f + 12));
    int32_t numBytesPerSecond = fourBytesToInt(fileDataBytes, f + 16);
    int16_t numBytesPerBlock = twoBytesToInt(fileDataBytes, f + 20);
    bitDepth = static_cast<int>(twoBytesToInt(fileDataBytes, f + 22));

    int numBytesPerSample = bitDepth / 8;

    // check that the audio format is PCM
    if (audioFormat != 1) {
        cout << "ERROR: this is a compressed .WAV file and this library does not support decoding them at present\n";
        return false;
    }

    // check the number of channels is mono or stereo
    if (numChannels < 1 || numChannels > 2) {
        cout << "ERROR: this WAV file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)\n";
        return false;
    }

    // check header data is consistent
    if (((static_cast<int>(numBytesPerSecond != numChannels * sampleRate * bitDepth) / 8) != 0) ||
        (numBytesPerBlock != (numChannels * numBytesPerSample))) {
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
    int d = indexOfDataChunk;
    string dataChunkID(fileDataBytes.begin() + d, fileDataBytes.begin() + d + 4);
    int32_t dataChunkSize = fourBytesToInt(fileDataBytes, d + 4);

    int numSamples = dataChunkSize / (numChannels * bitDepth / 8);
    int samplesStartIndex = indexOfDataChunk + 8;

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamples; i++) {
        for (int channel = 0; channel < numChannels; channel++) {
            int sampleIndex = samplesStartIndex + (numBytesPerBlock * i) + channel * numBytesPerSample;

            if (bitDepth == 8) {
                DataType sample = singleByteToSample(fileDataBytes[sampleIndex]);
                samples[channel].push_back(sample);
            } else if (bitDepth == 16) {
                int16_t sampleAsInt = twoBytesToInt(fileDataBytes, sampleIndex);
                DataType sample = sixteenBitIntToSample(sampleAsInt);
                samples[channel].push_back(sample);
            } else if (bitDepth == 24) {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileDataBytes[sampleIndex + 2] << 16) | (fileDataBytes[sampleIndex + 1] << 8) |
                              fileDataBytes[sampleIndex];

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
bool Audio<DataType>::decodeAiffFile(vector<uint8_t>& fileDataBytes) {
    // -----------------------------------------------------------
    // HEADER CHUNK
    string headerChunkID(fileDataBytes.begin(), fileDataBytes.begin() + 4);
    // int32_t fileSizeInBytes = fourBytesToInt (fileDataBytes, 4, Endianness::BigEndian) + 8;
    string format(fileDataBytes.begin() + 8, fileDataBytes.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfString(fileDataBytes, "COMM");
    int indexOfSoundDataChunk = getIndexOfString(fileDataBytes, "SSND");

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfSoundDataChunk == -1 || indexOfCommChunk == -1 || headerChunkID != "FORM" || format != "AIFF") {
        cout << "ERROR: this doesn't seem to be a valid AIFF file\n";
        return false;
    }

    // -----------------------------------------------------------
    // COMM CHUNK
    int p = indexOfCommChunk;
    string commChunkID(fileDataBytes.begin() + p, fileDataBytes.begin() + p + 4);
    // int32_t commChunkSize = fourBytesToInt (fileDataBytes, p + 4, Endianness::BigEndian);
    int16_t numChannels = twoBytesToInt(fileDataBytes, p + 8, Endianness::BigEndian);
    int32_t numSamplesPerChannel = fourBytesToInt(fileDataBytes, p + 10, Endianness::BigEndian);
    bitDepth = static_cast<int>(twoBytesToInt(fileDataBytes, p + 14, Endianness::BigEndian));
    sampleRate = getAiffSampleRate(fileDataBytes, p + 16);

    // check the sample rate was properly decoded
    if (sampleRate == -1) {
        cout << "ERROR: this AIFF file has an unsupported sample rate\n";
        return false;
    }

    // check the number of channels is mono or stereo
    if (numChannels < 1 || numChannels > 2) {
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
    int s = indexOfSoundDataChunk;
    string soundDataChunkID(fileDataBytes.begin() + s, fileDataBytes.begin() + s + 4);
    int32_t soundDataChunkSize = fourBytesToInt(fileDataBytes, s + 4, Endianness::BigEndian);
    int32_t offset = fourBytesToInt(fileDataBytes, s + 8, Endianness::BigEndian);
    // int32_t blockSize = fourBytesToInt (fileDataBytes, s + 12, Endianness::BigEndian);

    int numBytesPerSample = bitDepth / 8;
    int numBytesPerFrame = numBytesPerSample * numChannels;
    int totalNumAudioSampleBytes = numSamplesPerChannel * numBytesPerFrame;
    int samplesStartIndex = s + 16 + static_cast<int>(offset);

    // sanity check the data
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes ||
        totalNumAudioSampleBytes > static_cast<int>(fileDataBytes.size() - samplesStartIndex)) {
        cout << "ERROR: the metadatafor this file doesn't seem right\n";
        return false;
    }

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamplesPerChannel; i++) {
        for (int channel = 0; channel < numChannels; channel++) {
            int sampleIndex = samplesStartIndex + (numBytesPerFrame * i) + channel * numBytesPerSample;

            if (bitDepth == 8) {
                auto sampleAsSigned8Bit = static_cast<int8_t>(fileDataBytes[sampleIndex]);
                DataType sample = static_cast<DataType>(sampleAsSigned8Bit) / static_cast<DataType>(128.);
                samples[channel].push_back(sample);
            } else if (bitDepth == 16) {
                int16_t sampleAsInt = twoBytesToInt(fileDataBytes, sampleIndex, Endianness::BigEndian);
                DataType sample = sixteenBitIntToSample(sampleAsInt);
                samples[channel].push_back(sample);
            } else if (bitDepth == 24) {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileDataBytes[sampleIndex] << 16) | (fileDataBytes[sampleIndex + 1] << 8) |
                              fileDataBytes[sampleIndex + 2];

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
int Audio<DataType>::getAiffSampleRate(vector<uint8_t>& fileDataBytes, int sampleRateStartIndex) {
    for (auto it : aiffSampleRateTable) {
        if (tenByteMatch(fileDataBytes, sampleRateStartIndex, it.second, 0)) {
            return it.first;
        }
    }

    return -1;
}

template <class DataType>
bool Audio<DataType>::tenByteMatch(vector<uint8_t>& v1, int startIndex1, vector<uint8_t>& v2, int startIndex2) {
    for (int i = 0; i < 10; i++) {
        if (v1[startIndex1 + i] != v2[startIndex2 + i]) {
            return false;
        }
    }

    return true;
}

template <class DataType>
void Audio<DataType>::addSampleRateToAiffData(vector<uint8_t>& fileDataBytes, int sampleRate) {
    if (aiffSampleRateTable.count(sampleRate) > 0) {
        for (int i = 0; i < 10; i++) {
            fileDataBytes.push_back(aiffSampleRateTable.at(sampleRate)[i]);
        }
    }
}

template <class DataType>
bool Audio<DataType>::save(string const& filePath, AudioFormat format) {
    AlbaLocalPathHandler filePathHandler(filePath);
    if (format == AudioFormat::Wave) {
        return saveToWaveFile(filePathHandler.getFullPath());
    }
    if (format == AudioFormat::Aiff) {
        return saveToAiffFile(filePathHandler.getFullPath());
    }

    return false;
}

template <class DataType>
bool Audio<DataType>::saveToWaveFile(string const& filePath) {
    vector<uint8_t> fileDataBytes;

    auto dataChunkSize = static_cast<int32_t>(getNumSamplesPerChannel() * (getNumChannels() * bitDepth / 8));

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData(fileDataBytes, "RIFF");

    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 24 + 8 + dataChunkSize;
    addInt32ToFileData(fileDataBytes, fileSizeInBytes);

    addStringToFileData(fileDataBytes, "WAVE");

    // -----------------------------------------------------------
    // FORMAT CHUNK
    addStringToFileData(fileDataBytes, "fmt ");
    addInt32ToFileData(fileDataBytes, 16);                                      // format chunk size (16 for PCM)
    addInt16ToFileData(fileDataBytes, 1);                                       // audio format = 1
    addInt16ToFileData(fileDataBytes, static_cast<int16_t>(getNumChannels()));  // num channels
    addInt32ToFileData(fileDataBytes, (int32_t)sampleRate);                     // sample rate

    auto numBytesPerSecond = static_cast<int32_t>((getNumChannels() * sampleRate * bitDepth) / 8);
    addInt32ToFileData(fileDataBytes, numBytesPerSecond);

    auto numBytesPerBlock = static_cast<int16_t>(getNumChannels() * (bitDepth / 8));
    addInt16ToFileData(fileDataBytes, numBytesPerBlock);

    addInt16ToFileData(fileDataBytes, (int16_t)bitDepth);

    // -----------------------------------------------------------
    // DATA CHUNK
    addStringToFileData(fileDataBytes, "data");
    addInt32ToFileData(fileDataBytes, dataChunkSize);

    for (int i = 0; i < getNumSamplesPerChannel(); i++) {
        for (int channel = 0; channel < getNumChannels(); channel++) {
            if (bitDepth == 8) {
                uint8_t byte = sampleToSingleByte(samples[channel][i]);
                fileDataBytes.push_back(byte);
            } else if (bitDepth == 16) {
                int16_t sampleAsInt = sampleToSixteenBitInt(samples[channel][i]);
                addInt16ToFileData(fileDataBytes, sampleAsInt);
            } else if (bitDepth == 24) {
                auto sampleAsIntAgain = (int32_t)(samples[channel][i] * static_cast<DataType>(8388608.));

                fileDataBytes.push_back(static_cast<uint8_t>(sampleAsIntAgain >> 16) & 0xFF);
                fileDataBytes.push_back(static_cast<uint8_t>(sampleAsIntAgain >> 8) & 0xFF);
                fileDataBytes.push_back(static_cast<uint8_t>(sampleAsIntAgain) & 0xFF);
            } else {
                assert(false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(fileDataBytes.size() - 8) ||
        dataChunkSize != static_cast<int32_t>(getNumSamplesPerChannel() * getNumChannels() * (bitDepth / 8))) {
        cout << "ERROR: couldn't save file to " << filePath << "\n";
        return false;
    }

    // try to write the file
    return writeDataToFile(fileDataBytes, filePath);
}

template <class DataType>
bool Audio<DataType>::saveToAiffFile(string const& filePath) {
    vector<uint8_t> fileDataBytes;

    int32_t numBytesPerSample = bitDepth / 8;
    auto numBytesPerFrame = static_cast<int32_t>(numBytesPerSample * getNumChannels());
    auto totalNumAudioSampleBytes = static_cast<int32_t>(getNumSamplesPerChannel() * numBytesPerFrame);
    int32_t soundDataChunkSize = totalNumAudioSampleBytes + 8;

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData(fileDataBytes, "FORM");

    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM
    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
    addInt32ToFileData(fileDataBytes, fileSizeInBytes, Endianness::BigEndian);

    addStringToFileData(fileDataBytes, "AIFF");

    // -----------------------------------------------------------
    // COMM CHUNK
    addStringToFileData(fileDataBytes, "COMM");
    addInt32ToFileData(fileDataBytes, 18, Endianness::BigEndian);                                      // commChunkSize
    addInt16ToFileData(fileDataBytes, static_cast<int16_t>(getNumChannels()), Endianness::BigEndian);  // num channels
    addInt32ToFileData(
        fileDataBytes, static_cast<int32_t>(getNumSamplesPerChannel()),
        Endianness::BigEndian);                                          // num samples per channel
    addInt16ToFileData(fileDataBytes, bitDepth, Endianness::BigEndian);  // bit depth
    addSampleRateToAiffData(fileDataBytes, sampleRate);

    // -----------------------------------------------------------
    // SSND CHUNK
    addStringToFileData(fileDataBytes, "SSND");
    addInt32ToFileData(fileDataBytes, soundDataChunkSize, Endianness::BigEndian);
    addInt32ToFileData(fileDataBytes, 0, Endianness::BigEndian);  // offset
    addInt32ToFileData(fileDataBytes, 0, Endianness::BigEndian);  // block size

    for (int i = 0; i < getNumSamplesPerChannel(); i++) {
        for (int channel = 0; channel < getNumChannels(); channel++) {
            if (bitDepth == 8) {
                uint8_t byte = sampleToSingleByte(samples[channel][i]);
                fileDataBytes.push_back(byte);
            } else if (bitDepth == 16) {
                int16_t sampleAsInt = sampleToSixteenBitInt(samples[channel][i]);
                addInt16ToFileData(fileDataBytes, sampleAsInt, Endianness::BigEndian);
            } else if (bitDepth == 24) {
                auto sampleAsIntAgain = (int32_t)(samples[channel][i] * static_cast<DataType>(8388608.));

                array<uint8_t, 3> bytes;
                bytes[0] = static_cast<uint8_t>(sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = static_cast<uint8_t>(sampleAsIntAgain >> 8) & 0xFF;
                bytes[2] = static_cast<uint8_t>(sampleAsIntAgain) & 0xFF;

                fileDataBytes.push_back(bytes[0]);
                fileDataBytes.push_back(bytes[1]);
                fileDataBytes.push_back(bytes[2]);
            } else {
                assert(false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(fileDataBytes.size() - 8) ||
        soundDataChunkSize != static_cast<int32_t>(getNumSamplesPerChannel() * numBytesPerFrame + 8)) {
        cout << "ERROR: couldn't save file to " << filePath << "\n";
        return false;
    }

    // try to write the file
    return writeDataToFile(fileDataBytes, filePath);
}

template <class DataType>
bool Audio<DataType>::writeDataToFile(vector<uint8_t>& fileDataBytes, string const& filePath) {
    ofstream outputFile(filePath, ios::binary);

    if (outputFile.is_open()) {
        for (uint8_t const fileDataBytesByte : fileDataBytes) {
            char value = static_cast<char>(fileDataBytesByte);
            outputFile.write(&value, sizeof(char));
        }
        outputFile.close();
        return true;
    }
    return false;
}

template <class DataType>
void Audio<DataType>::addStringToFileData(vector<uint8_t>& fileDataBytes, string const& s) {
    fileDataBytes.reserve(fileDataBytes.size() + s.size());
    copy(s.cbegin(), s.cend(), back_inserter(fileDataBytes));
}

template <class DataType>
void Audio<DataType>::addInt32ToFileData(vector<uint8_t>& fileDataBytes, int32_t i, Endianness endianness) {
    array<uint8_t, 4> bytes;

    if (endianness == Endianness::LittleEndian) {
        bytes[3] = (i >> 24) & 0xFF;
        bytes[2] = (i >> 16) & 0xFF;
        bytes[1] = (i >> 8) & 0xFF;
        bytes[0] = i & 0xFF;
    } else {
        bytes[0] = (i >> 24) & 0xFF;
        bytes[1] = (i >> 16) & 0xFF;
        bytes[2] = (i >> 8) & 0xFF;
        bytes[3] = i & 0xFF;
    }

    fileDataBytes.reserve(fileDataBytes.size() + 4);
    copy(bytes.cbegin(), bytes.cend(), back_inserter(fileDataBytes));
}

template <class DataType>
void Audio<DataType>::addInt16ToFileData(vector<uint8_t>& fileDataBytes, int16_t i, Endianness endianness) {
    array<uint8_t, 2> bytes{};

    if (endianness == Endianness::LittleEndian) {
        bytes[1] = (i >> 8) & 0xFF;
        bytes[0] = i & 0xFF;
    } else {
        bytes[0] = (i >> 8) & 0xFF;
        bytes[1] = i & 0xFF;
    }

    fileDataBytes.push_back(bytes[0]);
    fileDataBytes.push_back(bytes[1]);
}

template <class DataType>
void Audio<DataType>::clearAudioBuffer() {
    for (int i = 0; i < static_cast<int>(samples.size()); i++) {
        samples[i].clear();
    }

    samples.clear();
}

template <class DataType>
AudioFormat Audio<DataType>::determineAudioFormat(vector<uint8_t>& fileDataBytes) {
    string header(fileDataBytes.begin(), fileDataBytes.begin() + 4);

    if (header == "RIFF") {
        return AudioFormat::Wave;
    }
    if (header == "FORM") {
        return AudioFormat::Aiff;
    }
    return AudioFormat::Error;
}

template <class DataType>
int32_t Audio<DataType>::fourBytesToInt(vector<uint8_t> const& source, int startIndex, Endianness endianness) {
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
int16_t Audio<DataType>::twoBytesToInt(vector<uint8_t> const& source, int startIndex, Endianness endianness) {
    int16_t result = 0;

    if (endianness == Endianness::LittleEndian) {
        result = (source[startIndex + 1] << 8) | source[startIndex];
    } else {
        result = (source[startIndex] << 8) | source[startIndex + 1];
    }

    return result;
}

template <class DataType>
int Audio<DataType>::getIndexOfString(vector<uint8_t> const& source, string const& stringToSearchFor) {
    int index = -1;
    int stringLength = static_cast<int>(stringToSearchFor.length());

    for (int i = 0; i < static_cast<int>(source.size() - stringLength); i++) {
        string section(source.cbegin() + i, source.cbegin() + i + stringLength);

        if (section == stringToSearchFor) {
            index = i;
            break;
        }
    }

    return index;
}

template <class DataType>
DataType Audio<DataType>::sixteenBitIntToSample(int16_t sample) {
    return static_cast<DataType>(sample) / static_cast<DataType>(32768.);
}

template <class DataType>
int16_t Audio<DataType>::sampleToSixteenBitInt(DataType sample) {
    sample = clamp(sample, -1., 1.);
    return static_cast<int16_t>(sample * 32767.);
}

template <class DataType>
uint8_t Audio<DataType>::sampleToSingleByte(DataType sample) {
    sample = clamp(sample, -1., 1.);
    sample = (sample + 1.) / 2.;
    return static_cast<uint8_t>(sample * 255.);
}

template <class DataType>
DataType Audio<DataType>::singleByteToSample(uint8_t sample) {
    return static_cast<DataType>(sample - 128) / static_cast<DataType>(128.);
}

template <class DataType>
DataType Audio<DataType>::clamp(DataType value, DataType minValue, DataType maxValue) {
    value = min(value, maxValue);
    value = max(value, minValue);
    return value;
}

//===========================================================
template class Audio<float>;
template class Audio<double>;

}  // namespace alba::AprgAudio
