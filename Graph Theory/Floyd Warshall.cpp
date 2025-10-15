// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define nl '\n'
const ll INF = 1e15;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, INF));

    for (ll i = 1; i <= n; i++) d[i][i] = 0;

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        d[a][b] = min(d[a][b], c);
        d[b][a] = min(d[b][a], c); // undirected
    }

    for (ll k = 1; k <= n; k++)
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= n; j++)
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    // detect negative cycle
    for (ll i = 1; i <= n; i++)
        if (d[i][i] < 0) {
            cout << "Negative cycle detected" << nl;
            return 0;
        }

    // print all-pairs distances
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (d[i][j] == INF) cout << "INF ";
            else cout << d[i][j] << " ";
        }
        cout << nl;
    }
}
