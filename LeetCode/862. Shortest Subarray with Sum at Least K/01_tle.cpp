

const int inf = numeric_limits<int>::max();

class Solution {
public:
    int shortestSubarray(vector<int>& a, int k) {
        int n = a.size();
        if (n == 0) return -1;
        assert(n >= 1);

        vector<int> sum(n);
        sum[0] = a[0];
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i-1] + a[i];
        }

        int low = 1, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            int best = maxSum(a, sum, n, mid);

            //printf("mid=%d, maxSum(mid)=%d\n", mid, best);
            if (best >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        assert(low == high);
        int best = maxSum(a, sum, n, low);
        //printf("ans=%d, maxSum(ans)=%d\n", low, best);
        if (best >= k) return low;
        return -1;
    }


    // Returns the maximum sum of all contiguous subarrays of 1 <= length <= L in a.
    // L >= 1
    int maxSum(const vector<int>& a, const vector<int>& sum, int n, int L) {
        //printf("maxSum called with L = %d\n", L);
        for (int i = 0; i < n; ++i) {
            //printf("sum[%d]=%d\n", i, sum[i]);
        }
        vector<int> dp(n);
        dp[0] = a[0];

        multiset<int> q;
        for (int i = 0; i < L; ++i) q.insert(0);

        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1];

            q.insert(sum[i - 1]);

            int to_remove = 0;
            if (i - L - 1 >= 0) {
                to_remove = sum[i - L - 1];
            }
            //printf("i=%d, to_remove=%d\n", i, to_remove);

            auto it = q.find(to_remove);
            if (it != q.end()) {
                q.erase(it);
            }

            //printf("q.size()=%d, L=%d\n", q.size(), L);
            assert(q.size() == L);
            int option = sum[i] - *q.begin();

            dp[i] = max(dp[i], option);
        }
        return dp[n - 1];
    }
};
