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

int main(){
    int hour, minute;
    while (scanf("%d:%d", &hour, &minute) == 2) {
        if (hour == 0 and minute == 0) break;
        if (hour == 12) hour = 0;
        double angle1 = 30 * hour + minute * 0.5;
        double angle2 = minute * 6;
        double answer = abs(angle1 - angle2);
        if (answer > 180) answer = 360 - answer;
        printf("%.3lf\n", answer);
    }
    return 0;
}