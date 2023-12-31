#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <CrnccIdMapping.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, DISABLED_PerformanceAddTestWithRandomValues) {
    constexpr unsigned int initialSize = 1000000;

    AlbaUniformNonDeterministicRandomizer<unsigned int> crnccIdRandomizer(1, 65536);
    AlbaUniformNonDeterministicRandomizer<unsigned int> nbccIdRandomizer(1, 2500);
    vector<unsigned int> crnccIds;
    for (unsigned int currentSize = 0; currentSize < initialSize; ++currentSize) {
        TCRNCCommunicationContextId const crnccId = crnccIdRandomizer.getRandomValue();
        TNbccId const nbccId = nbccIdRandomizer.getRandomValue();
        crnccIds.emplace_back(crnccId);
        setCrnccIdMapping(crnccId, nbccId);
    }
}

TEST(SampleTest, DISABLED_PerformanceAccessTestWithRandomValues) {
    constexpr unsigned int initialSize = 2500;
    constexpr unsigned int accessIterations = 1000000;

    AlbaUniformNonDeterministicRandomizer<unsigned int> crnccIdRandomizer(1, 65536);
    AlbaUniformNonDeterministicRandomizer<unsigned int> nbccIdRandomizer(1, 2500);
    vector<unsigned int> crnccIds;
    for (unsigned int currentSize = 0; currentSize < initialSize; ++currentSize) {
        TCRNCCommunicationContextId const crnccId = crnccIdRandomizer.getRandomValue();
        TNbccId const nbccId = nbccIdRandomizer.getRandomValue();
        crnccIds.emplace_back(crnccId);
        setCrnccIdMapping(crnccId, nbccId);
    }

    for (unsigned int iteration = 0; iteration < accessIterations; ++iteration) {
        TCRNCCommunicationContextId const crnccIdAccess = crnccIds[crnccIdRandomizer.getRandomValue()];
        TNbccId const nbccIdAccess = getNbccIdFromCrnccId(crnccIdAccess);
        setCrnccIdMapping(crnccIdAccess, nbccIdAccess);
    }
}

}  // namespace alba
