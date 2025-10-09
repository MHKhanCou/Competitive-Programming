// In the name of Allah, the most merciful
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define nl '\n'
const ll INF = 1LL << 60;

// -------------------------------------------------
// Min-Cost Max-Flow (Successive Shortest Path + Potentials)
//
// Supports negative costs (Bellman-Ford for init potentials).
// Returns {max flow, min cost}.
// Complexity ~ O(F * E log V), F = total flow sent.
// -------------------------------------------------
struct MCMF {
    struct Edge {
        int u, v;     // from, to
        ll cap, cost; // remaining capacity, edge cost
        int id;       // optional id for tracking flow_through
        Edge(int _u, int _v, ll _cap, ll _cost, int _id)
            : u(_u), v(_v), cap(_cap), cost(_cost), id(_id) {}
    };

    int n, s, t, mxid;   // graph size, source, sink, max edge id
    ll flow, cost;       // total flow, total cost
    vector<vector<int>> g;   // adjacency list (stores edge indices)
    vector<Edge> e;          // edges (each real edge has forward+backward)
    vector<ll> potential;    // Johnson potentials to remove negative weights
    vector<ll> dist;         // distance array in Dijkstra
    vector<ll> flow_through; // flow sent through edge ids
    vector<int> par;         // parent edge index for path reconstruction
    bool neg;                // flag: does graph have negative cost edge?

    MCMF() {}
    MCMF(int _n) {
        n = _n + 10; // safe buffer
        g.assign(n, {});
        neg = false;
        mxid = 0;
    }

    // add_edge(u, v, capacity, cost, [id], [directed])
    void add_edge(int u, int v, ll cap, ll cost, int id = -1, bool directed = true) {
        if (cost < 0) neg = true;
        g[u].push_back(e.size());
        e.push_back(Edge(u, v, cap, cost, id));
        g[v].push_back(e.size());
        e.push_back(Edge(v, u, 0, -cost, -1)); // reverse edge
        mxid = max(mxid, id);
        if (!directed) add_edge(v, u, cap, cost, -1, true);
    }

    // Dijkstra with reduced costs (using potentials)
    bool dijkstra() {
        par.assign(n, -1);
        dist.assign(n, INF);
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            int u = pq.top().second; ll du = pq.top().first; pq.pop();
            if (du != dist[u]) continue;
            for (int idx : g[u]) {
                Edge &ed = e[idx];
                ll w = ed.cost + potential[u] - potential[ed.v];
                if (ed.cap > 0 && dist[ed.v] > dist[u] + w) {
                    dist[ed.v] = dist[u] + w;
                    par[ed.v] = idx;
                    pq.push({dist[ed.v], ed.v});
                }
            }
        }

        // reweight distances → update potentials
        for (int i = 0; i < n; i++)
            if (dist[i] < INF) dist[i] += (potential[i] - potential[s]);
        for (int i = 0; i < n; i++)
            if (dist[i] < INF) potential[i] = dist[i];

        return dist[t] != INF; // path exists?
    }

    // send flow along augmenting path (backtrack from sink to source)
    ll send_flow(int v, ll cur) {
        if (par[v] == -1) return cur; // reached source
        int id = par[v];
        int u = e[id].u;
        ll f = send_flow(u, min(cur, e[id].cap));
        cost += f * e[id].cost; // accumulate total cost
        e[id].cap -= f;         // use forward edge
        e[id ^ 1].cap += f;     // add to reverse edge
        return f;
    }

    // solve: returns {flow, cost}
    // goal = desired flow (default INF = push as much as possible)
    pair<ll, ll> solve(int _s, int _t, ll goal = INF) {
        s = _s; t = _t;
        flow = 0; cost = 0;
        potential.assign(n, 0);

        if (neg) {
            // Bellman-Ford for initial potentials (handle negative edges)
            dist.assign(n, INF);
            dist[s] = 0;
            bool relax = true;
            for (int i = 0; i < n && relax; i++) {
                relax = false;
                for (int u = 0; u < n; u++) {
                    for (int idx : g[u]) {
                        Edge &ed = e[idx];
                        if (ed.cap > 0 && dist[ed.v] > dist[u] + ed.cost) {
                            dist[ed.v] = dist[u] + ed.cost;
                            relax = true;
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++) if (dist[i] < INF) potential[i] = dist[i];
        }

        // keep augmenting until no more paths or flow goal reached
        while (flow < goal && dijkstra())
            flow += send_flow(t, goal - flow);

        // record flow through each original edge (by id)
        flow_through.assign(mxid + 10, 0);
        for (int u = 0; u < n; u++)
            for (int idx : g[u])
                if (e[idx].id >= 0) flow_through[e[idx].id] = e[idx ^ 1].cap;

        return {flow, cost};
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    MCMF F(n);

    for (int i = 1; i <= m; i++) {
        int a, b, r, c;
        cin >> a >> b >> r >> c;
        F.add_edge(a, b, r, c); // edge a->b, capacity=r, cost=c
    }

    auto ans = F.solve(1, n, k); // try to send exactly k flow from 1→n
    if (ans.first < k) cout << -1 << nl; // not enough flow possible
    else cout << ans.second << nl;       // print min cost
}

// Problem: https://cses.fi/problemset/task/2121
