struct Trie {
  vector<vector<int>> data;
  map<pair<int, char>, int> next;

  Trie() : data(1, vector<int>()) { }

  void add(const string &s, int t) {
    int at = 0;
    for (char c : s) {
      assert(at < data.size());

      data[at].push_back(t);
      if (next.count({at, c}) == 0) {
          next[{at, c}] = data.size();
          data.push_back(vector<int>());
      }
      at = next[{at, c}];
    }
    data.at(at).push_back(t);
  }

  vector<int>& find(const string &s) {
      return data[walk(s)];
  }

  int walk(const string &s) {
    int at = 0;
    for (char c : s) {
      if (next.count({at, c}) == 0) {
          next[{at, c}] = data.size();
          data.push_back(vector<int>());
      }
      at = next[{at, c}];
    }
    return at;
  }
};

class WordFilter {
    Trie forward, backward;

public:
    WordFilter(vector<string> words) {
        for (int i = 0; i < words.size(); ++i) {
            string w = words[i];
            forward.add(w, i);
            reverse(w.begin(), w.end());
            backward.add(w, i);
        }
    }

    int f(string prefix, string suffix) {
        reverse(suffix.begin(), suffix.end());

        const vector<int>& a = forward.find(prefix);
        const vector<int>& b = backward.find(suffix);

        for (int i = a.size() - 1, j = b.size() - 1; i >= 0 and j >= 0; ) {
            if (a[i] == b[j]) {
                return a[i];
            }
            if (a[i] < b[j]) {
                j--;
            } else {
                i--;
            }
        }
        return -1;
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter obj = new WordFilter(words);
 * int param_1 = obj.f(prefix,suffix);
 */
