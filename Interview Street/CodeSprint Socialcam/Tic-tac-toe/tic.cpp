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

struct Board {
    int b[3][3];
    
    bool playerWon(int who) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int di[] = {+1, +1, +0, +1 };
                int dj[] = {+1, +0, +1, -1 };
                for (int k = 0; k < 4; ++k) {
                    int ei = i + di[k] * 2;
                    int ej = j + dj[k] * 2;
                    if (0 <= ei and ei < 3 and 0 <= ej and ej < 3) {
                        // printf("i = %d, j = %d, k = %d, who = %d, di[k] = %d, dj[k] = %d\n", i, j, k, who, di[k], dj[k]);
                        // for (int p = 0; p < 3; ++p) {
                        //     printf("%d ", b[i + di[k] * p][j + dj[k] * p]);
                        // }
                        // puts("");
                        
                        int dii = di[k];
                        int djj = dj[k];
                        

                        
                        if (b[i][j] == who and b[i + dii][j + djj] == who and b[i + dii + dii][j + djj + djj] == who) {
                            return true;
                        }
                    }
                }
                
            }
        }
        return false;
    }
    
    bool somebodyWon() {
        return playerWon(-1) or playerWon(+1);
    }
    
    bool draw() {
        if (somebodyWon()) return false;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (b[i][j] == 0) return false;
        return true;
    }
    
    void print() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                printf("%2d ", b[i][j]);
            }
            puts("");
        }
    }
};

Board board;

// me - minimize the score
// him - maximize the score
int minimax(bool me) {
    
    // printf("currently on this board. Me = %d\n", me);
    // for (int i = 0; i < 3; ++i) {
    //     for (int j = 0; j < 3; ++j) {
    //         printf("%d ", board.b[i][j]);
    //     }
    //     puts("");
    // }
    
    if (board.draw()) return 0;
    if (board.playerWon(+1)) {
        //fuck, I won :(
        return +1;
    }
    if (board.playerWon(-1)) {
        // yeah, baby!
        return -1;
    }
    
    
    if (me) {
        int smallest = INT_MAX;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.b[i][j] != 0) continue;
                
                board.b[i][j] = +1;
                int end = minimax(!me);
                if (end < smallest) smallest = end;
                board.b[i][j] = 0;
            }
        }
        return smallest;
    } else {
        int biggest = INT_MIN;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.b[i][j] != 0) continue;
                
                board.b[i][j] = -1;
                int end = minimax(!me);
                if (end > biggest) biggest = end;
                board.b[i][j] = 0;
            }
        }
        return biggest;
    }
}

void solve() {
    int smallest = INT_MAX;
    int how = -1;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.b[i][j] != 0) continue;
            
//            printf("first turn at (%d, %d)\n", i, j);
            
            board.b[i][j] = +1;
            int end = minimax(false);
            
//            printf("got %d\n\n", end);

            
            if (end < smallest) {
                how = i * 3 + j;
                smallest = end;
            }
            board.b[i][j] = 0;
        }
    }
//    D(smallest);
    cout << how << endl;
}

int main(){
    int n;
    cin >> n;
    while (n--) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cin >> board.b[i][j];
            }
        }
        
        // puts("initial board:");
        // board.print();
        // D(board.playerWon(+1));
        // D(board.playerWon(-1));
        // return 0;
        
        solve();
    }
    return 0;
}