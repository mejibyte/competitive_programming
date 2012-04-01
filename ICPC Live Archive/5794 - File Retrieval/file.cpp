// Andrés Mejía

// Accepted, but slow.

// Complexity: O(n log^2 n) when building the suffix array
//             O(n log n) for RMQ to solve the queries

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

const int MAXN = 60 * 10005;

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

using namespace SuffixArray;
set< long long > seen;

int cnt[MAXN][60], F;
int who[MAXN];
int rmq[MAXN][20];

void add(int i, int j) {
    long long mask = 0;
    assert(i > 0);
    assert(i <= j);
    for (int k = 0; k < F; ++k) {
        if (cnt[j][k] - cnt[i - 1][k] > 0){
            mask |= (1LL << k);
        }
    }
    seen.insert(mask);
}

// [from, to]
int query(int from, int to) {
    int n = to - from + 1;
    if (n == 1) return rmq[from][0];
    int p = 0;
    while ( (1 << (p + 1)) < n ) p++;
    int length = 1 << p;
    assert(length < n and 2*length >= n);
    
    int left = rmq[from][p];
    int right = rmq[to - length + 1][p];
    
    return lcp[left] <= lcp[right] ? left : right;
}

int main(){
    while (scanf("%d ", &F) == 1) {
        if (F == 0) break;
        //vector<string> files;
        int N = 0;
        text[N] = '\0';
        for (int i = 0; i < F; ++i) {
            static char buffer[10005];
            scanf(" %s ", buffer);
            //files.push_back(string(buffer));
            int add = strlen(buffer);
            strcat(text + N, buffer);
            N += add;
            text[N++] = 'a' - i - 1;
            text[N] = '\0';
        }
        
        if (F == 1) {
            puts("1");
            continue;
        }
        
        #ifdef LOCAL
        double timeBefore = clock();
        #endif
        
        assert(N == strlen(text));
        SuffixArray::build(N);
        for (int i = 0; i + 1 < N; ++i) {
            SuffixArray::lcp[i] = SuffixArray::lcp[i + 1];
        }
        SuffixArray::lcp[N - 1] = 0;
        
        #ifdef LOCAL
        printf("Time after suffix array: %.3lf\n", (clock() - timeBefore) / CLOCKS_PER_SEC);
        #endif
        
        vector<int> L(N);
        for (int i = N - 1, k, len; i >= 0; --i) {
            if (text[i] < 'a') {
                len = 0;
                k = 'a' - text[i] - 1;
            } else {
                len++;
                L[SuffixArray::rank[i]] = len;
                who[SuffixArray::rank[i]] = k;
            }
        }
        
        for (int i = 0; i < F; ++i) cnt[0][i] = 0;
        cnt[0][who[0]]++;
        for (int i = 1; i < N; ++i){
            for (int j = 0; j < F; ++j) {
                cnt[i][j] = cnt[i - 1][j];
            }
            cnt[i][who[i]]++;
        }
        
        
        for (int i = 0; i < N; ++i) rmq[i][0] = i;
        for (int p = 1; p < 20; ++p) {
            int length = 1 << p;
            for (int i = 0; i + length <= N; ++i) {
                int half = length >> 1;
                
                int left = rmq[i][p - 1];
                int right = rmq[i + half][p - 1];
                
                rmq[i][p] = lcp[left] <= lcp[right] ? left : right;
            }
        }
        
        seen.clear();
        for (int i = F; i < N; ++i){
            if (lcp[i - 1] < L[i] and lcp[i] < L[i]) add(i, i);
        }
        
        //for (int i = 0; i < N; ++i) printf("%d ", lcp[i]); puts("");
        
        queue<int> q;
        q.push(F - 1);
        q.push(N - 2);
        while (q.size() > 0) {
            int from = q.front(); q.pop();
            int to = q.front(); q.pop();
            assert(from - 1 >= 0 and to + 1 < N);
            
            int split = query(from, to);
            if (lcp[from - 1] < lcp[split] and lcp[to + 1] < lcp[split]) { // this interval is OK
                add(from, to + 1);
            }
            
            assert(from <= split and split <= to);
            if (from <= split - 1) { // push left
                q.push(from);
                q.push(split - 1);
            }
            
            if (split + 1 <= to) { // push right
                q.push(split + 1);
                q.push(to);
            }
        }
        

        
        printf("%d\n", seen.size());
    }
    return 0;
}