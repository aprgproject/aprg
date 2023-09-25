#include <Common/Debug/AlbaExit.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaExitTest, DISABLED_ExitMacrosWorks) {
    // too slow
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto,concurrency-mt-unsafe,cert-err33-c,cppcoreguidelines-pro-type-vararg,hicpp-vararg)
    EXPECT_EXIT(ALBA_SUCCESSFUL_EXIT, ::testing::ExitedWithCode(0), string());

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto,concurrency-mt-unsafe,cert-err33-c,cppcoreguidelines-pro-type-vararg,hicpp-vararg)
    EXPECT_DEATH(ALBA_FAILURE_EXIT, string());

    // EXPECT_EXIT(ALBA_SUCCESSFUL_QUICK_EXIT, ::testing::ExitedWithCode(0), string());
    // EXPECT_DEATH(ALBA_FAILURE_QUICK_EXIT, string());
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto,cert-err33-c,cppcoreguidelines-pro-type-vararg,hicpp-vararg)
    EXPECT_DEATH(ALBA_ABORT, string());

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto,cert-err33-c,cppcoreguidelines-pro-type-vararg,hicpp-vararg)
    EXPECT_DEATH(ALBA_TERMINATE, string());
}

}  // namespace alba
