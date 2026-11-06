// P8 Bipartite Checking: offline segment tree over time with a rollback DSU storing parity.
// An odd cycle in a node makes every query in its range NO.
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int fa[N], sz[N], par_[N];
vector<pair<int, int>> tr[4 * N];
vector<int> undo;
char ans[N];
void add(int o, int l, int r, int a, int b, pair<int, int> e) {
    if (a <= l && r <= b) { tr[o].push_back(e); return; }
    int m = (l + r) / 2;
    if (a <= m) add(o * 2, l, m, a, b, e);
    if (b > m) add(o * 2 + 1, m + 1, r, a, b, e);
}
void solve(int o, int l, int r) {
    size_t mark = undo.size();
    bool ok = true;
    for (auto [x, y] : tr[o]) {
        int px = 0, py = 0;
        while (fa[x] != x) { px ^= par_[x]; x = fa[x]; }
        while (fa[y] != y) { py ^= par_[y]; y = fa[y]; }
        if (x == y) {
            if (px == py) { ok = false; break; }
            continue;
        }
        if (sz[x] > sz[y]) swap(x, y);
        fa[x] = y;
        par_[x] = px ^ py ^ 1;
        sz[y] += sz[x];
        undo.push_back(x);
    }
    if (!ok) fill(ans + l, ans + r + 1, 0);
    else if (l == r) ans[l] = 1;
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
        par_[x] = 0;
    }
}
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    map<pair<int, int>, int> live;
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        auto it = live.find({x, y});
        if (it == live.end()) live[{x, y}] = i;
        else {
            add(1, 0, q - 1, it->second, i - 1, {x, y});
            live.erase(it);
        }
    }
    for (auto &[e, s] : live) add(1, 0, q - 1, s, q - 1, e);
    for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
    solve(1, 0, q - 1);
    for (int i = 0; i < q; i++) puts(ans[i] ? "YES" : "NO");
}
