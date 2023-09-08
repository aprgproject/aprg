#pragma once

#include <AudioManipulator/CommonTypes.hpp>

namespace alba::AprgAudio {

class NearestSamples {
public:
    explicit NearestSamples(Samples const& samples);
    Indexes getNearestSamplesIndexes(double const value, int const recommendedNumberOfSamples);

private:
    void saveToValuesToIndexes();
    Samples const& m_samples;
    ValuesToIndexes m_valuesToIndexes;
};

}  // namespace alba::AprgAudio
