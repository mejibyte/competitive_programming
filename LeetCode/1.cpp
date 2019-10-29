class Solution {
public:
    int numJewelsInStones(string jewels, string have) {
        int answer = 0;
        for (auto c : have) {
            answer += (jewels.find(c) != string::npos);
        }
        return answer;
    }
};
