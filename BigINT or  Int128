#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

// Read signed 128-bit integer
istream& operator>>(istream& in, i128 &x) {
    string s;
    in >> s;
    bool neg = false;
    x = 0;
    for (char c : s) {
        if (c == '-') {
            neg = true;
        } else {
            x = x * 10 + (c - '0');
        }
    }
    if (neg) x = -x;
    return in;
}

// Write signed 128-bit integer
ostream& operator<<(ostream& out, i128 x) {
    if (x == 0) return out << "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        s += '0' + (x % 10);
        x /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return out << s;
}

int main() {
    int n;
    cin >> n;
    multiset<i128> v;
    for (int i = 0; i < n; ++i) {
        i128 x;
        cin >> x;
        v.insert(x);
    }

    while (true) {
        i128 x = *v.begin();
        int c = v.count(x);

        if (v.size() == 1) {
            cout << x << "\n";
            return 0;
        }
        if (c == 1) {
            v.erase(x);
            continue;
        }

        v.erase(v.find(x));
        v.erase(v.find(x));
        v.insert(x + x);
    }

    return 0;
}
