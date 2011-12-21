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

const int MAXT = 1000005, MAXN = 32;
vector< int > at[MAXT];

int number[MAXN][MAXN], certain[MAXN], cur[MAXN], next[MAXN];
vector< pair<int, int> > positions[MAXN * MAXN];

vector< int > heights;

int main(){
    int N, T, X, Y;
    scanf("%d %d %d %d", &N, &T, &X, &Y);
    X--, Y--;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int v; scanf("%d", &v);
            number[i][j] = v;
            if (v == 1) {
                certain[i] |= (1 << j);
            } else if (v == 2) {
                if ( ( (i + j) % 2 ) == ( (X + Y) % 2 ) ) certain[i] |= (1 << j);
            } else {
                heights.push_back( v );
            }
        }
    }

    sort(heights.begin(), heights.end());
    heights.resize(unique(heights.begin(), heights.end()) - heights.begin());
    
    for (int k = 0; k < heights.size(); ++k) {
        int v = heights[k];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (number[i][j] == v) {
                    positions[k].push_back( make_pair(i, j) );
                }
            }
        }
        
        int z = v;
        while (z <= T) {
            at[z].push_back( k );
            z += v;
        }
    }
    cur[X] |= (1 << Y);
    for (int t = 1; t <= T; ++t) {
        for (int i = 0; i < N; ++i) next[i] = certain[i];

        foreach(k, at[t]) {
            const vector< pair<int, int> > &steps = positions[*k];
            foreach(p, steps) {
                int r = p->first, c = p->second;
                next[r] |= (1 << c);
            }
        }
        
        for (int i = 0; i < N; ++i) {
            int advance = 0;
            if (i - 1 >= 0) advance |= (cur[i - 1] << 2) | (cur[i - 1] >> 2);
            if (i + 1 < N)  advance |= (cur[i + 1] << 2) | (cur[i + 1] >> 2);
            if (i - 2 >= 0) advance |= (cur[i - 2] << 1) | (cur[i - 2] >> 1);
            if (i + 2 < N)  advance |= (cur[i + 2] << 1) | (cur[i + 2] >> 1);
            next[i] &= advance;
        }
        
        for (int i = 0; i < N; ++i) {
            cur[i] = next[i];
        }
    }
    
    vector< pair<int, int> > ans;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (cur[i] & (1 << j)) {
                ans.push_back( make_pair(i, j) );
            }
        }
    }
    printf("%d\n", (int)ans.size());
    foreach(p, ans) {
        printf("%d %d\n", p->first + 1, p->second + 1);
    }
    return 0;
}