// P10: y = f^n(1) is on a cycle. Find the cycle length L with baby-step giant-step (under 900 queries).
// Take c = y and r = f^a(c) with a = -c mod L. Then f^c(r) = f^(a+c)(c) = c.
#include <bits/stdc++.h>
using namespace std;
int ask(int c, int r) {
    cout << "? " << c << " " << r << endl;
    int h;
    cin >> h;
    return h;
}
int main() {
    int n;
    cin >> n;
    int y = ask(n, 1);
    int s = max(1, (int)ceil(sqrt((double)n)));
    vector<int> pos(n + 1, -1);
    pos[y] = 0;
    int cur = y;
    for (int i = 1; i < s; i++) {
        cur = ask(1, cur);
        pos[cur] = i;     // keep the largest i so the first hit gives the minimal length
    }
    int g = y, L = 0;
    for (int j = 1; !L; j++) {
        g = ask(s, g);
        if (pos[g] >= 0) L = j * s - pos[g];
    }
    int a = (L - y % L) % L;
    int r = a ? ask(a, y) : y;
    cout << "! " << y << " " << r << endl;
}
