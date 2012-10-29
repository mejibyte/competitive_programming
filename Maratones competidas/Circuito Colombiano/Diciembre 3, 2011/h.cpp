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

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "paint"

const double PI = 2 * acos(0);

void print(int c, double x) {
    printf("Case %d: Green occupies an area of %.2lf square meters.\n", c, x);
}


int main(){
    freopen(INPUT_FILE ".in", "r", stdin); // Read from file
    double r1, r2, d;
    int caso = 0;
    while (cin >> r1 >> r2 >> d) {
        caso++;
        
        if (cmp(r1, 0) == 0 and cmp(r2, 0) == 0 and cmp(d, 0) == 0) break;
        
        if (cmp(r1, r2) > 0) swap(r1, r2);
        assert( cmp(r1, r2) <= 0 );
        
        if (cmp(d + r1, r2) <= 0) {
            print(caso, PI * r1 * r1);
            continue;
        }
        
        if (cmp(r1 + r2, d) <= 0) {
            print(caso, 0);
            continue;
        }
        
        assert(cmp(d, 0) > 0);
        double h2 = d / 2 - (r1 * r1 - r2 * r2) / 2 / d;
        double h1 = d - h2;
        
        //D(h1); D(h2);
        
        double b = 2 * sqrt( r1 * r1 - h1 * h1 );
        assert( cmp(b, 2 * sqrt(r2 * r2 - h2 * h2) ) == 0 );
        
        double pizza1 = r1 * r1 * atan2( b / 2, h1 );
        double pizza2 = r2 * r2 * atan2( b / 2, h2 );
        
        double area1 = pizza1 - h1 * b / 2;
        double area2 = pizza2 - h2 * b / 2;
        print(caso, area1 + area2);
    }
    return 0;
}
