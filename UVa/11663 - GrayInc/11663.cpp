/*
  Time limit exceeded!

  I know the algorithm is fast enough (it's O(m * n)) but the implementation is slow
 */
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

string next(const string &s);
string prev(const string &s);

bool looksLike0000(const string &s){
  for (int i=0; i<s.size(); ++i) if (s[i] != '0') return false;
  return true;
}

bool looksLike1000(const string &s){
  return s[0] == '1' && looksLike0000(s.substr(1));
}

string next(const string &s){
  if (s.size() == 1) return s == "0" ? "1" : "0";
  string t = s.substr(1);
  if (s[0] == '0'){
    if (looksLike1000(t)){
      return "1" + t;
    }else{
      return "0" + next(t);
    }
  }else{
    if (looksLike0000(t)){
      return "0" + t;
    }else{
      return "1" + prev(t);
    }
  }
}

string prev(const string &s){
  if (s.size() == 1) return s == "0" ? "1" : "0";
  string t = s.substr(1);
  if (s[0] == '0'){
    if (looksLike0000(t)){
      return "1" + t;
    }else{
      return "0" + prev(t);
    }
  }else{
    if (looksLike1000(t)){
      return "0" + t;
    }else{
      return "1" + next(t);
    }
  }
}

int main(){
  int m;
  string s;
  while (cin >> m >> s && m){
    while (m--) s = next(s);
    cout << s << endl;
  }
  return 0;
}
