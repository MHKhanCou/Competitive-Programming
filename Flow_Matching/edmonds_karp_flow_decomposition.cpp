// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'
#define F first
#define S second

const int INF = 1e9;

int bfs(int s, int t, vector<int>& parent, const vector<vector<int>>& cap, const vector<vector<int>>& g) {
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;
	queue<pair<int, int>> q;
	q.push({s, INF});
	while (!q.empty()) {
		int u = q.front().F;
		int flow = q.front().S;
		q.pop();
		for (int v : g[u]) {
			if (parent[v] == -1 && cap[u][v] > 0) {
				parent[v] = u;
				int new_flow = min(flow, cap[u][v]);
				if (v == t) return new_flow;
				q.push({v, new_flow});
			}
		}
	}
	return 0;
}

int max_flow(int s, int t, vector<vector<int>>& cap, const vector<vector<int>>& g) {
	int n = cap.size() - 1;
	int flow = 0;
	vector<int> parent(n + 1);
	while (true) {
		int new_flow = bfs(s, t, parent, cap, g);
		if (!new_flow) break;
		flow += new_flow;
		int v = t;
		while (v != s) {
			int u = parent[v];
			cap[u][v] -= new_flow;
			cap[v][u] += new_flow;
			v = u;
		}
	}
	return flow;
}

bool dfs_decomp(int u, int t, vector<int>& parent, const vector<vector<int>>& g, vector<vector<int>>& flow) {
	if (u == t) return true;
	for (int v : g[u]) {
		if (parent[v] == -1 && flow[u][v] > 0) {
			parent[v] = u;
			if (dfs_decomp(v, t, parent, g, flow)) return true;
		}
	}
	return false;
}

int main() {
	mh
	int n, m;
	if (!(cin >> n >> m)) return 0;
	int s = 1, t = n;

	vector<vector<int>> g(n + 1);
	vector<vector<int>> cap(n + 1, vector<int>(n + 1, 0));
	vector<vector<int>> orig(n + 1, vector<int>(n + 1, 0));

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		orig[u][v] = 1;
		cap[u][v] = 1;
	}

	int flow = max_flow(s, t, cap, g);

	vector<vector<int>> flowed(n + 1, vector<int>(n + 1, 0));
	for (int u = 1; u <= n; ++u) {
		for (int v : g[u]) {
			if (orig[u][v] > 0) {
				flowed[u][v] = orig[u][v] - cap[u][v];
				if (flowed[u][v] < 0) flowed[u][v] = 0;
			}
		}
	}

	vector<vector<int>> paths;
	while (true) {
		vector<int> parent(n + 1, -1);
		parent[s] = -2;
		if (!dfs_decomp(s, t, parent, g, flowed)) break;
		vector<int> path;
		int v = t;
		while (v != s) {
			path.push_back(v);
			int u = parent[v];
			flowed[u][v] -= 1;
			v = u;
		}
		path.push_back(s);
		reverse(path.begin(), path.end());
		paths.push_back(path);
	}

	cout << flow << nl;
	for (auto &p : paths) {
		cout << (int)p.size() << nl;
		for (int i = 0; i < (int)p.size(); ++i) {
			cout << p[i] << (i + 1 == (int)p.size() ? '\n' : ' ');
		}
	}
	return 0;
}


//https://cses.fi/problemset/task/1711
