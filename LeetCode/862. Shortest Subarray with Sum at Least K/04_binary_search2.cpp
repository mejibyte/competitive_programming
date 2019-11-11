class Solution {
public:
    int shortestSubarray(vector<int>& a, int k) {
        int n = a.size();
        if (n == 0) return -1;
        assert(n >= 1);

        vector<int> sum(n+1);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + a[i-1];
        }

        // Here, the sum of subarray a[i,j] is sum[j+1] - sum[i] (Let's call this Eq. 1)
        // If we assume we fix j (and we take the best answer among all j's), the problem can be
        // re-phrased like this:
        //
        // Given a fixed j, find the max i such that i <= j and sum of subarray a[i,j] >= k
        // This is equivalent to:
        // Given a fixed j, find the max i such that i <= j and sum[j+1] - sum[i] >= k (by Eq. 1)
        // This is equivalent to:
        // Given a fixed j, find the max i such that i <= j and sum[i] <= sum[j+1] - k (by simple algebra)
        // In other words, we want to find the largest i among the indexes we have seen so far that
        // has sum[i] "small enough".
        //
        // We can do this quickly like this:
        //
        // First, wee keep a data structure which is a list of pairs of <sum[i], i> (for all i <= j),
        // but we make sure the pairs are sorted by increasing values of sum[i]. In other words,
        // once we insert a new element, we remove ALL elements that have a larger sum that the new one.
        // This list will also have elements sorted by increasing values of i  (because we insert elements
        // left to right).
        //
        // The important observation why we do this is that if we have two valid solutions a[i0,j]
        // and a[i1,j] with i0 <= i1 but sum[i0] > sum[i1], the solution with i1 is ALWAYS better
        // (because it has a larger i, and we are looking for the max i, and it is still small enough
        // because sum[i0] was already small enough and sum[i1] < sum[i0]).
        // In other words, if we come across a new index i1 that has a smaller sum that index i0,
        // i1 "overshadows" i0 and we will never need i0 again, so we can remove it from our
        // data structure.
        // By doing this repeatedly, we end up with a monotonically increasing sequence.
        // (This is similar to the idea of implementing a FIFO queue that also supports the getMin()
        // operation).
        //
        // With this data structure, we can use binary search to find the largest sum that is still
        // "small enough" ("small enough" means <= sum[j+1] - k).
        // Binary search works because the list we have is sorted by increasing values of sums
        // and also has increasing values of i's, so finding the largest sum that is "small enough"
        // also gives is the max i that we need.
        int best = -1;
        vector<pair<int, int>> seen; // <sum, index>
        for (int j = 0; j < n; ++j) {
            // Remove all elements with larger sum that the new one.
            while (seen.size() > 0 and seen.back().first > sum[j]) {
                seen.pop_back();
            }
            // Insert the new one.
            seen.push_back({sum[j], j});

            // Using binary search, find the first element strictly greater than <sum[j+1] - k, infinity>.
            // This is one past the answer we need.
            pair<int, int> limit = make_pair(sum[j+1] - k, numeric_limits<int>::max());
            auto p = upper_bound(seen.begin(), seen.end(), limit);
            if (p == seen.begin()) {
                 // We didn't find an i with sum small enough.
                continue;
            }
            p--;

            // We found a solution [i, j].
            int i = p->second;
            assert(p->first == sum[i]);
            assert(sum[j+1] - sum[i] >= k);

            int length = j - i + 1;
            if (best == -1 or length < best) {
                best = length;
            }
        }
        return best;
    }
};
