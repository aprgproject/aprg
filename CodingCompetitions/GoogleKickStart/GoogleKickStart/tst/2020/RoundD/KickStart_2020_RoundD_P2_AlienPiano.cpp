// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundD_P2_AlienPiano.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <algorithm>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2020_RoundD_P2_AlienPiano {

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
    int N = 0;
    my_cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        my_cin >> A[i];
    }
    array<int, 4> dp{0, 0, 0, 0};
    for (int i = 1; i < N; ++i) {
        array<int, 4> ndp{N + 1, N + 1, N + 1, N + 1};
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                ndp[y] = min(ndp[y], dp[x] + static_cast<int>(compare(x, y) != compare(A[i - 1], A[i])));
            }
        }
        dp = ndp;
    }

    int ans = std::min({dp[0], dp[1], dp[2], dp[3]});

    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

int signum(int const a) { return static_cast<int>(a > 0) - static_cast<int>(a < 0); }
int compare(int const a, int const b) { return signum(a - b); }
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2020_RoundD_P2_AlienPiano

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
