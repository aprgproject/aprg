#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaStreamBitWriterTest, WriteBoolDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeBoolData(false);
    writer.writeBoolData(false);
    writer.writeBoolData(true);
    writer.writeBoolData(true);
    writer.writeBoolData(false);
    writer.writeBoolData(false);
    writer.writeBoolData(true);
    writer.writeBoolData(true);

    EXPECT_EQ(R"(3)", testStream.str());
}

TEST(AlbaStreamBitWriterTest, WriteCharDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeCharData('.');
    writer.writeCharData('/');
    writer.writeCharData('*');

    EXPECT_EQ(R"(./*)", testStream.str());
}

TEST(AlbaStreamBitWriterTest, WriteStringDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeStringData("A1BA");

    EXPECT_EQ(R"(A1BA)", testStream.str());
}

TEST(AlbaStreamBitWriterTest, WriteHexDigitDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeHexDigitData("A1BAA1BA");

    EXPECT_EQ(R"(A1BAA1BA)", getHexEquivalentOfCharacters(testStream.str()));
}

TEST(AlbaStreamBitWriterTest, WriteNumberDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeNumberData<uint32_t>(AlbaStreamBitEndianType::BigEndian, 0x0102'0304);
    writer.writeNumberData<uint32_t>(AlbaStreamBitEndianType::LittleEndian, 0x0102'0304);

    EXPECT_EQ(R"(0102030404030201)", getHexEquivalentOfCharacters(testStream.str()));
}

TEST(AlbaStreamBitWriterTest, WriteBigEndianNumberDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeBigEndianNumberData<uint32_t>(0x0102'0304);

    EXPECT_EQ(R"(01020304)", getHexEquivalentOfCharacters(testStream.str()));
}

TEST(AlbaStreamBitWriterTest, WriteLittleEndianNumberDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);

    writer.writeLittleEndianNumberData<uint32_t>(0x0102'0304);

    EXPECT_EQ(R"(04030201)", getHexEquivalentOfCharacters(testStream.str()));
}

TEST(AlbaStreamBitWriterTest, WriteBitsetDataWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);
    bitset<32U> bitsetToWrite(0x1234'5678);

    writer.writeBitsetData<32U>(bitsetToWrite, 15U, 22U);

    EXPECT_EQ(R"(16)", getHexEquivalentOfCharacters(testStream.str()));
}

TEST(AlbaStreamBitWriterTest, FlushWorks) {
    stringstream testStream;
    AlbaStreamBitWriter writer(testStream);
    writer.writeBoolData(true);

    writer.flush();

    EXPECT_EQ(R"(80)", getHexEquivalentOfCharacters(testStream.str()));
}

}  // namespace alba
