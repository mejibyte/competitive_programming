// Knuth-Morris-Pratt algorithm for string matching
// Complexity: O(n + m)

// Reports all occurrences of 'needle' in 'haystack'.
void kmp(const string &needle, const string &haystack) {
  // Precompute border function
  int m = needle.size();
  vector<int> border(m);
  border[0] = 0;
  for (int i = 1; i < m; ++i) {
    border[i] = border[i - 1];
    while (border[i] > 0 and needle[i] != needle[border[i]]) {
       border[i] = border[border[i] - 1];
    }
    if (needle[i] == needle[border[i]]) border[i]++;
  }

  // Now the actual matching
  int n = haystack.size();
  int seen = 0;
  for (int i = 0; i < n; ++i){
    while (seen > 0 and haystack[i] != needle[seen]) {
      seen = border[seen - 1];
    }
    if (haystack[i] == needle[seen]) seen++;
    
    if (seen == m) {
      printf("Needle occurs from %d to %d\n", i - m + 1, i);
      seen = border[m - 1];
    }
  }
}