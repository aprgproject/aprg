#include <Audio/Audio.hpp>
#include <AudioTests/ExpectedValues/aiff_stereo_16bit_44100.hpp>
#include <AudioTests/ExpectedValues/aiff_stereo_16bit_48000.hpp>
#include <AudioTests/ExpectedValues/aiff_stereo_24bit_44100.hpp>
#include <AudioTests/ExpectedValues/aiff_stereo_24bit_48000.hpp>
#include <AudioTests/ExpectedValues/aiff_stereo_8bit_44100.hpp>
#include <AudioTests/ExpectedValues/aiff_stereo_8bit_48000.hpp>
#include <AudioTests/ExpectedValues/wav_mono_16bit_44100.hpp>
#include <AudioTests/ExpectedValues/wav_mono_16bit_48000.hpp>
#include <AudioTests/ExpectedValues/wav_stereo_16bit_44100.hpp>
#include <AudioTests/ExpectedValues/wav_stereo_16bit_48000.hpp>
#include <AudioTests/ExpectedValues/wav_stereo_24bit_44100.hpp>
#include <AudioTests/ExpectedValues/wav_stereo_24bit_48000.hpp>
#include <AudioTests/ExpectedValues/wav_stereo_8bit_44100.hpp>
#include <AudioTests/ExpectedValues/wav_stereo_8bit_48000.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba::AprgAudio {

TEST(AiffLoadingTests, DISABLED_StereoWith8BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\aiff_stereo_8bit_44100.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), aiff_stereo_8bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_8bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_8bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), aiff_stereo_8bit_44100::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(aiff_stereo_8bit_44100::testBuffer.size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                aiff_stereo_8bit_44100::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(AiffLoadingTests, DISABLED_StereoWith16BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\aiff_stereo_16bit_44100.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), aiff_stereo_16bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_16bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_16bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), aiff_stereo_16bit_44100::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(aiff_stereo_16bit_44100::testBuffer.size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                aiff_stereo_16bit_44100::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(AiffLoadingTests, DISABLED_StereoWith24BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\aiff_stereo_24bit_44100.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), aiff_stereo_24bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_24bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_24bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), aiff_stereo_24bit_44100::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(aiff_stereo_24bit_44100::testBuffer.size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                aiff_stereo_24bit_44100::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(AiffLoadingTests, DISABLED_StereoWith8BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\aiff_stereo_8bit_48000.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), aiff_stereo_8bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_8bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_8bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), aiff_stereo_8bit_48000::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(aiff_stereo_8bit_48000::testBuffer.size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                aiff_stereo_8bit_48000::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(AiffLoadingTests, DISABLED_StereoWith16BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\aiff_stereo_16bit_48000.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), aiff_stereo_16bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_16bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_16bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), aiff_stereo_16bit_48000::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(aiff_stereo_16bit_48000::testBuffer.size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                aiff_stereo_16bit_48000::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(AiffLoadingTests, DISABLED_StereoWith24BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\aiff_stereo_24bit_48000.aif)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), aiff_stereo_24bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), aiff_stereo_24bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), aiff_stereo_24bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), aiff_stereo_24bit_48000::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(aiff_stereo_24bit_48000::testBuffer.size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                aiff_stereo_24bit_48000::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WritingTest, DISABLED_WriteFromCopiedSampleBuffer) {
    Audio<float> audioFile1;
    Audio<float> audioFile2;

    bool isLoadingSuccessful =
        audioFile1.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_16bit_44100.wav)");
    ASSERT_TRUE(isLoadingSuccessful);

    audioFile2.setAudioBuffer(audioFile1.samples);
    audioFile2.save("audio-write-tests/copied_audio_file.aif", AudioFormat::Aiff);
}

TEST(WavLoadingTests, DISABLED_StereoWith8BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_8bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_stereo_8bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_8bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_8bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), static_cast<int>(wav_stereo_8bit_44100::testBuffer.size()));

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_stereo_8bit_44100::testBuffer[0].size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                wav_stereo_8bit_44100::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_StereoWith16BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_16bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_stereo_16bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_16bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_16bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), static_cast<int>(wav_stereo_16bit_44100::testBuffer.size()));

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_stereo_16bit_44100::testBuffer[0].size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                wav_stereo_16bit_44100::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_StereoWith24BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_24bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_stereo_24bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_24bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_24bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), static_cast<int>(wav_stereo_24bit_44100::testBuffer.size()));

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_stereo_24bit_44100::testBuffer[0].size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                wav_stereo_24bit_44100::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_MonoWith16BitWithSampleRate44100) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_mono_16bit_44100.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_mono_16bit_44100::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_mono_16bit_44100::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_mono_16bit_44100::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), wav_mono_16bit_44100::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_mono_16bit_44100::testBuffer.size()); ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex], wav_mono_16bit_44100::testBuffer[bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_StereoWith8BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_8bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_stereo_8bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_8bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_8bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), static_cast<int>(wav_stereo_8bit_48000::testBuffer.size()));

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_stereo_8bit_48000::testBuffer[0].size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                wav_stereo_8bit_48000::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_StereoWith16BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_16bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_stereo_16bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_16bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_16bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), static_cast<int>(wav_stereo_16bit_48000::testBuffer.size()));

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_stereo_16bit_48000::testBuffer[0].size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                wav_stereo_16bit_48000::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_StereoWith24BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_stereo_24bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_stereo_24bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_stereo_24bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_stereo_24bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), static_cast<int>(wav_stereo_24bit_48000::testBuffer.size()));

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_stereo_24bit_48000::testBuffer[0].size());
         ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex],
                wav_stereo_24bit_48000::testBuffer[channelIndex][bufferIndex]));
        }
    }
}

TEST(WavLoadingTests, DISABLED_MonoWith16BitWithSampleRate48000) {
    Audio<double> audioFile;
    bool isLoadingSuccessful =
        audioFile.load(APRG_DIR R"(\AprgAudio\FilesForTests\ActualAudioFiles\wav_mono_16bit_48000.wav)");

    ASSERT_TRUE(isLoadingSuccessful);
    EXPECT_EQ(audioFile.getNumberOfSamplesPerChannel(), wav_mono_16bit_48000::numberOfSamplesPerChannel);
    EXPECT_EQ(audioFile.getBitDepth(), wav_mono_16bit_48000::bitDepth);
    EXPECT_EQ(audioFile.getSampleRate(), wav_mono_16bit_48000::sampleRate);
    EXPECT_EQ(audioFile.getNumberOfChannels(), wav_mono_16bit_48000::numberOfChannels);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(wav_mono_16bit_48000::testBuffer.size()); ++bufferIndex) {
        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            EXPECT_TRUE(isAlmostEqual(
                audioFile.samples[channelIndex][bufferIndex], wav_mono_16bit_48000::testBuffer[bufferIndex]));
        }
    }
}

bool writeTest(int numberOfChannels, int sampleRate, int bitDepth, AudioFormat format) {
    auto sampleRateAsFloat = static_cast<float>(sampleRate);

    Audio<float> audioFile;

    audioFile.setAudioBufferSize(numberOfChannels, sampleRate * 4);

    for (int bufferIndex = 0; bufferIndex < static_cast<int>(audioFile.getNumberOfSamplesPerChannel()); ++bufferIndex) {
        auto sample = static_cast<float>(sin(2.0 * getPi() * bufferIndex / sampleRateAsFloat * 440.0));

        for (int channelIndex = 0; channelIndex < static_cast<int>(audioFile.getNumberOfChannels()); ++channelIndex) {
            audioFile.samples[channelIndex][bufferIndex] = static_cast<float>(sample * 0.5);
        }
    }

    audioFile.setSampleRate(sampleRate);
    audioFile.setBitDepth(bitDepth);

    std::string numberOfChannelsAsString = numberOfChannels == 1 ? "mono" : "stereo";
    std::string bitDepthAsString = std::to_string(bitDepth);
    std::string sampleRateAsString = std::to_string(sampleRate);

    if (format == AudioFormat::Wave) {
        return audioFile.save(
            APRG_DIR R"(\AprgAudio\FilesForTests\WrittenAudioFiles\)" + numberOfChannelsAsString + "_" +
            sampleRateAsString + "_" + bitDepthAsString + "bit" + ".wav");
    }
    if (format == AudioFormat::Aiff) {
        return audioFile.save(
            APRG_DIR R"(\AprgAudio\FilesForTests\WrittenAudioFiles\)" + numberOfChannelsAsString + "_" +
            sampleRateAsString + "_" + bitDepthAsString + "bit" + ".aif");
    }

    return false;
}

TEST(WritingTest, DISABLED_WriteSineToneToManyFormats) {
    std::vector<int> sampleRates = {22050, 44100, 48000, 96000};
    std::vector<int> bitDepths = {8, 16, 24};
    std::vector<int> numberOfChannels = {1, 2};
    std::vector<AudioFormat> audioFormats = {AudioFormat::Wave, AudioFormat::Aiff};

    for (auto& sampleRate : sampleRates) {
        for (auto& bitDepth : bitDepths) {
            for (auto& channels : numberOfChannels) {
                for (auto& format : audioFormats) {
                    EXPECT_TRUE(writeTest(channels, sampleRate, bitDepth, format));
                }
            }
        }
    }
}

}  // namespace alba::AprgAudio
