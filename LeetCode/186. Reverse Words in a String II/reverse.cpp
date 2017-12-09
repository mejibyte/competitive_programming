class Solution {
public:
    void reverseWords(vector<char>& str) {
        for (int i = 0, j = str.size() - 1; i < j; i++, j--) {
            swap(str[i], str[j]);
        }
        for (int k = 0; k < str.size(); ++k) {
            if (str[k] == ' ') continue;
            int q = k;
            while (q+1 < str.size() and str[q+1] != ' ') q++;
            for (int i = k, j = q; i < j; i++, j--) {
                swap(str[i], str[j]);
            }
            k = q;
        }
    }
};
