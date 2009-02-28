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
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

char buf[32];

bool p(int n){
  for (int i=2; i*i<=n; ++i) if (n % i == 0) return false;
  return true;
}

int main(){
  while (fgets(buf, 32, stdin) != NULL){
    int n = 0;
    for (int i=0; i<strlen(buf)-1; ++i){
      char c = buf[i];
      n += (islower(c) ? c - 'a' + 1 : c - 'A' + 27);
    }
    printf("It is %sa prime word.\n", p(n) ? "" : "not ");
  }
  return 0;
}
