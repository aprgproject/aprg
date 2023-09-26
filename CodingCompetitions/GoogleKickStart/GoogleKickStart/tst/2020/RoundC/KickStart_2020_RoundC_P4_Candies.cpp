// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// #define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundC_P4_Candies.hpp"

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

namespace KickStart_2020_RoundC_P4_Candies {

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif
#define ll long long
#define ar array
const int mxN = 2e5;

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

struct ft {
    void upd(int const i, ll const x) {
        for (++i; i <= n; i += i & -i) {
            a[i] += x;
        }
    }

    ll qry(int const i) {
        ll r = 0;
        for (; i != 0; i -= i & -i) {
            r += a[i];
        }
        return r;
    }

    ll a[mxN + 1];

}

int n,
    q;
ll a[mxN];
f0[2], f1[2];

void app(int const i, ll const x) {
    f0[i & 1].upd(i, x - a[i]);
    f1[i & 1].upd(i, i * (x - a[i]));
    f0[(i & 1) ^ 1].upd(i, -(x - a[i]));
    f1[(i & 1) ^ 1].upd(i, -i * (x - a[i]));
    a[i] = x;
}

void runTestCase(int const testCaseNumber) {
    my_cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        ll a_temp = 0;
        my_cin >> a_temp;
        app(i, a_temp);
    }
    ll ans = 0;
    while ((q--) != 0) {
        char qt = 0;
        my_cin >> qt;
        if (qt == 'Q') {
            int l = 0;
            int r = 0;
            my_cin >> l >> r, --l, --r;
            ll s = f1[l & 1].qry(r + 1) - f1[l & 1].qry(l) - (l - 1) * (f0[l & 1].qry(r + 1) - f0[l & 1].qry(l));
            ans += s;
            // cout << s << "\n";
        } else {
            int i = 0;
            int x = 0;
            my_cin >> i >> x, --i;
            app(i, x);
        }
    }
    for (int i = 0; i < n; ++i) {
        app(i, 0);
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

}  // namespace KickStart_2020_RoundC_P4_Candies

#undef FOR_SUBMISSION

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
