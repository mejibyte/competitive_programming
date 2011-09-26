//AC
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

char mat[25][25];

int main(){
  int casos;
  cin >> casos;
  for (int C=1; C<=casos; ++C){
    cout << "Case " << C << ": ";
    int rows, cols, important, notimportant;
    cin >> rows >> cols >> important >> notimportant;

    map<char, int> freq;
    For(i, 0, rows){
      For(j, 0, cols){
        cin >> mat[i][j];
        freq[mat[i][j]]++;
      }
    }
    vector<pair<int, char> > v;
    foreach(p, freq){
      v.push_back(make_pair(p->second, p->first));
    }
    sort(v.rbegin(), v.rend());
    int ans = 0;
    for (int i=0; i<v.size(); ++i){
      if (v[i].first == v[0].first) ans += v[i].first * important;
      else ans += v[i].first * notimportant;
    }
    cout << ans << endl;
  }
  return 0;
}
