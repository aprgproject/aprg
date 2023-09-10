#include <Common/Container/AlbaAny.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaAnyTest, DefaultConstructorWorks) {
    AlbaAny const any;

    EXPECT_FALSE(any.hasContent());
}

TEST(AlbaAnyTest, CopyConstructorWorks) {
    AlbaAny const originalAny(1234);

    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    AlbaAny const copiedAny(originalAny);

    EXPECT_EQ(1234, originalAny.getContentAs<int>());
    EXPECT_EQ(1234, copiedAny.getContentAs<int>());
}

TEST(AlbaAnyTest, CopyAssignmentWorks) {
    AlbaAny const originalAny(1234);

    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    AlbaAny const copiedAny = originalAny;

    EXPECT_EQ(1234, originalAny.getContentAs<int>());
    EXPECT_EQ(1234, copiedAny.getContentAs<int>());
}

TEST(AlbaAnyTest, MoveConstructorWorks) {
    AlbaAny originalAny(1234);

    AlbaAny const movedAny(std::move(originalAny));

    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move,hicpp-invalid-access-moved)
    EXPECT_FALSE(originalAny.hasContent());
    EXPECT_EQ(1234, movedAny.getContentAs<int>());
}

TEST(AlbaAnyTest, MoveAssignmentWorks) {
    AlbaAny originalAny(1234);

    AlbaAny const assignedAny = std::move(originalAny);

    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move,hicpp-invalid-access-moved)
    EXPECT_FALSE(originalAny.hasContent());
    EXPECT_EQ(1234, assignedAny.getContentAs<int>());
}

TEST(AlbaAnyTest, BoolOperatorWorks) {
    AlbaAny const emptyAny;
    AlbaAny const nonEmptyAny(1234);

    EXPECT_FALSE(static_cast<bool>(emptyAny));
    EXPECT_TRUE(static_cast<bool>(nonEmptyAny));
}

TEST(AlbaAnyTest, HasContentWorks) {
    AlbaAny const emptyAny;
    AlbaAny const nonEmptyAny(1234);

    EXPECT_FALSE(emptyAny.hasContent());
    EXPECT_TRUE(nonEmptyAny.hasContent());
}

TEST(AlbaAnyTest, GetContentAsWorks) {
    AlbaAny const any(1234);

    EXPECT_EQ(1234, any.getContentAs<int>());
}

TEST(AlbaAnyTest, GetContentReferenceAsWorks) {
    AlbaAny any(1234);

    int& intReference = any.getContentReferenceAs<int>();
    intReference = 5678;

    EXPECT_EQ(5678, any.getContentAs<int>());
}

TEST(AlbaAnyTest, SaveContentWorks) {
    AlbaAny any(1234);

    any.saveContent<int>(5678);

    EXPECT_EQ(5678, any.getContentAs<int>());
}

TEST(AlbaAnyTest, ClearWorks) {
    AlbaAny any(1234);

    any.clear();

    EXPECT_FALSE(any.hasContent());
}

TEST(AlbaAnyTest, OutputStreamOperatorWorks) {
    stringstream testStream;
    AlbaAny const any(1234);

    testStream << any;

    EXPECT_EQ(
        "hasContent: 1\n savedMemory: Decimal values: {210, 4, 0, 0, }\nHexadecimal values: {d2, 4, 0, 0, }\n",
        testStream.str());
}

}  // namespace alba
