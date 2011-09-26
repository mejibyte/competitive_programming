using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

template <class T> string toStr(const T &x){ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x){ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl


int main(){
  srand(time(0));
  int casos = 1000;
  while (casos--){
    int m, n;
    m = random() % 64 + 1;
    m = 64;
    n = random() % 2 + 1;
    vector<string> prefixes;

    printf("%d %d\n", n, m);
    for (int i=0; i<n; ++i){
      int len = random() % m + 1;
      string s = "";
      for (int i=0; i<len; ++i){
        char c = random() % 2 + '0';
        s += c;
      }
      s += "*";
      prefixes.push_back(s);
      cout << s << endl;
    }
    prefixes.push_back("*");

    int k = (4*n) + 1;
    k = min(k, 1000);
    printf("%d\n", k);
    while (k--){
      cout << prefixes[random() % prefixes.size()] << endl;
    }
    cout << endl;
  }
  puts("0 0");
  return 0;
}
