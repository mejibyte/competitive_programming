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

typedef pair< double, double > interval;

const double eps = 1e-9;

const int MAXN = 1001;

interval intervals[MAXN];
int B;

void delete_redundant() {
    bitset<MAXN> deleted;
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < B; ++j) {
            if (i == j) continue;
            // delete interval j if interval i is completely inside it
            if (intervals[j].first < intervals[i].first - eps and intervals[i].second + eps < intervals[j].second) {
                deleted[j] = true;
            }
        }
    }
    int k = 0;
    for (int i = 0; i < B; ++i) {
        if (!deleted[i]) intervals[k++] = intervals[i];
    }
    B = k;
}

int main(){
    while (cin >> B) {
        if (B == 0) break;
        for (int i = 0; i < B; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            double t1 = atan2(y1, x1), t2 = atan2(y2, x2);
            intervals[i] = make_pair( min(t1, t2), max(t1, t2) );
        }
        delete_redundant();
        sort(intervals, intervals + B);
        int ans = 0;
        for (int i = 0; i < B; ) {
            ans++;
            double pick = intervals[i].second;
            while (i < B and intervals[i].first - eps < pick) i++;
        }
        printf("%d\n", ans);
    }
    return 0;
}