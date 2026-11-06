// P1 Password: flips toggle two points of the difference array.
// BFS gives the cost to cancel each pair of odd points, then bitmask matching.
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k, l;
    scanf("%d %d %d", &n, &k, &l);
    vector<int> s(n + 2, 0), a(l);
    for (int i = 0, x; i < k; i++) { scanf("%d", &x); s[x] = 1; }
    for (int &v : a) scanf("%d", &v);
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    vector<int> pts;
    for (int i = 0; i <= n; i++) if (s[i] ^ s[i + 1]) pts.push_back(i);
    int m = pts.size();
    const int INF = 1e9;
    vector<vector<int>> cost(m, vector<int>(m, INF));
    vector<int> d(n + 1), q(n + 1);
    for (int i = 0; i < m; i++) {
        fill(d.begin(), d.end(), -1);
        int h = 0, t = 0;
        q[t++] = pts[i];
        d[pts[i]] = 0;
        while (h < t) {
            int u = q[h++];
            for (int v : a) {
                if (u + v <= n && d[u + v] < 0) { d[u + v] = d[u] + 1; q[t++] = u + v; }
                if (u - v >= 0 && d[u - v] < 0) { d[u - v] = d[u] + 1; q[t++] = u - v; }
            }
        }
        for (int j = 0; j < m; j++) if (d[pts[j]] >= 0) cost[i][j] = d[pts[j]];
    }
    vector<int> dp(1 << m, INF);
    dp[0] = 0;
    for (int mask = 0; mask + 1 < (1 << m); mask++) {
        if (dp[mask] >= INF) continue;
        int i = __builtin_ctz(~mask);
        for (int j = i + 1; j < m; j++) {
            if (mask >> j & 1 || cost[i][j] >= INF) continue;
            int nm = mask | 1 << i | 1 << j;
            dp[nm] = min(dp[nm], dp[mask] + cost[i][j]);
        }
    }
    int ans = dp[(1 << m) - 1];
    printf("%d\n", ans >= INF ? -1 : ans);
}
