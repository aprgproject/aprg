#pragma once

#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatistics.hpp>

#include <map>
#include <unordered_map>

namespace alba::TwoDimensionsStatistics {

using Sample = DataSample<2>;
using Statistics = DataStatistics<2>;
using Samples = std::vector<Sample>;
using ValueToSampleMultimap = std::multimap<double, Sample>;
using ValueToSamplePair = std::pair<double, Sample>;

struct LineModel {
    LineModel() : aCoefficient(0), bCoefficient(0), cCoefficient(0) {}
    LineModel(double const a, double const b, double const c) : aCoefficient(a), bCoefficient(b), cCoefficient(c) {}
    double aCoefficient;
    double bCoefficient;
    double cCoefficient;
};

LineModel calculateLineModelUsingLeastSquares(Samples const& samples);
ValueToSampleMultimap getSquareErrorToSampleMultimap(Samples& samples, LineModel const& lineModel);
double calculateSquareError(Sample const& sample, LineModel const& lineModel);

}  // namespace alba::TwoDimensionsStatistics
