#include <Statistics/DataStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

TEST(DataStatisticsTest, StatisticsCanBeClearedAfterCalculation) {
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSample const expectedSum{0, 0, 0};
    LocalSample const expectedMean{0, 0, 0};
    LocalSample const expectedSampleVariance{0, 0, 0};
    LocalSample const expectedSampleStandardDeviation{0, 0, 0};
    LocalSample const expectedPopulationVariance{0, 0, 0};
    LocalSample const expectedPopulationStandardDeviation{0, 0, 0};
    double const expectedDispersion(0);

    LocalSamples samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalStatistics localStatistics(samples);
    LocalSample sum(localStatistics.getSum());
    LocalSample mean(localStatistics.getMean());
    LocalSample sampleVariance(localStatistics.getSampleVariance());
    LocalSample sampleStandardDeviation(localStatistics.getSampleStandardDeviation());
    LocalSample populationVariance(localStatistics.getPopulationVariance());
    LocalSample populationStandardDeviation(localStatistics.getPopulationStandardDeviation());
    samples.clear();
    localStatistics.clearPreviousCalculations();
    sum = localStatistics.getSum();
    mean = localStatistics.getMean();
    sampleVariance = localStatistics.getSampleVariance();
    sampleStandardDeviation = localStatistics.getSampleStandardDeviation();
    populationVariance = localStatistics.getPopulationVariance();
    populationStandardDeviation = localStatistics.getPopulationStandardDeviation();
    double const dispersion = localStatistics.getDispersionAroundTheCentroid();

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

TEST(DataStatisticsTest, StatisticsAreCorrectWhenSamplesAreEmpty) {
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSample const expectedSum{0, 0, 0};
    LocalSample const expectedMean{0, 0, 0};
    LocalSample const expectedSampleVariance{0, 0, 0};
    LocalSample const expectedSampleStandardDeviation{0, 0, 0};
    LocalSample const expectedPopulationVariance{0, 0, 0};
    LocalSample const expectedPopulationStandardDeviation{0, 0, 0};
    double const expectedDispersion(0);

    LocalSamples const samples;
    LocalStatistics localStatistics(samples);
    LocalSample const sum(localStatistics.getSum());
    LocalSample const mean(localStatistics.getMean());
    LocalSample const sampleVariance(localStatistics.getSampleVariance());
    LocalSample const sampleStandardDeviation(localStatistics.getSampleStandardDeviation());
    LocalSample const populationVariance(localStatistics.getPopulationVariance());
    LocalSample const populationStandardDeviation(localStatistics.getPopulationStandardDeviation());
    double const dispersion(localStatistics.getDispersionAroundTheCentroid());

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

TEST(DataStatisticsTest, StatisticsAreCorrect) {
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSample const expectedSum{6, 60, 600};
    LocalSample const expectedMean{2, 20, 200};
    LocalSample const expectedSampleVariance{1, 100, 10000};
    LocalSample const expectedSampleStandardDeviation{1, 10, 100};
    LocalSample const expectedPopulationVariance{0.66666666666666662966, 66.666666666666671404, 6666.6666666666669698};
    LocalSample const expectedPopulationStandardDeviation{
        0.81649658092772603446, 8.1649658092772607887, 81.64965809277261144};
    double const expectedDispersion(100.50373127401788);

    LocalSamples const samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalStatistics localStatistics(samples);
    LocalSample const sum(localStatistics.getSum());
    LocalSample const mean(localStatistics.getMean());
    LocalSample const sampleVariance(localStatistics.getSampleVariance());
    LocalSample const sampleStandardDeviation(localStatistics.getSampleStandardDeviation());
    LocalSample const populationVariance(localStatistics.getPopulationVariance());
    LocalSample const populationStandardDeviation(localStatistics.getPopulationStandardDeviation());
    double const dispersion(localStatistics.getDispersionAroundTheCentroid());

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

}  // namespace alba
