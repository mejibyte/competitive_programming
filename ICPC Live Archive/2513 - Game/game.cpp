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

const int MAXN = 105;

int K, L;
double Pa, Pb;

double memogame[MAXN][MAXN][2];
double memomatch[MAXN][MAXN][2];

double wingame(int pointsA, int pointsB, int turn) {
    if (pointsA == L) return 1.0;
    if (pointsB == L) return 0.0;
    
    if (memogame[pointsA][pointsB][turn] > -0.5) return memogame[pointsA][pointsB][turn];
    
    double ans = 0.0;
    if (turn == 0) {
        ans += Pa * wingame(pointsA + 1, pointsB,  0);
        ans += (1.0 - Pa) * wingame(pointsA, pointsB + 1, 1);
    } else {
        assert(turn == 1);
        ans += Pb * wingame(pointsA, pointsB + 1, 1);
        ans += (1.0 - Pb) * wingame(pointsA + 1, pointsB, 0);
    }
    return memogame[pointsA][pointsB][turn] = ans;
}

double winmatch(int gamesA, int gamesB, int turn) {
    if (gamesA == K) return 1.0;
    if (gamesB == K) return 0.0;
    
    if (memomatch[gamesA][gamesB][turn] > -0.5) return memomatch[gamesA][gamesB][turn];
    
    double ans = 0.0;
    ans += wingame(0, 0, turn) * winmatch(gamesA + 1, gamesB, !turn);
    ans += (1.0 - wingame(0, 0, turn)) * winmatch(gamesA, gamesB + 1, !turn);
    return memomatch[gamesA][gamesB][turn] = ans;
}

int main(){
    int sets;
    cin >> sets;
    while (sets--) {
        int a, b; cin >> a >> b >> K >> L;
        Pa = 0.01 * a, Pb = 0.01 * b;
        
        for (int i = 0; i <= max(K, L); ++i) {
            for (int j = 0; j <= max(K, L); ++j) {
                memogame[i][j][0] = memogame[i][j][1] = -1.0;
                memomatch[i][j][0] = memomatch[i][j][1] = -1.0;
            }
        }
        
        double ans = 0.5 * winmatch(0, 0, 0) + 0.5 * winmatch(0, 0, 1);
        printf("%.1lf\n", ans * 100.0);
    }
    return 0;
}