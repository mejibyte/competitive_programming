// Accepted
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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl


struct point {
    int x, y;
    point(){} point(int x, int y) : x(x), y(y) {}
    bool operator < (const point &t) const {
        return x * t.y - y * t.x > 0;
    }
    bool operator == (const point &t) const {
        return x * t.y - y * t.x == 0;
    }
    bool operator <= (const point &t) const {
        return *this < t or *this == t;
    }
    bool operator != (const point &t) const {
        return !(*this == t);
    }    
};

typedef pair< point, point > interval;

// Returns true if interval 'a' is strictly included in interval 'b'
bool included(const interval &a, const interval &b) {
    return b.first < a.first and a.second < b.second;
}

const int MAXN = 1001;

interval intervals[MAXN];
int B;

void delete_redundant() {
    bitset<MAXN> deleted;
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < B; ++j) {
            // delete interval i if interval j is completely inside it
            if (included(intervals[j], intervals[i])) {
                deleted[i] = true;
                break;
            }
        }
    }
    int k = 0;
    for (int i = 0; i < B; ++i) {
        if (!deleted[i]) {
            intervals[k++] = intervals[i];
        }
    }
    B = k;
}

int main(){
    while (cin >> B) {
        if (B == 0) break;
        for (int i = 0; i < B; ++i) {
            point p1, p2;
            cin >> p1.x >> p1.y >> p2.x >> p2.y;
            assert(p1 != p2);
            if (p2 < p1) swap(p1, p2);
            intervals[i] = make_pair( p1, p2 );
        }
        //printf("Before removing redundant B is %d\n", B);
        delete_redundant();
        sort(intervals, intervals + B);
        //printf("After removing redundant B is %d\n", B);
        
        //printf("Before removing duplicates B is %d\n", B);
        B = unique(intervals, intervals + B) - intervals;
        //printf("After removing duplicates B is %d\n", B);
        
        int ans = 0, i = 0;
        while (i < B) {
            ans++;
            point pick = intervals[i].second;
            while (i < B and intervals[i].first <= pick) i++;
        }
        printf("%d\n", ans);
    }
    return 0;
}