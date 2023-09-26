// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundC_P2_StableWall.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <cstdint>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2020_RoundC_P2_StableWall {

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif
const int mxN = 30;

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

int n, m;
string s[mxN], ans;
vector<int> adj[26];
bool bad;
bool vis[26], act[26];

void dfs(int const u) {
    act[u] = true;
    vis[u] = true;
    for (int v : adj[u]) {
        if (act[v] && ((v ^ u) != 0)) {
            bad = true;
        } else {
            if (!vis[v]) {
                dfs(v);
            }
        }
    }
    act[u] = false;
    ans += static_cast<char>(u + 'A');
}

void runTestCase(int const testCaseNumber) {
    my_cin >> n >> m;
    set<char> t;
    for (int i = 0; i < n; ++i) {
        my_cin >> s[i];
        for (char c : s[i]) {
            t.insert(c);
        }
        if (i != 0) {
            for (int j = 0; j < m; ++j) {
                adj[s[i - 1][j] - 'A'].push_back(s[i][j] - 'A');
            }
        }
    }
    memset(vis, 0, 26);
    memset(act, 0, 26);
    ans = "";
    bad = false;
    for (char c : t) {
        if (!vis[c - 'A']) {
            dfs(c - 'A');
        }
    }
    if (bad) {
        ans = "-1";
    }
    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';

    for (int i = 0; i < 26; ++i) {
        adj[i].clear();
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

}  // namespace KickStart_2020_RoundC_P2_StableWall

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
