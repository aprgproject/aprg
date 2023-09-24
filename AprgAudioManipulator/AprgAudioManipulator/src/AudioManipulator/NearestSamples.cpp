#include "NearestSamples.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <set>

using namespace std;

namespace alba::AprgAudio {

NearestSamples::NearestSamples(Samples const& samples) : m_samples(samples) { saveToValuesToIndexes(); }

Indexes NearestSamples::getNearestSamplesIndexes(double const value, int const recommendedNumberOfSamples) {
    Indexes result;
    pair<ValuesToIndexes::const_iterator, ValuesToIndexes::const_iterator> const lowerAndUpperIterator(
        containerHelper::getLowerAndUpperConstIteratorsInMap(m_valuesToIndexes, value));

    set<int> indexesInOrder;
    for (auto it = lowerAndUpperIterator.first; it != lowerAndUpperIterator.second; ++it) {
        indexesInOrder.emplace(it->second);
    }
    auto itLower = lowerAndUpperIterator.first;
    auto itUpper = lowerAndUpperIterator.second;
    while (static_cast<int>(indexesInOrder.size()) < recommendedNumberOfSamples &&
           itLower != m_valuesToIndexes.cbegin() && itUpper != m_valuesToIndexes.cend()) {
        if (itLower != m_valuesToIndexes.cbegin()) {
            indexesInOrder.emplace(itLower->second);
            --itLower;
        }
        indexesInOrder.emplace(itUpper->second);
        ++itUpper;
    }
    result.reserve(result.size());
    copy(indexesInOrder.cbegin(), indexesInOrder.cend(), back_inserter(result));
    return result;
}

void NearestSamples::saveToValuesToIndexes() {
    int i = 0;
    for (double const sample : m_samples) {
        m_valuesToIndexes.emplace(sample, i++);
    }
}

}  // namespace alba::AprgAudio
