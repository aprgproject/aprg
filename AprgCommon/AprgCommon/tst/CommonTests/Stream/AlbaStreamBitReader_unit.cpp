#include <Common/Stream/AlbaStreamBitReader.hpp>

#include <gtest/gtest.h>

#include <sstream>

using namespace std;

namespace alba {

TEST(AlbaStreamBitReaderTest, ReadStringDataWorks) {
    stringstream testStream;
    testStream << "./*";
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ("./", reader.readStringData(2));
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadWholeStreamAsStringDataWorks) {
    stringstream testStream;
    testStream << "./*";
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ("./*", reader.readWholeStreamAsStringData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadCharDataWorks) {
    stringstream testStream;
    testStream << "./*";
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ('.', reader.readCharData());
    EXPECT_EQ('/', reader.readCharData());
    EXPECT_EQ('*', reader.readCharData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadBoolDataWorks) {
    stringstream testStream;
    testStream << "A";
    AlbaStreamBitReader reader(testStream);

    EXPECT_FALSE(reader.readBoolData());
    EXPECT_TRUE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_TRUE(reader.readBoolData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadNumberDataWorks) {
    stringstream testStream;
    testStream.put(0x01);
    testStream.put(0x02);
    testStream.put(0x03);
    testStream.put(0x04);
    testStream.put(0x01);
    testStream.put(0x02);
    testStream.put(0x03);
    testStream.put(0x04);
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ(0x01020304U, reader.readNumberData<uint32_t>(AlbaStreamBitEndianType::BigEndian));
    EXPECT_EQ(0x04030201U, reader.readNumberData<uint32_t>(AlbaStreamBitEndianType::LittleEndian));
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadBigEndianNumberDataWorks) {
    stringstream testStream;
    testStream.put(0x01);
    testStream.put(0x02);
    testStream.put(0x03);
    testStream.put(0x04);
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ(0x01020304U, reader.readBigEndianNumberData<uint32_t>());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadLittleEndianNumberDataWorks) {
    stringstream testStream;
    testStream.put(0x01);
    testStream.put(0x02);
    testStream.put(0x03);
    testStream.put(0x04);
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ(0x04030201U, reader.readLittleEndianNumberData<uint32_t>());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, ReadBitsetDataWorks) {
    stringstream testStream;
    testStream.put(0x12);
    testStream.put(0x34);
    AlbaStreamBitReader reader(testStream);

    EXPECT_EQ(
        0x00000C48U,
        static_cast<uint32_t>(reader.readBitsetData<32>(0, 11).to_ulong()));  // swapped due to reversed index
    EXPECT_FALSE(reader.noRemainingBitsInBuffer());                           // 4Bits remaining
}

}  // namespace alba
