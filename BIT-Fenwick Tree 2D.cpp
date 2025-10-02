// In the name of Allah, the most merciful, the most gracious
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mh ios::sync_with_stdio(false); cin.tie(0);
#define nl '\n'

// MAX_N should be >= max n in problem (n <= 1000)
const int MAXN = 1005;

//https://cses.fi/problemset/task/1739

struct BIT2D {
    int n;
    // bit is 1-indexed: bit[1..n][1..n]
    vector<vector<int>> bit;

    BIT2D(int _n = 0) { init(_n); }

    void init(int _n) {
        n = _n;
        bit.assign(n + 1, vector<int>(n + 1, 0));
    }

    // point add: add 'delta' at (r, c)
    inline void point_add(int r, int c, int delta) {
        for (int i = r; i <= n; i += i & -i)
            for (int j = c; j <= n; j += j & -j)
                bit[i][j] += delta;
    }

    // prefix sum from (1,1) to (r,c)
    inline ll prefix_sum(int r, int c) const {
        ll res = 0;
        for (int i = r; i > 0; i -= i & -i)
            for (int j = c; j > 0; j -= j & -j)
                res += bit[i][j];
        return res;
    }

    // rectangle sum (r1,c1) .. (r2,c2)
    inline ll rect_sum(int r1, int c1, int r2, int c2) const {
        if (r1 > r2 || c1 > c2) return 0;
        return prefix_sum(r2, c2)
               - prefix_sum(r1 - 1, c2)
               - prefix_sum(r2, c1 - 1)
               + prefix_sum(r1 - 1, c1 - 1);
    }
};

int main() {
    mh
    int n, q;
    if (!(cin >> n >> q)) return 0;

    BIT2D bit(n);
    vector<vector<int>> a(n + 1, vector<int>(n + 1, 0));

    // read grid and initialize
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        s = " " + s; // 1-index
        for (int j = 1; j <= n; ++j) {
            if (s[j] == '*') {
                a[i][j] = 1;
                bit.point_add(i, j, 1);
            }
        }
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int y, x; cin >> y >> x;
            int newv = 1 - a[y][x];
            int delta = newv - a[y][x]; // +1 or -1
            if (delta) bit.point_add(y, x, delta);
            a[y][x] = newv;
        } else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << bit.rect_sum(y1, x1, y2, x2) << nl;
        }
    }
    return 0;
}
