//Equipo Poncho, carriel y ruana
// Sala Tayrona, maquina 140
using namespace std;
#include<algorithm>
#include<iostream>
#include<iterator>
#include<sstream>
#include<fstream>
#include<cassert>
#include<climits>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<deque>
#include<stack>
#include<list>
#include<map>
#include<set>

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x ,v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl
#define V(a,n) for (int o=0; o<(n);++o) printf(#a "[%d] = %d\n", o, a[o])

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int main() {
    
    long long f, input_f;
    vector<int> flavors;
    
    while(cin >> f) {
        input_f = f;
        flavors.clear();
        if (f == 0) break;
        
        long long c;
        while(input_f--) {
            // Aqui meto los flavors
            cin >> c;
            flavors.push_back(c);      
        }

        
        V(flavors, flavors.size());
    }

   return 0;
}
