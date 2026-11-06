// P2 (CF 2246E): send x = 1. A bit above bit 0 in o proves OR and reveals a bit of v.
// Otherwise use random high bits in m0, m1: an exact match means v = 0, else bit 0 decides.
// Wrong only if v == m0 ^ m1, probability 2^-29 per test case.
#include <bits/stdc++.h>
using namespace std;
int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int t;
    cin >> t;
    while (t--) {
        int o, r, b;
        cout << 1 << endl;
        cin >> o;
        if (o < 0) return 0;
        int high = o >> 1 << 1;
        if (high) {
            int p = __builtin_ctz(high);
            cout << (1 << p) << " " << 0 << endl;
            cin >> r;
            if (r < 0) return 0;
            b = r >> p & 1;           // v has bit p set, so m0 gives 0 here, m1 gives 1
        } else {
            int mask = (1 << 30) - 1;
            int m0 = (rng() & mask) | 1, m1 = (rng() & mask) & ~1;
            cout << m0 << " " << m1 << endl;
            cin >> r;
            if (r < 0) return 0;
            if (r == m0) b = 0;
            else if (r == m1) b = 1;
            else b = (r & 1) ^ (o & 1) ^ 1;   // bit 0 of v equals o here
        }
        cout << b << endl;
    }
}
