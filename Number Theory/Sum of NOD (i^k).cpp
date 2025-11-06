// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define pb push_back
#define vl vector<ll>
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define tst int t; cin >> t; while(t--)
#define nl '\n'
#define cinv(v) for(auto &it:v) cin >> it;
#define coutv(v) for(auto it:v) cout << it << ' '; cout << nl;

const int N = 1e6 + 7;

ll n, k;                 // n = limit, k = exponent for i^k
int lim, tot, p[N];      // primes & limit
ll f1[N], f2[N];         // prefix sums for small and large values

// Preprocessing: build f1/f2 for Min_25 sieve
inline void init() {
    lim = sqrt(n);
    tot = 0;

    // Initialize f1 (small) and f2 (large)
    for (int i = 1; i <= lim; ++i) f1[i] = i - 1, f2[i] = n / i - 1;

    // Sieve over primes
    for (int pp = 2; pp <= lim; ++pp) {
        if (f1[pp] != f1[pp - 1]) {  // pp is prime
            p[++tot] = pp;
            ll t = f1[pp - 1];

            // Update large values
            for (int i = 1, li = lim / pp; i <= li; ++i)
                f2[i] -= f2[i * pp] - t;
            for (int i = lim / pp + 1, li = min(n / pp / pp, (ll)lim); i <= li; ++i)
                f2[i] -= f1[n / i / pp] - t;

            // Update small values
            if ((ll)pp * pp <= lim)
                for (int i = lim, li = pp * pp; i >= li; --i)
                    f1[i] -= f1[i / pp] - t;
        }
    }
}

// Recursive function to compute sum_{i=1..n} d(i^k)
ll solve(ll nn, int i) {
    if (nn == 0) return 0;

    ll g = (nn <= lim) ? f1[nn] : f2[n / nn];
    ll ans = (k + 1) * (g - (i == 1 ? 0 : f1[p[i - 1]]));

    for (int j = i; j <= tot; ++j) {
        ll pp = p[j];
        if (pp * pp > nn) break;

        for (ll now = pp, t = 1; now <= nn; now *= pp, ++t) {
            if (now > ULLONG_MAX / pp) break;
            ll nxt = now * pp;

            if (nxt <= nn) ans += (k * t + 1) * solve(nn / now, j + 1);
            if (t > 1) ans += (k * t + 1);  // contribution for cofactor == 1
        }
    }
    return ans;
}

int main() {
    mh
    tst {
        cin >> n;
        k = 2;  // read n and exponent k
        init();         // build prefix sums
        cout << solve(n, 1) + 1 << nl;  // +1 for f(1)
    }
}
