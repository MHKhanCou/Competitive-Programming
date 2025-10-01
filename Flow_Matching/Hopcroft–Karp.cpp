// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

struct HopcroftKarp {
    static const int INF = 1e9;
    int n, m;                        // left size = n, right size = m
    vector<int> l, r, d;             // l[u] = matched right vertex, r[v] = matched left vertex
    vector<vector<int>> g;           // adjacency from left to right (shifted by n)

    HopcroftKarp(int _n = 0, int _m = 0) {
        init(_n, _m);
    }

    void init(int _n, int _m) {
        n = _n; m = _m;
        int sz = n + m + 1;
        g.assign(sz, {});
        l.assign(sz, 0);
        r.assign(sz, 0);
        d.assign(sz, 0);
    }

    // add edge from left u (1..n) to right v (1..m)
    void add_edge(int u, int v) {
        g[u].push_back(v + n); // shift right side by n
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!l[u]) {
                d[u] = 0;
                q.push(u);
            } else d[u] = INF;
        }
        d[0] = INF;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v : g[u]) {
                if (d[r[v]] == INF) {
                    d[r[v]] = d[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return d[0] != INF;
    }

    bool dfs(int u) {
        if (!u) return true;
        for (auto v : g[u]) {
            if (d[r[v]] == d[u] + 1 && dfs(r[v])) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        d[u] = INF;
        return false;
    }

    int maximum_matching() {
        int ans = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (!l[u] && dfs(u)) ans++;
            }
        }
        return ans;
    }
};

int main() {
    mh
    int n, m, q;
    cin >> n >> m >> q;
    HopcroftKarp M(n, m);
    while (q--) {
        int u, v;
        cin >> u >> v;
        M.add_edge(u, v);
    }
    cout << M.maximum_matching() << nl;
    return 0;
}

//https://www.spoj.com/problems/MATCHING/
