class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<long long> a;
        for (int k : nums) a.push_back(k);
        a.push_back(upper+1LL);

        long long from = lower;
        vector<string> ans;
        for (int i = 0; i < a.size(); ++i) {
            long long to = a[i]-1LL;
            if (from < to) {
                ans.push_back(toS(from) + "->" + toS(to));
            } else if (from == to) {
                ans.push_back(toS(from));
            }
            from = a[i]+1LL;
        }
        return ans;
    }

    string toS(long long i) {
        stringstream sin;
        sin << i;
        return sin.str();
    }
};
