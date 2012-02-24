#include <bitset>
int L, R, int matchL[MAXN], matchR[MAXN];
bitset<MAXN> seenL, seenR;
vector<int> g[MAXN];

void dfs(int u) { // u is on L
    if (u == -1 or seenL[u]) return;
    seenL[u] = true;
    foreach(out, g[u]) {
        int v = *out;
        if (!seenR[v]) {
            seenR[v] = true;
            dfs(matchR[v]);
        }
    }
}

// Build the maximum bipartite matching first!
void minimumVertexCover() {
    int size = 0;
    for (int i = 0; i < L; ++i) {
        if (matchL[i] == -1) dfs(i);
        else size++;
    }
    // size == size of the minimum vertex cover.
    // The actual mininum vertex cover is formed by:
    //    + nodes in L such that seenL[i] == false
    //    + nodes in R such that seenR[i] == true
}