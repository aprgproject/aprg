#pragma once

#include <mutex>

namespace alba {

class AlbaOldRandomizer {
public:
    AlbaOldRandomizer();
    static void resetRandomSeed();
    static int getRandomIntegerInUniformDistribution(int const minimum, int const maximum);
    static double getRandomFloatingValueInUniformDistribution(double const minimum, double const maximum);

private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::mutex m_mutex;
};

}  // namespace alba
