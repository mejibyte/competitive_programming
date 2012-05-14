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

typedef long double Double;

Double power(Double x, int e) {
    if (e == 0) return 1.0;
    return powl(x, e);
}

int a, b, c, s;
Double distance(Double x, Double y, Double z) {
    return power(x, a) * power(y, b) * power(z, c);
}

Double ans_y, ans_z;

Double get(Double x) {
    // find y and z
    Double low = 0, high = s - x;
    for (int i = 0; i < 200; ++i) {
        Double left = (high - low) / 3 + low;
        Double right = 2 * (high - low) / 3 + low;
        
        if (distance(x, left, s - x - left) > distance(x, right, s - x - right)) {
            high = right;
        } else {
            low = left;
        }
    }
    ans_y = low;
    ans_z = s - x - low;
    return low;
}

int main(){
    cin >> s >> a >> b >> c;
    
    // find x
     Double low = 0, high = s;
     for (int i = 0; i < 10; ++i) {
         Double left = (high - low) / 3 + low;
         Double right = 2 * (high - low) / 3 + low;

         cout << "x es " << left << ", get es " << get(left) << endl;
         
         if (get(left) > get(right)) {
             high = right;
         } else {
             low = left;
         }
     }
     printf("%.10lf %.10lf %.19lf\n", (double)low, (double)ans_y, (double)ans_z);

    return 0;
}