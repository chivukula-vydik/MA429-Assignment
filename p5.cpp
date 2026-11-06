// P5 Spy Syndrome: trie of lowercased words. Scanning t backward from j reads a word forward,
// so reach[j] holds if some word ends the scan at a reachable position. Parents rebuild the sentence.
#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int nxt[N][26], term[N], cnt = 1;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    string t;
    cin >> n >> t >> m;
    vector<string> w(m);
    memset(term, -1, sizeof(term));
    for (int i = 0; i < m; i++) {
        cin >> w[i];
        int u = 0;
        for (char ch : w[i]) {
            int c = tolower(ch) - 'a';
            if (!nxt[u][c]) nxt[u][c] = cnt++;
            u = nxt[u][c];
        }
        term[u] = i;
    }
    vector<int> from(n + 1, -1);
    vector<char> reach(n + 1, 0);
    reach[0] = 1;
    for (int j = 1; j <= n; j++) {
        int u = 0;
        for (int p = j - 1; p >= 0; p--) {
            u = nxt[u][t[p] - 'a'];
            if (!u) break;
            if (term[u] >= 0 && reach[p]) {
                reach[j] = 1;
                from[j] = term[u];
                break;
            }
        }
    }
    vector<int> ans;
    for (int j = n; j > 0; j -= w[from[j]].size()) ans.push_back(from[j]);
    reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < ans.size(); i++) cout << (i ? " " : "") << w[ans[i]];
    cout << "\n";
}
