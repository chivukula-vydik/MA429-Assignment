// P3 Password restore: two-char prefixes are nodes, each triple is an edge.
// The password is an Eulerian path (Hierholzer).
#include <bits/stdc++.h>
using namespace std;
const int V = 62 * 62;
int idx(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}
char chr(int i) {
    if (i < 26) return 'a' + i;
    if (i < 52) return 'A' + i - 26;
    return '0' + i - 52;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> adj(V);
    vector<int> in(V, 0), out(V, 0);
    char s[8];
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        int u = idx(s[0]) * 62 + idx(s[1]), v = idx(s[1]) * 62 + idx(s[2]);
        adj[u].push_back(v);
        out[u]++; in[v]++;
    }
    int start = -1, plus = 0, minus = 0;
    for (int i = 0; i < V; i++) {
        int d = out[i] - in[i];
        if (d == 1) { plus++; start = i; }
        else if (d == -1) minus++;
        else if (d != 0) { puts("NO"); return 0; }
    }
    if (plus > 1 || minus > 1 || plus != minus) { puts("NO"); return 0; }
    if (start < 0) for (int i = 0; i < V; i++) if (out[i]) { start = i; break; }
    vector<int> st = {start}, path;
    while (!st.empty()) {
        int u = st.back();
        if (!adj[u].empty()) { st.push_back(adj[u].back()); adj[u].pop_back(); }
        else { path.push_back(u); st.pop_back(); }
    }
    if ((int)path.size() != n + 1) { puts("NO"); return 0; }   // graph not connected
    reverse(path.begin(), path.end());
    string res;
    res += chr(path[0] / 62);
    for (int u : path) res += chr(u % 62);
    printf("YES\n%s\n", res.c_str());
}
