#include <Algorithm/Stack/FixedSizeStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba::algorithm {

namespace {
using StackForTest = FixedSizeStack<int, 10>;
}  // namespace

TEST(FixedSizeStackTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<StackForTest>(); }
TEST(FixedSizeStackTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<StackForTest>(); }
TEST(FixedSizeStackTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<StackForTest>(); }
TEST(FixedSizeStackTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<StackForTest>(); }
TEST(FixedSizeStackTest, PushWorks) { testPushWithInt<StackForTest>(); }
TEST(FixedSizeStackTest, PopWorks) { testPopWithInt<StackForTest>(); }

// disabled because it takes too long
TEST(FixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) {
    testPopAssertionWhenEmptyWithInt<StackForTest>();
}

// disabled because it takes too long
TEST(FixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize) {
    StackForTest stack;

    for (int i = 0; i < 10; ++i) {
        stack.push(i);
    }
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto,cert-err33-c,cppcoreguidelines-pro-type-vararg,hicpp-vararg)
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

}  // namespace alba::algorithm
