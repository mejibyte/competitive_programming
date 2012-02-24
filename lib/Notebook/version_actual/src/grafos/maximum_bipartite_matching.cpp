// Maximum Bipartite Matching
// Complexity: O(VE)

// Finds a maximum bipartite matching for two sets of
// size L and R.

// How to use:
// Set g[i][j] to true if element i of the Left set can
// be paired with element j of the Right set.
// Fill the table for all 0 <= i < L and 0 <= j < R.

// matchL[i] will contain i's match in the Right set
// and matchR[j] will contain j's match in the Left set.

bool g[MAXN][MAXN], seen[MAXN];
int L, R, matchL[MAXN], matchR[MAXN];

bool assign(int i) {
    for (int j = 0; j < R; ++j) if (g[i][j] and !seen[j]) {
        seen[j] = true;
        if ( matchR[j] < 0 or assign(matchR[j]) )
            return matchL[i] = j, matchR[j] = i, true;
    }
    return false;
}

int maxBipartiteMatching() {
    for (int i = 0; i < L; ++i) matchL[i] = -1;
    for (int j = 0; j < R; ++j) matchR[j] = -1;
    int ans = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < R; ++j) seen[j] = false; // or memset
        if (assign(i)) ans++;
    }
    return ans;
}

