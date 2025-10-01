// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'
#define F first
#define S second

const int N = 500 + 5;

vector<int> g[N];
ll cap[N][N];

int bfs(int s, int t, vector<int>& parent)
{
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;
	queue<pair<int, int>> q;
	q.push({s, INT_MAX});
	while (!q.empty())
	{
		ll u = q.front().F, flow = q.front().S;
		q.pop();

		for (int v : g[u]) {
			if (parent[v] == -1 and cap[u][v] > 0) {
				parent[v] = u;
				ll new_flow = min(flow, cap[u][v]);
				if (v == t) return new_flow;
				q.push({v, new_flow});
			}
		}
	}
	return 0;
}

ll max_flow(int s, int t)
{
	ll flow = 0, new_flow = 0;

	vector<int> parent(N, 0);

	while (true) {
		new_flow = bfs(s, t, parent);
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


int main()
{
	mh

	int n, m;
	cin >> n >> m;

	memset(cap, 0, sizeof(cap));

	for (int i = 1; i <= m; ++i)
	{
		int u, v, c;
		cin >> u >> v >> c;
		g[u].push_back(v);
		g[v].push_back(u);
		cap[u][v] += c;
	}

	cout << max_flow(1, n) << nl;

	return 0;
}

//https://cses.fi/problemset/task/1694/
