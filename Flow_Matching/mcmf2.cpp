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

// ---------------------------- MCMF TEMPLATE ----------------------------
// Min-Cost Max-Flow using successive shortest paths + potentials
struct MCMF {
	struct edge {
		int u, v, id;
		ll cap, cost;
		edge(int _u, int _v, ll _cap, ll _cost, int _id) {
			u = _u; v = _v; cap = _cap; cost = _cost; id = _id;
		}
	};
	int n, s, t, mxid;
	ll flow, cost;
	vector<vector<int>> g;
	vector<edge> e;
	vector<ll> d, potential, flow_through;
	vector<int> par;
	bool neg;
	MCMF() {}
	MCMF(int _n) {
		n = _n + 10;
		g.assign(n, vector<int>());
		neg = false;
		mxid = 0;
	}
	void add_edge(int u, int v, ll cap, ll cost, int id = -1, bool directed = true) {
		if (cost < 0) neg = true;
		g[u].push_back(e.size());
		e.push_back(edge(u, v, cap, cost, id));
		g[v].push_back(e.size());
		e.push_back(edge(v, u, 0, -cost, -1));
		mxid = max(mxid, id);
		if (!directed) {
			g[v].push_back(e.size());
			e.push_back(edge(v, u, cap, cost, -1));
			g[u].push_back(e.size());
			e.push_back(edge(u, v, 0, -cost, -1));
		}
	}
	bool dijkstra() {
		par.assign(n, -1);
		d.assign(n, INF);
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
		d[s] = 0;
		q.push({0, s});
		while (!q.empty()) {
			int u = q.top().second;
			ll nw = q.top().first;
			q.pop();
			if (nw != d[u]) continue;
			for (int id : g[u]) {
				int v = e[id].v;
				ll cap = e[id].cap;
				ll w = e[id].cost + potential[u] - potential[v];
				if (d[u] + w < d[v] && cap > 0) {
					d[v] = d[u] + w;
					par[v] = id;
					q.push({d[v], v});
				}
			}
		}
		for (int i = 0; i < n; i++)
			if (d[i] < INF) d[i] += (potential[i] - potential[s]);
		for (int i = 0; i < n; i++)
			if (d[i] < INF) potential[i] = d[i];
		return d[t] != INF;
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
	ll get(int v, vector<bool> &vis) {
		if (vis[v]) return potential[v];
		vis[v] = true;
		potential[v] = INF;
		if (v == s) return potential[v] = 0;
		for (int id : g[v]) {
			int u = e[id ^ 1].u;
			ll w = e[id ^ 1].cost;
			if (e[id ^ 1].cap > 0)
				potential[v] = min(potential[v], get(u, vis) + w);
		}
		return potential[v];
	}
	pair<ll, ll> solve(int _s, int _t, ll goal = INF) {
		s = _s; t = _t;
		flow = cost = 0;
		potential.assign(n, INF);
		if (neg) {
			vector<bool> vis(n, 0);
			for (int i = 0; i < n; i++) if (potential[i] == INF) get(i, vis);
		}
		while (flow < goal && dijkstra()) flow += send_flow(t, goal - flow);
		flow_through.assign(mxid + 10, 0);
		for (int u = 0; u < n; u++)
			for (int id : g[u])
				if (e[id].id >= 0) flow_through[e[id].id] = e[id ^ 1].cap;
		return {flow, cost};
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	int source = 2 * n + 1, sink = 2 * n + 2;
	MCMF F(sink + 5);

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	for (int i = 1; i <= n; i++) {
		F.add_edge(source, i, 1, 0);
		F.add_edge(i, i + n, 1, -1);
		F.add_edge(i + n, sink, 1, 0);
		for (int j = 1; j < i; j++) {
			if (abs(a[i] - a[j]) == 1 || a[i] % 7 == a[j] % 7)
				F.add_edge(j + n, i, 1, 0);
		}
	}

	auto ans = F.solve(source, sink, 4);
	cout << -ans.second << nl;
}
