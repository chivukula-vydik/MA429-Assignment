// P4 Network Safety: for a fixed x, only edges with c[u]^c[v] == x force u, v to share a state.
// That x contributes 2^components; every x not appearing on an edge contributes 2^n.
#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
vector<int> par;
int find(int x) {
    while (par[x] != x) x = par[x] = par[par[x]];
    return x;
}
int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    vector<long long> c(n);
    for (auto &v : c) scanf("%lld", &v);
    vector<tuple<long long, int, int>> e(m);
    for (auto &[w, u, v] : e) {
        scanf("%d %d", &u, &v);
        u--; v--;
        w = c[u] ^ c[v];
    }
    sort(e.begin(), e.end());
    vector<long long> pw(n + 1, 1);
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 2 % MOD;
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    long long sum = 0, distinct = 0;
    for (int i = 0; i < m;) {
        int j = i, comps = n;
        for (; j < m && get<0>(e[j]) == get<0>(e[i]); j++) {
            int a = find(get<1>(e[j])), b = find(get<2>(e[j]));
            if (a != b) { par[a] = b; comps--; }
        }
        sum = (sum + pw[comps]) % MOD;
        distinct++;
        for (int p = i; p < j; p++) {
            par[get<1>(e[p])] = get<1>(e[p]);
            par[get<2>(e[p])] = get<2>(e[p]);
        }
        i = j;
    }
    long long rest = ((1LL << k) % MOD - distinct % MOD + MOD) % MOD;
    printf("%lld\n", (sum + rest * pw[n]) % MOD);
}
