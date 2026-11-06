// P9 Virus: a contact on day d lives until the end of day d+k-1. Index time by type 2 queries,
// put each contact on a segment tree over that range, answer with a rollback DSU.
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int fa[N], sz[N];
vector<vector<pair<int, int>>> tr;
vector<int> ask, res, undo;
void add(int o, int l, int r, int a, int b, pair<int, int> e) {
    if (a <= l && r <= b) { tr[o].push_back(e); return; }
    int m = (l + r) / 2;
    if (a <= m) add(o * 2, l, m, a, b, e);
    if (b > m) add(o * 2 + 1, m + 1, r, a, b, e);
}
int find(int x) {
    while (fa[x] != x) x = fa[x];
    return x;
}
void solve(int o, int l, int r) {
    size_t mark = undo.size();
    for (auto [x, y] : tr[o]) {
        x = find(x);
        y = find(y);
        if (x == y) continue;
        if (sz[x] > sz[y]) swap(x, y);
        fa[x] = y;
        sz[y] += sz[x];
        undo.push_back(x);
    }
    if (l == r) res[l] = sz[find(ask[l])];
    else {
        int m = (l + r) / 2;
        solve(o * 2, l, m);
        solve(o * 2 + 1, m + 1, r);
    }
    while (undo.size() > mark) {
        int x = undo.back();
        undo.pop_back();
        sz[fa[x]] -= sz[x];
        fa[x] = x;
    }
}
int main() {
    int n, q, k;
    scanf("%d %d %d", &n, &q, &k);
    struct C { int x, y, day, start; };
    vector<C> contacts;
    vector<int> dayEnd;   // number of type 2 queries before each day ended
    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            contacts.push_back({x, y, (int)dayEnd.size(), (int)ask.size()});
        } else if (t == 2) {
            int z;
            scanf("%d", &z);
            ask.push_back(z);
        } else dayEnd.push_back(ask.size());
    }
    int Q = ask.size();
    if (!Q) return 0;
    tr.resize(4 * Q);
    res.resize(Q);
    for (auto &c : contacts) {
        long long last = (long long)c.day + k - 1;
        int stop = last < (long long)dayEnd.size() ? dayEnd[last] : Q;
        if (c.start < stop) add(1, 0, Q - 1, c.start, stop - 1, {c.x, c.y});
    }
    for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
    solve(1, 0, Q - 1);
    for (int v : res) printf("%d\n", v);
}
