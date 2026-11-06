# MA429 Assignment - approach notes

Short notes on how I solved each problem. All solutions are in C++ (compiled with g++ -O2, C++17).

**P1 - Password**
Taking the difference array of the bit string, every flip of length a only changes two positions (i and i+a). So the problem becomes: pair up the positions where the difference array is 1, and the cost of a pair is the shortest number of moves between them. I ran BFS from each of those positions (there are at most 20 of them since k <= 10) to get pairwise distances, then did a bitmask DP to find the cheapest perfect matching. If no matching works the answer is -1.

**P2 - Interactive (CF 2246E)**
First query x = 1. If the reply has any bit set above bit 0, that bit tells me something about v and I can use it with a second query to read the answer bit directly. If not, I send two random 30-bit masks m0 and m1 (one odd, one even). An exact match with one of them decides it, otherwise bit 0 decides. This can only fail when v happens to equal m0 ^ m1, which is about 2^-29 per test, so I was fine with that.

**P3 - Password restore**
Classic one. Treat every two-character string as a node and each three-letter substring as an edge from its first two chars to its last two. The password is then an Eulerian path through this graph. I check the in/out degree condition, run Hierholzer's algorithm, and if the path doesn't use all n edges the graph wasn't connected, so the answer is NO.

**P4 - Network Safety**
For a fixed x, an edge (u, v) only becomes a problem when c[u] ^ c[v] == x, and in that case u and v must be both infected or both not. So for that x the count is 2^(number of components) using just those edges. I grouped edges by their xor value, used a DSU for each group (resetting only the touched nodes afterwards so it stays O(m log m) overall), and every x that doesn't show up on any edge just contributes 2^n.

**P5 - Spy Syndrome**
Built a trie of the words in lowercase. Since the cipher text is the sentence reversed, scanning the text backwards from position j reads a word forwards, so I can walk the trie while going left. reach[j] is true if some word ends exactly at a reachable position. Storing which word got me there lets me rebuild the sentence at the end.

**P6 - Cipher**
The key observation is that an operation never changes the length of the word or the sum of its letters (a=0, ..., z=25), and any word with the same length and sum can be reached. So the answer is just (number of words with that length and letter sum) - 1. I precomputed dp[len][sum] once for len up to 100 and sum up to 2500.

**P7 - Xenon's Attack on the Gangs**
Took a while to see this one. In an optimal labelling the small labels 0, 1, 2, ... grow outward along a single path, so the answer only depends on which path we extend. dp[u][v] = sub(v rooted at u) * sub(u rooted at v) + max of extending from either end. Precomputing parents and subtree sizes for every root makes it O(n^2), which is ok for n = 3000.

**P8 - Bipartite Checking**
Did this offline. Each edge is alive on some interval of queries, so I put it onto a segment tree over time and walked the tree with a DSU that stores parity and supports rollback (union by size, no path compression). If adding an edge creates an odd cycle, every query in that node's range is NO and I don't go deeper.

**P9 - Virus**
Same trick as P8. A contact on day d stays relevant until the end of day d+k-1, so I mapped that to a range of type 2 queries and added it to a segment tree over those queries. Rollback DSU with sizes gives the component size at each leaf.

**P10 - Interactive (functional graph)**
After n steps from 1 we are guaranteed to be on the cycle, so y = f^n(1) is on it. I find the cycle length L with baby-step giant-step, which keeps the query count under the limit (around 2*sqrt(n)). Then with c = y and r = f^a(y) where a = -y mod L, applying f c times to r lands back on y, which is what the problem asks for.
