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
#define D(x) cout << #x " = " << (x) << endl

int next(const string &s, int i);
int prev(const string &s, int i);

bool looksLike0000(const string &s, int i){
  for (; i<s.size(); ++i) if (s[i] != '0') return false;
  return true;
}

bool looksLike1000(const string &s, int i){
  if (s[i] != '1') return false;
  for (++i; i<s.size(); ++i) if (s[i] != '0') return false;
  return true;
}

int next(const string &s, int i){
  if (i == s.size() - 1) return i;
  if (s[i] == '0'){
    if (looksLike1000(s, i+1)){
      return i;
    }else{
      return next(s, i+1);
    }
  }else{
    if (looksLike0000(s, i+1)){
      return i;
    }else{
      return prev(s, i+1);
    }
  }
}

int prev(const string &s, int i){
  if (i == s.size() - 1) return i;
  if (s[i] == '0'){
    if (looksLike0000(s, i+1)){
      return i;
    }else{
      return prev(s, i+1);
    }
  }else{
    if (looksLike1000(s, i+1)){
      return i;
    }else{
      return next(s, i+1);
    }
  }
}

int main(){
  int m;
  string s;
  while (cin >> m >> s && m){
    while (m--){
      int where = next(s, 0);
      s[where] = s[where] == '0' ? '1' : '0';
    }
    cout << s << endl;
  }
  return 0;
}
