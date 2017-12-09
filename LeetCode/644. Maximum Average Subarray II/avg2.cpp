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

        vector<double> least(n+1, 0.0);
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            sum += a[i] - mid;
            least[i+1] = min(least[i+1], sum);
            least[i+1] = min(least[i+1], least[i]);
        }

        sum = 0.0;
        for (int q = 0; q < n; ++q) {
            sum += a[q] - mid;
            int p = q-k+1;
            if (p < 0) continue;
            if (sum - least[p] >= 0) {
                return true;
            }
        }
        return false;
    }
};
