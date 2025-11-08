// In the name of Allah, the Most Merciful, the Most Gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

// ====================== CONFIG ======================
const int MAXB = 20;          // default max bits (change per problem)
int k = MAXB;                 // active bit-width (set from input)
int LIM = 1 << MAXB;         // active limit (set to 1<<k in main)
// ====================================================

// ====================== HELPERS ======================
inline int popcnt(int x) { return __builtin_popcount(x); }

// compute C(n, r) without modulo for small r (r <= 5 etc.)
inline ll C_small(ll n, int r) {
    if (n < r) return 0;
    if (r == 0) return 1;
    if (r == 1) return n;
    if (r == 2) return n * (n - 1) / 2;
    if (r == 3) return n * (n - 1) * (n - 2) / 6;
    // fallback (rare): generic multiplicative
    ll num = 1, den = 1;
    for (int i = 0; i < r; ++i) {
        num *= (n - i);
        den *= (i + 1);
    }
    return num / den;
}

// Modular helpers if needed (uncomment to use)
// const ll MOD = 1000000007LL;
// ll modpow(ll a, ll e, ll m=MOD){ ll r=1; a%=m; while(e){ if(e&1) r=r*a%m; a=a*a%m; e>>=1;} return r; }
// ll inv(ll x){ return modpow(x, MOD-2); }
// ll C_small_mod(ll n, int r){ if(n<r) return 0; /*use factorials if r large*/ }

// ====================== TRANSFORMS ======================
// inplace OR-zeta (subset -> superset): F[mask] = sum_{sub ⊆ mask} freq[sub]
void sos_or_zeta(vector<ll> &F, int kk) {
    int lim = 1 << kk;
    for (int i = 0; i < kk; ++i) {
        for (int mask = 0; mask < lim; ++mask) {
            if ((mask & (1 << i)) == 0) F[mask | (1 << i)] += F[mask];
        }
    }
}

// inplace OR-mobius (inverse of zeta above): recovers exact values
void sos_or_mobius(vector<ll> &F, int kk) {
    int lim = 1 << kk;
    for (int i = 0; i < kk; ++i) {
        for (int mask = 0; mask < lim; ++mask) {
            if ((mask & (1 << i)) == 0) F[mask | (1 << i)] -= F[mask];
        }
    }
}

// inplace AND-zeta (superset -> subset): G[mask] = sum_{sup ⊇ mask} freq[sup]
void sos_and_zeta(vector<ll> &G, int kk) {
    int lim = 1 << kk;
    for (int i = 0; i < kk; ++i) {
        for (int mask = 0; mask < lim; ++mask) {
            if ((mask & (1 << i)) != 0) G[mask ^ (1 << i)] += G[mask];
        }
    }
}

// inplace AND-mobius (inverse of AND-zeta)
void sos_and_mobius(vector<ll> &G, int kk) {
    int lim = 1 << kk;
    for (int i = 0; i < kk; ++i) {
        for (int mask = 0; mask < lim; ++mask) {
            if ((mask & (1 << i)) != 0) G[mask ^ (1 << i)] -= G[mask];
        }
    }
}

// XOR Fast Walsh–Hadamard Transform (inplace); invert with inverse=true (for real conv use scaling)
void fwt_xor(vector<ll> &a, int kk, bool inverse = false) {
    int lim = 1 << kk;
    for (int len = 1; len < lim; len <<= 1) {
        for (int i = 0; i < lim; i += (len << 1)) {
            for (int j = 0; j < len; ++j) {
                ll u = a[i + j];
                ll v = a[i + j + len];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }
    if (inverse) {
        for (int i = 0; i < lim; ++i) a[i] /= lim; // integer division only if values divisible; otherwise use modular inverse
    }
}

// ====================== ITERATORS ======================
// iterate ALL non-empty submasks s of mask m:
// for (int s = m; s; s = (s - 1) & m) { ... }  (add s=0 separately if needed)

// iterate all supermasks sup such that m ⊆ sup ⊆ (1<<k)-1
// use: for (int t = inv; ; t = (t - 1) & inv) { int sup = t | m; if (t==0) break; }
void iterate_supermasks_example(int m, int kk) {
    int inv = ((1 << kk) - 1) ^ m;
    for (int t = inv; ; t = (t - 1) & inv) {
        int sup = t | m;
        // process sup
        if (t == 0) break;
    }
}

// ====================== USAGE EXAMPLES ======================
// Example: Given input counts cnt[mask] (exact masks), count number of unordered triples (i<j<k)
// whose OR is exactly 'mask' (no modulo).
// Steps:
//  1) F = cnt (ll vector)
//  2) sos_or_zeta(F) -> F[mask] = number of elements with value subset of mask
//  3) A[mask] = C(F[mask], 3)    (triples with OR ⊆ mask)
//  4) sos_or_mobius(A) -> A[mask] = # triples with OR == mask

int main() {
    mh;
    // Example driver: read N, K, N strings, then M queries (same format you used earlier)
    int n;
    if (!(cin >> n >> k)) return 0;
    cin >> ws;
    LIM = 1 << k;

    vector<int> a(n);
    vector<ll> cnt(LIM, 0);   // cnt[mask] = number of students whose exact mask == mask
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int num = 0;
        for (int j = 0; j < k; ++j) if (s[j] == '1') num |= (1 << j);
        a[i] = num;
        cnt[num]++;
    }

    // Make a working copy for OR-zeta
    vector<ll> F = cnt;
    sos_or_zeta(F, k);   // F[mask] = number of students with mask ⊆ mask

    // compute number of unordered triples with OR ⊆ mask
    vector<ll> A(LIM, 0);
    for (int mask = 0; mask < LIM; ++mask) {
        A[mask] = C_small(F[mask], 3); // change r here for different team sizes
    }

    // invert to get exact OR == mask
    sos_or_mobius(A, k); // now A[mask] = number of triples with OR exactly mask

    // answer queries
    int q; cin >> q;
    while (q--) {
        string s; cin >> s;
        int num = 0;
        for (int j = 0; j < k; ++j) if (s[j] == '1') num |= (1 << j);
        cout << A[num] << nl;
    }

    // ---------- Additional short examples / snippets ----------
    // To compute number of pairs (i<j) with OR exactly mask, use C_small(F[mask], 2) etc.
    // To compute number of ordered triples by OR convolution: do OR-zeta on cnt, cube pointwise, invert.

    return 0;
}
