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

int cities, cars, rounds;

const int MAXN = 62;

int speed[MAXN][MAXN][MAXN];

int single[MAXN][MAXN];

int ans[MAXN][MAXN][1005];

const int oo = 1 << 30;

#define minimize(a, x) if ((x) < (a)) (a) = (x)

int main(){
    scanf("%d %d %d", &cities, &cars, &rounds);
    
    for (int i = 0; i < cities; ++i) {
        for (int j = 0; j < cities; ++j) {
            single[i][j] = oo;
        }
    }
    
    for (int c = 0; c < cars; ++c) {
        for (int i = 0; i < cities; ++i) {
            for (int j = 0; j < cities; ++j) {
                scanf("%d", &speed[c][i][j]);
            }
        }
        
        for (int k = 0; k < cities; ++k) {
            for (int i = 0; i < cities; ++i) {
                for (int j = 0; j < cities; ++j) {
                    minimize(speed[c][i][j], speed[c][i][k] + speed[c][k][j]);
                    minimize(single[i][j], speed[c][i][j]);
                }
            }
        }
        
        // printf("min for car c = %d\n", c);
        // for (int i = 0; i < cities; ++i){
        //     for (int j = 0; j < cities; ++j){
        //         printf("%d ", speed[c][i][j]);
        //     }
        //     puts("");
        // }
    }
    
    // speed[c][i][j] = The minimum time that car c takes to go from city i to j.
    // single[i][j] = The minimum time to go from i to j using a single car.
    
    // puts("single");
    // for (int i = 0; i < cities; ++i){
    //     for (int j = 0; j < cities; ++j){
    //         printf("%d ", single[i][j]);
    //     }
    //     puts("");
    // }
    
    memset(ans, -1, sizeof ans);
    
    
    while (rounds--) {
        int start, finish, changes;
        scanf("%d %d %d", &start, &finish, &changes);
        start--, finish--;
        
        if (ans[start][finish][changes] != -1) {
            printf("%d\n", ans[start][finish][changes]);
            continue;
        }
        
        for (int c = 0; c < cities; ++c) {
            ans[c][finish][0] = single[c][finish];
        }
        
        for (int k = 1; k <= 1000; ++k) {
            for (int c = 0; c < cities; ++c) {
                ans[c][finish][k] = oo;
                for (int v = 0; v < cities; ++v) {
                    int option = single[c][v] + ans[v][finish][k - 1];
                    minimize(ans[c][finish][k], option);
                }
            }
        }
        printf("%d\n", ans[start][finish][changes]);
    }
    
    return 0;
}