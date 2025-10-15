// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define vi vector<int>
#define nl '\n'
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define srt(v) sort(v.begin(), v.end());
#define coutv(v) for (auto x : v) cout << x << ' '; cout << nl;

const int N = 1e5 + 5;
const ll INF = 1e17;

/*
  🧠 Topological Sorting — Kahn’s Algorithm
  ----------------------------------------
  ✔ Used for Directed Acyclic Graphs (DAG)
  ✔ Orders nodes so that for every edge u -> v, u appears before v
  ✔ Common Uses:
      - Dependency resolution (build order, courses, tasks)
      - Longest/shortest path in DAG
      - Detect cycles in directed graphs
  ✔ Time Complexity: O(n + m)
*/

vi g[N];  // adjacency list

void solve() {
    int n, m;
    cin >> n >> m;

    vi in_deg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        in_deg[b]++;
    }

    // --- Kahn’s Algorithm ---
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (in_deg[i] == 0) q.push(i);

    vi topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.pb(u);
        for (int v : g[u]) {
            if (--in_deg[v] == 0)
                q.push(v);
        }
    }

    // Check if cycle exists
    if ((int)topo.size() < n) {
        cout << "IMPOSSIBLE" << nl;
        for (int i = 1; i <= n; ++i) g[i].clear();
        return;
    }

    /*
       🧩 Example Use: Longest Path in DAG (CSES Longest Flight Route)
       --------------------------------------------------------------
       dp[v] = max path length from node 1 → v
       par[v] = previous node on the best path (for reconstruction)
    */
    vi dp(n + 1, -1), par(n + 1, 0);
    dp[1] = 1;

    for (int u : topo) {
        if (dp[u] < 0) continue;
        for (int v : g[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                par[v] = u;
            }
        }
    }

    // reconstruct path to node n
    vi path;
    int cur = n;
    while (cur) {
        path.pb(cur);
        cur = par[cur];
    }
    reverse(path.begin(), path.end());

    if (path[0] != 1) cout << "IMPOSSIBLE" << nl;
    else {
        cout << path.size() << nl;
        coutv(path);
    }

    for (int i = 1; i <= n; ++i) g[i].clear();
}

int main() {
    mh
    solve();
    return 0;
}

//https://cses.fi/problemset/task/1680
