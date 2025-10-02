//https://codeforces.com/problemset/problem/808/F

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

const int MAXN = 205;
const ll INF = (ll)1e15;

struct node { int p, c, l; };

vector<bool> sieve_primes(int maxV) {
    vector<bool> is_prime(maxV + 1, true);
    if (maxV >= 0) is_prime[0] = false;
    if (maxV >= 1) is_prime[1] = false;
    for (int i = 2; i * i <= maxV; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= maxV; j += i) is_prime[j] = false;
        }
    }
    return is_prime;
}

class Dinic {
public:
    int n, s, t;
    ll cap[MAXN][MAXN], flow[MAXN][MAXN];
    vector<int> g[MAXN];
    int level[MAXN], ptr[MAXN];

    Dinic(int _n = 0, int _s = 0, int _t = 0) { init(_n, _s, _t); }

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 0; i <= n; ++i) g[i].clear();
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
    }

    void add_edge(int u, int v, ll capacity = INF) {
        if (cap[u][v] == 0 && cap[v][u] == 0) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
        cap[u][v] += capacity;
    }

    void add_source_edge(int v, ll capacity) { add_edge(s, v, capacity); }
    void add_sink_edge(int u, ll capacity) { add_edge(u, t, capacity); }

    bool bfs() {
        fill(level, level + n + 1, -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : g[v]) {
                if (level[to] == -1 && cap[v][to] - flow[v][to] > 0) {
                    level[to] = level[v] + 1;
                    q.push(to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, ll pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int)g[v].size(); ++cid) {
            int to = g[v][cid];
            if (level[to] != level[v] + 1) continue;
            ll tr = dfs(to, min(pushed, cap[v][to] - flow[v][to]));
            if (tr == 0) continue;
            flow[v][to] += tr;
            flow[to][v] -= tr;
            return tr;
        }
        return 0;
    }

    // IMPORTANT: do not reset 'flow' here — we want to keep previous flows for incremental updates.
    ll max_flow_incremental() {
        ll f = 0;
        while (bfs()) {
            fill(ptr, ptr + n + 1, 0);
            while (ll pushed = dfs(s, INF)) {
                f += pushed;
            }
        }
        return f;
    }
};


int main() {
    mh
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<bool> prime = sieve_primes(200000);
    vector<node> a(n + 1);

    map<int, int> m[2]; // m[0] for even values -> node ids starting at 1, m[1] for odd values -> node ids starting at n+1
    int id1 = 1, id2 = n + 1;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i].p >> a[i].c >> a[i].l;
        if (a[i].c % 2 == 0) {
            if (!m[0].count(a[i].c)) m[0][a[i].c] = id1++;
        } else {
            if (!m[1].count(a[i].c)) m[1][a[i].c] = id2++;
        }
    }

    // sort by level asc, tie by p desc
    sort(a.begin() + 1, a.end(), [](const node & A, const node & B) {
        if (A.l == B.l) return A.p > B.p;
        return A.l < B.l;
    });

    int s = 0, t = id1 + id2; // ensure t > all assigned ids
    Dinic M(t + 5, s, t);     // single Dinic object reused
    ll tot = 0;
    ll flowed_total = 0; // amount of flow already pushed (we'll accumulate new flow returned by max_flow_incremental)
    int ans = -1;

    // We'll incrementally add nodes (cards) in order of increasing level.
    int one = 0;
    for (int i = 1; i <= n; ++i) {
        // add this card to the graph
        if (a[i].c > 1) tot += a[i].p;

        if (a[i].c == 1) {
            if (one == 0) M.add_edge(m[1].at(1), t, 0);
            tot -= one;
            one = max(one, a[i].p);
            tot += one;
            M.cap[m[1].at(1)][t] += one - M.cap[m[1].at(1)][t];
        } else if (a[i].c % 2 == 0) {
            M.add_source_edge(m[0][a[i].c], a[i].p);
        } else {
            // odd but not 1
            M.add_sink_edge(m[1][a[i].c], a[i].p);
        }

        // add prime edges between this card's value and previous card values (values are mapped to node ids)
        for (int j = 1; j < i; ++j) {
            if (a[i].c == 1 && a[j].c == 1) continue; // skip 1-1
            int sum = a[i].c + a[j].c;
            if (sum >= 0 && sum < (int)prime.size() && prime[sum]) {
                int evenVal = a[i].c % 2 == 0 ? a[i].c : a[j].c;
                int oddVal  = a[i].c % 2 == 1 ? a[i].c : a[j].c;
                // map to node ids
                int u = m[0][evenVal]; // even -> source side
                int v = m[1][oddVal];  // odd  -> sink side
                // add infinite capacity edge from even-node to odd-node
                M.add_edge(u, v, INF);
            }
        }

        // Now augment flow incrementally (Dinic will continue from previous flow state)
        flowed_total += M.max_flow_incremental();


        ll total_flow = tot - flowed_total;

        if (total_flow >= k) {
            ans = a[i].l;
            break;
        }
    }

    cout << ans << nl;
    return 0;
}
