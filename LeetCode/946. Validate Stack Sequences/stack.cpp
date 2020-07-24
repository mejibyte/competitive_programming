class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        vector<int> s;
        int i = 0;
        for (int j = 0; j < popped.size(); ++j) {
            while (s.size() == 0 || s.back() != popped[j]) {
                if (i == pushed.size()) return false;
                s.push_back(pushed[i++]);
            }
            assert(s.size() > 0 and s.back() == popped[j]);
            s.pop_back();
        }
        return true;
    }
};