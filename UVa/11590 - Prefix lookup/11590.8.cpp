//Accepted
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

#define D(x) cout << #x " = " << (x) << endl

typedef unsigned long long Int;
const int BUFSIZE = 256;
char buf[BUFSIZE];

int M;
map<string, Int> ans;

struct node{
  node * left, * right;
  bool end; //is this node a complete prefix?
  node(bool e) : end(e) {
    left = right = NULL;
  }
};

//not used, because I love to waste memory (makes me feel sexy)
void clean(node * n){
  if (n == NULL) return;
  clean(n->left); clean(n->right);
  delete n;
}

Int f(string s, node * n){ //s = string built so far, n = the node we are standing at
  Int left = 0, right = 0, ret = 0;
  if (n->left != NULL){
    left = f(s + "0", n->left);
  }
  if (n->right != NULL){
    right = f(s + "1", n->right);
  }
  ret += left + right;

  if (n->end){
    Int howmany;
    if (M - s.size() < 64){ //we are safe from overflow
      Int x = ((1ULL) << (M - s.size())); //2^(m - |s|)
      howmany = x - left - right;
    }else{ //2^64 overflows!
      Int x = 0;
      x = ~x; // (x = ~0ULL) <-> (x = 2^64 - 1)
      howmany = x - left - right + 1;
    }
    ret += howmany;
    ans[s] = howmany;
  }
  return ret;
}

int main(){
  int n;
  while (scanf("%d%d\n", &n, &M)==2 && !(n == 0 && M == 0)){
    ans.clear();
    node * root = new node(true);
    while (n--){
      scanf("%s", buf);
      node * cur = root;
      for (int i=0; ; ++i){
        if (buf[i] == '*'){
          cur->end = true;
          break;
        }
        if (buf[i] == '0'){
          if (cur->left == NULL) cur->left = new node(false);
          cur = cur->left;
        }else if (buf[i] == '1'){
          if (cur->right == NULL) cur->right = new node(false);
          cur = cur->right;
        }
      }
    }

    f("", root);

    int K;
    scanf("%d\n", &K);
    while (K--){
      scanf("%s", buf);
      buf[strlen(buf)-1] = 0; //delete *
      Int t = ans[string(buf)];
      printf("%llu\n", t);
    }
    puts("");
  }
  return 0;
}
