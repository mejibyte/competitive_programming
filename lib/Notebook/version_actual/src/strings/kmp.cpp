///////////////////////////////////////////////////////////////
//      Knuth-Morris-Pratt algorithm for string matching     //
//                    Complexity: O(n + m)                   //
///////////////////////////////////////////////////////////////

// Reports all occurrences of 'needle' in 'haystack'.
void kmp(const string &needle, const string &haystack) {
  // Precompute border function
  int m = needle.size();
  vector<int> border(m + 1);
  border[0] = -1;
  for (int i = 0; i < m; ++i) {
    border[i+1] = border[i];
    while (border[i+1] > -1 and
           needle[border[i+1]] != needle[i]) {
      border[i+1] = border[border[i+1]];
    }
    border[i+1]++;
  }

  // Now the actual matching
  int n = haystack.size();
  int seen = 0;
  for (int i = 0; i < n; ++i){
    while (seen > -1 and needle[seen] != haystack[i]) {
      seen = border[seen];
    }
    if (++seen == m) {
      printf("Needle occurs from %d to %d\n", i - m + 1, i);
      seen = border[m];
    }
  }
}