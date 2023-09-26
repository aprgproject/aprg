#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <gtest/gtest.h>

#include <array>

using namespace std;

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
namespace alba {

TEST(AlbaMemoryBufferTest, OperatorBoolWorks) {
    int input = 11111111;
    AlbaMemoryBuffer const buffer1(static_cast<void*>(&input), sizeof(input));
    AlbaMemoryBuffer const buffer2;

    EXPECT_TRUE(buffer1);
    EXPECT_FALSE(buffer2);
}

TEST(AlbaMemoryBufferTest, OperatorSubscriptWorksForReading) {
    int input = 0x12345678;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    EXPECT_TRUE(buffer);
    EXPECT_EQ(0x78, buffer[0]);
    EXPECT_EQ(0x56, buffer[1]);
    EXPECT_EQ(0x34, buffer[2]);
    EXPECT_EQ(0x12, buffer[3]);
}

TEST(AlbaMemoryBufferTest, OperatorSubscriptWorksForWriting) {
    int input = 0x12345678;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    buffer[1] = 0xAA;

    EXPECT_TRUE(buffer);
    EXPECT_EQ(0x78, buffer[0]);
    EXPECT_EQ(0xAA, buffer[1]);
    EXPECT_EQ(0x34, buffer[2]);
    EXPECT_EQ(0x12, buffer[3]);
}

TEST(AlbaMemoryBufferTest, OutputStreamOperatorWorks) {
    int input = 0x12345678;
    AlbaMemoryBuffer const buffer(static_cast<void*>(&input), sizeof(input));
    stringstream testStream;

    testStream << buffer;

    EXPECT_EQ("Decimal values: {120, 86, 52, 18, }\nHexadecimal values: {78, 56, 34, 12, }\n", testStream.str());
}

TEST(AlbaMemoryBufferTest, DefaultConstructorWorks) {
    AlbaMemoryBuffer const buffer;

    EXPECT_FALSE(buffer);
    EXPECT_EQ(0U, buffer.getSize());
}

TEST(AlbaMemoryBufferTest, ConstructorWithPointerAndSizeWorks) {
    int input = 11111111;

    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    int const output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_EQ(4U, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, CopyConstructorWorks) {
    int input = 11111111;
    AlbaMemoryBuffer const buffer1(static_cast<void*>(&input), sizeof(input));

    AlbaMemoryBuffer buffer2(buffer1);

    int const output = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, CopyAssignmentWorks) {
    int input = 11111111;
    AlbaMemoryBuffer const buffer1(static_cast<void*>(&input), sizeof(input));
    AlbaMemoryBuffer buffer2;

    buffer2 = buffer1;

    int const output = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, MoveConstructorWorks) {
    int input = 11111111;
    AlbaMemoryBuffer buffer1(static_cast<void*>(&input), sizeof(input));

    AlbaMemoryBuffer buffer2(std::move(buffer1));

    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move,hicpp-invalid-access-moved)
    EXPECT_EQ(0U, buffer1.getSize());
    int const output2 = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output2);
}

TEST(AlbaMemoryBufferTest, MoveAssignmentWorks) {
    int input = 11111111;
    AlbaMemoryBuffer buffer1(static_cast<void*>(&input), sizeof(input));
    AlbaMemoryBuffer buffer2;

    buffer2 = std::move(buffer1);

    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move,hicpp-invalid-access-moved)
    EXPECT_EQ(0U, buffer1.getSize());
    int const output2 = *reinterpret_cast<int*>(buffer2.getBufferPointer());
    EXPECT_TRUE(buffer2);
    EXPECT_EQ(4U, buffer2.getSize());
    EXPECT_EQ(input, output2);
}

TEST(AlbaMemoryBufferTest, ClearAndSetNewDataWorks) {
    int input = 11111111;
    int input2 = 22222222;
    AlbaMemoryBuffer buffer;

    buffer.clearAndSetNewData(static_cast<void*>(&input), sizeof(input));
    buffer.clearAndSetNewData(static_cast<void*>(&input2), sizeof(input2));

    int const output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_EQ(4U, buffer.getSize());
    EXPECT_EQ(input2, output);
}

TEST(AlbaMemoryBufferTest, ResizeWorksOnMakingTheBufferLarger) {
    int input = 11111111;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    buffer.resize(8);

    int const output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_EQ(8U, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, AddDataWorksOnPrimitiveTypes) {
    int input = 11111111;
    AlbaMemoryBuffer buffer;

    buffer.addData(static_cast<void*>(&input), sizeof(input));

    int const output = *reinterpret_cast<int*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_EQ(4U, buffer.getSize());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, AddDataWorksOnPodStructure) {
    AlbaMemoryBuffer buffer;
    struct Sample {
        bool param1;
        int param2;
        double param3;
    };
    Sample input{};
    input.param1 = true;
    input.param2 = 12345678;
    input.param3 = 1.234E56;

    buffer.addData(static_cast<void*>(&input), sizeof(input));

    Sample const output = *reinterpret_cast<Sample*>(buffer.getBufferPointer());
    EXPECT_TRUE(buffer);
    EXPECT_EQ(sizeof(Sample), buffer.getSize());
    EXPECT_EQ(input.param1, output.param1);
    EXPECT_EQ(input.param2, output.param2);
    EXPECT_EQ(input.param3, output.param3);
}

TEST(AlbaMemoryBufferTest, ResizeWorksOnMakingTheBufferSmaller) {
    int input = 0x12345678;
    AlbaMemoryBuffer buffer(static_cast<void*>(&input), sizeof(input));

    buffer.resize(3);

    EXPECT_TRUE(buffer);
    EXPECT_EQ(3U, buffer.getSize());
    EXPECT_EQ(0x78, buffer[0]);
    EXPECT_EQ(0x56, buffer[1]);
    EXPECT_EQ(0x34, buffer[2]);
}

TEST(AlbaMemoryBufferTest, ResizeWithAdditionalSizeAndReturnBeginOfAdditionalDataWorks) {
    AlbaMemoryBuffer buffer;
    array<uint8_t, 4> inputBuffer1 = {0x12, 0x34, 0x56, 0x78};
    array<uint8_t, 4> inputBuffer2 = {0x87, 0x65, 0x43, 0x21};

    memcpy(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(4), inputBuffer1.data(), 4);
    memcpy(buffer.resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(4), inputBuffer2.data(), 4);

    EXPECT_TRUE(buffer);
    EXPECT_EQ(8U, buffer.getSize());
    EXPECT_EQ(0x12U, buffer[0]);
    EXPECT_EQ(0x34U, buffer[1]);
    EXPECT_EQ(0x56U, buffer[2]);
    EXPECT_EQ(0x78U, buffer[3]);
    EXPECT_EQ(0x87U, buffer[4]);
    EXPECT_EQ(0x65U, buffer[5]);
    EXPECT_EQ(0x43U, buffer[6]);
    EXPECT_EQ(0x21U, buffer[7]);
}

TEST(AlbaMemoryBufferTest, SaveObjectWorksOnPrimitiveTypes) {
    AlbaMemoryBuffer buffer;
    constexpr int input = 0x12345678;

    buffer.saveObject<int>(input);

    int const& output(buffer.retrieveObjectAsReference<int>());
    EXPECT_EQ(input, buffer.retrieveObjectAsConstReference<int>());
    EXPECT_EQ(input, output);
}

TEST(AlbaMemoryBufferTest, SaveObjectWorksOnStandardLayoutTypes) {
    AlbaMemoryBuffer buffer;
    struct SampleStandardLayoutClass {
        bool field1;
        char field2;
        int field3;
    };
    SampleStandardLayoutClass standardLayoutInput{};
    standardLayoutInput.field1 = true;
    standardLayoutInput.field2 = 'A';
    standardLayoutInput.field3 = 0xA1BA;

    buffer.saveObject<SampleStandardLayoutClass>(standardLayoutInput);

    auto& output(buffer.retrieveObjectAsReference<SampleStandardLayoutClass>());
    EXPECT_TRUE(output.field1);
    EXPECT_EQ('A', output.field2);
    EXPECT_EQ(0xA1BA, output.field3);
}

}  // namespace alba

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
