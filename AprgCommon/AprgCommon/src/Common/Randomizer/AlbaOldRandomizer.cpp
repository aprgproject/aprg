#include "AlbaOldRandomizer.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

using namespace std;

namespace alba {

AlbaOldRandomizer::AlbaOldRandomizer() { resetRandomSeed(); }

void AlbaOldRandomizer::resetRandomSeed() {
    lock_guard<mutex> lock(m_mutex);
    srand(getCurrentDateTime().getMicroSeconds());  // srand is not thread safe
}

double AlbaOldRandomizer::getRandomFloatingValueInUniformDistribution(double const minimum, double const maximum) {
    lock_guard<mutex> lock(m_mutex);
    double delta = maximum - minimum;
    // NOLINTNEXTLINE(cert-msc30-c,cert-msc50-cpp,concurrency-mt-unsafe)
    double randomValue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    return minimum + randomValue * delta;
}

int AlbaOldRandomizer::getRandomIntegerInUniformDistribution(int const minimum, int const maximum) {
    lock_guard<mutex> lock(m_mutex);
    int deltaInclusive = maximum - minimum + 1;
    // NOLINTNEXTLINE(cert-msc30-c,cert-msc50-cpp,concurrency-mt-unsafe)
    double randomValue = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1);
    return static_cast<int>(minimum + randomValue * deltaInclusive);  // implicit floor conversion from double to int
    // randomValue looks like this:
    // | 0-value possibility | 1-value possibility | ... | RAND_MAX-1 value possibility | RAND_MAX value possibility |
    // randomValue with delta inclusive looks like this:
    // | minimum value possibility | minimum+1 value possibility | ... |  maximum value possibility |
    // so we get the floor to have the final value
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
mutex AlbaOldRandomizer::m_mutex;

}  // namespace alba

// Notes on rand():
// It is implementation-defined whether rand() is thread-safe.
// Output has equal possibility between 0 to RAND_MAX (inclusive)

// Source: https://en.cppreference.com/w/cpp/numeric/random/rand
// There are no guarantees as to the quality of the random sequence produced.
// In the past, some implementations of rand() have had serious shortcomings in the randomness,
// distribution and period of the sequence produced (in one well-known example,
// the low-order bit simply alternated between 1 and 0 between calls).

// The function rand() is not recommended for serious random-number generation needs.
// It is recommended to use C++11's random number generation facilities to replace rand(). (since C++11)

// Problem: non uniformity on rand() values
// Problem: Dont use modulo because its slow and might ruin uniformity
// Problem: encoding in double is losing information

// The implementation above (floating point operations) doesn't guarantee uniformity too.
// -> Stephan T Lavavej said:
// ---> A floating-point variation is "Hilariously non-uniform."
// ---> "It's the pigeonhole principle: if you have 2^32 pigeons,"
// -----> " you can't put them in [specific size] pigeonholes without having more pigeons in some holes than others."
