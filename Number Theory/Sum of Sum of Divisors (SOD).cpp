// In the name of Allah
#include <bits/stdc++.h>
using namespace std;

#define mhkhan ios::sync_with_stdio(false); cin.tie(0);
typedef long long ll;

const ll MOD = 1e9+7;
const ll INV2 = 5e8+4; // Modular inverse of 2 modulo MOD

int main() {
    mhkhan;
    
    ll n;
    cin >> n;
    ll ans = 0;

    // Loop over groups where n/i is constant
    for (ll i = 1, j; i <= n; i = j + 1) {
        ll value = n / i;
        j = n / value;

        value %= MOD;
        ll len = (j - i + 1) % MOD;

        // Compute sum of the range i..j modulo MOD
        ll x = (len * ((i - 1) % MOD)) % MOD;
        ll y = (len * ((len + 1) % MOD)) % MOD;
        x = (x + y * INV2 % MOD) % MOD;

        ans = (ans + x * value % MOD) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
