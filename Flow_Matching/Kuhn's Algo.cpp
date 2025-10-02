// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

const int N = 4005;

struct Kuhn {
    int n, m;
    vector<vector<int>> g;   // adjacency: left -> right (both ids passed as in your main)
    vector<int> matchR;      // matchR[v] = left vertex matched to v (or -1)
    vector<int> vis;

    Kuhn(int _n = 0, int _m = 0) { init(_n, _m); }

    void init(int _n, int _m) {
        n = _n; m = _m;
        g.assign(n + 1, {});
        // allocate match array large enough to hold right ids (mirror Hopcroft's combined size)
        matchR.assign(n + m + 5, -1);
    }

    void add_edge(int u, int v) { // u and v are used exactly as in your main
        if (u >= 1 && u <= n) g[u].push_back(v);
    }

    bool dfs(int u) {
        if (vis[u]) return false;
        vis[u] = 1;
        for (int v : g[u]) {
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int maximum_matching() {
        int ans = 0;
        for (int u = 1; u <= n; ++u) {
            vis.assign(n + 1, 0);
            if (dfs(u)) ++ans;
        }
        return ans;
    }
};

int main() {
    mh
    int n, m, node = 1;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n ; ++i) cin >> a[i];
    vector<pair<int, int>> g[n + 1];
    for (int i = 1; i <= n ; ++i) {
        int x = a[i];
        for (int j = 2; j * j <= x; ++j)
        {
            if (x % j) continue;
            while (x % j == 0) {
                x /= j;
                g[i].push_back({node++, j});
            }
        }
        if (x > 1) g[i].push_back({node++, x});
    }

    Kuhn M(N, N);
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (v & 1) swap(v, u);
        for (auto x : g[u])
        {
            for (auto y : g[v]) {
                if (x.second == y.second) M.add_edge(x.first, y.first);
            }
        }
    }
    cout << M.maximum_matching() << nl;
    return 0;
}

//https://codeforces.com/contest/499/problem/E
