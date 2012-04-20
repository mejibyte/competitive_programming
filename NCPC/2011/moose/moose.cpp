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

const int MAXN = 200005;

struct Moose {
    int strength;
    int year;
    bool karl;
    
    void print() {
        printf("(s = %d, y = %d, k = %d)\n", strength, year, karl);
    }
    
    // para el set
    bool operator < (const Moose &t) const {
        if (strength != t.strength)
            return strength > t.strength;
        if (year != t.year)
            return year > t.year;
        return karl > t.karl;
    }
} M[MAXN];

// para el sort
struct ByYear {
    bool operator()(const Moose &i, const Moose &j) {
        return i.year < j.year;
    }
};

set<Moose> pool;

int main(){
    int n, k;
    cin >> k >> n;

    cin >> M[0].year >> M[0].strength;
    M[0].karl = true;
    
    n = n + k - 1;
    for (int i = 1; i < n; ++i) {
        cin >> M[i].year >> M[i].strength;
        M[i].karl = false;

    }
    //D(n);
    sort(M, M + n, ByYear());
    
    int lastYear = M[n - 1].year;
    // for (int i = 0; i < n; ++i) M[i].print();
    
    for (int i = 0; i < k; ++i) {
        //assert(M[i].year == 2011);
        pool.insert(M[i]);
    }
    
    bool found = false;
    for (int i = k, y = 2011; i <= n; ++i, y++) {
        //assert(pool.size() > 0);

        if (pool.size() > 0) {
            const Moose winner = *pool.begin();
        
            if (winner.karl) {
                printf("%d\n", y);
                found = true;
                break;
            }
        
            pool.erase(pool.begin());
        
        }
        
        
        
        if (i < n) {
            pool.insert(M[i]);
        }
    }
    if (!found) puts("unknown");
    
    return 0;
}
