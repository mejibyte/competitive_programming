// Andrés Mejía
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
#include <bitset>
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
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

void print(string what, int width) {
    int remain = width - what.size();
    assert(remain % 2 == 0);
    for (int i = 0; i < remain / 2; ++i) printf(" ");
    printf("%s\n", what.c_str());
}

int main(){
    int n; cin >> n;
    int width = 0;

    for (int i = 0, start = 1; i < n; ++i) {
        for (int k = 0; k < 4 + i; ++k) {
            width = start;
            start += 2;
        }
        start -= 4;
        if (i % 2 == 1) start -= 2;
    }
    
    for (int i = 0, start = 1; i < n; ++i) {
          for (int k = 0; k < 4 + i; ++k) {
              string line = "";
              for (int w = 0; w < start; ++w) line += "*";
              print(line, width);
              start += 2;
          }
          start -= 4;
          if (i % 2 == 1) start -= 2;
    }
    
    string trunk = "";
    int w = n;
    if (w % 2 == 0) w++;
    for (int i = 0; i < w; ++i) trunk += "|";
    for (int i = 0; i < n; ++i) print(trunk, width);
    

    return 0;
}