// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

struct FlowEdge {
    int v, u;
    long long cap, flow;
    FlowEdge(int v=0, int u=0, long long cap=0) : v(v), u(u), cap(cap), flow(0) {}
};

struct Dinic {
    const long long INF = (long long)4e18;
    int n, s, t;
    vector<FlowEdge> edges;
    vector<vector<int>> g;
    vector<int> level, ptr;

    Dinic(int _n=0) { init(_n); }

    void init(int _n) {
        n = _n;
        g.assign(n+1, {});
        edges.clear();
        level.resize(n+1);
        ptr.resize(n+1);
    }

    void add_edge(int u, int v, long long cap) {
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        g[u].push_back((int)edges.size()-2);
        g[v].push_back((int)edges.size()-1);
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

    long long dfs(int v, long long pushed) {
        if (!pushed) return 0;
        if (v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int)g[v].size(); cid++) {
            int id = g[v][cid];
            FlowEdge &e = edges[id];
            if (level[e.u] != level[v] + 1 || e.cap - e.flow <= 0) continue;
            long long tr = dfs(e.u, min(pushed, e.cap - e.flow));
            if (!tr) continue;
            e.flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long max_flow(int _s, int _t, long long limit=-1) {
        s = _s; t = _t;
        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, INF)) {
                flow += pushed;
                if (limit != -1 && flow >= limit) return limit; // optional early exit
            }
        }
        return flow;
    }
};

int main() {
    mh
    int n, m;
    cin >> n >> m;
    Dinic D(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        D.add_edge(a, b, c);
    }
    cout << D.max_flow(1, n) << nl;
    return 0;
}
