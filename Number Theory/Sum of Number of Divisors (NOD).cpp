// In the name of Allah, the most merciful, the most gracious
/*
    Author: Mehedi Hasan Khan
    Problem: Sum of Number of Divisors (NOD)
    Description:
        Given n, compute the sum of the number of divisors of all numbers from 1 to n:
            S(n) = sum_{i=1}^{n} NOD(i)
        Efficient approach: use the "range grouping" trick where floor(n/d) is constant.
    Complexity: O(sqrt(n))
    Notes:
        - Supports n up to 1e12
        - Modular arithmetic can be added if needed
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define vl vector<ll>
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define tst int t;cin>>t;while(t--)
#define nl '\n'
#define cinv(v) for(auto &it:v) cin>>it;
#define coutv(v) for(auto it:v) cout<<it<<' '; cout<<nl;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i,a,b) for (int i=a; i <= b; ++i)
#define rev(i, n) for (int i=(n)-1; i >= 0; --i)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pii pair<int,int>
#define F first
#define S second
#define ld long double
#define no cout << "No\n"
#define yes cout << "Yes\n"
#define dbg(x) cerr << #x << " = " << x << '\n'

const ll INF = LLONG_MAX;
const ll MOD = 1e9+7;

// Function to compute sum of number of divisors up to n
ll sum_nod(ll n) {
    ll ans = 0;
    // Iterate over all ranges where floor(n/d) is constant
    for (ll i = 1, j; i <= n; i = j + 1) {
        ll q = n / i;      // q = floor(n / i)
        j = n / q;         // maximum i in this range with same q
        ans += q * (j - i + 1); // contribution of all d in [i,j]
    }
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    ll ans = sum_nod(n);
    cout << ans << nl;
}

int main() {
    mh
    // Uncomment below for multiple test cases
    // tst { solve(); }
    
    // Single test case
    solve();
    
    return 0;
}
