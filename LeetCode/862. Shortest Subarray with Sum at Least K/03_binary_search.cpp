// Accepted but slow:
// Runtime: 664 ms, faster than 5.14% of C++ online submissions for Shortest Subarray with Sum at Least K.

// Queue that allows getting min value inside of it in O(1).
class MinQueue {
  public:
    // O(1) amortized
    void push(int x) {
        while (q.size() > 0 and x <= q.back().first) {
            q.pop_back();
        }
        q.push_back({x, tail++});
    }

    // O(1)
    void pop() {
        assert(size() > 0 and q.size() > 0);
        if (q.front().second == head) {
            q.pop_front();
        }
        head++;
    }

    // O(1)
    int min() {
        assert(size() > 0 and q.size() > 0);
        return q.front().first;
    }

    int size() {
        return tail - head;
    }

  private:
    int head = 0, tail = 0;
    deque<pair<int, int>> q; // <value, index>
};

class Solution {
public:
    int shortestSubarray(vector<int>& a, int k) {
        int n = a.size();
        if (n == 0) return -1;
        assert(n >= 1);

        vector<int> sum(n+1);
        sum[0] = 0;
        for (int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + a[i];
        }

        // Binary search for upper bound of length of subarray
        int low = 1, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            int best = maxSum(a, sum, n, mid);

            if (best >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        assert(low == high);
        int best = maxSum(a, sum, n, low);
        if (best >= k) return low;
        return -1;
    }


    // Returns the maximum sum among all contiguous subarrays of length
    // between 1 and L (both inclusive) in a.
    // L >= 1
    int maxSum(const vector<int>& a, const vector<int>& sum, int n, int L) {
        int best = a[0];

        MinQueue q;
        for (int i = 0; i < n; ++i) {
            // Sums of all subarrays with length <= L ending in i:
            // sum[i+1] - sum[i] (length 1 ending in i)
            // sum[i+1] - sum[i-1] (length 2 ending in i)
            // sum[i+1] - sum[i-2] (length 3 ending in i)
            // ...
            // sum[i+1] - sum[i-L+1] (length L ending in i)
            //
            // We keep a sliding window to have
            // sum[i-L+1], ..., sum[i-2], sum[i-1], sum[i]
            // in the queue, and then we find the minimum in O(1)
            // to find the best possible answer ending in i.
            q.push(sum[i]);
            while (q.size() > L) {
                q.pop();
            }
            best = max(best, sum[i+1] - q.min());
        }

        return best;
    }
};
