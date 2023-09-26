#include <Fake/FakeNames.hpp>

#include <iostream>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <cstdint>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#include "KickStart_2020_RoundH_P2_BoringNumbers.hpp"

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
using namespace alba;
using namespace std;

namespace KickStart_2020_RoundH_P2_BoringNumbers {

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

void runTestCase(int const testCaseNumber) {
    int64_t L = 0;
    int64_t R = 0;
    my_cin >> L >> R;
    ++R;
    bool parity = false;
    int64_t coeff = 1;
    int64_t ans = 0;
    while (L < R) {
        auto is_good = [&](int64_t const v) {
            bool d = (v % 2) != 0;
            while (v > 0) {
                if (v % 2 != static_cast<long>(d)) {
                    return false;
                }
                d = !d;
                v /= 10;
            }
            return static_cast<int>(d) == 0;
        };
        while (L < R && L % 10 != 0) {
            if (is_good(L)) {
                ans += coeff;
            }
            ++L;
        }
        while (L < R && R % 10 != 0) {
            --R;
            if (is_good(R)) {
                ans += coeff;
            }
        }

        if (L == R) {
            break;
        }

        L /= 10;
        R /= 10;

        coeff *= 5;
        parity = !parity;
    }
    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2020_RoundH_P2_BoringNumbers

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
