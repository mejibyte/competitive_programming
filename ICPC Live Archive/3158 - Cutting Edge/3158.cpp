// Andrés Mejía
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

enum { CLOSE, OPEN };

struct Event {
    int at, from, to, type;
    Event(){}
    Event(int a, int f, int t, int p) : at(a), from(f), to(t), type(p){}
    bool operator < (const Event &e) const {
        if (at != e.at) return at < e.at;
        return type < e.type; // CLOSE events come before OPEN events
    }
};

struct Cut {
    int x1, y1, x2, y2;
    Cut(){}
    Cut(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2){}
    bool operator < (const Cut &t) const {
        if (x1 != t.x1) return x1 < t.x1;
        if (y1 != t.y1) return y1 < t.y1;
        if (x2 != t.x2) return x2 < t.x2;
        return y2 < t.y2;
    }
};

vector<Event> event_x, event_y;

// This merges the cuts made on the two halves.
// Since the two halves are independent, we can merge them in any order
// as long as the relative order between cuts in the same half doesn't change.
// This is the same idea used in merge sort.
vector<Cut> merge(const Cut &first, const vector<Cut> &left, const vector<Cut> &right) {
    vector<Cut> ans(1, first);
    int i = 0, j = 0;
    while (i < left.size() and j < right.size()) {
        if (left[i] < right[j]) {
            ans.push_back(left[i++]);
        } else {
            ans.push_back(right[j++]);
        }
    }
    while (i < left.size()) ans.push_back(left[i++]);
    while (j < right.size()) ans.push_back(right[j++]);
    return ans;
}

// Returns the cuts that need to be made (in the correct order)
// to completely separate the glass panel with coordinates (x1, y1)
// to (x2, y2) in the correct pieces.
vector<Cut> split(int x1, int y1, int x2, int y2) {
    int balance;
    
    // Scan vertically, sweeping a horizontal line
    balance = 0;
    for (int k = 0; k < event_y.size(); ++k) {
        const Event &e = event_y[k];
        if (e.type == OPEN and (e.at < y1 or y2 <= e.at)) continue;
        if (e.type == CLOSE and (e.at <= y1 or y2 < e.at)) continue;
        if (x1 <= e.from and e.to <= x2) {
            balance += (e.type == OPEN ? +1 : -1);
            if (balance == 0 and e.at < y2) {
                // found a horizontal cut!
                return merge(Cut(x1, e.at, x2, e.at), split(x1, y1, x2, e.at), split(x1, e.at, x2, y2));
            }
        }
    }
    
    // Scan horizontally, sweeping a vertical line
    balance = 0;
    for (int k = 0; k < event_x.size(); ++k) {
        const Event &e = event_x[k];
        if (e.type == OPEN and (e.at < x1 or x2 <= e.at)) continue;
        if (e.type == CLOSE and (e.at <= x1 or x2 < e.at)) continue;
        if (y1 <= e.from and e.to <= y2) {
            balance += (e.type == OPEN ? +1 : -1);
            if (balance == 0 and e.at < x2) {
                // found a vertical cut!
                return merge(Cut(e.at, y1, e.at, y2), split(x1, y1, e.at, y2), split(e.at, y1, x2, y2));
            }
        }
    }
    return vector<Cut>(); // Nothing left to do, since we didn't find any vertical nor horizontal cuts.
}

int main(){
    int n;
    while (cin >> n) {
        if (n == 0) break;
        int px1 = INT_MAX, py1 = INT_MAX, px2 = INT_MIN, py2 = INT_MIN; // coordinates of the whole panel
        
        event_x.clear();
        event_y.clear();
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            px1 = min(px1, x1);
            py1 = min(py1, y1);
            px2 = max(px2, x2);
            py2 = max(py2, y2);
            
            event_x.push_back(Event(x1, y1, y2, OPEN));
            event_x.push_back(Event(x2, y1, y2, CLOSE));
            
            event_y.push_back(Event(y1, x1, x2, OPEN));
            event_y.push_back(Event(y2, x1, x2, CLOSE));
        }
        sort(event_x.begin(), event_x.end());
        sort(event_y.begin(), event_y.end());
        vector<Cut> ans = split(px1, py1, px2, py2);
        assert(ans.size() == n - 1);
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i].x1 << " " << ans[i].y1 << " " << ans[i].x2 << " " << ans[i].y2 << endl;
        }
        cout << endl;
    }
    return 0;
}