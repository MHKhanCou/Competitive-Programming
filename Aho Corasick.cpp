#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr)

const int ALPHABET_SIZE = 26;
const int MAX_NODES = 5e5 + 5;

struct TrieNode {
    int failureLink;
    int child[ALPHABET_SIZE];
    int occurrences;
    vector<int> patternIndices;

    TrieNode() : failureLink(0), occurrences(0) {
        fill(child, child + ALPHABET_SIZE, 0);
    }
};

struct AhoCorasick {
    vector<TrieNode> trie;
    vector<vector<int>> failureTree;
    vector<int> patternFound;
    int nodeCount;

    AhoCorasick(int maxPatterns) : nodeCount(1), patternFound(maxPatterns) {
        trie.resize(MAX_NODES);
        failureTree.resize(MAX_NODES);
        trie[1] = TrieNode();
    }

    inline int charToIndex(char c) {
        return c - 'a';
    }

    void insert(const string& pattern, int idx) {
        int node = 1;
        for (char c : pattern) {
            int ch = charToIndex(c);
            if (!trie[node].child[ch]) {
                trie[node].child[ch] = ++nodeCount;
                trie[nodeCount] = TrieNode();
            }
            node = trie[node].child[ch];
        }
        trie[node].patternIndices.pb(idx);
    }

    void build() {
        queue<int> q;
        trie[1].failureLink = 1;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (trie[1].child[i]) {
                trie[trie[1].child[i]].failureLink = 1;
                q.push(trie[1].child[i]);
            } else {
                trie[1].child[i] = 1;
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int& v = trie[u].child[i];
                if (v) {
                    trie[v].failureLink = trie[trie[u].failureLink].child[i];
                    q.push(v);
                } else {
                    v = trie[trie[u].failureLink].child[i];
                }
            }
            if (u != trie[u].failureLink)
                failureTree[trie[u].failureLink].pb(u);
        }
    }

    void processText(const string& text) {
        int node = 1;
        for (char c : text) {
            node = trie[node].child[charToIndex(c)];
            trie[node].occurrences++;
        }
    }

    void propagate() {
        function<int(int)> dfs = [&](int u) -> int {
            int sum = trie[u].occurrences;
            for (int v : failureTree[u]) {
                sum += dfs(v);
            }
            for (int idx : trie[u].patternIndices)
                patternFound[idx] = sum;
            return sum;
        };
        dfs(1);
    }

    vector<int>& getResult() {
        return patternFound;
    }

    void reset() {
        nodeCount = 1;
        trie.assign(MAX_NODES, TrieNode());
        failureTree.assign(MAX_NODES, {});
        fill(all(patternFound), 0);
    }
};

int main() {
    FAST_IO;
    string text;
    cin >> text;

    int n;
    cin >> n;

    AhoCorasick ac(n);

    for (int i = 0; i < n; i++) {
        string pattern;
        cin >> pattern;
        ac.insert(pattern, i);
    }

    ac.build();
    ac.processText(text);
    ac.propagate();

    for (int count : ac.getResult()) {
        cout << (count > 0 ? "YES" : "NO") << '\n'; // or just `cout << count << '\n';`
    }

    return 0;
}

