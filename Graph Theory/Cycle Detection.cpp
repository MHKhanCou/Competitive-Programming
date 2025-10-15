// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define vl vector<ll>
#define vi vector<int>
#define nl '\n'

const ll N = 2e5 + 5;

// --- Directed / Undirected Graph Cycle Finder ---
// Set `DIR = true` for directed graphs, `false` for undirected.
bool DIR = true;

vector<int> g[N], p(N);
int vis[N];
int cs = 0, ce = 0;

// vis[x] = 0 → unvisited
// vis[x] = 1 → visiting
// vis[x] = 2 → finished

bool dfs(int v, int pr = -1) {
    vis[v] = 1;
    for (auto &u : g[v]) {
        if (u == pr && !DIR) continue; // ignore parent edge in undirected
        if (!vis[u]) {
            p[u] = v;
            if (dfs(u, v)) return true;
        } else if (vis[u] == 1) {
            cs = u;
            ce = v;
            return true;
        }
    }
    vis[v] = 2;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        if (!DIR) g[b].pb(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i] && dfs(i)) break;
    }

    if (!cs) cout << "IMPOSSIBLE" << nl;
    else {
        vector<int> c;
        c.pb(cs);
        for (int v = ce; v != cs; v = p[v])
            c.pb(v);
        c.pb(cs);
        reverse(c.begin(), c.end());
        cout << c.size() << nl;
        for (auto &x : c) cout << x << " ";
        cout << nl;
    }
}

//https://cses.fi/problemset/task/1678 (dir = true)
//https://cses.fi/problemset/task/1669 (dir = false)
