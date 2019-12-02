class Solution {
public:
    vector<int> num;
    vector<int> digits;

    int atMostNGivenDigitSet(vector<string>& D, int N) {
        if (N == 0) return 0;
        num.clear();
        digits.clear();
        memo.clear();

        for (auto s : D) digits.push_back(s[0] - '0');
        sort(digits.begin(), digits.end());
        while (N > 0) {
            num.push_back(N % 10);
            N /= 10;
        }
        reverse(num.begin(), num.end());

        return count(0, true, false) - 1; // -1 is to uncount 0
    }

    map< vector<int>, int> memo;

    // Try to place the "at"-th digit from left to right.
    int count(int at, bool canUseZero, bool alreadyLess) {
        if (at >= num.size()) return 1;

        if (memo.count({at, canUseZero, alreadyLess}) > 0) {
            return memo[{at, canUseZero, alreadyLess}];
        }

        int ans = 0;
        if (canUseZero) {
            if (alreadyLess || 0 <= num[at]) { // In theory unnecessary because num[at] >= 0
                ans += count(at+1, true, alreadyLess || 0 < num[at]);
            }
        }
        for (auto d : digits) {
            if (alreadyLess || d <= num[at]) { // Otherwise I will exceed the threshold.
                ans += count(at+1, false, alreadyLess || d < num[at]);
            }
        }
        memo[{at, canUseZero, alreadyLess}] = ans;
        return ans;
    }
};