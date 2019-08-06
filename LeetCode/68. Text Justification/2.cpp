class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> answer;
        int n = words.size();
        assert(n >= 1);
        vector<int> length(n + 1);
        length[0] = 0;
        for (int i = 0; i < n; ++i) {
            length[i+1] = words[i].size() + length[i];
        }

        for (int i = 0, j; i < n; ) {
            for (j = i; j < n; j++) {
                // Check if words [i, j] fits in this line. If it does, keep going. If it doesn't, break.
                int numWords = j - i + 1;
                if (length[j+1] - length[i] + (numWords - 1) > maxWidth) {
                    break;
                }
            }
            // use words [i, j) to build line.
            int numWords = j - i;
            if (j >= n or numWords == 1) {
                // last line
                string line = "";
                for (int k = i; k < j; ++k) {
                    if (k > i) line += " ";
                    line += words[k];
                }
                while  (line.size() < maxWidth) line += " ";
                answer.push_back(line);
            } else {
                int totalSpaces = maxWidth - (length[j] - length[i]);
                int buckets = numWords - 1;
                string line = "";
                for (int k = i; k < j; ++k) {
                    line += words[k];
                    if (k + 1 < j) {
                        int spacesHere = totalSpaces / buckets;
                        if (k - i < totalSpaces % buckets) {
                            spacesHere++;
                        }
                        while (spacesHere--) {
                            line += " ";
                        }
                    }
                }
                assert(line.size() == maxWidth);
                answer.push_back(line);
            }

            i = j;
        }

        return answer;
    }
};
