/*
  Runtime error
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define D(x) cout << #x " is " << (x) << endl

typedef unsigned long long uint64;

const int BUFSIZE = 512;
char buf[BUFSIZE];

struct node{
    string s;
    bool end;
    node * left;
    node * right;
    node(bool end) : end(end) {
        left = right = NULL;
        s = "";
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

//return 2^e
uint64 pow2(int e){
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
uint64 alreadyCounted(node * cur){
    if (cur == NULL) return 0;
    uint64 left = alreadyCounted(cur->left);
    uint64 right = alreadyCounted(cur->right);
    uint64 ret = left + right;
    if (cur->end){
        //count strings matched to this one
        ret += pow2(m - cur->s.size()) - left - right;
    }
    return ret;
}


int main(){
    while (true){
        scanf("%d", &n);
        scanf("%d", &m);
        while (getchar() != '\n');
        if (n == 0 && m == 0) break;
        node * root = new node(true);
        for (int i=0; i<n; ++i){
            node * cur = root;
            fgets(buf, BUFSIZE, stdin);
            for (int j=0; ; ++j){
                if (buf[j] == '*'){
                    cur->end = true;
                    break;
                }
                node * next;
                if (buf[j] == '0'){
                    next = cur->getLeft();
                    next->s = cur->s + '0';
                }else if (buf[j] == '1'){
                    next = cur->getRight();
                    next->s = cur->s + '1';
                }else{
                    printf("Bad character %c at query %d, position %d\n", buf[j], i, j);
                    //assert(false);
                }
                cur = next;
            }
        }
        fgets(buf, BUFSIZE, stdin);
        int k;
        sscanf(buf, "%d", &k);
        for (int i=0; i<k; ++i){
            fgets(buf, BUFSIZE, stdin);
            buf[strlen(buf)-1] = 0;

            node * cur = root;
            for  (int j=0; buf[j] != '*'; ++j){
                if (buf[j] == '0'){
                    cur = cur->left;
                }else if (buf[j] == '1'){
                    cur = cur->right;
                }
            }
            uint64 ans = pow2(m - cur->s.size()) - alreadyCounted(cur->left) - alreadyCounted(cur->right);
            cout << ans << endl;
        }
        while (getchar() != '\n'); //empty line
        printf("\n");
        clean(root);
    }
    return 0;
}
