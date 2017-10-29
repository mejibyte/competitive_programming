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

//#define For(i,a,b) for (int i=(a); i<(b); ++i)
//#define foreach(x,v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
//#define D(X) cout << #x " = " << (x) << endl
//#define V(a,n) for (int o=0; o<(n);++o) printf(#a "[%d] = %d\n", o, a[o])

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;   
}


int braille[10] = { 14, 1, 5, 3, 11, 9, 7, 15, 13, 6 };


void print(string s) {
    for (int start = 0; start < 6; start += 2) {
        for (int k = 0; k < s.size(); ++k) {
            if (k > 0) printf(" ");
            int num = s[k] - '0';
            
            int b0 = !!(braille[num] & (1 << (start)));
            int b1 = !!(braille[num] & (1 << (start + 1)));
            printf("%c%c", b0 ? '*' : '.', b1 ? '*' : '.');          
            
            if (k + 1 >= s.size()) printf("\n");
        }
    }    
}

int main() {
    int D;
    while (cin >> D) {
        if (D == 0) break;
        
        char type; cin >> type;        
        if (type == 'S') {
            string s; cin >> s;
            print(s);
        } else if (type == 'B') {
            vector<int> v(D);
            for (int start = 0; start < 6; start += 2){
                for (int k = 0; k < D; ++k) {
                    char c0, c1; cin >> c0 >> c1;
                    if (c0 == '*') v[k] |= (1 << (start));
                    if (c1 == '*') v[k] |= (1 << (start + 1));              
                }
            }
            
            for (int k = 0; k < D; ++k) {
                int x = v[k];
                for (int j = 0; j < 10; ++j) {
                    if (braille[j] == x) {
                        printf("%d", j);
                        break;
                    }
                }
            }
            printf("\n");
        }
        
    }
    return 0;   
}
