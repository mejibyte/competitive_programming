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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 105, MAXL = 55, oo = 1 << 28;
string words[MAXN];
int dist[MAXN][MAXL];
int n;

long long pack(int index, int behind, int weight) {
    return ((long long)weight << 16L) + (behind << 8L) + index;
}

void unpack(long long state, int &index, int &behind, int &weight) {
    index = state & 255L;
    state >>= 8L;
    behind = state & 255L;
    state >>= 8L;
    weight = state;
}

inline bool isPrefix(const string &a, const string &b) {
    if (a.size() > b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


int search() {
    for (int i = 0; i < n; ++i) {
        for (int d = 0; d < MAXL; ++d) {
            dist[i][d] = oo;
        }
    }
    
    priority_queue<long long, vector<long long>, greater<long long> > q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (isPrefix(words[j], words[i])) {
                assert(words[j].size() < words[i].size());
                int diff = words[i].size() - words[j].size();
                dist[i][diff] = words[i].size();
                long long state = pack(i, diff, dist[i][diff]);
                q.push(state);
            }
        }
    }
    
    while (q.size() > 0) {
        long long state = q.top(); q.pop();
        int index, behind, weight;
        unpack(state, index, behind, weight);
        //printf("Popped state <i=%d, d=%d> (%s, %s) with weight w=%d\n", index, behind,  words[index].c_str(), words[index].substr(0, words[index].size() - behind).c_str(),  weight);        
        if (behind == 0) {
            return weight;
        }
        if (weight > dist[index][behind]) continue;
        
        const string tail = words[index].substr(words[index].size() - behind);
        //printf("  Tail is %s\n", tail.c_str());
        assert(tail.size() == behind);
        
        for (int k = 0; k < n; ++k) {
            //printf("  Trying words[k=%d] = %s\n", k, words[k].c_str());
            if (words[k].size() - behind >= 0 and isPrefix(tail, words[k]) ) {
                int new_index = k;
                int new_behind = words[new_index].size() - behind;
                int new_weight = weight + new_behind;
                //printf("   Option 1: Can reach state <i=%d, d=%d> (%s, %s) with weight = w=%d\n", new_index, new_behind, words[new_index].c_str(), words[new_index].substr(0, words[new_index].size() - new_behind).c_str(), new_weight );                
                if (new_weight < dist[new_index][new_behind]) {
                    dist[new_index][new_behind] = new_weight;
                    q.push( pack(new_index, new_behind, new_weight) );
                    //printf("   That's better.\n");
                }
            }
            
            if (behind - words[k].size() >= 0 and isPrefix(words[k], tail) ) {
                int new_index = index;
                int new_behind = behind - words[k].size();
                int new_weight = weight + 0;
                //printf("   Option 2: Can reach state <i=%d, d=%d> (%s, %s) with weight = w=%d\n", new_index, new_behind, words[new_index].c_str(), words[new_index].substr(0, words[new_index].size() - new_behind).c_str(), new_weight );                
                if (new_weight < dist[new_index][new_behind]) {
                    dist[new_index][new_behind] = new_weight;
                    q.push( pack(new_index, new_behind, new_weight) );
                    //printf("   That's better.\n");
                }
            }
        }
        
    }
    return -1;
}

int main(){
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) cin >> words[i];
        int ans = search();
        cout << ans << endl;
    }
    return 0;
}