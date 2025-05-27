#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<int> adj[N]; // adjacency list
vector<int> path;
map<pair<int, int>, int> edge_used;
int deg[N];

// Add undirected edge
void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    deg[u]++;
    deg[v]++;
}

void dfs(int u) {
    while (!adj[u].empty()) {
        int v = adj[u].back(); adj[u].pop_back();
        if (edge_used[{u, v}]) continue;
        edge_used[{u, v}] = edge_used[{v, u}] = 1;
        dfs(v);
    }
    path.push_back(u);
}

bool has_euler_path(int n, int &start) {
    int odd = 0;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] % 2) {
            odd++;
            start = i;
        }
    }
    if (odd != 0 && odd != 2) return false;
    if (odd == 0) {
        for (int i = 1; i <= n; ++i) {
            if (deg[i]) {
                start = i;
                break;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m; // number of nodes and edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    int start = 1;
    if (!has_euler_path(n, start)) {
        cout << "No Eulerian Path\n";
        return 0;
    }

    dfs(start);
    reverse(path.begin(), path.end());

    if (path.size() != m + 1) {
        cout << "Graph is disconnected\n";
    } else {
        for (int v : path) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}
