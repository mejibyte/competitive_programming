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

int avail[14];

struct hand {
    int c[3];
    hand(){}
    hand(int a, int b, int d) {
        c[0] = a; c[1] = b; c[2] = d;
        sort(c, c + 3);
    }
    
    bool operator == (const hand &t) const {
        return c[0] == t.c[0] and c[1] == t.c[1] and c[2] == t.c[2];
    }
};

inline bool isSet(const hand &a) {
    if (a.c[0] == a.c[1] and a.c[1] == a.c[2]) return true;
    return false;
}

inline bool isPair(const hand &a) {
    if (isSet(a)) return false;
    if (a.c[0] == a.c[1] or a.c[1] == a.c[2] or a.c[0] == a.c[2]) return true;
    return false;
}

int cartaRepetida(const hand &h) {
    int a = h.c[0], b = h.c[1], c = h.c[2];
    if (a == b or a == c) return a;
    if (b == a or b == c) return b;
    if (c == a or c == b) return c;
    assert(false);
}

int cartaNoRepetida(const hand &h) {
    int a = h.c[0], b = h.c[1], c = h.c[2];
    if (a != b and a != c) return a;
    if (b != a and b != c) return b;
    if (c != a and c != b) return c;
    assert(false);
}

bool gana(const hand &a, const hand &b) {
    if (isSet(a) and !isSet(b)) return true;
    if (isSet(b) and !isSet(a)) return false;
    if (isSet(a) and isSet(b)) return a.c[0] > b.c[0];
    
    // ninguna de las 2 es set
    
    if (isPair(a) and !isPair(b)) return true;
    if (isPair(b) and !isPair(a)) return false;
    
    assert(isPair(a)); assert(isPair(b)); 
    
    int left = cartaRepetida(a);
    int right = cartaRepetida(b);
    if (left > right) return true;
    if (left < right) return false;
    
    left = cartaNoRepetida(a);
    right = cartaNoRepetida(b);
    if (left > right) return true;
    if (left < right) return false;
    return false;
}

int main() {

    //D(gana(hand(2, 2, 3), hand(1, 1, 13)));
    //D(gana(hand(1, 1, 13), hand(1, 1, 12)));    
    int a,b,c;
    
    while(scanf("%d %d %d", &a, &b, &c) == 3) {
        if (a == 0 and b == 0 and c == 0) break;
        
        if (a == 13 and b == 13 and c == 13) {
            puts("*");
            continue;
        }
        
        for (int i = 1; i <= 13; ++i) avail[i] = 4;
        
        avail[a]--;
        avail[b]--;
        avail[c]--;
        
        vector< hand > options;  
        
        for (int c1 = 1; c1 <= 13; c1++) {
            for (int c2 = c1; c2 <= 13; c2++) {
                for (int c3 = c2; c3 <= 13; c3++) {
                    avail[c1]--;
                    avail[c2]--;
                    avail[c3]--;
                    
                    //printf("opcion: %d %d %d\n", c1, c2, c3);
                    
                    if (avail[c1] >= 0 and avail[c2] >= 0 and avail[c3] >= 0) {
                        hand h = hand(c1, c2, c3);
                        if (h == hand(a, b, c)) goto end;
                        //D("no igual");
                        if (!isSet(h) and !isPair(h)) goto end;
                        //printf("Meti (%d, %d, %d)\n", c1, c2, c3);
                        options.push_back( h );
                    }
               
                end:     
                    avail[c1]++;
                    avail[c2]++;
                    avail[c3]++;
                }
            }
        }                                                                                                                                                                                                            
        
        options.push_back( hand(a, b, c) );
        sort(options.begin(), options.end(), gana);
        
        hand original = hand(a, b, c);
        
        //For(i, 0, options.size()) {
        //    printf("options[i=%d] = %d %d %d\n", i, options[i].c[0], options[i].c[1], options[i].c[2]);
       //  }
        
        for (int i = 0; i < options.size(); ++i) {
            if (options[i] == original) {
                assert(i > 0);
                printf("%d %d %d\n", options[i-1].c[0], options[i-1].c[1], options[i-1].c[2]); 
                break;
            }
        }
        
    }
   return 0;
}
