class Solution {
public:
    int lengthOfLIS(vector<int>& X) {
        int n = X.size();
        if (n == 0) return 0;

        // M[L] = index of smallest processed item that is the final element of a LIS of length L,
        // or -1 if there is no LIS of length L.
        vector<int> M(n + 1, -1);

        // P[i] = Index of predecessor in LIS that finishes on item i.
        vector<int> P(n);

        for (int i = 0; i < n; ++i) {
            // Find max L >= 1 such that X[ M[L] ] <= X[i], or make L = 0 if it doesn't exist
            int L = 0;
            for (int l = 1; l <= n; ++l) {
                if (M.at(l) != -1 and X[ M[l] ] < X[i]) {
                    L = l;
                }
            }

            // The best sequence I can make that ends on X[i] has length L+1.
            assert(L + 1 <= n);

            // The previous element is M[L] (which we know is smaller than X[i] if it exists).
            P[i] = M[L];

            // We a candidate to form a sequence of length L+1. Let's see if it beats the one
            // we had before to keep M[L+1] up-to-date with the index of the smallest tail
            // of a LIS of length L+1.
            if (M[L + 1] == -1 or X[i] < X[ M[L + 1] ]) {
                M[L + 1] = i;
            }
        }
        for (int l = n; l >= 1; --l) {
            if (M[l] != -1) return l;
        }
        assert(false);
    }
};
