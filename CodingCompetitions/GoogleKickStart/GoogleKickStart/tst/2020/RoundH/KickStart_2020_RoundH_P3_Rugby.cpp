#include <Fake/FakeNames.hpp>

#include <cstdint>
#include <iostream>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <algorithm>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#include "KickStart_2020_RoundH_P3_Rugby.hpp"

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
using namespace alba;
using namespace std;

namespace KickStart_2020_RoundH_P3_Rugby {

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
    vector<int64_t> X(N);
    vector<int64_t> Y(N);
    for (int i = 0; i < N; ++i) {
        my_cin >> X[i] >> Y[i];
    }
    sort(X.begin(), X.end());
    for (int i = 0; i < N; ++i) {
        X[i] -= i;
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    int64_t mx = X[N / 2];
    int64_t my = Y[N / 2];
    int64_t ans = 0;
    for (auto& x : X) {
        ans += abs(x - mx);
    }
    for (auto& y : Y) {
        ans += abs(y - my);
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

}  // namespace KickStart_2020_RoundH_P3_Rugby

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
