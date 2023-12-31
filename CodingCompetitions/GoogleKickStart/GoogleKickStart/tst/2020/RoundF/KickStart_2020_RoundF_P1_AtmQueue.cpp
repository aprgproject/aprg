// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundF_P1_AtmQueue.hpp"

#include <Fake/FakeNames.hpp>
#endif
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

namespace KickStart_2020_RoundF_P1_AtmQueue {

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
    int n = 0;
    int x = 0;
    my_cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        my_cin >> a[i];
    }
    vector<pair<int, int> > q;
    q.reserve(n);
    for (int i = 0; i < n; ++i) {
        q.emplace_back((a[i] + x - 1) / x, i);
    }
    sort(q.begin(), q.end());
    vector<int> ord(n);
    for (int i = 0; i < n; ++i) {
        ord[i] = q[i].second;
    }
    my_cout << "Case #" << testCaseNumber << ":";
    for (int answer : ord) {
        my_cout << ' ' << answer + 1;
    }
    my_cout << '\n';
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2020_RoundF_P1_AtmQueue

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
