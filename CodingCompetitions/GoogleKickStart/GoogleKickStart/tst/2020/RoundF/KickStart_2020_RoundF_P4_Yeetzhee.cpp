// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundF_P4_Yeetzhee.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <algorithm>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2020_RoundF_P4_Yeetzhee {

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

vector<int> need;
int n, m;
map<vector<int>, double> mp;
double iv;

void runTestCase(int const testCaseNumber) {
    mp.clear();
    my_cin >> n >> m;
    iv = 1 / static_cast<double>(m);
    int k = 0;
    my_cin >> k;
    need.resize(k);
    for (int i = 0; i < k; ++i) {
        my_cin >> need[i];
    }
    sort(need.begin(), need.end());
    vector<int> go;
    my_cout.precision(10);
    my_cout << "Case #" << testCaseNumber << ": " << fixed << ans(go, 0) << '\n';
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

double ans(vector<int> a, int const tot) {
    sort(a.begin(), a.end());
    if (!in(a)) {
        return 1e18;
    }
    // NOLINTNEXTLINE(readability-container-contains)
    if (mp.contains(a)) {
        return mp[a];
    }
    if (tot == n) {
        return 0;
    }
    vector<pair<int, double> > go;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        a[i]++;
        double ret = ans(a, tot + 1);
        go.emplace_back(1, ret);
        a[i]--;
    }
    if (static_cast<int>(a.size()) != m) {
        auto b = a;
        b.insert(b.begin(), 1);
        go.emplace_back(m - static_cast<int>(a.size()), ans(b, tot + 1));
    }
    auto check = [&](double const x) {
        double sum = 1;
        for (auto c : go) {
            sum += min(c.second, x) * c.first / m;
        }
        return sum <= x;
    };
    double sum = 1;
    for (auto c : go) {
        sum += c.second * c.first / m;
    }
    double vl = 0;
    double vr = sum;
    int it = 100;
    while ((it--) != 0) {
        double vm = (vl + vr) / 2;
        if (check(vm)) {
            vr = vm;
        } else {
            vl = vm;
        }
    }
    return mp[a] = vr;
}

bool in(vector<int> a) {
    if (a.size() > need.size()) {
        return false;
    }
    int ptr = static_cast<int>(need.size()) - static_cast<int>(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        if (ptr == static_cast<int>(need.size())) {
            return true;
        }
        if (a[i] <= need[ptr]) {
            ++ptr;
        }
    }
    return (ptr == static_cast<int>(need.size()));
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2020_RoundF_P4_Yeetzhee

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
