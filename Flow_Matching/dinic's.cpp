// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'
#define F first
#define S second

struct FlowEdge {
    int v, u;
    ll cap, flow;
    FlowEdge(int v = 0, int u = 0, ll cap = 0) : v(v), u(u), cap(cap), flow(0) {}
};

struct Dinic {
    const ll INF = (ll)4e18;
    int n;                     // number of nodes
    vector<vector<int>> g;     // adjacency: stores edge indices
    vector<FlowEdge> edges;    // edge list (forward, reverse pairs)
    vector<int> level;         // level graph
    vector<int> ptr;           // current edge pointer
    int s, t;

    Dinic(int _n = 0) { init(_n); }

    void init(int _n) {
        n = _n;
        g.assign(n + 1, {});
        edges.clear();
        level.assign(n + 1, -1);
        ptr.assign(n + 1, 0);
    }

    // add directed edge u -> v with capacity cap
    void add_edge(int u, int v, ll cap) {
        edges.emplace_back(u, v, cap);    // id = edges.size()-1
        edges.emplace_back(v, u, 0);      // reverse edge
        g[u].push_back((int)edges.size() - 2);
        g[v].push_back((int)edges.size() - 1);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int id : g[v]) {
                FlowEdge &e = edges[id];
                if (e.cap - e.flow > 0 && level[e.u] == -1) {
                    level[e.u] = level[v] + 1;
                    q.push(e.u);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, ll pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int)g[v].size(); ++cid) {
            int id = g[v][cid];
            FlowEdge &e = edges[id];
            if (level[e.u] != level[v] + 1) continue;
            ll tr = dfs(e.u, min(pushed, e.cap - e.flow));
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr; // id^1 is the reverse edge
            return tr;
        }
        return 0;
    }

    ll max_flow(int _s, int _t) {
        s = _s; t = _t;
        ll flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    mh
    int n, m;
    if (!(cin >> n >> m)) return 0;
    Dinic D(n);
    int a, b;
    ll c;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        D.add_edge(a, b, c);
    }
    cout << D.max_flow(1, n) << nl;
    return 0;
}
