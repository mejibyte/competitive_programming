class Solution {
public:
    string toHex(int num) {

        const string digits = "0123456789abcdef";

        unsigned int x = static_cast<unsigned int>(num);
        string answer;
        do {
            answer = digits.substr(x % 16, 1) + answer;
            x /= 16;
        } while (x != 0);
        return answer;
    }
};