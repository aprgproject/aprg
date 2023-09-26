// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_PracticeRound_P1_NumberGuessing.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <iostream>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <cstdint>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2019_PracticeRound_P1_NumberGuessing {

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

void runTestCase(int const) {
    long long minimumValue = 0;
    long long maximumValue = 0;
    my_cin >> minimumValue >> maximumValue;
    int numberOfTries = 0;
    my_cin >> numberOfTries;
    long long lowValue = minimumValue + 1;
    long long highValue = maximumValue;
    while (true) {
        long long m = (lowValue + highValue) / 2;
        my_cout << m << endl;
        string s;
        my_cin >> s;
        if (s == "CORRECT") {
            break;
        }
        if (s == "TOO_SMALL") {
            lowValue = m + 1;
        } else {
            highValue = m - 1;
        }
    }
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2019_PracticeRound_P1_NumberGuessing

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
