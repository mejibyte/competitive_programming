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

const double pi = 2 * acos(0.0);

int main(){
    // for (int i = 0; i < 1000; ++i){
    //     int n = 10;
    //     while (true) {
    //         int a = rand() % n, b = rand() % n, c = rand() % n, d = rand() % n;
    //         if (rand() % 2) a = -a;
    //         if (rand() % 2) b = -b;
    //         if (rand() % 2) c = -c;
    //         if (rand() % 2) d = -d;
    //         
    //         if (a == 0 and b == 0 or c == 0 and d == 0) continue;
    //         printf("%d %d %d %d\n", a, b, c, d);
    //         break;
    //     }
    // }
    
    double ax, ay, bx, by;
    while (cin >> ax >> ay >> bx >> by) {
        double k = (ax * bx + ay * by) / (hypot(ax, ay) * hypot(bx, by) );
        if (k < -1.0) k = -1.0;
        if (k > 1.0) k = 1.0;
        double ans = acos( k );
        //ans = floor(100000.0 * ans + 0.5) / 100000.0;
        //cout << ax << " " << ay << " " << bx << " " << by << endl;
        //assert(ans >= 0);
        assert(ans == ans);
        printf("%.5lf\n", fabs(ans));
    }
    return 0;
}