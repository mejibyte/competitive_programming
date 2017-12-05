class Solution {
public:
    int smallestDistancePair(vector<int>& a, int k) {
        sort(a.begin(), a.end());

        int low = 0, high = a.back() - a.front();
        while (low < high) {
            int m = (low + high) / 2;
            if (f(a, m) >= k) {
                high = m;
            } else {
                low = m + 1;
            }
        }
        assert(low == high);
        return low;
    }

    // Counts how many pairs there are with distance <= dist in linear time.
    int f(const vector<int>& a, int dist) {
        int ans = 0;
        for (int i = 0, j = 0; i < a.size(); ++i) {
            while (j < a.size() and a[j] - a[i] <= dist) j++;
            if (j - 1 > i and a[j - 1] - a[i] <= dist) {
                ans += j - i - 1;
            }
        }
        return ans;
    }
};
