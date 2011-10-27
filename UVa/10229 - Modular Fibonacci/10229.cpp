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

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl

int mod;
struct matrix{
  //2 x 2 matrix:
  //a b
  //c d
  int a, b, c, d;
  matrix(){}
  matrix(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
  const matrix  operator * (const matrix &t){
    long long A = 1LL * a * t.a + 1LL * b * t.c;
    long long B = 1LL * a * t.b + 1LL * b * t.d;
    long long C = 1LL * c * t.a + 1LL * d * t.c;
    long long D = 1LL * c * t.b + 1LL * d * t.d;
    if (A >= mod) A %= mod;
    if (B >= mod) B %= mod;
    if (C >= mod) C %= mod;
    if (D >= mod) D %= mod;
    return matrix(A, B, C, D);
  }
};

//returns p^n
matrix pow(const matrix &p, int n){
  if (n == 1) return p;
  matrix k = pow(p, n/2);
  matrix ans = k*k;
  if (n & 1) ans = ans * p;
  return ans;
}

int main(){
  int n, m;
  while (cin >> n >> m){
    mod = 1 << m;
    if (n == 0){ cout << 0 << endl; continue; }
    matrix fib = pow(matrix(0, 1, 1, 1), n);
    cout << fib.b << endl;
  }
  return 0;
}
/*
  It can be proved by induction that:

 _   _ ^ n     _                   _
| 0 1 |    =  |  fib(n-1)  fib(n)   |
|_0 1_|       |_  fib(n)  fib(n+1) _|

 */
