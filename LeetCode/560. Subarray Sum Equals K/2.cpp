// O(n log n)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        return count(nums, 0, nums.size() - 1, k);
    }
    // Returns count in [start, end] (both inclusive).
    int count(const vector<int>& nums, int start, int end, int k) {
        int n = end - start + 1;
        if (n == 0) return 0;
        if (n == 1) return (nums[start] == k);
        assert(n >= 2);

        // Split array in two non-empty halves.
        int half = start + n / 2;
        // [a b]
        //    ^half

        // [a b c]
        //    ^half

        // [a b c d]
        //      ^half

        assert(start <= half - 1); // Make sure left half has at least one element
        assert(half <= end); // Make sure right half has at least one element

        // Count answers for subarrays entirely on left side or entirely on right side.
        int answer = count(nums, start, half - 1, k) +
                     count(nums, half, end, k);

        // Count answers that cross both sides.
        unordered_map<int, int> seen_on_right;
        for (int sum = 0, i = half; i <= end; ++i) {
            sum += nums[i];
            seen_on_right[sum]++;
        }

        for (int sum = 0, i = half - 1; i >= start; --i) {
            sum += nums[i];
            int need = k - sum;
            answer += seen_on_right[need];
        }
        return answer;
    }

};
