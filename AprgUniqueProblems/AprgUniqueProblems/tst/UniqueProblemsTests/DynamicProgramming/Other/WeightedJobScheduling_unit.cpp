#include <UniqueProblems/DynamicProgramming/Other/WeightedJobScheduling.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(WeightedJobSchedulingTest, GetMaxProfitWorksOnEmpty) {
    WeightedJobScheduling const queryForTest({});

    EXPECT_EQ(0, queryForTest.getMaxProfitByMonitoringTimeStampsUsingIterativeDP());
    EXPECT_EQ(0, queryForTest.getMaxProfitByMonitoringJobsUsingIterativeDP());
}

TEST(WeightedJobSchedulingTest, GetMaxProfitWorksOnExample1) {
    WeightedJobScheduling const queryForTest({{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}});

    EXPECT_EQ(250, queryForTest.getMaxProfitByMonitoringTimeStampsUsingIterativeDP());
    EXPECT_EQ(250, queryForTest.getMaxProfitByMonitoringJobsUsingIterativeDP());
}

}  // namespace alba
