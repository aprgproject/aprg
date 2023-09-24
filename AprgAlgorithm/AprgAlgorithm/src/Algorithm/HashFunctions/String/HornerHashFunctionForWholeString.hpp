#pragma once

#include <numeric>
#include <string>
#include <vector>

namespace alba::algorithm {

template <typename HashValue>
class HornerHashFunctionForWholeString {
    // horners rule: continuously mod to keep the value
public:
    HornerHashFunctionForWholeString(HashValue const radix, HashValue const largeRandomPrime)
        : m_radix(radix), m_largeRandomPrime(largeRandomPrime) {}
    [[nodiscard]] HashValue getHashCode(std::string const& stringToHash) const { return getFinalHPart(stringToHash); }

private:
    [[nodiscard]] HashValue getFinalHPart(std::string const& stringToHash) const {
        // Based from formula (check substrings file notes): h[k] = (h[k-1]*A + s[k]) mod B
        // linear time
        return accumulate(
            stringToHash.cbegin(), stringToHash.cend(), HashValue(0),
            [&](HashValue const partialResult, char const character) {
                return (partialResult * m_radix + character) % m_largeRandomPrime;
            });
    }

    HashValue m_radix;
    HashValue m_largeRandomPrime;
};

}  // namespace alba::algorithm
