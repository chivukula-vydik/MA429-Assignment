// P7 Xenon's Attack: optimal labels 0..len-1 form a valley along one path.
// dp[u][v] = sub[v][u] * sub[u][v] + max(dp[par[v][u]][v], dp[u][par[u][v]]), O(n^2).
#include <bits/stdc++.h>
using namespace std;
const int N = 3001;
vector<int> g[N];
short par[N][N], sub[N][N];
long long dp[N][N];
void dfs(int r, int u, int p) {
    par[r][u] = p;
    sub[r][u] = 1;
    for (int v : g[u]) if (v != p) { dfs(r, v, u); sub[r][u] += sub[r][v]; }
}
long long f(int u, int v) {
    if (u == v) return 0;
    long long &res = dp[u][v];
    if (res >= 0) return res;
    return res = (long long)sub[v][u] * sub[u][v] + max(f(par[v][u], v), f(u, par[u][v]));
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int r = 1; r <= n; r++) dfs(r, r, 0);
    memset(dp, -1, sizeof(dp));
    long long ans = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++) ans = max(ans, f(u, v));
    printf("%lld\n", ans);
}
