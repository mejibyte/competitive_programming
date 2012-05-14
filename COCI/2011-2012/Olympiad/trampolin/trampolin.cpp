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

const int MAXN = 300010;
int go_left[MAXN], go_right[MAXN], tramp_left[MAXN], tramp_right[MAXN], h[MAXN], sum[MAXN];
bool tramp[MAXN];

void visit(int from, int to) {
    //if (to < from) swap(from, to);
    assert(from <= to);
    sum[from]++;
    sum[to + 1]--;
}

int main(){
    int n, start;
    scanf("%d %d", &n, &start);
    start--;
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }
    
    for (int i = 0; i < n; ++i) {
        char c; scanf(" %c ", &c);
        tramp[i] = (c == 'T');
    }
    
    go_left[0] = 0;
    tramp_left[0] = (tramp[0] ? 0 : -1);
    
    for (int i = 1; i < n; ++i) {
        go_left[i] = i;
        tramp_left[i] = (tramp[i] ? i : -1);
        
        if (h[i] >= h[i - 1]) { // can walk left
            go_left[i] = go_left[i - 1];
            if (tramp_left[i - 1] != -1) tramp_left[i] = tramp_left[i - 1];
        }
    }
    
    go_right[n - 1] = n - 1;
    tramp_right[n - 1] = (tramp[n - 1] ? n - 1 : -1);
    
    for (int i = n - 2; i >= 0; --i) {
        go_right[i] = i;
        tramp_right[i] = (tramp[i] ? i : -1);
        if (h[i] >= h[i + 1]) { // can walk right
            go_right[i] = go_right[i + 1];
            if (tramp_right[i + 1] != -1) tramp_right[i] = tramp_right[i + 1];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        assert(go_left[i] <= i and i <= go_right[i]);
        if (tramp_left[i] != -1) assert(tramp_left[i] <= i and tramp[tramp_left[i]]);
        if (tramp_right[i] != -1) assert(i <= tramp_right[i] and tramp[tramp_right[i]]);

        // printf("i = %d, h = %d, go left = %d, go right = %d, tramp left = %d, tramp right = %d\n", 
        //      i, h[i], go_left[i], go_right[i], tramp_left[i], tramp_right[i]);
    }

    if (tramp_left[start] == -1 and tramp_right[start] == -1) { // too bad, I can't reach any trampolines :(
        // walk as far as I can go without jumping
        int left = start;
        while (left >= 0 and h[left] == h[start]) left--;
        left++;
        
        int right = start;
        while (right < n and h[right] == h[start]) right++;
        right--;
        
        assert(go_left[right] == go_left[start] and go_right[left] == go_right[start]);
    
        int ans = max(right - go_left[right] + 1, go_right[left] - left + 1);
        printf("%d\n", ans);
        return 0;
    }

    // visit the same height as start
    for (int i = start; i >= 0 and h[i] == h[start]; --i) visit(i, i);
    for (int i = start; i < n and h[i] == h[start]; ++i) visit(i, i);
    
    for (int i = 0; i < n; ++i) {
        if (tramp_left[i] != -1) visit(tramp_left[i], i);
        if (tramp_right[i] != -1) visit(i, tramp_right[i]);
    }
    
    int ans = 0;
    static bool visited[MAXN];
    for (int i = 0, accumulated = 0; i < n; ++i) {
        accumulated += sum[i];
        visited[i] = (accumulated > 0);
        if (visited[i]) ans++;
    }
    
    // now find the longest decreasing sequence of buildings
    int extra = 0;
    
    // first going right
    for (int i = 0, seen = 0; i < n; ++i) {
        if (i > 0 and h[i] > h[i - 1]) seen = 0; // reset
        if (!visited[i]) seen++;
        extra = max(extra, seen);
    }
    
    // then going left
    for (int i = n - 1, seen = 0; i >= 0; --i) {
        if (i + 1 < n and h[i] > h[i + 1]) seen = 0; // reset
        if (!visited[i]) seen++;
        extra = max(extra, seen);
    }
    
    printf("%d\n", ans + extra);
    
    return 0;
}