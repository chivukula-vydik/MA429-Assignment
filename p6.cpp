// P6 Cipher: an operation keeps length and letter sum, and every word with the same
// length and sum is reachable. Answer = (words with that length and sum) - 1.
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int dp[101][2601];
int main() {
    dp[0][0] = 1;
    for (int l = 1; l <= 100; l++)
        for (int s = 0; s <= 2500; s++) {
            long long v = 0;
            for (int c = 0; c < 26 && c <= s; c++) v += dp[l - 1][s - c];
            dp[l][s] = v % MOD;
        }
    int t;
    scanf("%d", &t);
    char w[128];
    while (t--) {
        scanf("%s", w);
        int s = 0, n = strlen(w);
        for (int i = 0; i < n; i++) s += w[i] - 'a';
        printf("%d\n", (dp[n][s] - 1 + MOD) % MOD);
    }
}
