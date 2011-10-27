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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

int main(){
    int a,b,c;
    while (cin >> a >> b >> c) {
        if (a == 0 and b == 0 and c == 0) break;
        if(a * a == b * b + c * c || b * b == a * a + c * c || c * c == b * b + a * a){
          cout << "right" << endl;
        } else{
          cout << "wrong" << endl;
        }
    }
    return 0;
}