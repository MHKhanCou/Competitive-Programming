// In the name of Allah, the most merciful
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define vi vector<int>
#define vl vector<ll>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define all(x) x.begin(), x.end()
#define nl '\n'
const ll INF = 1LL << 60;

struct MCMF {
	struct Edge {
		int u, v;
		ll cap, cost;
		int id;
		Edge(int _u, int _v, ll _cap, ll _cost, int _id)
			: u(_u), v(_v), cap(_cap), cost(_cost), id(_id) {}
	};

	int n, s, t, mxid;
	ll flow, cost;
	vector<vector<int>> g;
	vector<Edge> e;
	vector<ll> potential, dist, flow_through;
	vector<int> par;
	bool neg;

	MCMF() {}
	MCMF(int _n) {
		n = _n + 10;
		g.assign(n, {});
		neg = false;
		mxid = 0;
	}

	void add_edge(int u, int v, ll cap, ll cost, int id = -1, bool directed = true) {
		if (cost < 0) neg = true;
		g[u].pb(e.size());
		e.pb(Edge(u, v, cap, cost, id));
		g[v].pb(e.size());
		e.pb(Edge(v, u, 0, -cost, -1));
		mxid = max(mxid, id);
		if (!directed) add_edge(v, u, cap, cost, -1, true);
	}

	bool dijkstra() {
		par.assign(n, -1);
		dist.assign(n, INF);
		priority_queue<pll, vector<pll>, greater<pll>> pq;
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

		for (int i = 0; i < n; i++)
			if (dist[i] < INF) dist[i] += (potential[i] - potential[s]);
		for (int i = 0; i < n; i++)
			if (dist[i] < INF) potential[i] = dist[i];

		return dist[t] != INF;
	}

	ll send_flow(int v, ll cur) {
		if (par[v] == -1) return cur;
		int id = par[v];
		int u = e[id].u;
		ll f = send_flow(u, min(cur, e[id].cap));
		cost += f * e[id].cost;
		e[id].cap -= f;
		e[id ^ 1].cap += f;
		return f;
	}

	// Returns {max flow, min cost}
	pair<ll, ll> solve(int _s, int _t, ll goal = INF) {
		s = _s; t = _t;
		flow = 0; cost = 0;
		potential.assign(n, 0);

		if (neg) {
			// Bellman-Ford to initialize potentials
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

		while (flow < goal && dijkstra())
			flow += send_flow(t, goal - flow);

		flow_through.assign(mxid + 10, 0);
		for (int u = 0; u < n; u++)
			for (int idx : g[u])
				if (e[idx].id >= 0) flow_through[e[idx].id] = e[idx ^ 1].cap;

		return {flow, cost};
	}
};

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	MCMF F(n);


	for (int i = 1; i <= m; i++)
	{
		int a, b, r, c;
		cin >> a >> b >> r >> c;
		F.add_edge(a, b, r, c);
	}

	auto ans = F.solve(1, n, k);
	if (ans.first < k) cout << -1 << nl;
	else cout << ans.second << nl;

}

//https://cses.fi/problemset/task/2121
