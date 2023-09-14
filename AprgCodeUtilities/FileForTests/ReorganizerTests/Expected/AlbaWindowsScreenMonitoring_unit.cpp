#include <gtest/gtest.h>
#include <iostream>
#include <ScreenMonitoring/AlbaWindowsScreenMonitoring.hpp>
#include <windows.h>

using namespace std;

namespace alba {

TEST(AlbaWindowsScreenMonitoringTest, GetPixelAtWorks) {
    AlbaWindowsScreenMonitoring screenMonitoring;
    screenMonitoring.capturePixelsFromScreen();

    EXPECT_NE(0U, screenMonitoring.getColorAt(100, 100));
}

}  // namespace alba
