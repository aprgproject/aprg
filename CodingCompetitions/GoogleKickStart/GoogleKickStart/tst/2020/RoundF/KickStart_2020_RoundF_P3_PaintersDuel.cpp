// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundF_P3_PaintersDuel.hpp"

#include <Fake/FakeNames.hpp>
#endif
#include <iostream>
#include <map>
#include <vector>

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#include <cstdint>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION

using namespace alba;

#endif

namespace KickStart_2020_RoundF_P3_PaintersDuel {

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

vector<int> g[36];
map<ll, int> ok[10][36][36][2];
int id[20][20];

// NOLINTEND(readability-use-anyofallof)
void dfs(int const v, ll &mask, ll const ban) {
    if (((mask >> v) & 1) != 0) {
        return;
    }
    mask |= (1LL << v);
    for (int x : g[v]) {
        if (((ban >> x) & 1) != 0) {
            continue;
        }
        dfs(x, mask, ban);
    }
}

void runTestCase(int const testCaseNumber) {
    int s = 0;
    int ra = 0;
    int pa = 0;
    int rb = 0;
    int pb = 0;
    int c = 0;
    my_cin >> s >> ra >> pa >> rb >> pb >> c;
    --ra, pa--, rb--, --pb;
    for (int i = 0; i < s * s; ++i) {
        g[i].clear();
    }
    int ptr = 0;
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < 2 * i + 1; ++j) {
            id[i][j] = ptr++;
        }
    }
    auto add_edge = [&](int const ra, int const pa, int const rb, int const pb) {
        int u = id[ra][pa];
        int v = id[rb][pb];
        g[u].push_back(v);
        g[v].push_back(u);
    };
    for (int i = 0; i < s; ++i) {
        for (int j = 1; j < 2 * i + 1; ++j) {
            add_edge(i, j, i, j - 1);
        }
        for (int j = 0; j < 2 * i + 1; ++j) {
            if (i + 1 < s && j % 2 == 0) {
                add_edge(i, j, i + 1, j + 1);
            }
        }
    }
    ll ban = 0;
    for (int i = 0; i < c; ++i) {
        int r = 0;
        int p = 0;
        my_cin >> r >> p;
        --r, --p;
        ban |= (1LL << id[r][p]);
    }
    int a = id[ra][pa];
    int b = id[rb][pb];
    ban |= (1LL << a);
    ban |= (1LL << b);
    my_cout << "Case #" << testCaseNumber << ": " << calc(s, ban, a, b, 0) << "\n";
}

void runAllTestCases() {
    int numberOfTestCases = 0;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber) {
        runTestCase(testCaseNumber);
    }
}

int calc(int const s, ll const ban, int const a, int const b, int const who) {
    ll msk = 0LL;
    dfs(a, msk, ban);
    dfs(b, msk, ban);
    for (int i = 0; i < s * s; ++i) {
        if (((msk >> i) & 1) != 0) {
            continue;
        }
        ban |= (1LL << i);
    }
    // NOLINTNEXTLINE(readability-container-contains)
    if (ok[s][a][b][who].contains(ban)) {
        return ok[s][a][b][who][ban];
    }
    if (!can_move(ban, a) && !can_move(ban, b)) {
        return 0;
    }
    if (who == 0) {
        if (can_move(ban, a)) {
            int score = -1e9;
            for (int x : g[a]) {
                if (((ban >> x) & 1) != 0) {
                    continue;
                }
                ll go = ban | (1LL << x);
                score = max(score, calc(s, go, x, b, 1) + 1);
            }
            return ok[s][a][b][who][ban] = score;
        }
        return ok[s][a][b][who][ban] = calc(s, ban, a, b, 1);
    }
    if (can_move(ban, b)) {
        int score = 1e9;
        for (int x : g[b]) {
            if (((ban >> x) & 1) != 0) {
                continue;
            }
            ll go = ban | (1LL << x);
            score = min(score, calc(s, go, a, x, 0) - 1);
        }
        return ok[s][a][b][who][ban] = score;
    }
    return ok[s][a][b][who][ban] = calc(s, ban, a, b, 0);
}

// NOLINTBEGIN(readability-use-anyofallof)
bool can_move(ll const ban, int const a) {
    for (int x : g[a]) {
        if (((ban >> x) & 1) != 0) {
            continue;
        }
        return true;
    }
    return false;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~

}  // namespace KickStart_2020_RoundF_P3_PaintersDuel

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
