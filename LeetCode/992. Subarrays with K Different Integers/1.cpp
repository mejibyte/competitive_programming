// O(n^2) times out
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        int answer = 0;
        for (int i = 0; i < A.size(); ++i) {
            unordered_set<int> seen;
            for (int j = i; j < A.size(); ++j) {
                seen.insert(A[j]);
                if (seen.size() == K) {
                    answer++;
                }
                if (seen.size() > K) {
                    break;
                }
            }
        }
        return answer;
    }
};


