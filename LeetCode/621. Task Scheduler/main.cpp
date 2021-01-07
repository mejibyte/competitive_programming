class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> capacity;
        map<char, int> freq;
        for (auto c : tasks) {
            freq[c]++;
        }
        for (auto p : freq) {
            int next = 0;
            int count = p->second;
            while (count > 0) {
                if (next < capacity.size()) {
                    if (capacity[next] > 0) {
                        capacity[next]--;
                        count--;
                    }
                    next++;
                } else {
                    capacity.push_back(n + 1);
                }
            }
        }
        return capacity.size() * (n+1) - capacity.back();
    }
};