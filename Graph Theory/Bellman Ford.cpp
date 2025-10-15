// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
#define pb push_back
#define nl '\n'
#define mh ios::sync_with_stdio(false); cin.tie(0);

const ll inf = 1e18;

ll n, m;
struct E { ll a, b, c; };
vector<E> e;       // edge list
vl d, p;           // distance and parent
ll x = -1;         // used to detect last relaxed vertex

bool bellman_ford() {
    d.assign(n + 1, 0);
    p.assign(n + 1, -1);
    x = -1;

    // relax edges n times
    for (ll i = 1; i <= n; i++) {
        x = -1;
        for (auto &ed : e) {
            if (d[ed.a] + ed.c < d[ed.b]) {
                d[ed.b] = max(-inf, d[ed.a] + ed.c);
                p[ed.b] = ed.a;
                x = ed.b; // remember last relaxed node
            }
        }
    }

    return (x != -1); // true if a negative cycle exists
}

int main() {
    mh;
    cin >> n >> m;
    e.resize(m);
    for (ll i = 0; i < m; i++)
        cin >> e[i].a >> e[i].b >> e[i].c;

    if (!bellman_ford()) {
        cout << "NO" << nl;
        return 0;
    }

    cout << "YES" << nl;

    // ensure x is inside the cycle
    for (ll i = 1; i <= n; i++) x = p[x];

    // reconstruct the cycle
    vector<ll> cyc;
    for (ll v = x;; v = p[v]) {
        cyc.pb(v);
        if (v == x && cyc.size() > 1) break;
    }
    reverse(cyc.begin(), cyc.end());

    for (auto v : cyc) cout << v << " ";
    cout << nl;
}

//https://cses.fi/problemset/task/1197
