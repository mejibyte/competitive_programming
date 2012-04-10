using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 100005;

// O(n log^2 n) time, 16 bytes/char overhead.
char text[MAXN];
namespace SuffixArray {
  // Input: text, N
  // Output: sa[] is a sorted list of offsets to all non-empty suffixes,
  // lcp[i] = length of longest common prefix of text+sa[i] and text+sa[i-1], and lcp[0] = 0.
  long long key[MAXN]; int sa[MAXN], rank[MAXN], *lcp=(int*)key;
  struct Cmp { bool operator()(int i, int j) const { return key[i]<key[j]; } };

  void build(int N) {
      for (int i = 0; i < N; i++) { sa[i] = i; key[i] = text[i]; }
      sort(sa, sa+N, Cmp());
      for (int K = 1; ; K *= 2) {
          for (int i = 0; i < N; i++)
              rank[sa[i]] = i>0 && key[sa[i-1]]==key[sa[i]] ? rank[sa[i-1]] : i;
          if (K >= N) break;
          for (int i = 0; i < N; i++)
              key[i] = rank[i] * (N+1LL) + (i+K < N ? rank[i+K]+1 : 0);
          sort(sa, sa+N, Cmp());
      }
      for(int i = 0, size = 0; i < N; i++) if (rank[i] > 0) {
          int j = sa[rank[i] - 1];
          while(text[i + size] == text[j + size]) ++size;
          lcp[rank[i]] = size;
          if (size > 0) --size;
      }
      lcp[0] = 0;
  }
};

int main(){
    gets(text);
    int n = strlen(text);
    SuffixArray::build(n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", SuffixArray::sa[i]);
    }
    return 0;
}