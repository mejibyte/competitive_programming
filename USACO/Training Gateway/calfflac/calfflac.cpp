/*
  LANG: C++
  PROB: calfflac
*/
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
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 30000;
char text[MAXN];
char s[MAXN];

int main(){
    freopen("calfflac.in", "r", stdin);
    freopen("calfflac.out", "w", stdout);
    int n = fread(text, sizeof(char), MAXN, stdin);
    
    int m = 0;
    for (int i = 0; i < n; ++i) {
        if (isalpha(text[i])) {
            s[m++] = tolower(text[i]);
        }
    }
    
    assert(m > 0);
    int longest = 1, start = 0;
    for (int i = 0; i < m; ++i) {
        
        int k = 1;
        while (i - k >= 0 and i + k < m and s[i - k] == s[i + k]) k++;
        k--;
        if (2 * k + 1 > longest) {
            longest = 2 * k + 1;
            start = i - k;
        }
        
        k = 1;
        while (i - k + 1 >= 0 and i + k < m and s[i - k + 1] == s[i + k]) k++;
        k--;
        if (2 * k > longest) {
            longest = 2 * k;
            start = i - k + 1;
        }
    }

    int left = 0;
    for (int cnt = 0; cnt < start + 1; ++left) {
        if (isalpha(text[left])) cnt++;
    }
    left--;
    
    int right = left;
    for (int cnt = 0; cnt < longest; ++right) {
        if (isalpha(text[right])) cnt++;
    }
    right--;
    
    printf("%d\n", longest);
    for (int i = left; i <= right; ++i) {
        putchar(text[i]);
    }
    puts("");
    

    return 0;
}