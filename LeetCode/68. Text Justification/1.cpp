class Solution {
public:
    string buildLine(vector<string>& words, int start, int end, int maxWidth) {
        if (end >= words.size()) {
            // last line
            stringstream sout;
            for (int k = start; k < end; ++k) {
                if (k > start) {
                    sout << " ";
                }
                sout << words[k];
            }
            while (sout.str().size() < maxWidth) sout << " ";
            return sout.str();
        }

        int numWords = end - start;
        int usedLength = 0;
        for (int k = start; k < end; ++k) {
            usedLength += words[k].size();
        }
        int spacesToDistribute = maxWidth - usedLength;
        //printf("spacesToDistribute = %d\n", spacesToDistribute);
        int buckets = numWords - 1;
        //printf("buckets = %d\n", buckets);
        int needExtra = buckets > 0 ? spacesToDistribute % buckets : 0;
        int perBucket = buckets > 0 ? spacesToDistribute / buckets : 0;

        //printf("perBucket = %d, needExtra = %d\n", perBucket, needExtra);
        stringstream sout;
        for (int k = start; k < end - 1; ++k) {
            sout << words[k];
            for (int i = 0; i < perBucket; i++) sout << " ";
            int at = k - start;
            if (at < needExtra) sout << " ";
        }
        assert(end -1 <= words.size());
        sout << words[end - 1];
        while (sout.str().size() < maxWidth) sout << " ";
        return sout.str();
    }

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> answer;

        int i = 0; // words[i...n) remaining
        while (i < words.size()) {
            int lengthSoFar = 0;
            int j = i; // j will be first index of word in next line
            while (j < words.size()) {
                int wordsInThisLine = j - i + 1;
                int tentativeLength = lengthSoFar + words[j].size() + (wordsInThisLine - 1);
                if (tentativeLength > maxWidth) {
                    break;
                }

                lengthSoFar += words[j].size();
                j++;
            }

            //printf("next line: i=%d, j=%d\n", i, j);
            //for (int k = i; k < j; ++k) cout << words[k] << "  "; cout << endl;

            // check here if I'm in last line
            // otherwise add spaces
            answer.push_back(buildLine(words, i, j, maxWidth));

            i = j;
        }

        return answer;
    }
};
