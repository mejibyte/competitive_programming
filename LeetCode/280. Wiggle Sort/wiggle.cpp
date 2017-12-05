class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int next = i;
            for (int j = i + 1; j < n; ++j) {
                if (i % 2 == 0 and nums[j] < nums[next]) { // put min element in position i.
                    next = j;
                }
                if (i % 2 == 1 and nums[j] > nums[next]) { // put max element in position i.
                    next = j;
                }
            }
            swap(nums[i], nums[next]);
        }
    }
};
