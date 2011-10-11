// Time Limit Exceeded
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

typedef pair<int, int> point;

const int MAXN = 10000;
const int MAXR = 101;

point points[2 * MAXN];
int height[MAXR], N, R;

void solve(int distance, int angle) {
    int ans = 0;
    int i = 0, j = 0;
    for (int r = 0; r <= R; ++r) {
        height[r] = 0;
    } 
    while (i < N) {
        while (j < N and points[i].first + angle >= points[j].first) {
            height[points[j].second]++;
            j++;
        }
        // from [i, j) they are correctly separated by angle
        // printf("i = %d, j = %d, angle = %d\n", i, j, angle);
        // printf("  "); For(k, i, j) printf("<%d, %d> ", points[k].first, points[k].second); puts("");
        // For(r, 0, MAXR) {
        //     if (height[r] > 0) {
        //         printf("height[%d] = %d\n", r, height[r]);
        //     }
        // }
        
        int sum = 0;
        int p = 0, q = 0;
        while (p <= R) {
            while (q <= R and p + distance > q) {
                sum += height[q];
                q++;
            }
            // if (sum > 0) {
            //     printf("possible option from p=%d to q=%d with sum = %d\n", p, q, sum);
            // }
            ans = max(ans, sum);
            sum -= height[p++];
            while (p <= R and height[p] == 0) p++;
        }
        
        height[points[i++].second]--;
    }
    printf("%d\n", ans);
}

int main(){
    while (scanf("%d %d", &N, &R) == 2) {
        if (N == 0 and R == 0) break;
        for (int i = 0; i < N; ++i) {
            int distance, angle;
            scanf("%d %d", &distance, &angle);
            points[2*i] = make_pair(angle, distance);
            points[2*i + 1] = make_pair(angle + 360, distance);
        }
        N *= 2;
        sort(points, points + N);
        
        int E;
        scanf("%d", &E);
        while (E--) {
            int distance, angle;
            scanf("%d %d", &distance, &angle);
            solve(distance, angle);
        }
    }
    return 0;
}