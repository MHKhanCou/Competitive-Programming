// In the name of Allah, the most merciful, the most gracious
// Problem: https://www.spoj.com/problems/JHNSN/
// Johnson's Algorithm: All-pairs shortest path with negative edges
// Handles negative edges but NOT negative cycles (prints "no" if cycle exists)
// Complexity: O(N*M) for Bellman-Ford + O(N * (M log N)) for Dijkstra
// Works efficiently for sparse graphs (N ~ 1000, M ~ few thousands)

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,int>
#define INF (ll)1e18

struct Edge {
    int u, v;
    ll w;
    Edge() {}
    Edge(int _u, int _v, ll _w) : u(_u), v(_v), w(_w) {}
};

// Bellman-Ford from auxiliary source s
// Returns false if a negative cycle is detected
bool bellman_ford(int n, int s, vector<Edge>& edges, vector<ll>& dist) {
    dist.assign(n+1, INF);
    dist[s] = 0;

    for (int i = 0; i <= n; i++) {
        bool updated = false;
        for (auto &e : edges) {
            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
                if (i == n) return false; // Negative cycle found
            }
        }
        if (!updated) break;
    }
    return true;
}

// Dijkstra with reweighted edges
vector<ll> dijkstra(int n, int src, vector<Edge>& edges, vector<ll>& h) {
    vector<vector<pll>> g(n+1);
    for (auto &e : edges) {
        ll w = e.w + h[e.u] - h[e.v]; // Reweight edges to remove negatives
        g[e.u].push_back({e.v, w});
    }

    vector<ll> dist(n+1, INF);
    vector<bool> vis(n+1, false);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &edge : g[u]) {
            int v = edge.first;
            ll w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Undo reweighting to restore original distances
    for (int i = 1; i <= n; i++) {
        if (dist[i] < INF) dist[i] = dist[i] - h[src] + h[i];
    }
    return dist;
}

// Johnson’s Algorithm
// Returns false if a negative cycle exists
bool johnson(int n, vector<Edge>& edges, vector<vector<ll>>& ans) {
    // Step 1: Add an auxiliary node 0 connected to all nodes with weight 0
    vector<Edge> extEdges = edges;
    for (int i = 1; i <= n; i++) extEdges.push_back({0, i, 0});

    // Step 2: Run Bellman-Ford from node 0
    vector<ll> h;
    if (!bellman_ford(n, 0, extEdges, h)) return false; // Negative cycle

    // Step 3: Run Dijkstra from each node on reweighted graph
    ans.assign(n+1, vector<ll>(n+1, INF));
    for (int i = 1; i <= n; i++) {
        vector<ll> dist = dijkstra(n, i, edges, h);
        for (int j = 1; j <= n; j++) {
            ans[i][j] = dist[j];
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, cs = 0;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<Edge> edges;
        while (m--) {
            int u, v; ll w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }

        vector<vector<ll>> ans;
        cout << "graph " << ++cs << ' ';
        if (!johnson(n, edges, ans)) {
            cout << "no\n"; // Negative cycle
            continue;
        }
        cout << "yes\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (j > 1) cout << ' ';
                if (ans[i][j] >= INF/2) cout << "#"; // Unreachable
                else cout << ans[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
