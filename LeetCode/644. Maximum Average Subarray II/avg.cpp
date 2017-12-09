class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double low = -1e9, high = 1e9;
        for (int r = 0; r < 250; ++r) {
            double mid = (low + high) / 2;
            if (works(nums, k, mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }

    // Returns true if there is a contiguous subarray of length >= k such that it's average is >= m.
    bool works(const vector<int> &a, int k, double mid) {
        int n = a.size();

        vector<double> b(n);
        for (int i = 0; i < n; ++i) {
            b[i] = a[i] - mid;
        }
        vector<double> sum = b;
        for (int i = 1; i < n; ++i) {
            sum[i] += sum[i-1];
        }
        vector<double> least = sum;
        for (int i = 0; i < n; ++i) {
            least[i] = min(least[i], 0.0);
            if (i-1 >= 0) least[i] = min(least[i], least[i-1]);
        }

        for (int q = 0; q < n; ++q) {
            int p = q-k+1;
            if (p < 0) continue;
            if (sum[q] - (p-1 >= 0 ? least[p-1] : 0) >= 0) {
                return true;
            }
        }
        return false;
    }
};
