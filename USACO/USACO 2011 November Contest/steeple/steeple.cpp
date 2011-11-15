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

typedef long long int64;

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}


/*
  Returns true if point (x, y) lies inside (or in the border)
  of box defined by points (x0, y0) and (x1, y1).
*/
bool point_in_box(int x,  int y,
                  int x0, int y0,
                  int x1, int y1){
  return
    min(x0, x1) <= x && x <= max(x0, x1) &&
    min(y0, y1) <= y && y <= max(y0, y1);
}


/*
  Returns the cross product of the segment that goes from
  (x1, y1) to (x3, y3) with the segment that goes from
  (x1, y1) to (x2, y2)
*/
int64 direction(int64 x1, int64 y1, int64 x2, int64 y2, int64 x3, int64 y3) {
    return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
}

/*
  Finds the intersection between two segments (Not infinite
  lines!)
  Segment 1 goes from point (x0, y0) to (x1, y1).
  Segment 2 goes from point (x2, y2) to (x3, y3).

  (Can be modified to find the intersection between a segment
  and a line)

  Handles the case when the 2 segments are:
  *Parallel but don't lie on the same line (No intersection)
  *Parallel and both lie on the same line (Infinite
  *intersections or no intersections)
  *Not parallel (One intersection or no intersections)

  Returns true if the segments do intersect in any case.
*/
bool segment_segment_intersection(int x1, int y1,
                                  int x2, int y2,
                                  
                                  int x3, int y3,
                                  int x4, int y4){
                                      
    int64 d1 = direction(x3, y3,   x4, y4,   x1, y1);
    int64 d2 = direction(x3, y3,   x4, y4,   x2, y2);
    int64 d3 = direction(x1, y1,   x2, y2,   x3, y3);
    int64 d4 = direction(x1, y1,   x2, y2,   x4, y4);
    bool b1 = d1 > 0 and d2 < 0 or d1 < 0 and d2 > 0;
    bool b2 = d3 > 0 and d4 < 0 or d3 < 0 and d4 > 0;
    if (b1 and b2) return true;
    if (d1 == 0 and point_in_box(x1, y1,     x3, y3, x4, y4))
        return true;

    if (d2 == 0 and point_in_box(x2, y2,     x3, y3, x4, y4))
        return true;

    if (d3 == 0 and point_in_box(x3, y3,     x1, y1, x2, y2))
        return true;

    if (d4 == 0 and point_in_box(x4, y4,     x1, y1, x2, y2))
        return true;

    return false;
}


/**
 *   ////////////////////////
 *   // BIPARTITE MATCHING //
 *   ////////////////////////
 *
 * This file is part of Advenego's library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2003
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/**********************
 * Bipartite matching * O(m*n^2))
 **********************
 * Given a bipartite graph represented as an m-by-n matrix, where graph[i][j]
 * is true iff there is an edge from pigeon i to hole j, computes the maximum
 * number of pigeons that can find a hole (one per pigeon) and an optimal
 * assignment.
 *      Formally, this is a stripped down version of Ford-Fulkerson with
 * DFS used to find an augmenting path. DFS does the job quickly because
 * capacities can only be 0 or 1.
 *
 * PARAMETERS:
 *      - graph: adjacency matrix as above.
 * RETURNS:
 *      - an integer corresponding to the number of assignments
 *      - matchL[m]: for each pigeon, a hole or -1
 *      - matchR[n]: for each hole, a pigeon or -1
 * DETAILS:
 *      - graph[m][n], matchL[n], matchR[m] and seen[m] are global arrays
 *      - main() initializes matchL[] and matchR[] to all -1.
 *      - main() does a loop over all pigeons i and in each iteration
 *          - clears seen[] to all 0
 *          - calls bpm(i) and increments the maxflow counter
 *      - bpm(i) returns true iff pigeon i can be assigned a hole
 * ACKNOWLEDGEMENTS:
 *      - Thanks to tjq from TopCoder for a reference implementation.
 * FIELD TESTING:
 *      - Valladolid 10080: Gopher (II)
 *      - Valladolid 10092: The Problem with the Problem Setter
 *      - Valladolid 670:   The dog task
 *      - Valladolid 259:   Software Allocation
 * #include <string.h>
 **/

#define M 255
#define N 255

namespace BPM {
    bool graph[M][N];
    bool seen[N];
    int matchL[M], matchR[N];
    int n, m;

    bool bpm( int u )
    {
        for( int v = 0; v < n; v++ ) if( graph[u][v] )
        {
            if( seen[v] ) continue;
            seen[v] = true;

            if( matchR[v] < 0 || bpm( matchR[v] ) )
            {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int find() {
        // Read input and populate graph[][]
        // Set m, n

        memset( matchL, -1, sizeof( matchL ) );
        memset( matchR, -1, sizeof( matchR ) );
        int cnt = 0;
        for( int i = 0; i < m; i++ )
        {
            memset( seen, 0, sizeof( seen ) );
            if( bpm( i ) ) cnt++;
        }

        // cnt contains the number of happy pigeons
        // matchL[i] contains the hole of pigeon i or -1 if pigeon i is unhappy
        // matchR[j] contains the pigeon in hole j or -1 if hole j is empty

        return cnt;
    }
};

////////////////////////// Solution starts below. //////////////////////////////


typedef pair<int, int> point;
typedef pair< point, point > segment;
vector< segment > v;

bool g[N][N];
int color[N];

void assign(int u, int c, int n) {
    if (color[u] != -1) {
        assert(color[u] == c);
        return;
    }
    color[u] = c;
    For(v, 0, n) {
        if (g[u][v]) {
            assign(v, c ^ 1, n);
        }
    }
}

int main(){
    #ifndef LOCAL_ANDRES_MEJIA
    freopen("steeple.in", "r", stdin);
    freopen("steeple.out", "w", stdout);
    #endif
    
    int n;
    scanf("%d", &n);
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1,   &x2, &y2);
        v[i] = make_pair(    make_pair(x1, y1),   make_pair(x2, y2)   );
    }
    
    For(i, 0, n) {
        g[i][i] = false;
        For(j, i+1, n) {
            if (i == j) continue;
            
            int x1 = v[i].first.first, y1 = v[i].first.second, x2 = v[i].second.first, y2 = v[i].second.second;
            
            int xx1 = v[j].first.first, yy1 = v[j].first.second, xx2 = v[j].second.first, yy2 = v[j].second.second;
            
            bool choque = segment_segment_intersection(x1, y1, x2, y2,    xx1, yy1,  xx2, yy2);
            g[i][j] = g[j][i] = choque;
        }
    }

    memset(color, -1, sizeof color);
    For(i, 0, n) {
        if (color[i] != -1) continue;
        assign(i, 0, n);
    }
    
    For(i, 0, n) {
        For(j, 0, n) {
            BPM::graph[i][j] = false;
            if (color[i] == 0 and color[j] == 1 and g[i][j]) {
                BPM::graph[i][j] = true;
            }
        }
    }

    BPM::n = n;
    BPM::m = n;
    
    int ans = BPM::find();
    printf("%d\n", n - ans);
    return 0;
}