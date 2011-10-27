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
template <class T> int Size(const T &x){ return (int)x.size(); }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl

typedef unsigned long long Int;
const int BUFSIZE = 128;
char buf[BUFSIZE];

int M;
map<string, Int> ans;

struct node{
  node * left, * right;
  bool end;
  node(bool e) : end(e) {
    left = right = NULL;
  }
};

void clean(node * n){
  if (n == NULL) return;
  clean(n->left); clean(n->right);
  delete n;
}


Int f(string s, node * n){
  Int left = 0, right = 0;
  if (n->left != NULL){
    left = f(s + "0", n->left);
  }
  if (n->right != NULL){
    right = f(s + "1", n->right);
  }
  if (n->end){
    Int x = ((1ULL) << (M - s.size())) - 1;
    if (M == 64 && s.size() == 0){
      x = ~(0ULL);
    }
    ans[s] = x - left - right + 1;
    //D(s); D(n->end);
    //D(ans[s]);
  }
  Int ret = 0;
  if (n->end){
    ret = ans[s];
  }
  return ret + left + right;
}

int main(){
  int n;
  while (cin >> n >> M && n && M){
    vector<string> prefixes(n+1, "");
    For(i, 0, n){
      cin >> prefixes[i];
      prefixes[i].resize(prefixes[i].size()-1); //delete *
    }

    map<string, int> ans;
    for (int i=0; i<(1<<M); ++i){
      string s = "";
      for (int k=0; k<M; ++k){
        char c = !!(i & (1 << k)) + '0';
        s = s + c;
      }
      int ibest = -1, lenbest = INT_MIN;
      for (int j=0; j<prefixes.size(); ++j){
        string prefix = prefixes[j];

        if (s.find(prefix) == 0){
          //cout << s << " starts with " << prefix << endl;
          if (lenbest < Size(prefix)){
            ibest = j;
            lenbest = prefix.size();
          }
        }
      }
      ans[prefixes[ibest]]++;

    }

    int K;
    cin >> K;
    while (K--){
      string q;
      cin >> q;
      q.resize(q.size()-1);
      cout << ans[q] << endl;
    }
    puts(" ");
  }
  return 0;
}
