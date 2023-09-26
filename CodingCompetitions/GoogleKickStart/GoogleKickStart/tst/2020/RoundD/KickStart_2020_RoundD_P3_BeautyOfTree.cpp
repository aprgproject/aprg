// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundD_P3_BeautyOfTree.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <cstdint>
#include <iostream>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <array>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2020_RoundD_P3_BeautyOfTree {

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
    array<int, 2> A{};
    my_cin >> A[0] >> A[1];

    vector<array<int, 20>> par(N);
    vector<int> depth(N);
    for (int i = 1; i < N; ++i) {
        my_cin >> par[i][0];
        par[i][0]--;
        depth[i] = depth[par[i][0]] + 1;
        for (int z = 0; par[i][z] != 0; ++z) {
            par[i][z + 1] = par[par[i][z]][z];
        }
    }

    double ans = 0;
    vector<array<int, 2>> cnt(N);
    for (int i = N - 1; i >= 0; --i) {
        for (int z = 0; z < 2; ++z) {
            cnt[i][z]++;
            if (depth[i] < A[z]) {
                continue;
            }
            int cur = i;
            for (int l = 0, v = A[z]; v != 0; v >>= 1, ++l) {
                if ((v & 1) != 0) {
                    cur = par[cur][l];
                }
            }
            cnt[cur][z] += cnt[i][z];
        }
        double va = static_cast<double>(cnt[i][0]) / static_cast<double>(N);
        double vb = static_cast<double>(cnt[i][1]) / static_cast<double>(N);
        ans += va + vb - va * vb;
    }

    my_cout << "Case #" << testCaseNumber << ": ";
    my_cout.precision(10);
    my_cout << fixed << ans << '\n';
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2020_RoundD_P3_BeautyOfTree

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
