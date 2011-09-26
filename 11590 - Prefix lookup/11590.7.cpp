/*
  Experimenting wiht the input...

  Accepted too.
 */
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

const int BUFSIZE = 512;
char buf[BUFSIZE];

#define D(x) cout << #x " is " << (x) << endl

typedef unsigned long long uint64;

struct node{
  bool end;
  node * left;
  node * right;
  node(bool end) : end(end) {
    left = right = NULL;
  }
  node * getLeft(){
    if (left == NULL) left = new node(false);
    return left;
  }
  node * getRight(){
    if (right == NULL) right = new node(false);
    return right;
  }
};

//returns 2^e
inline uint64 pow2(int e){
  if (e == 64) return 0;
  return uint64(1) << e;
}

void clean(node * cur){
  if (cur == NULL) return;
  clean(cur->left);
  clean(cur->right);
  delete cur;
}

int n, m;

/*
  Returns how many strings were counted under the tree rooted at cur, including it.
*/
uint64 alreadyCounted(node * cur, int depth = 0){
  if (cur == NULL) return 0;
  uint64 left = alreadyCounted(cur->left, depth + 1);
  uint64 right = alreadyCounted(cur->right, depth + 1);
  uint64 ret = left + right;
  if (cur->end){
    //count strings matched to this one
    ret += pow2(m - depth) - left - right;
  }
  return ret;
}


int main(){
  while (true){
    scanf("%d%d\n", &n, &m);
    if (n == 0 && m == 0) break;
    node * root = new node(true);
    for (int i=0; i<n; ++i){
      scanf("%s", buf);
      node * cur = root;
      for (int j=0; ; ++j){
        if (buf[j] == '*'){
          cur->end = true;
          break;
        }
        node * next;
        if (buf[j] == '0'){
          next = cur->getLeft();
        }else if (buf[j] == '1'){
          next = cur->getRight();
        }else{
          printf("Bad character %c at query %d, position %d\n", buf[j], i, j);
          //assert(false);
        }
        cur = next;
      }
    }
    int k;
    scanf("%d\n", &k);
    for (int i=0; i<k; ++i){
      scanf("%s", buf);
      node * cur = root;
      for  (int j=0; buf[j] != '*'; ++j){
        if (buf[j] == '0'){
          cur = cur->left;
        }else if (buf[j] == '1'){
          cur = cur->right;
        }
      }
      string s(buf);
      s = s.substr(0, s.size()-1);

      uint64 ans = pow2(m - s.size())
        - alreadyCounted(cur->left, s.size()+1) - alreadyCounted(cur->right, s.size()+1);
      printf("%llu\n", ans);
    }
    printf("\n");
    clean(root);
  }
  return 0;
}
