using namespace std;
#include <iostream>
#include <algorithm>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

#define BMAX 500
#define CMAX 2500

int mat [BMAX+5][CMAX+5];


void solve(int b, int c) {
    for (int w = 0; w < c; ++w) {

        bool wins = true;
        for (int p = 0; p < c; ++p) {            
            if (p == w) continue;
            
            int score = 0;
            for (int ball = 0; ball < b; ++ball) {
                score += mat[ball][w] < mat[ball][p]; 
            }
            
            if (score > b - score) {
                // sigue ganadando
            } else {
                wins = false;
                break;
            }
        }
        if (wins) {
            printf("%d\n", w);
            return;
        }
    }
    printf("No Condorcet winner\n");
}

int main (){
    int b,c, run = 1;
    while(cin>>b>>c) {
        if (b == 0 and c == 0) break;
        
        int x,y;
        
        for (int i = 0; i < b; ++i) {
            for (int j = 0; j < c; ++j) {
                cin>>x;
                mat[i][x] = j;  
            }   
        }
        
        printf("Case %d: ", run++);
        solve(b, c);
        
           
    }
    
    return 0;
}
