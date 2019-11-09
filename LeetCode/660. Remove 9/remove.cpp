class Solution {
public:
    int newInteger(int n) {
        int ans = 0;
        int pow = 1;

        while (n > 0) {
            ans += (n % 9) * pow;
            n /= 9;
            pow *= 10;
        }
        return ans;
    }
};
