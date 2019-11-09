// O(n)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        assert(n >= 1);

        // Let's define sum[i,j] as the sum of all elements in nums between i and j (inclusive).
        // In other words, sum[i,j] = nums[i] + nums[i+1] + ... + nums[j]
        // For convenience, let's also assume sum[i,j] == 0 for empty subarrays.
        //
        // Then the problem can be restated as follows:
        // Count how many pairs (i, j) exist such that i <= j and sum[i,j] == k.
        //
        // But sum[i,j] == sum[0,j] - sum[0, i-1] (expand it on paper if you don't see why)
        //
        // So the problem can be rephrased as:
        // Count how many pairs (i,j) exist such that i <= j and sum[0,j] - sum[0, i-1] == k.
        //
        // Let's assume we know j, then bythe problem can be restated as:
        // Count how many indexes i exist such that i <= j and sum[0,i-1] == k - sum[0,j] (just by reordering the equality above)
        //
        // We can count this as follows:
        // We start moving the j index from left to right.
        // In each iteration, we make sure the map contains the value of sum[0,i-1] for all possible i <= j. We can insert these values on the loop as we go.
        // The we compute k - sum[0,j] and use the map to count how many i's we've seen so far such that sum[0,i-1] == k - sum[0,j].

        unordered_map<int, int> seen;
        int sum = 0, answer = 0;

        for (int j = 0; j < n; ++j) {
            seen[sum]++; // After this line, the map contains sum[0,0], sum[0,1], ..., sum[0,i-1] for all possible i <= j
            sum += nums[j]; // After this line, sum == sum[0,j]
            int need = sum - k; // need == sum[0,j] - k
            answer += seen[need];
        }
        return answer;
    }
};
