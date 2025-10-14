#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 9;

vector<int> a[N]; // adjacency list
int n;

/*
  ===== Green Hackenbush on Trees Template =====
  
  Principles / Hints:
  
  1. Colon Principle:
     - For a tree, Grundy(node) = xor of all child subtrees
     - Leaf edges → Grundy = 1
     - Internal edges → xor(child Grundies + 1 for connecting edge)
  
  2. Fusion Principle (for general graphs / cycles):
     - If two vertices are part of a cycle, you can contract them without
       changing the Grundy number.
  
  3. Self-loop Principle:
     - An edge from a node to itself contributes Grundy = 1

  4. Sprague-Grundy / XOR Sum Principle:
     - Disjoint sum of games → Grundy = xor of each component
  
  5. Hot Game Principle (Advanced / Partisan Hackenbush):
     - Non-impartial edges (red/blue) → compute Left/Right options
       → game value becomes {L|R}
  
  6. Ordinal Sum Principle:
     - Chains of edges can be treated as ordinal sums → compute recursively
  
  7. Bridge vs Non-bridge (for general graphs):
     - Bridge = removing it disconnects → count +1
     - Non-bridge = part of cycle → can fuse, Grundy unchanged
  
  8. Graph Decomposition:
     - Decompose graph into bridges, 2-edge-connected components, self-loops
     - Compute Grundy per component and xor all → total Grundy
*/

int dfs(int v, int p = 0) {
    int x = 0; // Grundy of current subtree
    for (int u : a[v]) {
        if (u == p) continue;      // skip parent
        x ^= (dfs(u, v) + 1);      // Colon Principle: xor children + edge
    }
    return x;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t; // number of test cases
    while (t--) {
        cin >> n; // number of nodes
        for (int i = 1; i <= n; i++) a[i].clear();

        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }

        int g = dfs(1); // compute Grundy from root
        if (g) cout << "Alice\n"; // first player wins
        else cout << "Bob\n";     // second player wins
    }
}
