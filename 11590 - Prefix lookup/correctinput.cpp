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
  int n, m;
  while (cin >> n >> m && (n || m)){
    assert(1 <= n && n <= 20000);
    assert(1 <= m && m <= 20000);
    string s;
    getline(cin, s);
    assert(s == "");
    for (int i=0; i<n; ++i){
      getline(cin, s);
      assert(s.size() > 1 && s[0] != '*');
    }

    int k;
    cin >> k;
    assert(0 < k && k < 1000);
    getline(cin, s);
    assert(s == "");

    for (int i=0; i<k; ++i){
      getline(cin, s);
      assert(s.size() > 0);
    }

    getline(cin, s);
    assert(s == "");

    printf("Good!\n");
  }
  return 0;
}
