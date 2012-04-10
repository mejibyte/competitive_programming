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

const int N = 1000005; // Maximum size of input string
int str[N]; //input
int rank[N], pos[N]; //output
int cnt[N], next[N]; //internal
bool bh[N], b2h[N];
 
// Compares two suffixes according to their first characters
bool smaller_first_char(int a, int b){
  return str[a] < str[b];
}
 
void suffixSort(int n){
  //sort suffixes according to their first characters
  for (int i=0; i<n; ++i){
    pos[i] = i;
  }
  sort(pos, pos + n, smaller_first_char);
  //{pos contains the list of suffixes sorted by their first
  //character}
 
  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
    b2h[i] = false;
  }
 
  for (int h = 1; h < n; h <<= 1){
    //{bh[i] == false if the first h characters of pos[i-1] ==
    // the first h characters of pos[i]}
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      next[i] = j;
      buckets++;
    }
    if (buckets == n) break; // We are done! Lucky bastards!
    //{suffixes are separted in buckets containing strings
    // starting with the same h characters}
 
    for (int i = 0; i < n; i = next[i]){
      cnt[i] = 0;
      for (int j = i; j < next[i]; ++j){
        rank[pos[j]] = i;
      }
    }
 
    cnt[rank[n - h]]++;
    b2h[rank[n - h]] = true;
    for (int i = 0; i < n; i = next[i]){
      for (int j = i; j < next[i]; ++j){
        int s = pos[j] - h;
        if (s >= 0){
          int head = rank[s];
          rank[s] = head + cnt[head]++;
          b2h[rank[s]] = true;
        }
      }
      for (int j = i; j < next[i]; ++j){
        int s = pos[j] - h;
        if (s >= 0 && b2h[rank[s]]){
          for (int k = rank[s]+1; !bh[k] && b2h[k]; k++){
              b2h[k] = false;
          }
        }
      }
    }
    for (int i=0; i<n; ++i){
      pos[rank[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    rank[pos[i]] = i;
  }
}
////////////////////////////////////////////////////////////////
//               End of Suffix Arrays implementation          //
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//         Begin of Longest Common Prefix implementation      //
////////////////////////////////////////////////////////////////
//                            O(n)                            //
//   Refer to "Linear-Time Longest-Common-Prefix Computation  //
//     in Suffix Arrays and Its Applications" by Toru Kasai,  //
// Gunho Lee, Hiroki Arimura, Setsuo Arikawa, and Kunsoo Park.//
////////////////////////////////////////////////////////////////

int height[N];
// - height[i] = length of the longest common prefix of suffix
//   pos[i] and suffix pos[i-1]
// - height[0] = 0
void getHeight(int n){
  for (int i=0; i<n; ++i) rank[pos[i]] = i;
  height[0] = 0;
  for (int i=0, h=0; i<n; ++i){
    if (rank[i] > 0){
      int j = pos[rank[i]-1];
      while (i + h < n && j + h < n && str[i+h] == str[j+h]){
          h++;
      }
      height[rank[i]] = h;
      if (h > 0) h--;
    }
  }
}
////////////////////////////////////////////////////////////////
//          End of Longest Common Prefix implementation       //
////////////////////////////////////////////////////////////////

char s[N];

int main(){
    gets(s);
    int n = strlen(s);
    for (int i = 0; i < n; ++i) {
        str[i] = s[i];
    }
    suffixSort(n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", pos[i]);
    }
    return 0;
}