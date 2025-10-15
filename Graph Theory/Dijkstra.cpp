// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pll pair<ll, ll>
#define vc vector
#define vl vc<ll>
#define vi vc<int>
#define nl '\n'
#define mh ios::sync_with_stdio(false);cin.tie(0);
#define F first
#define S second
const ll INF = 1e17;
const int N = 2e5 + 5;

// --- Dijkstra’s Algorithm Template ---
// Supports both normal shortest path and K-shortest paths (CSES Flight Routes)

int n, m, k;
vc<pll> g[N];
vc<vl> dis;

void dijkstra(int s) {
    dis.assign(n + 1, vl(k, INF));
    priority_queue<pll, vc<pll>, greater<pll>> pq;

    dis[s][0] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (w > dis[u][k - 1]) continue; // already worse than kth shortest

        for (auto e : g[u]) {
            ll v = e.F, x = e.S;
            ll nw = w + x;

            if (nw < dis[v][k - 1]) {
                dis[v][k - 1] = nw;
                sort(dis[v].begin(), dis[v].end());
                pq.push({nw, v});
            }
        }
    }
}

int main() {
    mh
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        ll a, b, w;
        cin >> a >> b >> w;
        g[a].pb({b, w});
    }

    dijkstra(1);

    for (int i = 0; i < k; i++) {
        cout << dis[n][i] << " \n"[i == k - 1];
    }
    return 0;
}

//https://cses.fi/problemset/task/1196
