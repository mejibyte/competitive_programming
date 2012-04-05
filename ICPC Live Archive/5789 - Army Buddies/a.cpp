//Equipo Poncho, carriel y ruana
// Sala Tayrona, maquina 140
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x ,v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl
#define V(a,n) for (int o=0; o<(n);++o) printf(#a "[%d] = %d\n", o, a[o])

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int main() {
    int S, B;
    while (scanf("%d %d", &S, &B) == 2) {
        if (S == 0 and B == 0) break;
        set<int> v;
        for (int i = 1; i <= S; ++i) v.insert(i);
        
        while (B--) {
            int l, r; scanf("%d %d", &l, &r);

            set<int>::iterator it;
            it = v.lower_bound(l);
            if (it == v.begin()) printf("*"); else printf("%d", *(--it));
                        
            for (int k = l; k <= r; ++k) v.erase(k);
            
            it = v.upper_bound(r);
            printf(" ");
            if (it == v.end()) printf("*"); else printf("%d", *it);
            printf("\n");
            
        }
        puts("-");
    }
    return 0;
}
